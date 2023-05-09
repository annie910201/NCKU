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
    static void insert_symbol();
    static void lookup_symbol();
    static void dump_symbol();

    struct table{
        struct table *next;
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
    struct symbol *head_symbol = NULL;
    struct table *head_table = NULL;
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
%type <s_val> Type

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
;
ParameterList
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
    struct symbol *cur = malloc(sizeof(struct symbol));
    cur -> index = 
    cur -> 
    printf("> Create symbol table (scope level %d)\n", 0);
}

static void insert_symbol(char* type, char* name, char* func_sig, int mark_var) {// if mark_var = 0, function; else if mark_var = 1, parameter
    // printf("> Insert `%s` (addr: %d) to scope level %d\n", name, 0, 0);
}

static void lookup_symbol() {
}

static void dump_symbol() {
    printf("\n> Dump symbol table (scope level: %d)\n", 0);
    printf("%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
        "Index", "Name", "Mut","Type", "Addr", "Lineno", "Func_sig");
    printf("%-10d%-10s%-10d%-10s%-10d%-10d%-10s\n",
            0, "name", 0, "type", 0, 0, "func_sig");
}
