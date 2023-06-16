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

    /* Used to generate code */
    /* As printf; the usage: CODEGEN("%d - %s\n", 100, "Hello world"); */
    /* We do not enforce the use of this macro */
    #define CODEGEN(...) \
        do { \
            for (int i = 0; i < g_indent_cnt; i++) { \
                fprintf(fout, "\t"); \
            } \
            fprintf(fout, __VA_ARGS__); \
        } while (0)

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
    struct switch_label{
        int index;
        int is_last;
        struct switch_label *next;
    };
    static void create_symbol();
    static void insert_symbol(bool, bool, char*, char*, char*);
    static char *lookup_symbol(char *, bool);
    static int lookup_symbol_addr(char *, bool);
    static char *lookup_symbol_type(char *, bool);
    static void dump_symbol();
    static void build_func_para(char *);

    /* Global variables */
    bool HAS_ERROR = false;
    int scope = -1, addr = 0, cmp_con = 0;
    struct table *cur_table = NULL;
    char func_para[100] = "(";
    char return_type = 'z';
    char id_storage[10], id_temp[10];
    int switch_num = 0;
    int is_main = 0;
    bool g_has_error = false;
    FILE *fout = NULL;
    int g_indent_cnt = 0;
    struct switch_label *switch_label_head;
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
            // strcat(func_para, ")");
            if(is_main == 0){
                CODEGEN("()V\n");
                CODEGEN(".limit stack 20\n");
                CODEGEN(".limit locals 20\n");
            }
            else{
                is_main = 0;
            }
        } 
        FuncBlock
    | FUNCOpen '(' ParameterList ')'  Type 
        {   
            strcat(func_para, ")");
            if(is_main == 0){
                CODEGEN("%s%c\n", func_para, toupper($<s_val>5[0]));
                CODEGEN(".limit stack 20\n");
                CODEGEN(".limit locals 20\n");
            }
            else{
                is_main = 0;
            }

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

    if(strcmp( $<s_val>2, "main")==0){
        CODEGEN(".method public static main([Ljava/lang/String;)V\n");
        CODEGEN(".limit stack 100\n");
        CODEGEN(".limit locals 100\n");
        is_main = 1;
    }
    else{
        CODEGEN(".method public static %s", $<s_val>2);
        is_main = 0;
    }

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
    : '{' NEWLINE StatementList '}' 
    {
        dump_symbol();
        CODEGEN("return\n");
        CODEGEN(".end method\n");
    }
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
    {
        if(return_type == 'v'){
            CODEGEN("return\n");
            CODEGEN(".end method\n");
        }
        else{
            CODEGEN("%creturn\n", return_type);
            CODEGEN(".end method\n");
        }
    }
    | RETURN
    {
        CODEGEN("return\n");
        CODEGEN(".end method\n");
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
    : Expression 
    {
        strcpy(id_storage, id_temp);
    }
    assign_op 
    {
        if(strcmp($<s_val>3, "ADD") == 0){
            CODEGEN("%cload %d\n", $<s_val>1[0], lookup_symbol_addr(id_storage, false));
        }
        else if(strcmp($<s_val>3, "SUB") == 0){
            CODEGEN("%cload %d\n", $<s_val>1[0], lookup_symbol_addr(id_storage, false));
        }
        else if(strcmp($<s_val>3, "MUL") == 0){
            CODEGEN("%cload %d\n", $<s_val>1[0], lookup_symbol_addr(id_storage, false));
        }
        else if(strcmp($<s_val>3, "QUO") == 0){
            CODEGEN("%cload %d\n", $<s_val>1[0], lookup_symbol_addr(id_storage, false));
        }
        else if(strcmp($<s_val>3, "REM") == 0){
            CODEGEN("%cload %d\n", $<s_val>1[0], lookup_symbol_addr(id_storage, false));
        }
    }
    Expression 
    {
        if(strcmp($<s_val>1, $<s_val>2) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno, $<s_val>3, $<s_val>1, $<s_val>2);
        }
        printf("%s\n", $<s_val>3);

        if(strcmp($<s_val>3, "ADD") == 0){
            CODEGEN("%cadd\n", $<s_val>1[0]);
        }
        else if(strcmp($<s_val>3, "SUB") == 0){
            CODEGEN("%csub\n", $<s_val>1[0]);
        }
        else if(strcmp($<s_val>3, "MUL") == 0){
            CODEGEN("%cmul\n", $<s_val>1[0]);
        }
        else if(strcmp($<s_val>3, "QUO") == 0){
            CODEGEN("%cdiv\n", $<s_val>1[0]);
        }
        else if(strcmp($<s_val>3, "REM") == 0){
            CODEGEN("%crem\n", $<s_val>1[0]);
        }
        if(strcmp($<s_val>1, "string")==0){
            CODEGEN("astore %d\n", lookup_symbol_addr(id_storage, false));
        }
        else if(strcmp($<s_val>1, "bool")==0){
            CODEGEN("istore %d\n", lookup_symbol_addr(id_storage, false));
        }
        else{
            CODEGEN("%cstore %d\n", $<s_val>1[0], lookup_symbol_addr(id_storage, false));
        }
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
    : Expression INC    
    {printf("INC\n");
    //new
    int temp = lookup_symbol_addr($<s_val>2, false); 
    if($<s_val>1[0] == 'i'){
        CODEGEN("ldc 1\niadd\nistore %d\n", temp);
    }
    else if($<s_val>1[0] == 'f'){
        CODEGEN("ldc 1.0\nfadd\nfstore %d\n", temp);
    }
    }
    | Expression DEC    
    {printf("DEC\n");
    //new
    int temp = lookup_symbol_addr($<s_val>2, false); 
    if($<s_val>1[0] == 'i'){
        CODEGEN("ldc 1\nisub\nistore %d\n", temp);
    }
    else if($<s_val>1[0] == 'f'){
        CODEGEN("ldc 1.0\nfsub\nfstore %d\n", temp);
    }
    }
;

PackageStmt
    : PACKAGE IDENT
        {printf("package: %s\n", $<s_val>2);}
;

DeclarationStmt
    : VAR IDENT Type '=' Expression
        {insert_symbol(false, false, $<s_val>2, $<s_val>3, "-");
            if(strcmp($<s_val>3, "int32") == 0){
                CODEGEN("istore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
            else if(strcmp($<s_val>3, "float32") == 0){
                CODEGEN("fstore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
            else if(strcmp($<s_val>3, "string") == 0){
                CODEGEN("astore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
            else if(strcmp($<s_val>3, "bool") == 0){
                CODEGEN("istore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
        }
    | VAR IDENT Type
        {insert_symbol(false, false, $<s_val>2, $<s_val>3, "-");
            if(strcmp($<s_val>3, "int32") == 0){
                CODEGEN("ldc 0\n");
                CODEGEN("istore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
            else if(strcmp($<s_val>3, "float32") == 0){
                CODEGEN("ldc 0.000000\n");
                CODEGEN("fstore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
            else if(strcmp($<s_val>3, "string") == 0){
                CODEGEN("ldc \"\\n\"\n");
                CODEGEN("astore %d\n", lookup_symbol_addr($<s_val>2, false));
            }
        }
;

Block  
    : '{'  NEWLINE  {create_symbol();} StatementList '}'   {dump_symbol();}
;

PrintStmt
    : PRINT '(' Expression ')'
        {
        printf("PRINT %s\n", $<s_val>3); 
        if(strcmp($<s_val>3, "bool")==0){
            CODEGEN("ifne L_cmp_%d\n", cmp_con++);
            CODEGEN("ldc \"false\"\n");
            CODEGEN("goto L_cmp_%d\n", cmp_con++);
            CODEGEN("L_cmp_%d:\n", cmp_con-2);
            CODEGEN("ldc \"true\"\n");
            CODEGEN("L_cmp_%d:\n", cmp_con-1);
        }
        CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        CODEGEN("swap\n");
        CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }
    | PRINTLN '(' Expression ')'
        {
        printf("PRINTLN %s\n", $<s_val>3); 
        if(strcmp($<s_val>3, "bool")==0){
            CODEGEN("ifne L_cmp_%d\n", cmp_con++);
            CODEGEN("ldc \"false\\n\"\n");
            CODEGEN("goto L_cmp_%d\n", cmp_con++);
            CODEGEN("L_cmp_%d:\n", cmp_con-2);
            CODEGEN("ldc \"true\\n\"\n");
            CODEGEN("L_cmp_%d:\n", cmp_con-1);
        }
        CODEGEN("getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        CODEGEN("swap\n");
        if(strcmp($<s_val>3, "bool")==0 || strcmp($<s_val>3, "string")==0){
            CODEGEN("invokevirtual java/io/PrintStream/print(Ljava/lang/String;)V\n");
        }
        else{
            CODEGEN("invokevirtual java/io/PrintStream/println(%c)V\n", toupper($<s_val>3[0]));
        }
        }
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
    : FOR 
    {
        CODEGEN("L_for_begin:\n");
    }
    ForAfter
;

ForAfter
    : Condition
    {
        CODEGEN("ifeq L_for_exit\n");
    }
    Block
    {
        CODEGEN("goto L_for_begin\n");
        CODEGEN("L_for_exit:\n");
    }
    | FOR ForClause Block
;

ForClause
    : InitStmt ';' Condition ';' PostStmt
;

InitStmt : SimpleStmt
PostStmt : SimpleStmt

SwitchStmt
    : SWITCH Expression 
    {
        switch_label_head = malloc(sizeof(struct switch_label));
        switch_label_head -> index = -1;
        switch_label_head -> next = NULL;
        switch_label_head -> is_last = 0;
        CODEGEN("goto L_switch_begin_%d\n", switch_num);
    }
    Block
;

CaseStmt
    : CASE INT_LIT 
    {
        printf("case %d\n", $<i_val>2);
        struct switch_label *temp = malloc(sizeof(struct switch_label));
        temp -> index = $<i_val>2;
        temp -> next = NULL;
        temp -> is_last = 0;
        struct switch_label *ptr = switch_label_head;
        while(ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = temp;
        CODEGEN("L_case_%d:\n", $<i_val>2);    
    } 
    ':' Block
    {
        CODEGEN("goto L_switch_end_%d\n", switch_num);
    }
    | DEFAULT 
    {
        struct switch_label *temp = malloc(sizeof(struct switch_label));
        struct switch_label *ptr = switch_label_head;
        while(ptr -> next != NULL){
            ptr = ptr -> next;
        }
        temp -> index = (ptr -> index) + 1;
        temp -> next = NULL;
        temp -> is_last = 1;
        ptr -> next = temp;
        CODEGEN("L_case_%d:\n", temp -> index);
    }
    ':' Block
    {
        CODEGEN("goto L_switch_end_%d\n\n", switch_num);
        CODEGEN("L_switch_begin_%d:\n", switch_num);
        CODEGEN("lookupswitch\n");
        struct switch_label *ptr = switch_label_head->next;
        while(ptr != NULL){
            if(ptr -> is_last ==  1){
                CODEGEN("default: L_case_%d\n", ptr -> index);
                break;
            }
            else{
                CODEGEN("%d: L_case_%d\n", ptr-> index, ptr -> index);
            }
            ptr = ptr -> next;
        }
        CODEGEN("L_switch_end_%d:\n", switch_num++);
        //CODEGEN("return\n");
    }
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
        CODEGEN("ior\n");
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
        CODEGEN("iand\n");
    }
    | ComparisonExpr {$$ = $1;}
;

ComparisonExpr
    : AdditionExpr cmp_op AdditionExpr
    {
        if(strcmp($<s_val>1, $<s_val>3) != 0){
            printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n", yylineno, $<s_val>2, $<s_val>1, $<s_val>3);
        }
        else {
            if($<s_val>1[0] == 'i'){
                CODEGEN("isub\n");
            }
            else if($<s_val>1[0] == 'f'){
                CODEGEN("fcmpl\n");
            }
            if(strcmp($<s_val>2, "GTR") == 0){
                CODEGEN("ifgt L_cmp_%d\n", cmp_con++);
                CODEGEN("iconst_0\n");
                CODEGEN("goto L_cmp_%d\n", cmp_con++);
                CODEGEN("L_cmp_%d:\n", cmp_con-2);
                CODEGEN("iconst_1\n");
                CODEGEN("L_cmp_%d:\n", cmp_con-1);
            }
            else if(strcmp($<s_val>2, "LES") == 0){
                CODEGEN("iflt L_cmp_%d\n", cmp_con++);
                CODEGEN("iconst_0\n");
                CODEGEN("goto L_cmp_%d\n", cmp_con++);
                CODEGEN("L_cmp_%d:\n", cmp_con-2);
                CODEGEN("iconst_1\n");
                CODEGEN("L_cmp_%d:\n", cmp_con-1);
            }
            
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
        //new
        CODEGEN("%c%s\n", tolower($<s_val>1[0]), $<s_val>2);
    }
    | AdditionExpr add_op MultiplicationExpr
    {$$ = $1;
    printf("%s\n", $<s_val>2);
    CODEGEN("%c%s\n", tolower($<s_val>1[0]), $<s_val>2);
    }
    | MultiplicationExpr {$$ = $1;}
;

MultiplicationExpr
    : UnaryExpr mul_op UnaryExpr
    {
        if((strcmp($<s_val>2, "rem") == 0)&&(strcmp($<s_val>3, "float32") == 0)){
            printf("error:%d: invalid operation: (operator REM not defined on float32)\n", yylineno);
        }
        $$ = $1;
        printf("%s\n", $<s_val>2);
        CODEGEN("%c%s\n", tolower($<s_val>1[0]), $<s_val>2);
    }
    | UnaryExpr {$$ = $1;}
;

UnaryExpr
    : unary_op UnaryExpr 
    {   $$ = $2;
        printf("%s\n", $<s_val>1);
        if(strcmp($<s_val>1, "NOT")==0){
            CODEGEN("iconst_1\n");
            if(strcmp($<s_val>2, "true")==0){
                CODEGEN("iconst_1\n");
            }
            else if(strcmp($<s_val>2, "false")==0){
                CODEGEN("iconst_0\n");
            }
            CODEGEN("ixor\n");
            $$ = "bool";
        }
        else if(strcmp($<s_val>1, "neg")==0){
            CODEGEN("%cneg\n", $<s_val>2[0]);
        }
    }
    | PrimaryExpr 
    {   $$ = $1;
        if(strcmp($<s_val>1, "true")==0){
            CODEGEN("iconst_1\n");
            $$ = "bool";
        }
        else if(strcmp($<s_val>1, "false")==0){
            CODEGEN("iconst_0\n");
            $$ = "bool";
        }
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
    : '+' { $$ = "add"; }
    | '-' { $$ = "sub"; }
;

mul_op 
    : '*' { $$ = "mul"; }
    | '/' { $$ = "div"; }
    | '%' { $$ = "rem"; }
;

unary_op 
    : '+' { $$ = "POS"; }
    | '-' { $$ = "neg"; }
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
    : Type '(' Expression ')'
    {
        printf("%c2%c\n", $<s_val>3[0], $<s_val>1[0]);
        CODEGEN("%c2%c\n", $<s_val>3[0], $<s_val>1[0]);
    }
;

Literal
    : INT_LIT
        {$$ = "int32"; 
        printf("INT_LIT %d\n", $<i_val>1); 
        CODEGEN("ldc %d\n", $<i_val>1);
        }
    | FLOAT_LIT
        {$$ = "float32"; 
        printf("FLOAT_LIT %f\n", $<f_val>1); 
        CODEGEN("ldc %f\n", $<f_val>1);
        }
    | TRUE 
        {$$ = "true"; 
        printf("TRUE 1\n");
        //CODEGEN("iconst_1\n");
        }
    | FALSE 
        {$$ = "false"; 
        printf("FALSE 0\n");
        //CODEGEN("iconst_0\n");
        }
    | '"' STRING_LIT '"'
        {$$ = "string"; 
        printf("STRING_LIT %s\n", $<s_val>2); 
        CODEGEN("ldc \"%s\\n\"\n", $<s_val>2);
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
    if (!yyin) {
        printf("file `%s` doesn't exists or cannot be opened\n", argv[1]);
        exit(1);
    }

    /* Codegen output init */
    char *bytecode_filename = "hw3.j";
    fout = fopen(bytecode_filename, "w");
    CODEGEN(".source hw3.j\n");
    CODEGEN(".class public Main\n");
    CODEGEN(".super java/lang/Object\n");
    

    yylineno = 0;
    create_symbol();
    yyparse();
    dump_symbol();

   

	printf("Total lines: %d\n", yylineno);
    fclose(fout);
    fclose(yyin);

    if (g_has_error) {
        remove(bytecode_filename);
    }
    yylex_destroy();
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
        //new
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
                    //new
                    if(strcmp(s_pointer -> type, "int32") == 0 || strcmp(s_pointer -> type, "bool") == 0){
                        CODEGEN("iload %d\n", s_pointer -> addr);
                    }
                    else if(strcmp(s_pointer -> type, "float32") == 0){
                        CODEGEN("fload %d\n", s_pointer -> addr);
                    }
                    else if(strcmp(s_pointer -> type, "string") == 0){
                        CODEGEN("aload %d\n", s_pointer -> addr);
                    }
                    strcpy(id_temp, s_pointer -> name);
                    return s_pointer -> type;
                }
                else{
                    printf("call: %s%s\n", s_pointer -> name, s_pointer -> func_sig);
                    CODEGEN("invokestatic Main/%s%s\n", s_pointer -> name, s_pointer -> func_sig);
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


static int lookup_symbol_addr(char *name, bool is_function) {
    struct table *t_pointer = cur_table;
    struct symbol *s_pointer = NULL;
    while(t_pointer != NULL){
        s_pointer = t_pointer -> head;
        while(s_pointer != NULL){
            if(strcmp(s_pointer -> name, name) == 0){
                if(is_function == false){
                    return s_pointer -> addr;
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

static char *lookup_symbol_type(char *name, bool is_function) {
    struct table *t_pointer = cur_table;
    struct symbol *s_pointer = NULL;
    while(t_pointer != NULL){
        s_pointer = t_pointer -> head;
        while(s_pointer != NULL){
            if(strcmp(s_pointer -> name, name) == 0){
                if(is_function == false){
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