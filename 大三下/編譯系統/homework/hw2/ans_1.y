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

    /* Symbol table function - you can add new functions if needed. */
    /* parameters and return type can be changed */
    static void create_symbol();
    static void insert_symbol(char * name, char * type, char * sig, int lin);
    static lookup lookup_symbol( char *ID);
    static void dump_symbol();
    static void ID_type_error(char *datatype);
    static void LIT_type_error(char *datatype);
    // static table* createNode();

    /* Global variables */
    bool HAS_ERROR = false;
    table *Node[4] = {};
    table *cur_fnc_node, *cur_param_node;
    int cur_scope   = -1;
    char *type      = NULL;
    char* Name      = NULL;
    char *FuncSig   = NULL;
    char *FuncName  = NULL;
    char *exprName  = NULL;
    int line        = 0;
    bool create     = true;
    int addr        = 0;
    int valLine     = 0;
    bool conver     = false;
    char *errorName = NULL;
    bool compare    = false;
    bool forbool    = false;
    bool iserror    = false;
    bool iserrorAsgn = false;
    char *errorType = NULL; 
    int  errorAsgnLine = 0;
    char returnType = 'v';
    bool isReturn = false;
    char *funcName = NULL;
    char *funcType = NULL;
    bool isFunc    = false;

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
%token VAR NEWLINE PACKAGE FUNC
%token INT FLOAT BOOL STRING TRUE FALSE
%token INC DEC GEQ LOR LAND LEQ EQL NEQ
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN QUO_ASSIGN REM_ASSIGN
%token IF ELSE FOR SWITCH CASE DEFAULT RETURN
%token PRINT PRINTIN

/* Token with return, which need to sepcify type */
%token <i_val> INT_LIT P_INT_LIT N_INT_LIT
%token <f_val> FLOAT_LIT P_FLOAT_LIT N_FLOAT_LIT
%token <s_val> STRING_LIT
%token <s_val> ID

/* Nonterminal with return, which need to sepcify type */
/* %type <s_val> Type */

/* Yacc will start at this nonterminal */
%start Program

/* Grammar section */
%%

Program
    : GlobalStatementList { dump_symbol(); }
;

GlobalStatementList 
    : GlobalStatement GlobalStatementList 
    | 
;
GlobalStatement
    : PackageStmt NEWLINE
    | FunctionDeclStmt
    | SentenceList
;
SentenceList
    : sentence SentenceList
    |
;
sentence 
    : NEWLINE {type = NULL;compare = false;}
    | VarStmt
    | PrintStmt
    | ExprStmt
    | BlockStmt
    | AsgnStmt
    | IF ExprStmt {  if(!forbool && strcmp(type,"bool") != 0)
            printf("error:%d: non-bool (type %s) used as for condition\n",yylineno+1,type);
            forbool = false;
        } 
     
    | FOR {forbool = false;} ExprStmt {
        if(!forbool && strcmp(type,"bool") != 0) 
            printf("error:%d: non-bool (type %s) used as for condition\n",yylineno+1,type);
        forbool = false;}
    | SWITCH ExprStmt
    | CASE INT_LIT {printf("case %d\n",yylval.i_val);} ':' 
    | DEFAULT ':'
    | RETURN {isReturn = true;} ExprStmt { if(returnType != 'v')printf("%c",returnType);printf("return\n");isReturn = false;returnType = 'v';}
;
BlockStmt : '{' {create_symbol();} SentenceList '}'{dump_symbol(); line = yylineno;};


VarStmt
    : VAR ID { Name = strdup(yylval.s_val);} VarTypeStmt
;
VarTypeStmt
    : INT    { type = strdup("int32");  valLine = yylineno;}    VarAsgnStmt
    | FLOAT  { type = strdup("float32");valLine = yylineno;}    VarAsgnStmt
    | STRING { type = strdup("string"); valLine = yylineno;}    VarAsgnStmt
    | BOOL   { type = strdup("bool");   valLine = yylineno;}    VarAsgnStmt
;
VarAsgnStmt
    : '=' ExprStmt 
        {
            insert_symbol(Name, type,"-",valLine); 
        }
    |   
        { 
            lookup i = lookup_symbol(Name);
            if(i.address != -1)
                printf("error:%d: %s redeclared in this block. previous declaration at line %d\n", yylineno, Name, i.line);
            insert_symbol(Name, type,"-",valLine); 
        }
