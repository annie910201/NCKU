/* Please feel free to modify any content */

/* Definition section */
%{
    #include "compiler_common.h" //Extern variables that communicate with lex
    // #define YYDEBUG 1
    // int yydebug = 1;

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    int yylex_destroy ();
    void yyerror (char const *s)
    {
        printf("error:%d: %s\n", yylineno, s);
    }

    extern int yylineno;
    extern int yylex();
    extern FILE *yyin;

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char*, char*, char*, int);
    static void *lookup_symbol(char*, int);
    static void dump_symbol();

    struct table{
        struct table *prev;
        struct symbol *head;
        int scope;
        int symbol_number;
    }
    struct symbol{
        int index;
        char* name;
        char* mut;
        char* type;
        int addr;
        int lineno;
        char* func_sig;
        struct symbol *next;
    }
    struct table *current_table = NULL;
    /* Global variables */
    bool HAS_ERROR = false;
    int global_scope = -1;
    int addr = 0;
    char return_type = 'z';
    
    // int number_node = 0;

%}

%error-verbose

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 *  - you can add new fields if needed.
 */
%union {
    int i_val;
    float f_val;
    char *s_val;
    /* ... */
}

/* Token without return */
%token LET MUT NEWLINE 
%token INT FLOAT BOOL STR 
%token TRUE FALSE
%token GEQ LEQ EQL NEQ LOR LAND
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN REM_ASSIGN
%token IF ELSE FOR WHILE LOOP
%token PRINT PRINTLN
%token FUNC RETURN BREAK 
%token ID ARROW AS IN DOTDOT RSHIFT LSHIFT

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT

/* Nonterminal with return, which need to sepcify type */
%type <s_val> Type Literal cmp_op add_op mul_op unary_op assign_op 
%type <s_val> Expression LogicalORExpr LogicalANDExpr ComparisonExpr AdditionExpr MultiplicationExpr UnaryExpr PrimaryExpr Operand
%type <s_val> FUNCOpen

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : GlobalStatementList
;

GlobalStatementList 
    : GlobalStatementList GlobalStatement
    | GlobalStatement
;

GlobalStatement
    : FunctionDeclStmt
    | NEWLINE
;

FunctionDeclStmt
    : FUNC ID '(' ')' // ex: fn main() 
    {
        create_symbol();
        printf("func: %s\n", $<s_val>2) /* fn main(), main is the string of 2  */
        insert_symbol("func", $<s_val>2, "()V", 0)
        printf("> Insert `%s` (addr: %d) to scope level %d\n", $<s_val>2, -1, 0);
    }
    FuncBlock // ex: fn foo(lhs: i32)
    | FUNC ID '(' ParameterList ')'
    {
        create_symbol();
        printf("func: %s\n", $<s_val>2) /* fn main(), main is the string of 2  */
        char func_para[100] = "()";

        // make new para
        char tmp = toupper($<s_val>5[0]);// transfer to 大寫
        strcat(func_para, &tmp);// why need to add &?

        insert_symbol("func", $<s_val>2,func_para , 0)
        printf("> Insert `%s` (addr: %d) to scope level %d\n", $<s_val>2, -1, 0);
        return_type = (tmp);
    }
    FuncBlock
;
FuncBlock 
    : '{' NEWLINE StatementList '}' // no return 
    {
        dump_symbol();
    }
    | '{' NEWLINE StatementList RETURN Expression ';' NEWLINE '}' // has return and return a value, ex: return 0;
    {
        if(return_type != 'z'){
            printf("%creturn\n", return_type);
                return_type = 'z';
        }
        dump_symbol();
    }
;
StatementList
    : Statement StatementList 
    | Statement 
;
Statement
    : DeclarationStmt NEWLINE
    | SimpleStmt NEWLINE
    | Block NEWLINE
    | PrintStmt NEWLINE
    | IFStmt NEWLINE
    | WHILEStmt NEWLINE
    | FORStmt NEWLINE
    | NEWLINE
DeclarationStmt
    : LET IDType ':' TYPE '=' Expression
    {
        insert_symbol($<s_val>4, ID,"-", 2);
    }
IDType
    : ID
    | MUT ID
