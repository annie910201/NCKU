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
    static void insert_symbol(char*, char*, char*, int, bool);
    static char *lookup_symbol(char*, int);
    static void dump_symbol();
    static void build_func_para(char *);

    struct table{
        struct table *prev;
        struct symbol *head;
        int scope;
        int symbol_number;
    };
    struct symbol{
        int index;
        char* name;
        int mut;
        char* type;
        int addr;
        int lineno;
        char* func_sig;
        struct symbol *next;
    };
    struct table *current_table = NULL;

    /* Global variables */
    bool HAS_ERROR = false;
    int global_scope = -1;
    int addr = 0;
    bool casting = false;
    char func_para[100] = "(";
    bool has_return = false;
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
%type <s_val> Type Literal cmp_op add_op mul_op unary_op assign_op shift_op 
%type <s_val> FuncOpen ExpressionStmt LogicalORExpr LogicalANDExpr ComparisonExpr AdditionExpr MultiplicationExpr UnaryExpr Operand ArrayExpr

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
    : FuncOpen
    '(' 
    {
        insert_symbol("func", $<s_val>2, func_para, 0, false);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", $<s_val>2, 0);
        create_symbol();
        has_return = true;
        // strcat(func_para, ")");
        // build_func_para($<s_val>6);
        // strcpy(func_para, "(");
        // return_type = ($<s_val>5[0]);
    }
    ParameterList ')' ARROW Type FuncBlock
    | FuncOpen
    '(' ')' 
    {   
        insert_symbol("func", $<s_val>2, "(V)V", 0, false);
        printf("> Insert `%s` (addr: -1) to scope level %d\n", $<s_val>2, 0);
        create_symbol();
    }
    FuncBlock
    
;
FuncOpen
    : FUNC ID 
    {
        printf("func: %s\n", $<s_val>2);
        $$ = $<s_val>2;
    }
;

ParameterList
    :  ParameterList  ',' ID ':' Type
    {
        insert_symbol($<s_val>5, $<s_val>3, "-", 1, false);
        printf("> Insert `%s` (addr: %d) to scope level %d\n", $<s_val>3, addr-1, global_scope);
        // build_func_para($<s_val>)
    }
    | ID ':' Type
    {
        insert_symbol($<s_val>3, $<s_val>1, "-", 1, false);
        printf("> Insert `%s` (addr: %d) to scope level %d\n", $<s_val>1, addr-1, global_scope);
        // build_func_para($<s_val>)
    }
;
FuncBlock
    : '{' NEWLINE StatementList '}' 
    { 
        if(has_return){
            printf("breturn\n");
            has_return = false;
        }
        dump_symbol(); 
    }
;
StatementList
    : Statement
    | Statement StatementList // statement越上面先做
;
Statement
    : Block NEWLINE // multi-statement
    | DeclarationStmt ';' NEWLINE
    | ExpressionStmt
    | AssignmentStmt ';' NEWLINE
    | IFStmt 
    | PrintStmt ';' NEWLINE
    | WhileStmt NEWLINE
    | ForStmt NEWLINE
    | CallFunction NEWLINE;
    | NEWLINE
;
CallFunction
    : ID '(' ')' ';' 
    { 
        addr = 0;
        // has_return = true;
        lookup_symbol($<s_val>1, 0); // function
    }
Block
    : StartBlock RETURN Literal ';' NEWLINE '}'
    {
        printf("breturn\n");
        dump_symbol();
        
    }
    | StartBlock StatementList '}' { dump_symbol(); }
    /* | StartBlock StatementList NEWLINE'}' { dump_symbol(); } */
    | StartBlock BREAK Literal ';' NEWLINE '}' { dump_symbol();}
    
;
StartBlock
    : '{' { create_symbol(); } NEWLINE
;
DeclarationStmt
    : LET ID ':' Type { insert_symbol($<s_val>4, $<s_val>2, "-", 2, false ); }
    | LET MUT ID ':' Type { insert_symbol($<s_val>5, $<s_val>3, "-", 2, true ); }
    | LET ID ':' Type '=' StatementList { insert_symbol($<s_val>4, $<s_val>2, "-", 2, false ); }
    | LET MUT ID ':' Type '=' ExpressionStmt { insert_symbol($<s_val>5, $<s_val>3, "-", 2, true ); }
    | LET ID ':' DeclareArrayStmt '=' ExpressionStmt { insert_symbol("array", $<s_val>2, "-", 2, false ); }
    // | LET MUT ID ':' DeclareArrayStmt '=' ExpressionStmt { insert_symbol("array", $<s_val>3, "-", 2, true ); }
    | LET MUT ID '=' ExpressionStmt { insert_symbol("i32", $<s_val>3, "-", 2, true ); }
    | LET ID '=' Literal { insert_symbol($<s_val>4, $<s_val>2, "-", 2, false); }
    | LET ID ':' Type '=' LoopStmt { insert_symbol($<s_val>4, $<s_val>2, "-", 2, false); }
