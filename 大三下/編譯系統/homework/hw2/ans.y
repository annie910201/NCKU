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
    struct table{
        struct table *prev;
        struct symbol *head;
        int scope;
        int size;
    };
    struct symbol{
        int index;
        char *name;
        char *type;
        int addr;
        int lineno;
        char *func_sig;
        struct symbol *next;
    };
    static void create_symbol();
    static void insert_symbol(bool, bool, char*, char*, char*);
    static char *lookup_symbol(char *, bool);
    static void dump_symbol();
    static void build_func_para(char *);

    /* Global variables */
    bool HAS_ERROR = false;
    int scope = -1, addr = 0;
    struct table *cur_table = NULL;
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
%token VAR NEWLINE
%token INT FLOAT BOOL STRING
%token TRUE FALSE
%token INC DEC 
%token GEQ LEQ EQL NEQ 
%token LOR LAND
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN QUO_ASSIGN REM_ASSIGN
%token IF ELSE FOR SWITCH CASE DEFAULT
%token PRINT PRINTLN
%token PACKAGE FUNC RETURN

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT
%token <f_val> FLOAT_LIT
%token <s_val> STRING_LIT IDENT 


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
    : PackageStmt NEWLINE
    | FunctionDeclStmt
    | NEWLINE
;

FunctionDeclStmt
    : FUNCOpen '(' ')'  
        {       
            printf("func_signature: ()V\n");
            insert_symbol(true, false, $<s_val>2, "func", "()V");
            printf("> Insert `%s` (addr: -1) to scope level %d\n", $<s_val>2, 0);
        } 
        FuncBlock
    | FUNCOpen '(' ParameterList ')'  Type 
        {   
            strcat(func_para, ")");
            printf("func_signature: %s%c\n", func_para, toupper($<s_val>5[0]));
            build_func_para($<s_val>5);
            insert_symbol(true, false, $<s_val>2, "func", func_para);
            printf("> Insert `%s` (addr: -1) to scope level %d\n", $<s_val>2, 0);
            strcpy(func_para, "(");
            return_type = ($<s_val>5[0]);
        }
        FuncBlock
;

FUNCOpen
    : FUNC IDENT 
    { printf("func: %s\n", $<s_val>2);
    create_symbol();
    $$ = $2; 
    }
;

ParameterList
    : ParameterList ',' IDENT Type
    {
        printf("param %s, type: %c\n", $<s_val>3, toupper($<s_val>4[0]));
        insert_symbol(false, true, $<s_val>3, $<s_val>4, "-");
        build_func_para($<s_val>4);
    }
    | IDENT Type
    {
        printf("param %s, type: %c\n", $<s_val>1, toupper($<s_val>2[0]));
        insert_symbol(false, true, $<s_val>1, $<s_val>2, "-");
        build_func_para($<s_val>2);
    }
;

FuncBlock
    : '{' NEWLINE StatementList '}' {dump_symbol();}
    | '{' NEWLINE StatementList RETURNExpr NEWLINE '}' 
        {
            if (return_type == 'z') {
                printf("return\n");
            } 
            else {
                printf("%creturn\n", return_type);
                return_type = 'z';
            }
            dump_symbol();
        }
;

RETURNExpr
    : RETURN Expression
    | RETURN
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
    | FORStmt NEWLINE
    | SwitchStmt NEWLINE
    | CaseStmt NEWLINE
    | NEWLINE
;

SimpleStmt
    : AssignmentStmt
    | ExpressionStmt
    | IncDecStmt
;

AssignmentStmt
    : Expression assign_op Expression 
    {
        if(strcmp($<s_val>1, $<s_val>3) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno, $<s_val>2, $<s_val>1, $<s_val>3);
        }
        printf("%s\n", $<s_val>2);
    }
;

assign_op
    : '=' {$$ = "ASSIGN";}
    | ADD_ASSIGN {$$ = "ADD";}
    | SUB_ASSIGN {$$ = "SUB";}
    | MUL_ASSIGN {$$ = "MUL";}
    | QUO_ASSIGN {$$ = "QUO";}
    | REM_ASSIGN {$$ = "REM";}