;
PrintStmt 
    :PRINTIN Stmt {printf("PRINTLN %s\n",type),type = NULL;}
    |PRINT   Stmt {printf(  "PRINT %s\n",type),type = NULL;}
;
Stmt
    : '(' ExprStmt ')'
;
AsgnStmt: IDs AsgnSelStmt;
AsgnSelStmt 
    : '='{
            exprName = strdup("ASSIGN");
            errorAsgnLine = yylineno+1;
        } ExprStmt {printf("ASSIGN\n");}
    | ADD_ASSIGN ExprStmt {printf("ADD\n");}
    | SUB_ASSIGN ExprStmt {printf("SUB\n");}
    | MUL_ASSIGN ExprStmt {printf("MUL\n");}
    | QUO_ASSIGN ExprStmt {printf("QUO\n");}
    | REM_ASSIGN ExprStmt {printf("REM\n");}
;
ExprStmt
    : LOR  {exprName = strdup("LOR"); forbool = true;}   ExprStmt 
        { 
            if(iserror) 
                printf("error:%d: invalid operation: (operator LOR not defined on %s)\n",yylineno,errorType);
            printf("LOR\n");
            iserror = false;
            errorType = NULL;
        }
    | LAND {exprName = strdup("LAND");forbool = true;}  ExprStmt 
        { 
            if(iserror) 
                printf("error:%d: invalid operation: (operator LAND not defined on %s)\n",yylineno,errorType);
            printf("LAND\n");
            iserror = false;
            errorType = NULL;
        }
    | CmpStmt ExprStmt
    | BoolStmt ExprStmt
    | callFuncStmt
    |
;
callFuncStmt
    : ID {
            funcName = strdup(yylval.s_val);
            table *temp = Node[0];
            while(strcmp(funcName,temp->Name)!=0){
                temp = temp -> next;
                if(temp == NULL) break;
            }
            if(temp) funcType = strdup(temp->Func_sig);
            isFunc = true;
        } '(' funcExprStmt ')' { printf("call: %s%s\n",funcName,funcType);isFunc = false;}
;
funcExprStmt
    : ExprStmt ',' funcExprStmt
    | ExprStmt
;
BoolStmt
    : '!'   BoolStmt  { printf("NOT\n");    }
    | TRUE  { 
             printf( "TRUE 1\n"); 
            if(type && exprName) {
                if(strcmp(type,"bool")!=0 && !compare) errorType = strdup(type),iserror = true;
            }
            
            type = strdup("bool");
        } BoolStmt  
    | FALSE { 
             printf("FALSE 0\n"); 
            if(type && exprName) {
                if(strcmp(type,"bool")!=0 && !compare) errorType = strdup(type),iserror = true;
            }
            type = strdup("bool");
        } BoolStmt  
    |
;
CmpStmt
    : '>' {exprName = strdup("GTR"); errorAsgnLine = yylineno; compare=true;} AddSubStmt {printf("GTR\n"); forbool=true;}
    | '<' {exprName = strdup("LSS"); errorAsgnLine = yylineno; compare=true;} AddSubStmt {printf("LSS\n"); forbool=true;}
    | GEQ {exprName = strdup("GEQ"); errorAsgnLine = yylineno; compare=true;} AddSubStmt {printf("GEQ\n"); forbool=true;}
    | LEQ {exprName = strdup("LEQ"); errorAsgnLine = yylineno; compare=true;} AddSubStmt {printf("LEQ\n"); forbool=true;}
    | EQL {exprName = strdup("EQL"); errorAsgnLine = yylineno; compare=true;} AddSubStmt {printf("EQL\n"); forbool=true;}
    | NEQ {exprName = strdup("NEQ"); errorAsgnLine = yylineno; compare=true;} AddSubStmt {printf("NEQ\n"); forbool=true;}
    | AddSubStmt CmpStmt
    |
;
AddSubStmt
    : '+' {exprName = strdup("ADD"); errorAsgnLine = yylineno+1;} term  {printf("ADD\n");}
    | '-' {exprName = strdup("SUB"); errorAsgnLine = yylineno+1;} term  {printf("SUB\n");}
    | term AddSubStmt
    |