;
AssignmentStmt
    : ID assign_op ExpressionStmt 
    { 
        if(strcmp(lookup_symbol($<s_val>1, 3), "undefined")!=0)
            printf("%s\n", $<s_val>2); 
    }
;
IFStmt
    : IFOpen NEWLINE
    // | IF ExpressionStmt Block RETURN ExpressionStmt ';' NEWLINE '}'
    | IFOpen NEWLINE ELSE Block
    | IFOpen ELSE Block
    
;
IFOpen
    : IF ExpressionStmt Block 
;
PrintStmt
    : PRINT '(' NEWLINE ExpressionStmt NEWLINE')' {printf("PRINT %s\n", $<s_val>4);}
    | PRINT '('  ExpressionStmt ')' {printf("PRINT %s\n", $<s_val>3);}
    | PRINTLN '(' ExpressionStmt ')'  {printf("PRINTLN %s\n", $<s_val>3);}
;

WhileStmt
    : WHILE ExpressionStmt Block
;
ForStmt
    : FOR ID IN ID 
    {
        lookup_symbol($<s_val>4, 2);
    }
    StartBlock
    {
        insert_symbol("i32", $<s_val>2, "-", 3, false);
    } 
    StatementList  '}'
    {
        dump_symbol();
    }
;
LoopStmt
    : LOOP Block
;
DeclareArrayStmt
    : '[' DeclareArrayStmt ']' // multi-dimension
    | Type ';' Literal 
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
        // lookup_symbol($<s_val>1, 2);
        if(strcmp($<s_val>1, $<s_val>3) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno+1, $<s_val>2, $<s_val>1, $<s_val>3);
        }
        $$ = "bool";
        printf("%s\n", $<s_val>2);
    }
    | AdditionExpr { $$ = $1; }
;
AdditionExpr
    : MultiplicationExpr add_op MultiplicationExpr
    {
        
        printf("%s\n", $<s_val>2);
        $$ = $1; 
    }
    | AdditionExpr add_op MultiplicationExpr
    {
        printf("%s\n", $<s_val>2);
        $$ = $1; 
        
    }
    | MultiplicationExpr { $$ = $1; }
;

MultiplicationExpr
    : UnaryExpr mul_op UnaryExpr
    {
        $$ = $1;
        printf("%s\n", $<s_val>2);

    }
    | UnaryExpr shift_op UnaryExpr
    {
        if(strcmp($<s_val>1, $<s_val>3) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno+1, $<s_val>2, $<s_val>1, $<s_val>3);
        }
        $$ = $1;
        printf("%s\n", $<s_val>2);
        
    }
    | UnaryExpr { $$ = $1; }
;
UnaryExpr
    : unary_op UnaryExpr { $$ = $2; printf("%s\n", $<s_val>1); }
    | ArrayExpr {$$ = $1;}
    | Operand { $$ = $1; }
;
ArrayExpr
    : Literal ',' ArrayExpr
    | '[' Literal ',' ArrayExpr
    | Literal ']'
    | '&' ID 
    {
        lookup_symbol($<s_val>2, 2);
    }
    '[' DotExpr ']'
;
DotExpr
    : DOTDOT 
    {
        printf("DOTDOT\n");
    }
    Literal 
    | DOtOpen
    {
        printf("DOTDOT\n");
    }
    | DOtOpen 
    {
        printf("DOTDOT\n");
    }
    Literal
;
DOtOpen
    : Literal DOTDOT
Operand
    : Literal { $$ = $1; }
    | Literal AS { casting = true; } Type // change_type
    | ID { $$ = lookup_symbol($<s_val>1, 2) ;}
    | '(' ExpressionStmt ')' { $$ = $2; } // call function
    | ID '[' INT_LIT ']' { $$ = lookup_symbol($<s_val>1, 2); printf("INT_LIT %d\n", $<i_val>3);} // array
    | ID AS // change_type
    {
        casting = true;
        lookup_symbol($<s_val>1, 1) ;
    }
    Type 
    | ID '(' ID ',' ID ')'
    {
        lookup_symbol($<s_val>3, 1); // parameter
        lookup_symbol($<s_val>5, 1); // parameter
        has_return = true;
        lookup_symbol($<s_val>1, 0); // function name
    }
