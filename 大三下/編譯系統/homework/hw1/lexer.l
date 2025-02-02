/*
    filename: lexer.l
*/
 
/* Definition section */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
 
    #define YY_NO_UNPUT
    #define YY_NO_INPUT
    #define print_token(token) \
        printf("%-8s \t %s\n", strcmp(token, "NEWLINE")? yytext: "", token)
    int line_num = 0;
    int comment_num = 0;
    int last_comment_line = -1;
    int multi = 1;
    int flag = 1;
    int block = 0;
%}

/* Define regular expression label */
letter [a-zA-Z_]
digit [0-9]
inumber {digit}+
fnumber ({digit}*\.{digit}+)
id {letter}+({letter}|{digit})*
%x C_comment Cpp_comment STRING
/* Rules section */
%%
"\"" {
    BEGIN(STRING);
    print_token("QUOTA");
}
"/*"        {
    BEGIN(C_comment);
    printf("/*");
}
"//"        {
    BEGIN(Cpp_comment); 
    printf("//");
}

"+"         { print_token("ADD"); }
"-"         { print_token("SUB"); }
"*"          { print_token("MUL"); }
"/"          { print_token("QUO"); }
"%"          { print_token("REM"); }
">"          { print_token("GTR"); }
"<"          { print_token("LSS"); }
">="          { print_token("GEQ"); }
"<="          { print_token("LEQ"); }
"=="          { print_token("EQL"); }
"!="          { print_token("NEQ"); }
"="          { print_token("ASSIGN"); }
"+="          { print_token("ADD_ASSIGN"); }
"-="          { print_token("SUB_ASSIGN"); }
"*="          { print_token("MUL_ASSIGN"); }
"/="          { print_token("QUO_ASSIGN"); }
"%="          { print_token("REM_ASSIGN"); }
"&"          { print_token("BAND"); }
"|"          { print_token("BOR"); }
"~"          { print_token("BNOT"); }
">>"          { print_token("RSHIFT"); }
"&&"          { print_token("LAND"); }
"||"          { print_token("LOR"); }
"!"          { print_token("NOT"); }
"("          { print_token("LPAREN"); }
")"          { print_token("RPAREN"); }
"["          { print_token("LBRACK"); }
"]"          { print_token("RBRACK"); }
"{"          { print_token("LBRACE"); }
"}"          { print_token("RBRACE"); }
";"          { print_token("SEMICOLON"); }
","          { print_token("COMMA"); }
"\n"          { print_token("NEWLINE"); line_num++;}
":"          { print_token("COLON"); }
"->"          { print_token("ARROW"); }
"<<"          { print_token("LSHIFT"); }
"print"          { print_token("PRINT"); }
"println"          { print_token("PRINTLN"); }
"if"          { print_token("IF"); }
"else"          { print_token("ELSE"); }
"for"          { print_token("FOR"); }
"i32"          { print_token("INT"); }
"f32"          { print_token("FLOAT"); }
".."          { print_token("DOTDOT"); }
"bool"          { print_token("BOOL"); }
"true"          { print_token("TRUE"); }
"false"          { print_token("FALSE"); }
"let"          { print_token("LET"); }
"mut"          { print_token("MUT"); }
"fn"          { print_token("FUNC"); }
"return"          { print_token("RETURN"); }
"break"          { print_token("BREAK"); }
"as"          { print_token("AS"); }
"in"          { print_token("IN"); }
"while"          { print_token("WHILE"); }
"loop"          { print_token("LOOP"); }

{inumber}   { print_token("INT_LIT"); }
{fnumber}   { print_token("FLOAT_LIT"); }
{id}        { print_token("IDENT"); }
<STRING>[^\"]* {
    print_token("STRING_LIT"); 
}
<STRING>\" {
    BEGIN(INITIAL);
    print_token("QUOTA");
}
<Cpp_comment>[^\n]* { 
    // print_token("COMMENT"); 
    printf("%-6s \t COMMENT\n",yytext);
}
<Cpp_comment>"\n" { 
    BEGIN(INITIAL);
    line_num++;
    comment_num++;
    print_token("NEWLINE"); 
}

<C_comment>"*/"        {
    
    if(multi)
        print_token("MUTI_LINE_COMMENT");
    else
        print_token("COMMENT");  
    
    if(flag){
        flag = 0;
        comment_num++;
        block = 1;
    }
    BEGIN(INITIAL);
}

<C_comment>"\n"        {
    if(!block)
        comment_num++;
    block = 0;
    printf("\n");
    multi = 1;
    line_num++;
    flag = 1;
}

{}

<<EOF>>     { line_num++; yyterminate(); }
[ \t]+      {;}
.           {;}
%%
 
/*  C Code section */
int yywrap(void)
{
    return 1;
}
 
int main(int argc, char *argv[])
{
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    } else {
        yyin = stdin;
    }
    yylex();
    printf("\nFinish scanning,\n");
    printf("total line: %d\n", line_num);
    printf("comment line: %d\n", comment_num);
    fclose(yyin);
    return 0;
}