;
term
    : '*' {exprName = strdup("MUL"); errorAsgnLine = yylineno;} term  {printf("MUL\n");}
    | '/' {exprName = strdup("QUO"); errorAsgnLine = yylineno;} term  {printf("QUO\n");}
    | '%' {exprName = strdup("REM"); errorAsgnLine = yylineno;} term  {printf("REM\n");}
    | factor INC                            {printf("INC\n");}
    | factor DEC                            {printf("DEC\n");}
    | factor term     { /*ERROR*/}
    | '(' AddSubStmt ')' term
    | INT   '(' {conver = true;}  factor ')' {printf("f2i\n");conver = false;}
    | FLOAT '(' {conver = true;}  factor ')' {printf("i2f\n");conver = false;}
    |
;
factor 
    : IDs
    | LITs 
;
IDs 
    :ID {
        lookup l = lookup_symbol(yylval.s_val);
        if(l.address == -1) {
           printf("error:%d: undefined: %s\n",yylineno + 1, yylval.s_val);
            iserrorAsgn = true;
            
        }
        else {
            printf("IDENT (name=%s, address=%d)\n",yylval.s_val, l.address);
            ID_type_error(l.type);
            if(isReturn) returnType = (strcmp(l.type,"int32")==0)? 'i': 'f';
        }
    }   
;
LITs
    : INT_LIT 
            {
                printf(  "INT_LIT %d\n",yylval.i_val);
                LIT_type_error("int32");
                if(isReturn) returnType = 'i';
                
            }
    | P_INT_LIT 
            { 
                printf(  "INT_LIT %d\n",yylval.i_val); 
                if(!forbool)printf("POS\n");
                else printf("ADD\n");
                LIT_type_error("int32");
                if(isReturn) returnType = 'i';

            }
    | N_INT_LIT 
            { 
                printf(  "INT_LIT %d\n",yylval.i_val); printf("NEG\n");
                LIT_type_error("int32");
                if(isReturn) returnType = 'i';

            }
    | FLOAT_LIT 
            { 
                printf("FLOAT_LIT %f\n",yylval.f_val);
                LIT_type_error("float32");
                if(isReturn) returnType = 'i';

            }
    | P_FLOAT_LIT 
            {  
                printf("FLOAT_LIT %f\n",yylval.f_val); printf("POS\n");
                LIT_type_error("float32");
                if(isReturn) returnType = 'i';
            }
    | N_FLOAT_LIT 
            { 
                printf("FLOAT_LIT %f\n",yylval.f_val); printf("NEG\n");
                LIT_type_error("float32");
                if(isReturn) returnType = 'i';
            }
    | '"' STRING_LIT 
            {
                if(!type) type = strdup("string");
                else if (strcmp(type,"string") != 0) ;//ERROR
                printf("STRING_LIT %s\n",yylval.s_val);
                if(isReturn) returnType = 's';
            } '"'
    | TRUE  {  printf( "TRUE 1\n");type = strdup("bool"); 
                if(isReturn) returnType = 'b';
                }
    | FALSE {  printf("FALSE 0\n"); type = strdup("bool"); 
                if(isReturn) returnType = 'b';
                }

;
PackageStmt
    :PACKAGE ID { 
                create_symbol();
                create = false;
                printf("package: %s\n", yylval.s_val);
            }
;

FunctionDeclStmt
    :FUNC ID { printf("func: %s\n", yylval.s_val); create = false; create_symbol(); FuncName = malloc(sizeof(char)*10); FuncName =strdup(yylval.s_val);} 
         '(' { FuncSig = malloc(sizeof(char)*10); FuncSig = strdup("("); } 
        ParamStmt ')' { strcat(FuncSig, ")"); } 
        FunctTypeStmt{ 
            cur_scope--;
            printf("func_signature: %s\n",FuncSig);
            insert_symbol(FuncName, "func", FuncSig, yylineno);
            cur_scope++;
        } '{' SentenceList '}' {dump_symbol(); line = yylineno;}
;
ParamStmt
    : ID        {   printf("param %s, type: ",yylval.s_val);
                    Name = strdup(yylval.s_val); 
                } ParamStmt 
    | INT       {   printf("I\n"); 
                    strcat(FuncSig, "I"); 
                    insert_symbol(Name, "int32","-", yylineno);
                }  ParamStmt
    | FLOAT     {   printf("F\n"); 
                    strcat(FuncSig, "F");
                    insert_symbol(Name, "float32","-", yylineno);
                }  ParamStmt
    | ','   ParamStmt
    |