;
Literal
    : INT_LIT { $$ = "i32"; printf("INT_LIT %d\n", $<i_val>1);}
    | FLOAT_LIT { $$ = "f32"; printf("FLOAT_LIT %f\n", $<f_val>1);}
    | '"' STRING_LIT '"' { $$ = "str"; printf("STRING_LIT \"%s\"\n", $<s_val>2);}
    | '"''"' { $$ = "str"; printf("STRING_LIT \"\"\n");}
    | TRUE { $$ = "bool"; printf("bool TRUE\n");}
    | FALSE { $$ = "bool"; printf("bool FALSE\n");}
;

assign_op
    : '=' {$$ = "ASSIGN";}
    | ADD_ASSIGN {$$ = "ADD_ASSIGN";}
    | SUB_ASSIGN {$$ = "SUB_ASSIGN";}
    | MUL_ASSIGN {$$ = "MUL_ASSIGN";}
    | DIV_ASSIGN {$$ = "DIV_ASSIGN";}
    | REM_ASSIGN {$$ = "REM_ASSIGN";}
;

cmp_op 
    : EQL { $$ = "EQL"; }
    | NEQ { $$ = "NEQ"; }
    | '<' { $$ = "LSS"; }
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
    | '/' { $$ = "DIV"; }
    | '%' { $$ = "REM"; }
;

shift_op
    : LSHIFT { $$ = "LSHIFT"; }
    | RSHIFT { $$ = "RSHIFT"; }
;

unary_op 
    : '+' { $$ = "POS"; }
    | '-' { $$ = "NEG"; }
    | '!' { $$ = "NOT"; }
;
Type 
    : INT		
    { 
        $$ = "i32";
        if(casting){
            casting = false;
            printf("f2i\n");
        } 
    }
	| FLOAT		
    { 
        $$ = "f32";
        if(casting){
            casting = false;
            printf("i2f\n");
        } 
    }
	| '&'STR	    { $$ = "str"; }
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
    create_symbol();
    yylineno = 0;
    yyparse();
    dump_symbol();

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

static void insert_symbol(char* type, char* name, char* func_sig, int mark_var, bool has_mut) {// if mark_var = 0, function; else if mark_var = 1, parameter, else if mark_var == 2, id, else(foreach), mark_var == 3
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
    if(mark_var == 0)
        new -> mut = -1;
    else if(has_mut)
        new -> mut = 1;
    else 
        new -> mut = 0;
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
    else if(mark_var == 2) { // id
        new -> lineno = yylineno + 1 ;
        new -> addr = addr;
        addr ++;
    }
    else{ // foreach
        new -> lineno = yylineno;
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
    if(mark_var ==2 || mark_var == 3)// id
        printf("> Insert `%s` (addr: %d) to scope level %d\n", name, new -> addr, global_scope);
}

static char *lookup_symbol(char *name, int mark_var) { // if mark_var = 0, function; else if mark_var = 1, parameter, else(id) is 2
    struct table *t = current_table;
    struct symbol *s = NULL;
    while(t!=NULL){
        s = t -> head;
        while(s!= NULL){
            if(strcmp(s-> name, name) == 0){
                if(mark_var == 0)// function
                {
                    if(has_return){
                        printf("call: %s(II)B\n", s -> name);
                        has_return = false;
                        s -> func_sig = "(II)B";
                        return "(II)B" ;
                    }
                    else{
                        printf("call: %s%s\n", s -> name, s -> func_sig);
                        return s -> func_sig;
                    }
                }
                    
                else if(mark_var != 3){// not function
                    printf("IDENT (name=%s, address=%d)\n", s->name, s->addr);
                    return s-> type;
                }
                else
                    return s-> type;
            }
            else// name is not same
                s = s->next;
        }
        t = t-> prev;
    }
    /* if it's not return until this step, it is represent the symbol is an error */
    printf("error:%d: undefined: %s\n", yylineno+1, name);
    return "undefined";
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
    current_table = current_table-> prev;
    global_scope--;
}

static void build_func_para(char *para) {
    char tmp = toupper(para[0]);
    strcat(func_para, &tmp);
}
