%option noyywrap
%option header-file="lex.yy.h"
%option outfile="lex.yy.cpp"

%{
#include <iostream>
#include "parser.tab.h"

#define YY_DECL int yylex()
%}

letter [a-zA-Z]
digit [0-9]
exp ((E|e)((\+|-)?)?{digit}+)
%%

\/\/.* /* ignore single line comment */;
\/\*(.|\n)*\*\/ /* ignore multi-line comment */;

[ \t\r\014] /*ignore ws*/ ;
"\n"		/*ignore newline*/ ;

(true|false)					{yylval=new Token(yytext); return T_BOOLEANLITERAL;}
{digit}+\.{digit}*{exp}?	{yylval=new Token(yytext); return T_DOUBLELITERAL;}
\"[^\"]*\"					{yylval=new Token(yytext); return T_STRINGLITERAL;}
({digit}+|0(X|x)[a-fA-F0-9]+)			{yylval=new Token(yytext); return T_INTLITERAL;}

"void" 			{Type *node = new Type();
                    node->setTypeNameId("void");
                    node->setDimension(0);
                    yylval = node;
                    return T_VOID;}
"int" 			{return T_INT;}
"double" 		{return T_DOUBLE;}
"bool" 			{return T_BOOL;}
"string" 		{return T_STRING;}
"class" 		{return T_CLASS;}
"interface" 	{return T_INTERFACE;}
"null" 			{return T_NULL;}
"this" 			{return T_THIS;}
"extends" 		{return T_EXTENDS;}
"implements" 	{return T_IMPLEMENTS;}
"for" 			{return T_FOR;}
"while" 		{return T_WHILE;}
"if" 			{return T_IF;}
"else" 			{return T_ELSE;}
"return" 		{return T_RETURN;}
"break" 		{return T_BREAK;}
"continue" 		{return T_CONTINUE;}
"new" 			{return T_NEW;}
"NewArray" 		{return T_NEWARRAY;}
"Print" 		{return T_PRINT;}
"ReadInteger" 	{return T_READINTEGER;}
"ReadLine" 		{return T_READLINE;}
"dtoi" 			{return T_DTOI;}
"itod" 			{return T_ITOD;}
"btoi" 			{return T_BTOI;}
"itob" 			{return T_ITOB;}
"private" 		{return T_PRIVATE;}
"protected" 	{return T_PROTECTED;}
"public" 		{return T_PUBLIC;}

"+" 	{return T_PLUS;}
"-" 	{return T_MINUS;}
"*" 	{return T_MUL;}
"/" 	{return T_DIV;}
"%" 	{return T_PERCENT;}
"<" 	{return T_CMPL;}
"<=" 	{return T_CMPLE;}
">" 	{return T_CMPG;}
">=" 	{return T_CMPGE;}
"=" 	{return T_ASSIGN;}
"==" 	{return T_CMPE;}
"!=" 	{return T_CMPNE;}
"||" 	{return T_OR;}
"&&"	{return T_AND;}
"!" 	{return T_NOT;}
";" 	{return T_SEMICOLON;}
"," 	{return T_COMMA;}
"." 	{return T_DOT;}
"[" 	{return T_OB;}
"]" 	{return T_CB;}
"(" 	{return T_OP;}
")" 	{return T_CP;}
"{" 	{return T_OCB;}
"}" 	{return T_CCB;}

{letter}({letter}|{digit}|_)* {yylval=new Token(yytext); return T_ID;}

.				{return T_UNDEFINED;}

%%
