%define parse.trace

%{

#include <iostream>
#include <fstream>

#include "lex.yy.h"
#include "SyntaxTree/SyntaxTree.h"
using namespace SyntaxTree;
using namespace SymbolTable;

#define YYSTYPE Node *

extern int yylex();
//extern int yyparse();

extern ProgramNode root;


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

program: decl { root.addDecl((Decl *)$1); }
		| program decl { root.addDecl((Decl *)$2); }
;

decl: variable_decl {   DeclToVariableDecl *node = new DeclToVariableDecl();
                        node->setVariableDecl((VariableDecl *) $1);
                        $$=node; }
	| function_decl {   DeclToFunctionDecl *node = new DeclToFunctionDecl();
						node->setFunctionDecl((FunctionDecl *) $1);
						$$=node;}
	| class_decl
	| interface_decl
;

variable_decl: variable T_SEMICOLON {   VariableDecl *node = new VariableDecl();
                                        node->setVariable((Variable *) $1);
                                        $$=node; }
;

variable: type T_ID {   Variable *node = new Variable();
                        node->setType((Type *) $1);
                        node->setId(yytext);
                        $$ = node; }
;

type: primitive_type { $$ = $1; }
	| T_ID { $$ = new Type(); //TODO: complete
	        }
	| array_type { $$ = $1; }
;

primitive_type: T_INT { Type *node = new Type();
                        node->setTypeName(TypeName("int", 0));
                        $$ = node;}
	| T_DOUBLE { Type *node = new SyntaxTree::Type();
                 node->setTypeName(TypeName("double", 0));
                 $$ = node;}
	| T_BOOL { Type *node = new SyntaxTree::Type();
               node->setTypeName(TypeName("bool", 0));
               $$ = node;}
	| T_STRING { Type *node = new SyntaxTree::Type();
                 node->setTypeName(TypeName("string", 0));
                 $$ = node;}
;

array_type: primitive_type T_OB T_CB
		| T_ID T_OB T_CB
		| array_type T_OB T_CB
;

function_decl: type T_ID T_OP formals T_CP stmt_block
			| T_VOID T_ID T_OP formals T_CP stmt_block
;

formals:
		| variable
		| formals T_COMMA variable
;

class_decl: T_CLASS T_ID extends implements T_OCB fields T_CCB
;

extends:
	| T_EXTENDS T_ID
;

implements:
	| T_IMPLEMENTS T_ID
	| implements T_COMMA T_ID
;

fields:
	| fields field
;

field: access_mode variable_decl
	| access_mode function_decl
;

access_mode:
		| T_PRIVATE
		| T_PROTECTED
		| T_PUBLIC
;

interface_decl: T_INTERFACE T_ID T_OCB proto_types T_CCB
;

proto_types:
		| proto_types proto_type
;

proto_type: type T_ID T_OP formals T_CP T_SEMICOLON
		| T_VOID T_ID T_OP formals T_CP T_SEMICOLON
;

stmt_block: T_OCB variable_decls stmts T_CCB
;

stmts:
	| stmt stmts
;

variable_decls:
		| variable_decls variable_decl
;

stmt: T_SEMICOLON
	| expr T_SEMICOLON
	| if_stmt
	| while_stmt
	| for_stmt
	| break_stmt
	| continue_stmt
	| return_stmt
	| print_stmt
	| stmt_block
;

if_stmt: T_IF T_OP expr T_CP stmt
		| T_IF T_OP expr T_CP stmt T_ELSE stmt
;

while_stmt: T_WHILE T_OP expr T_CP stmt
;

expr2:
	| expr
;

for_stmt: T_FOR T_OP expr2 T_SEMICOLON expr T_SEMICOLON expr2 T_CP stmt
;

return_stmt: T_RETURN expr2 T_SEMICOLON
;

break_stmt: T_BREAK T_SEMICOLON
;

continue_stmt: T_CONTINUE T_SEMICOLON
;

print_stmt: T_PRINT T_OP actuals1 T_CP T_SEMICOLON
;

actuals1: expr { PrintStmt *node = new PrintStmt(); node->addExpr((Expr *)$1); $$=node; }
	| expr T_COMMA actuals1 { ((PrintStmt *)$3)->addExpr((Expr *)$1); $$=$3; }
;

expr: lvalue T_ASSIGN expr
	| constant
	| lvalue
	| T_THIS
	| call
	| T_OP expr T_CP
	| expr T_PLUS expr 
	| expr T_MINUS expr
	| expr T_MUL expr
	| expr T_DIV expr
	| expr T_PERCENT expr
	| T_MINUS expr
	| expr T_CMPL expr
	| expr T_CMPLE expr
	| expr T_CMPG expr
	| expr T_CMPGE expr
	| expr T_CMPE expr
	| expr T_CMPNE expr
	| expr T_AND expr
	| expr T_OR expr
	| T_NOT expr
	| T_READINTEGER T_OP T_CP
	| T_READLINE T_OP T_CP
	| T_NEW T_ID
	| T_NEWARRAY T_OP expr T_COMMA type T_CP
	| T_ITOD T_OP expr T_CP
	| T_DTOI T_OP expr T_CP
	| T_ITOB T_OP expr T_CP
	| T_BTOI T_OP expr T_CP
;

lvalue: T_ID
	| T_ID T_OB expr T_CB
	| expr T_DOT T_ID
	| expr T_OB expr T_CB
;

call: T_ID T_OP actuals T_CP
	| expr T_DOT T_ID T_OP actuals T_CP
;

actuals:
	| actuals1
;

constant: T_INTLITERAL { /*ConstantNode *node = new ConstantNode(); node->type = "int"; node->val = yytext; $$ = node;*/}
		| T_DOUBLELITERAL
		| T_BOOLEANLITERAL
		| T_STRINGLITERAL
		| T_NULL
;



%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	fprintf(output_file, "Syntax Error\n");
	exit(0);
}