Type   
    : INT		{ $$ = "i32"; }
	| FLOAT		{ $$ = "f32"; }
	| STR	    { $$ = "str"; }
	| BOOL		{ $$ = "bool"; }
;
Expression
    : LogicalORExpr
;
LogicalORExpr
    : LogicalANDExpr LOR LogicalANDExpr
    {
        if((strcmp($<s_val>1, "i32") == 0) || (strcmp($<s_val>3, "i32") == 0))
            printf("error:%d: invalid operation: (operator LOR not defined on int32)\n", yylineno);
        printf("LOR\n");
        $$ = "bool"
    }
    | LogicalANDExpr {$$ = $1;}
;
LogicalANDExpr
    : ComparisonExpr LAND ComparisonExpr
    {
        if((strcmp($<s_val>1, "i32") == 0)||(strcmp($<s_val>3, "i32") == 0)){
            printf("error:%d: invalid operation: (operator LAND not defined on int32)\n", yylineno);
        }
        $$ = "bool"; 
        printf("LAND\n");
    }
    | ComparisonExpr {$$ = $1;}
;
ComparisonExpr
    : AdditionExpr cmp_op AdditionExpr
    {
        if(strcmp($<s_val>1, $<s_val>3) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno, $<s_val>2, $<s_val>1, $<s_val>3);
        }
        $$ = "bool";
        printf("%s\n", $<s_val>2);
    }
    | AdditionExpr {$$ = $1;}
;

AdditionExpr
    : MultiplicationExpr add_op MultiplicationExpr
    {
        if(strcmp($<s_val>1, $<s_val>3) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno, $<s_val>2, $<s_val>1, $<s_val>3);
        }
        $$ = $1;
        printf("%s\n", $<s_val>2);
    }
    | AdditionExpr add_op MultiplicationExpr
    {$$ = $1;
    printf("%s\n", $<s_val>2);
    }
    | MultiplicationExpr {$$ = $1;}
;

MultiplicationExpr
    : UnaryExpr mul_op UnaryExpr
    {
        if((strcmp($<s_val>2, "REM") == 0)&&(strcmp($<s_val>3, "f32") == 0)){
            printf("error:%d: invalid operation: (operator REM not defined on f32)\n", yylineno);
        }
        $$ = $1;
        printf("%s\n", $<s_val>2);
    }
    | UnaryExpr {$$ = $1;}
;

UnaryExpr
    : unary_op UnaryExpr 
    { 
        $$ = $2; 
        printf("%s\n", $<s_val>1);
    }
    | PrimaryExpr { $$ = $1; }
;
PrimaryExpr 
    : Operand { $$ = $1; }
    | ConversionExpr
;
Operand 
    : Literal { $$ = $1; }
    | ID { $$ = lookup_symbol($<s_val>1, false); } 
    | ID '(' ')' { lookup_symbol($<s_val>1, true);} 
    | ID '(' FuncPara ')' { lookup_symbol($<s_val>1, true);} 
    | '(' Expression ')' { $$ = $2; }
;
Literal
    : INT_LIT
        {$$ = "i32"; 
        printf("INT_LIT %d\n", $<i_val>1); 
        }
    | FLOAT_LIT
        {$$ = "f32"; 
        printf("FLOAT_LIT %f\n", $<f_val>1); 
        }
    | TRUE 
        {$$ = "bool"; 
        printf("TRUE\n");
        }
    | FALSE 
        {$$ = "bool"; 
        printf("FALSE\n");
        }
    | '"' STR '"'
        {$$ = "string"; 
        printf("STRING_LIT %s\n", $<s_val>2); 
        }
;
ConversionExpr 
    : Type '(' Expression ')' 
    {
        printf("%c2%c\n", $<s_val>3[0], $<s_val>1[0]);
    }
;
cmp_op 
    : EQL { $$ = "EQL"; }
    | NEQ { $$ = "NEQ"; }
    | '<' { $$ = "LES"; }
    | LEQ { $$ = "LEQ"; }
    | '>' { $$ = "GTR"; }
    | GEQ { $$ = "GEQ"; }
;

add_op 
    : '+' { $$ = "ADD"; }
    | '-' { $$ = "SUB"; }
;