;
FunctTypeStmt
    : INT       { strcat(FuncSig, "I"); }   
    | FLOAT     { strcat(FuncSig, "F"); }   
    | BOOL      { strcat(FuncSig, "B"); }   
    | STRING    { strcat(FuncSig, "S"); }   
    |           { strcat(FuncSig, "V"); }
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

	printf("Total lines: %d\n", line + 1);
    fclose(yyin);
    return 0;
}

static void create_symbol() {
    cur_scope++;
    printf("> Create symbol table (scope level %d)\n", cur_scope);
    Node[cur_scope] = NULL;
}

static void insert_symbol(char * name, char * type, char *sig, int lin) {
    int cur_addr = (strcmp(type,"func") == 0) ? -1 : addr;
    addr =  (strcmp(type,"func") == 0)? addr : addr + 1;
    if(!Node[cur_scope]) {
        Node[cur_scope] = malloc(sizeof(table));
        Node[cur_scope]->next = NULL;
        Node[cur_scope]->Name = strdup(name);
        Node[cur_scope]->Addr = cur_addr;
        Node[cur_scope]->Type = strdup(type);
        Node[cur_scope]->Lineno = lin + 1;
        Node[cur_scope]->Func_sig = strdup(sig);
    }
    else {
        table * temp = Node[cur_scope];
        while(temp->next) {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(table));
        temp = temp->next;
        temp->next = NULL;
        temp->Name = strdup(name);
        temp->Addr = cur_addr;
        temp->Type = strdup(type);
        temp->Lineno = lin + 1;
        temp->Func_sig = strdup(sig);
    }
    printf("> Insert `%s` (addr: %d) to scope level %d\n", name, cur_addr, cur_scope);
}

static lookup lookup_symbol(char *name) {
    int scp = cur_scope;
    lookup i;
    i.address = -1;
    if(scp == 0) return i; // Cannot found
    table * cur_node = Node[scp];
    while( !cur_node ) cur_node = Node[--scp];
    if(scp == 0 || !cur_node) return i; // Cannot found
    while( strcmp(cur_node->Name,name) != 0){
        if(cur_node->next) cur_node = cur_node->next;
        else {
            if(scp == 0) {
                i.address = -1;
                cur_node = NULL;
                return i;
            }
            else cur_node = Node[--scp];
        }
    }
    if(cur_node) {
        i.address = cur_node->Addr;
        i.type = strdup(cur_node->Type);
        i.line = cur_node->Lineno;
    }
    return i;
}

static void dump_symbol() {
    printf("\n> Dump symbol table (scope level: %d)\n",cur_scope );
    printf("%-10s%-10s%-10s%-10s%-10s%-10s\n", "Index", "Name", "Type", "Addr", "Lineno", "Func_sig");
    
    table* temp = Node[cur_scope];
    
    int index = 0;
    while(temp) {
        printf("%-10d%-10s%-10s%-10d%-10d%-10s\n", index, temp->Name, temp->Type, temp->Addr, temp->Lineno, temp->Func_sig);
        temp = temp->next; 
        index++;
    }
    printf("\n");
    cur_scope--;
}

static void ID_type_error(char *datatype)
{
    if(!type) type = strdup(datatype);
    else if (exprName && strcmp(exprName,"REM") == 0 && strcmp(datatype,"float32") == 0 )
        printf("error:%d: invalid operation: (operator %s not defined on %s)\n"
                ,yylineno+1,exprName,datatype);//ERROR
    else if (strcmp(type,datatype) != 0 && !conver && !isFunc) {
        printf("error:%d: invalid operation: %s (mismatched types %s and %s)\n"
                ,errorAsgnLine,exprName,type,datatype);//ERROR
        forbool = true;
    }
}

static void LIT_type_error(char *datatype)
{
    if(iserrorAsgn) 
        printf("error:%d: invalid operation: %s (mismatched types ERROR and %s)\n",errorAsgnLine,exprName,datatype),iserrorAsgn = false;
    if(!type) type = strdup(datatype);
    else if (strcmp(type,datatype) != 0 && !conver && !isFunc){
        
        if(strcmp(exprName,"LOR")==0 || strcmp(exprName,"LAND") == 0) iserror = true;
        else{
            printf("error:%d: invalid operation: ",yylineno+1);
            printf("%s (mismatched types %s and %s)\n", exprName,type,datatype);//ERROR
        }
        type = strdup(datatype);
        forbool = true;
    }
    else if(exprName) {
        if(strcmp(exprName,"LOR")==0 || strcmp(exprName,"LAND") == 0) errorType = strdup(type),iserror = true;
    }
}
