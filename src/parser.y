%define parse.trace

%{

#include <iostream>
#include <fstream>
#include <string>

#include "lex.yy.h"
#include "SyntaxTree/SyntaxTree.h"
#include <stack>
using namespace SyntaxTree;
using namespace SymbolTable;
using namespace std;

std::stack<string> saved_yytext;

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
	| class_decl {  DeclToClassDecl *node = new DeclToClassDecl();
	                node->setClassDecl((ClassDecl *) $1);
	                $$ = node;
	              }
	| interface_decl {  DeclToInterfaceDecl *node = new DeclToInterfaceDecl();
	                    node->setInterfaceDecl((InterfaceDecl *) $1);
	                    $$ = node;
	                    }
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
	| T_ID {    Type *node = new Type();
	            node->setTypeNameId(yytext);
	            node->setDimension(0);
	            $$ = node;
	        }
	| array_type { $$ = $1; }
;

primitive_type: T_INT { Type *node = new Type();
                        node->setTypeNameId("int");
                        node->setDimension(0);
                        $$ = node;}
	| T_DOUBLE {    Type *node = new SyntaxTree::Type();
	                node->setTypeNameId("double");
	                node->setDimension(0);
                    $$ = node;}
	| T_BOOL { Type *node = new SyntaxTree::Type();
               node->setTypeNameId("bool");
               node->setDimension(0);
               $$ = node;}
	| T_STRING { Type *node = new SyntaxTree::Type();
                 node->setTypeNameId("string");
                 node->setDimension(0);
                 $$ = node;}
;

array_type: primitive_type T_OB T_CB {  Type *node = (Type *) $1;
                                        node->incrementDimension();
                                        $$ = node;
                                        }
		| T_ID {saved_yytext.push(yytext);} T_OB T_CB {     Type *node = new Type();
		                                                    node->setTypeNameId(saved_yytext.top());
		                                                    saved_yytext.pop();
		                                                    node->setDimension(1);
		                                                    $$ = node;
		                                              }
		| array_type T_OB T_CB {    Type *node = (Type *) $1;
		                            node->incrementDimension();
		                            $$ = node;
		                       }
;

function_decl: type T_ID { saved_yytext.push(yytext); } T_OP formals T_CP stmt_block {  FunctionDeclToTypeIdent *node = new FunctionDeclToTypeIdent();
                                                                                        node->setFunctionIdentifier(saved_yytext.top());
                                                                                        saved_yytext.pop();
                                                                                        node->setFormals((Formals *) $5);
                                                                                        node->setStmtBlock((StmtBlock *) $7);
                                                                                        $$ = node;
                                                                                     }
			| T_VOID T_ID { saved_yytext.push(yytext); } T_OP formals T_CP stmt_block { FunctionDeclToVoidIdent *node = new FunctionDeclToVoidIdent();
			                                                                            node->setFunctionIdentifier(saved_yytext.top());
			                                                                            saved_yytext.pop();
			                                                                            node->setFormals((Formals *) $5); // TODO: check
			                                                                            node->setStmtBlock((StmtBlock *) $7);
			                                                                            $$ = node;
			                                                                          }
;

formals:
		| variable {Formals *node = new Formals();
		            node->addVariable((Variable *) $1);
		            $$ = node;}
		| formals T_COMMA variable {    Formals *node = (Formals *) $1;
		                                node->addVariable((Variable *) $2);
		                                $$ = node;
		                           }
;

class_decl: T_CLASS T_ID extends implements T_OCB fields T_CCB {    ClassDecl *node = new ClassDecl();
                                                                    node->setExtends((Extends *) $3);
                                                                    node->setImplements((Implements *) $4);
                                                                    node->setFields((Fields *) $6);
                                                                    $$ = node;
                                                               }
;

extends: {  Extends *node = new Extends();
            $$ = node;
         }
	| T_EXTENDS T_ID {  Extends *node = new Extends();
	                    node->setParentClassId(yytext);
	                    $$ = node;
	                    }
;

implements:
	| T_IMPLEMENTS T_ID {  Implements *node = new Implements();
	                       node->addInterfaceId(yytext);
	                       $$ = node; }
	| implements T_COMMA T_ID { Implements *node = (Implements *) $1;
	                            node->addInterfaceId(yytext);
	                            $$ = node;
	                          }
;

fields: {   Fields *node = new Fields();
            $$ = node; }
	| fields field {    Fields *node = (Fields *) $1;
	                    node->addField( (Field *) $2);
	                    $$ = node;
	                    }
;

field: access_mode variable_decl {  FieldToVariableDecl *node = new FieldToVariableDecl();
                                    node->setAccessMode((AccessMode *) $1);
                                    node->setVariableDecl((VariableDecl *) $2);
                                    $$ = node;
                                 }
	| access_mode function_decl {   FieldToFunctionDecl *node = new FieldToFunctionDecl();
	                                node->setAccessMode((AccessMode *) $1);
	                                node->setFunctionDecl((FunctionDecl *) $2);
	                                $$ = node;
	                            }
;

access_mode: {  AccessMode *node = new AccessMode();
                node->setAccessModeId("public");
                $$ = node;
                }
		| T_PRIVATE {  AccessMode *node = new AccessMode();
                       node->setAccessModeId("private");
                       $$ = node;
                    }

		| T_PROTECTED {  AccessMode *node = new AccessMode();
                         node->setAccessModeId("private");
                         $$ = node;
                      }
		| T_PUBLIC {    AccessMode *node = new AccessMode();
		                node->setAccessModeId("public");
		                $$ = node;
		                }
;

interface_decl: T_INTERFACE T_ID {saved_yytext.push(yytext); } T_OCB proto_types T_CCB {
                                                                                            InterfaceDecl *node = new InterfaceDecl();
                                                                                            node->setInterfaceId(saved_yytext.top());
                                                                                            saved_yytext.pop();
                                                                                            node->setPrototypes((Prototypes *) $5);
                                                                                            $$ = node;
                                                                                       }
;

proto_types: {  Prototypes *node = new Prototypes();
                $$ = node;
                }
		| proto_types proto_type {  Prototypes *node = (Prototypes *) $1;
		                            node->addPrototype((Prototype *) $2);
		                            $$ = node;
		                            }
;

proto_type: type T_ID {saved_yytext.push(yytext); } T_OP formals T_CP T_SEMICOLON {     PrototypeToTypeIdent *node = new PrototypeToTypeIdent();
                                                                                        node->setType((Type *) $1);
                                                                                        node->setPrototypeDeclId(saved_yytext.top());
                                                                                        saved_yytext.pop();
                                                                                        node->setFormals((Formals *) $5);
                                                                                        $$ = node;
                                                                                  }

		| T_VOID T_ID {saved_yytext.push(yytext); } T_OP formals T_CP T_SEMICOLON { PrototypeToVoid *node = new PrototypeToVoid();
		                                                                            node->setPrototypeDeclId(saved_yytext.top());
                                                                                    saved_yytext.pop();
                                                                                    node->setFormals((Formals *) $5);
                                                                                    $$ = node;
                                                                                  }
;

stmt_block: T_OCB variable_decls stmts T_CCB {  StmtBlock *node = new StmtBlock();
                                                node->setVariableDecls((VariableDecls *) $2);
                                                node->setStmts((Stmts *) $3);
                                                $$ = node;}
;

stmts: {    Stmts *node = new Stmts();
            $$ = node;
            }
	| stmt stmts {  Stmts *node = (Stmts *) $2;
	                node->addStmt((Stmt *) $1);
	                $$ = node;
	                }
;

variable_decls: {   VariableDecls *node = new VariableDecls();
                    $$ = node;
                }
		| variable_decls variable_decl {    VariableDecls *node = (VariableDecls *) $1;
		                                    node->addVariableDecl((VariableDecl *) $2);
		                                    $$ = node; }
;

stmt: T_SEMICOLON { Stmt *node = new Stmt();
                    $$ = node;
                    }
	| expr T_SEMICOLON {    StmtToExpr *node = new StmtToExpr();
	                        node->setExpr((Expr *) $1);
	                        $$ = node;
	                   }
	| if_stmt   {   StmtToIfStmt *node = new StmtToIfStmt();
	                node->setIfStmt((IfStmt *) $1);
	                $$ = node;
	            }
	| while_stmt {  StmtToWhileStmt *node = new StmtToWhileStmt();
	                node->setWhileStmt((WhileStmt *) $1);
	                $$ = node;
	                }
	| for_stmt {    StmtToForStmt *node = new StmtToForStmt();
	                node->setForStmt((ForStmt *) $1);
	                $$ = node;
	           }
	| break_stmt {  StmtToBreakStmt *node = new StmtToBreakStmt();
	                node->setBreakStmt((BreakStmt *) $1);
	                $$ = node;
	                }
	| continue_stmt {   StmtToContinueStmt *node = new StmtToContinueStmt();
	                    node->setContinueStmt((ContinueStmt *) $1);
	                    $$ = node;
	                    }
	| return_stmt { StmtToReturnStmt *node = new StmtToReturnStmt();
	                node->setReturnStmt((ReturnStmt *) $1);
	                $$ = node;
	                }
	| print_stmt {  StmtToPrintStmt *node = new StmtToPrintStmt();
	                node->setPrintStmt((PrintStmt *) $1);
	                $$ = node;
	                }
	| stmt_block {  StmtToStmtBlock *node = new StmtToStmtBlock();
	                node->setStmtBlock((StmtBlock *) $1);
	                $$ = node;
	                }
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
