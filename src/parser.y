%{

#include <iostream>
#include <fstream>

#include "lex.yy.h"

extern int yylex();
//extern int yyparse();

void yyerror(const char* s);

FILE *output_file;
%}

%token T_VOID T_INT T_DOUBLE T_BOOL T_STRING
%token T_CLASS T_INTERFACE T_NULL T_THIS T_EXTENDS T_IMPLEMENTS T_PRIVATE T_PROTECTED T_PUBLIC
%token T_FOR T_WHILE T_IF T_ELSE T_RETURN T_BREAK T_CONTINUE
%token T_NEW T_NEWARRAY T_PRINT T_READINTEGER T_READLINE T_DTOI T_ITOD T_BTOI T_ITOB
%token T_PLUS T_MINUS T_MUL T_DIV T_PERCENT T_CMPL T_CMPLE T_CMPG T_CMPGE T_ASSIGN T_CMPE T_CMPNE T_OR T_AND T_NOT T_SEMICOLON T_COMMA T_DOT T_OB T_CB T_OP T_CP T_OCB T_CCB
%token T_NEWLINE T_UNDEFINED

%token T_ID
%token T_INTLITERAL
%token T_DOUBLELITERAL
%token T_STRINGLITERAL
%token T_BOOLEANLITERAL

%start program

%%

program:
		| program line
		| program words
;

line: T_NEWLINE
		| words T_NEWLINE
;

words: word
		| words word
;

word: keyword 		{fprintf(output_file, "%s\n", yytext);}
	| operator		{fprintf(output_file, "%s\n", yytext);}	
	| id 			{fprintf(output_file, "T_ID %s\n", yytext);}
	| T_INTLITERAL		{fprintf(output_file, "T_INTLITERAL %s\n", yytext);}
	| T_DOUBLELITERAL 	{fprintf(output_file, "T_DOUBLELITERAL %s\n", yytext);}
	| T_STRINGLITERAL	{fprintf(output_file, "T_STRINGLITERAL %s\n", yytext);}
	| T_BOOLEANLITERAL	{fprintf(output_file, "T_BOOLEANLITERAL %s\n", yytext);}
	| T_UNDEFINED 	{fprintf(output_file, "UNDEFINED_TOKEN\n"); exit(0);}
;

id:	T_ID
;

keyword: T_VOID
		| T_INT
		| T_DOUBLE
		| T_BOOL
		| T_STRING
		| T_CLASS
		| T_INTERFACE
		| T_NULL
		| T_THIS
		| T_EXTENDS
		| T_IMPLEMENTS
		| T_FOR
		| T_WHILE
		| T_IF
		| T_ELSE
		| T_RETURN
		| T_BREAK
		| T_CONTINUE
		| T_NEW
		| T_NEWARRAY
		| T_PRINT
		| T_READINTEGER
		| T_READLINE
		| T_DTOI
		| T_ITOD
		| T_BTOI
		| T_ITOB
		| T_PRIVATE
		| T_PROTECTED
		| T_PUBLIC
;

operator: T_PLUS
		| T_MINUS
		| T_MUL
		| T_DIV
		| T_PERCENT
		| T_CMPL
		| T_CMPLE
		| T_CMPG
		| T_CMPGE
		| T_ASSIGN
		| T_CMPE
		| T_CMPNE
		| T_OR
		| T_AND
		| T_NOT
		| T_SEMICOLON
		| T_COMMA
		| T_DOT
		| T_OB
		| T_CB
		| T_OP
		| T_CP
		| T_OCB
		| T_CCB
;

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
