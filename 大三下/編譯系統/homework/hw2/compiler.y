/* Please feel free to modify any content */

/* Definition section */
%{
    #include "compiler_hw_common.h" //Extern variables that communicate with lex
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
    static void insert_symbol();
    static void lookup_symbol();
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
    char func_para[100] = "(";
    char return_type = 'z';
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
%type <s_val> ExpressionStmt LogicalORExpr LogicalANDExpr ComparisonExpr AdditionExpr MultiplicationExpr UnaryExpr Operand

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
    : FUNC ID 
    {
        printf("func: %s\n", $<s_val>2);
        create_symbol();
        $$ = $2;
    }
    '(' ')' 
    {
        insert_symbol("func", $<s_val>2, "()V", 0);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", $<s_val>2, 0);
    }
    FuncBlock
    | FUNC ID
    {
        printf("func: %s\n", $<s_val>2);
        create_symbol();
        $$ = $2;
    } 
    '(' ParameterList ')' ARROW Type 
    {
        strcat(func_para, ")");
        build_func_para($<s_val>5);
        insert_symbol("func", $<s_val>2, func_para, 0);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", $<s_val>2, 0);
        strcpy(func_para, "(");
        return_type = ($<s_val>5[0]);
    }
    FuncBlock
;
ParameterList
    : ParameterList ',' ID ':' Type
    {
        insert_symbol($<s_val>4, $<s_val>2, "-", 1);
        // build_func_para($<s_val>)
    }
    | ID ':' Type
    {
        insert_symbol($<s_val>6, $<s_val>4, "-", 1);
        // build_func_para($<s_val>)
    }
;
FuncBlock
    : '{' NEWLINE StatementList '}' { dump_symbol(); }
    | '{' NEWLINE StatementList RETURN ExpressionStmt NEWLINE'}' { dump_symbol(); }
;
StatementList
    : Statement
    | Statement StatementList // statement越上面先做
;
Statement
    : Block NEWLINE // multi-statement
    | DeclarationStmt NEWLINE
    | ExpressionStmt
    | AssignmentStmt NEWLINE
    | IFStmt NEWLINE
    | PrintStmt NEWLINE
    | WhileStmt NEWLINE
    | ForStmt NEWLINE
    | NEWLINE
;
Block
    : '{' 
    {
        create_symbol();
    }
    NEWLINE StatementList '}'
    {
        dump_symbol();
    }
;
DeclarationStmt
    : LET ID ':' Type '=' ExpressionStmt { insert_symbol($<s_val>4, $<s_val>2, "-", 2 ) }
    | LET MUT ID ':' Type '=' ExpressionStmt { insert_symbol($<s_val>5, $<s_val>3, "-", 2 ) }
    | LET ID ':' DeclareArrayStmt '=' ExpressionStmt { insert_symbol("array", $<s_val>2, "-", 2 ) }
    | LET MUT ID ':' DeclareArrayStmt '=' ExpressionStmt { insert_symbol("array", $<s_val>3, "-", 2 ) }
;
AssignmentStmt
    : ExpressionStmt assign_op ExpressionStmt { printf("%s\n", $<s_val>2); }
;
IFStmt
    : IF ExpressionStmt Block
    | IF ExpressionStmt Block ELSE Block
;
PrintStmt
    : PRINT '(' ExpressionStmt ')' {printf("PRINT %s\n", $<s_val>3);}
    | PRINTLN '(' ExpressionStmt ')'  {printf("PRINTLN %s\n", $<s_val>3);}
;
WhileStmt
    : WHILE ExpressionStmt '{' NEWLINE StatementList '}'
;
ForStmt
    : FOR ID IN ExpressionStmt '{' NEWLINE StatementList '}'
;
DeclareArrayStmt
    : '[' DeclareArrayStmt ']'
    | Type ';' ExpressionStmt
;
ExpressionStmt
    : LogicalORExpr {$$ = $1;}
;
LogicalORExpr
    : LogicalANDExpr LOR LogicalANDExpr
    {
        $$ = "bool";
        printf("LOR\n");
    }
    | LogicalANDExpr { $$ = $1; }
;
LogicalANDExpr
    : ComparisonExpr LAND ComparisonExpr
    {
        $$ = "bool"; 
        printf("LAND\n");
    }
    | ComparisonExpr { $$ = $1; }
;
ComparisonExpr
    : AdditionExpr cmp_op AdditionExpr
    {
        $$ = "bool";
        printf("%s\n", $<s_val>2);
    }
    | AdditionExpr { $$ = $1; }
;
AdditionExpr
    : MultiplicationExpr add_op MultiplicationExpr
    {
        $$ = $1; 
        printf("%s\n", $<s_val>2);
    }
    | AdditionExpr add_op MultiplicationExpr
    {
        $$ = $1; 
        printf("%s\n", $<s_val>2);
    }
    | MultiplicationExpr { $$ = $1; }
;
MultiplicationExpr
    : UnaryExpr mul_op UnaryExpr
    {
        $$ = $1;
        printf("%s\n", $<s_val>2)

    }
    | UnaryExpr { $$ = $1; }
;
UnaryExpr
    : unary_op UnaryExpr { $$ = $2; printf("%s\n", $<s_val>1); }
    | Operand { $$ = $1; }
;
Operand
    : Literal { $$ = $1; }
    | ID { $$ = lookup_symbol($<s_val>1, false) }
    | '(' ExpressionStmt ')' } { $$ = $2; }
;
Literal
    : INT_LIT { $$ = "i32"; printf("INT_LIT %d\n", $<i_val>1);}
    | FLOAT_LIT { $$ = "f32"; printf("FLOAT_LIT %d\n", $<f_val>1);}
    | '"' STRING_LIT '"' { $$ = "str"; printf("STRING_LIT %s\n", $<s_val>1);}
    | TRUE { $$ = "bool"; printf("FALSE 0\n");}
    | FALSE { $$ = "bool"; printf("TRUE 1\n");}
;

assign_op
    : '=' {$$ = "ASSIGN";}
    | ADD_ASSIGN {$$ = "ADD";}
    | SUB_ASSIGN {$$ = "SUB";}
    | MUL_ASSIGN {$$ = "MUL";}
    | QUO_ASSIGN {$$ = "QUO";}
    | REM_ASSIGN {$$ = "REM";}
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
Type 
    : INT		{ $$ = "i32"; }
	| FLOAT		{ $$ = "f32"; }
	| STRING	{ $$ = "str"; }
	| BOOL		{ $$ = "bool"; }
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
    tmp -> prev = cur_table;
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

static void lookup_symbol(char *name, int mark_var) {
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