;

ExpressionStmt
    : Expression
;

IncDecStmt
    : Expression INC    {printf("INC\n");}
    | Expression DEC    {printf("DEC\n");}
;

PackageStmt
    : PACKAGE IDENT
        {printf("package: %s\n", $<s_val>2);}
;

DeclarationStmt
    : VAR IDENT Type '=' Expression
        {insert_symbol(false, false, $<s_val>2, $<s_val>3, "-");}
    | VAR IDENT Type
        {insert_symbol(false, false, $<s_val>2, $<s_val>3, "-");}
;

Block  
    : '{'  NEWLINE  {create_symbol();} StatementList '}'   {dump_symbol();}
;

PrintStmt
    : PRINT '(' Expression ')'
        {printf("PRINT %s\n", $<s_val>3); }
    | PRINTLN '(' Expression ')'
        {printf("PRINTLN %s\n", $<s_val>3); }
;

IFStmt
    : IF Condition Block
    | IF Condition Block ELSE Block
    | IF Condition Block ELSE IFStmt
;

Condition
    : Expression 
    {
        if(strcmp($<s_val>1, "bool") != 0){
            printf("error:%d: non-bool (type %s) used as for condition\n", yylineno + 1, $<s_val>1);
        }
    }
;

FORStmt
    : FOR Condition Block
    | FOR ForClause Block
;

ForClause
    : InitStmt ';' Condition ';' PostStmt
;

InitStmt : SimpleStmt
PostStmt : SimpleStmt

SwitchStmt
    : SWITCH Expression Block
;

CaseStmt
    : CASE INT_LIT 
        {printf("case %d\n", $<i_val>2);} 
        ':' Block
    | DEFAULT ':' Block
;

Expression
    : LogicalORExpr {$$ = $1;}
;

FuncPara
    : Expression ',' FuncPara
    | Expression
;

LogicalORExpr
    : LogicalANDExpr LOR LogicalANDExpr
    {
        if((strcmp($<s_val>1, "int32") == 0)||(strcmp($<s_val>3, "int32") == 0)){
            printf("error:%d: invalid operation: (operator LOR not defined on int32)\n", yylineno);
        }
        $$ = "bool";
    printf("LOR\n");
    }
    | LogicalANDExpr {$$ = $1;}
;

LogicalANDExpr
    : ComparisonExpr LAND ComparisonExpr
    {
        if((strcmp($<s_val>1, "int32") == 0)||(strcmp($<s_val>3, "int32") == 0)){
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
        if((strcmp($<s_val>2, "REM") == 0)&&(strcmp($<s_val>3, "float32") == 0)){
            printf("error:%d: invalid operation: (operator REM not defined on float32)\n", yylineno);
        }
        $$ = $1;
        printf("%s\n", $<s_val>2);
    }
    | UnaryExpr {$$ = $1;}
;

UnaryExpr
    : unary_op UnaryExpr { $$ = $2; printf("%s\n", $<s_val>1);}
    | PrimaryExpr { $$ = $1; }
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
	: INT		{ $$ = "int32"; }
	| FLOAT		{ $$ = "float32"; }
	| STRING	{ $$ = "string"; }
	| BOOL		{ $$ = "bool"; }
;

PrimaryExpr 
    : Operand { $$ = $1; }
    | ConversionExpr
;

Operand 
    : Literal { $$ = $1; }
    | IDENT { $$ = lookup_symbol($<s_val>1, false); } 
    | IDENT '(' ')' { lookup_symbol($<s_val>1, true);} 
    | IDENT '(' FuncPara ')' { lookup_symbol($<s_val>1, true);} 
    | '(' Expression ')' { $$ = $2; }
;

ConversionExpr 
    : Type '(' Expression ')' {printf("%c2%c\n", $<s_val>3[0], $<s_val>1[0]);}
;

Literal
    : INT_LIT
        {$$ = "int32"; 
        printf("INT_LIT %d\n", $<i_val>1); 
        }
    | FLOAT_LIT
        {$$ = "float32"; 
        printf("FLOAT_LIT %f\n", $<f_val>1); 
        }
    | TRUE 
        {$$ = "bool"; 
        printf("TRUE 1\n");
        }
    | FALSE 
        {$$ = "bool"; 
        printf("FALSE 0\n");
        }
    | '"' STRING_LIT '"'
        {$$ = "string"; 
        printf("STRING_LIT %s\n", $<s_val>2); 
        }
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
    create_symbol();
    yyparse();
    dump_symbol();

	printf("Total lines: %d\n", yylineno);
    fclose(yyin);
    return 0;
}