mul_op 
    : '*' { $$ = "MUL"; }
    | '/' { $$ = "QUO"; }
    | '%' { $$ = "REM"; }
;

unary_op 
    : '+' { $$ = "POS"; }
    | '-' { $$ = "NEG"; }
    | '!' { $$ = "NOT"; }
;
%%

/* C code section */
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }

    yylineno = 0;
    yyparse();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void create_symbol() {
    global_scope ++;
    struct table *tmp = malloc(sizeof(struct symbol));
    tmp -> prev = current_table;
    tmp -> scope = global_scope;
    tmp -> symbol_number = 0;
    tmp -> head = NULL;
    current_table = tmp;
    printf("> Create symbol table (scope level %d)\n", global_scope);
}

static void insert_symbol(char* type, char* name, char* func_sig, int mark_var) {// if mark_var = 0, function; else if mark_var = 1, parameter, else is 2
    struct symbol *tail = NULL;
    struct table *first = current_table;
    bool empty = false;
    if(mark_var == 0){ // function
        while(first-> prev != NULL) // is not the head of table
            first = first -> prev;
        /* after find the head of table */
        if(first -> head != NULL){ // not empty -> add to tail
            tail = first -> head;
            while(tail -> next != NULL)
                tail = tail->next;
        }
        else // empty
            empty = true;
    }
    else{
        if(first -> head != NULL){
            tail = current_table -> head;
            while(tail -> next !=NULL){
                tail = tail->next;
            }
        }
        else
            empty = true;
    }
    /* to this point, first and tail is moved to the right position */
        /* function: first -> head of table, tail -> the tail of first */
        /* parameter: first -> current of table, tail -> the tail of first */
    struct symbol *new = malloc(sizeof(struct symbol));
    // next
    new -> next = NULL;
    // name
    new -> name = strdup(name);// 和strcpy不太一樣，可以直接把要複製的內容給未經過初始化或分配空間的指標，相當於strlen + 分配空間 + strcpy  
    // mut
    // type
    new -> type = strdup(type);
    // addr and lineno 
    if(mark_var == 0){// function
        new -> lineno = yylineno + 1;
        new -> addr = -1;
    }
    else if(mark_var == 1){// parameter
        new -> lineno = yylineno + 1;
        new -> addr = addr;
        addr ++;
    }
    else {
        new -> lineno = yylineno ;
        new -> addr = addr;
        addr ++;
    }
    // func_sig
    new -> func_sig = strdup(func_sig);
    // index
    if(!empty){
        new -> index = (tail -> index) + 1;
        tail -> next = new;
    }
    else{
        new -> index = 0;
        first -> head = new;
    }
    // print
    if(mark_var !=0)// not function
        printf("> Insert `%s` (addr: %d) to scope level %d\n", name, new -> addr, global_scope);
}

static char *lookup_symbol(char *name, int mark_var) {
    struct table *t = current_table;
    struct symbol *s = NULL;
    while(t!=NULL){
        s = t -> head;
        while(s!= NULL){
            if(strcmp(s-> name, name) == 0){
                if(mark_var == 0){// function
                    printf("call: %s%s\n", s -> name, s -> func_sig);
                    return s_pointer -> func_sig;
                }
                else{// not function
                    printf("IDENT (name=%s, address=%d)\n", s->name, s->addr);
                    return s-> type;
                }
            }
            else// name is not same
                s = s->next;
        }
        t = t-> prev;
    }
    /* if it's not return until this step, it is represent the symbol is an error */
    printf("error:%d: undefined: %s\n", yylineno+1, name);
    return "ERROR";
}

static void dump_symbol() {
    printf("\n> Dump symbol table (scope level: %d)\n", current_table -> scope);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
    
    struct symbol *tmp = current_table-> head;
    while(tmp!= NULL){
        printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            tmp-> index, tmp-> name, tmp-> mut, tmp-> type, tmp-> addr, tmp-> lineno, tmp-> func_sig);
        tmp = tmp->next;
    }
    printf("\n");
    current_table = current_table-> prev;
    global_scope--;
}

static void build_func_para(char *para) {
    char tmp = toupper(para[0]);
    strcat(func_para, &tmp);
}