static void create_symbol() {
    scope++;
    struct table *new = malloc(sizeof(struct table));
    new -> prev = cur_table;
    new -> head = NULL;
    new -> scope = scope;
    new -> size = 0;
    cur_table = new;
    printf("> Create symbol table (scope level %d)\n", scope);
}

static void insert_symbol(bool is_function, bool is_param, char *name, char *type, char *func_sig) {
    struct symbol *new = malloc(sizeof(struct symbol));
    struct symbol *old = NULL;
    struct table *temp = cur_table;
    bool is_empty = false;

    if(is_function == true){
        while(temp -> prev != NULL){
            temp = temp -> prev;
        }
        if(temp -> head != NULL){
            old = temp -> head;
            while(old -> next != NULL){
                old = old -> next;
            }
        } 
        else{
            is_empty = true;
        }
    }
    else{
        if(cur_table -> head != NULL){
            old = cur_table -> head;
            if(strcmp(old -> name, name) == 0){
                printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, name, old -> lineno);
            }
            while(old -> next != NULL){
                old = old -> next;
                if(strcmp(old -> name, name) == 0){
                    printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, name, old -> lineno);
                }
            }
        } 
        else{
            is_empty = true;
        }
    }

    new -> name = strdup(name);
    new -> type = strdup(type);
    new -> func_sig = strdup(func_sig);
    new -> next = NULL;
    if(is_function == true){
        new -> lineno = yylineno + 1;
        new -> addr = -1;
    }
    else if(is_param == true){
        new -> lineno = yylineno + 1;
        new -> addr = addr;
        addr++;
    }
    else{
        new -> lineno = yylineno;
        new -> addr = addr;
        addr++;
    }
    if(is_empty == false){
        new -> index = (old -> index) + 1;
        old -> next = new;
    }
    else{
        new -> index = 0;
        if(is_function){
            temp -> head = new;   
        }
        else{
            cur_table -> head = new;
        }
         
    }

    
    if(is_function == false){
        printf("> Insert `%s` (addr: %d) to scope level %d\n", name, new -> addr, scope);
    }
    
}

static char *lookup_symbol(char *name, bool is_function) {
    struct table *t_pointer = cur_table;
    struct symbol *s_pointer = NULL;
    while(t_pointer != NULL){
        s_pointer = t_pointer -> head;
        while(s_pointer != NULL){
            if(strcmp(s_pointer -> name, name) == 0){
                if(is_function == false){
                    printf("IDENT (name=%s, address=%d)\n", s_pointer->name, s_pointer->addr);
                    return s_pointer -> type;
                }
                else{
                    printf("call: %s%s\n", s_pointer -> name, s_pointer -> func_sig);
                    return s_pointer -> func_sig;
                }
            }
            else{
                s_pointer = s_pointer -> next;
            }
        }
        t_pointer = t_pointer -> prev;
    }
    printf("error:%d: undefined: %s\n", yylineno+1, name);
    return "ERROR";
}

static void dump_symbol() {
    printf("\n> Dump symbol table (scope level: %d)\n", cur_table -> scope);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s\n",
           "Index", "Name", "Type", "Addr", "Lineno", "Func_sig");

    struct symbol *cur = cur_table -> head;
    while(cur != NULL){
        printf("%-10d%-10s%-10s%-10d%-10d%-10s\n",
            cur -> index, cur -> name, cur -> type, cur -> addr, cur -> lineno, cur -> func_sig);
        cur = cur -> next;
    }
    printf("\n");
    cur_table = cur_table -> prev;
    scope--;
}

static void build_func_para(char *para) {
    char temp = para[0];
    temp = toupper(temp);
    strcat(func_para, &temp);
}