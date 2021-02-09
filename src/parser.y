%define parse.trace

%code requires {
#include "SyntaxTree/SyntaxTree.h"
#define YYSTYPE Node *

using namespace SyntaxTree;
}

%{

#include <iostream>
#include <fstream>
#include "parser.tab.h"

#include "lex.yy.h"
#include "SyntaxTree/SyntaxTree.h"

using namespace SymbolTable;
using namespace std;

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
%token T_MUL T_DIV T_PERCENT T_PLUS T_MINUS T_CMPL T_CMPLE T_CMPG T_CMPGE T_ASSIGN T_CMPE T_CMPNE T_OR T_AND T_NOT T_SEMICOLON T_COMMA T_DOT T_OB T_CB T_OP T_CP T_OCB T_CCB
%token T_NEWLINE T_UNDEFINED

%token T_ID
%token T_INTLITERAL
%token T_DOUBLELITERAL
%token T_STRINGLITERAL
%token T_BOOLEANLITERAL

%right T_ASSIGN
%left T_OR
%left T_AND
%left T_CMPE T_CMPNE
%left T_CMPL T_CMPLE T_CMPG T_CMPGE
%left T_PLUS T_MINUS
%left T_MUL T_DIV T_PERCENT
%left T_DOT

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
                        node->setId(((Token *)$2)->getLexeme());
                        $$ = node; }
;

type: primitive_type { $$ = $1; }
	| T_ID {    Type *node = new Type();
	            node->setTypeNameId(((Token *)$1)->getLexeme());
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
		| T_ID T_OB T_CB { Type *node = new Type();
                           node->setTypeNameId(((Token *)$1)->getLexeme());
                           node->setDimension(1);
                           $$ = node;
                         }
		| array_type T_OB T_CB {    Type *node = (Type *) $1;
		                            node->incrementDimension();
		                            $$ = node;
		                       }
;

function_decl: type T_ID T_OP formals T_CP stmt_block { FunctionDeclToTypeIdent *node = new FunctionDeclToTypeIdent();
                                                        node->setFunctionIdentifier(((Token *)$2)->getLexeme());
                                                        node->setFormals((Formals *) $4);
                                                        node->setStmtBlock((StmtBlock *) $6);
                                                        $$ = node;
                                                      }
			| T_VOID T_ID T_OP formals T_CP stmt_block {    FunctionDeclToVoidIdent *node = new FunctionDeclToVoidIdent();
                                                            node->setFunctionIdentifier(((Token *)$2)->getLexeme());
                                                            node->setFormals((Formals *) $4); // TODO: check
                                                            node->setStmtBlock((StmtBlock *) $6);
                                                            $$ = node;
                                                       }
;

formals:           {$$ = new Formals();}
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
	                    node->setParentClassId(((Token *)$2)->getLexeme());
	                    $$ = node;
	                    }
;

implements:
	| T_IMPLEMENTS T_ID {  Implements *node = new Implements();
	                       node->addInterfaceId(((Token *)$2)->getLexeme());
	                       $$ = node; }
	| implements T_COMMA T_ID { Implements *node = (Implements *) $1;
	                            node->addInterfaceId(((Token *)$3)->getLexeme());
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

interface_decl: T_INTERFACE T_ID T_OCB proto_types T_CCB {  InterfaceDecl *node = new InterfaceDecl();
                                                            node->setInterfaceId(((Token *)$2)->getLexeme());
                                                            node->setPrototypes((Prototypes *) $4);
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

proto_type: type T_ID T_OP formals T_CP T_SEMICOLON {   PrototypeToTypeIdent *node = new PrototypeToTypeIdent();
                                                        node->setType((Type *) $1);
                                                        node->setPrototypeDeclId(((Token *)$2)->getLexeme());
                                                        node->setFormals((Formals *) $4);
                                                        $$ = node;
                                                    }

		| T_VOID T_ID T_OP formals T_CP T_SEMICOLON {   PrototypeToVoid *node = new PrototypeToVoid();
                                                        node->setPrototypeDeclId(((Token *)$2)->getLexeme());
                                                        node->setFormals((Formals *) $4);
                                                        $$ = node;
                                                    }
;

stmt_block: T_OCB variable_decls stmts T_CCB {  StmtBlock *node = new StmtBlock();
                                                node->setVariableDecls((VariableDecls *) $2);
                                                ((Stmts *) $3)->reverseStmts();
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

if_stmt: T_IF T_OP expr T_CP stmt { IfStmt *node = new IfStmt();
                                    node->setConditionalExpr((Expr *) $3);
                                    node->setTrueStmt((Stmt *) $5);
                                    node->setFalseStmt(nullptr);
                                    $$ = node;
                                    }
		| T_IF T_OP expr T_CP stmt T_ELSE stmt {    IfStmt *node = new IfStmt();
		                                            node->setConditionalExpr((Expr *) $3);
                                                    node->setTrueStmt((Stmt *) $5);
                                                    node->setFalseStmt((Stmt *) $7);
                                                    $$ = node;
                                                    }

;

while_stmt: T_WHILE T_OP expr T_CP stmt {   WhileStmt *node = new WhileStmt();
                                            node->setConditionalExpr((Expr *) $3);
                                            node->setStmt((Stmt *) $5);
                                            $$ = node;
                                            }
;

expr2: {    $$ = nullptr;}
	| expr {    Expr *node = (Expr *) $1;
	            $$ = node;
	            }
;

for_stmt: T_FOR T_OP expr2 T_SEMICOLON expr T_SEMICOLON expr2 T_CP stmt {   ForStmt *node = new ForStmt();
                                                                            node->setForInit((Expr *) $3);
                                                                            node->setForCondition((Expr *) $5);
                                                                            node->setForStep((Expr *) $7);
                                                                            node->setStmt((Stmt *) $9);
                                                                            $$ = node;
                                                                            }
;

return_stmt: T_RETURN expr2 T_SEMICOLON {   ReturnStmt *node = new ReturnStmt();
                                            node->setExpr((Expr *) $2);
                                            $$ = node;
                                            }
;

break_stmt: T_BREAK T_SEMICOLON {   BreakStmt *node = new BreakStmt();
                                    $$ = node;
                                    }
;

continue_stmt: T_CONTINUE T_SEMICOLON { ContinueStmt *node = new ContinueStmt();
                                        $$ = node;
                                        }
;

print_stmt: T_PRINT T_OP actuals1 T_CP T_SEMICOLON {    PrintStmt *node = new PrintStmt();
                                                        node->setActuals((Actuals *) $3);
                                                        $$ = node;
                                                        }
;

actuals1: expr {    Actuals *node = new Actuals();
                    node->addExpression((Expr *) $1);
                    $$ = node;
                    }
	| actuals1 T_COMMA expr {   Actuals *node = (Actuals *) $1; // TODO: may need to be reversed
	                            node->addExpression((Expr *) $3);
	                            $$ = node;
	                            }
;

expr: lvalue T_ASSIGN expr {    ExprToAssignmentExpr *node = new ExprToAssignmentExpr();
                                node->setLValue((LValue *) $1);
                                node->setExpr((Expr *) $3);
                                $$ = node;
                                }
	| constant {    ExprToConstant *node = new ExprToConstant();
	                node->setConstant((Constant *) $1);
	                $$ = node;
	                }
	| lvalue {  ExprToLValue *node = new ExprToLValue();
	            node->setLValue((LValue *) $1);
	            $$ = node;
	            }
	| T_THIS {  ExprToThis *node = new ExprToThis();
	            $$ = node; }
	| call {    ExprToCall *node = new ExprToCall();
	            node->setCall((Call *) $1);
	            $$ = node;
	            }
	| T_OP expr T_CP {  ExprToParenthesisExpr *node = new ExprToParenthesisExpr();
	                    node->setExpr((Expr *) $2);
	                    $$ = node;
	                    }
	| expr T_MUL expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                      	   node->setOperatorSymbol("*");
                      	   node->setOperand1((Expr *) $1);
                      	   node->setOperand2((Expr *) $3);
                      	   $$ = node;
                      	   }
	| expr T_DIV expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                      	   node->setOperatorSymbol("/");
                      	   node->setOperand1((Expr *) $1);
                      	   node->setOperand2((Expr *) $3);
                      	   $$ = node;
                      	   }
	| expr T_PERCENT expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                         	   node->setOperatorSymbol("%");
                         	   node->setOperand1((Expr *) $1);
                         	   node->setOperand2((Expr *) $3);
                         	   $$ = node;
                         	   }
	| expr T_PLUS expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
	                        node->setOperatorSymbol("+");
	                        node->setOperand1((Expr *) $1);
	                        node->setOperand2((Expr *) $3);
	                        $$ = node;
	                        }
	| expr T_MINUS expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                        	 node->setOperatorSymbol("-");
                        	 node->setOperand1((Expr *) $1);
                        	 node->setOperand2((Expr *) $3);
                        	 $$ = node;
                        	 }
	| T_MINUS expr {    ExprToUnaryOperation *node = new ExprToUnaryOperation();
	                    node->setOperatorSymbol("-");
	                    node->setOperand((Expr *) $2);
	                    $$ = node;
	                    }
	| expr T_CMPL expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                            node->setOperatorSymbol("<");
                            node->setOperand1((Expr *) $1);
                            node->setOperand2((Expr *) $3);
                            $$ = node;
                            }
	| expr T_CMPLE expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                             node->setOperatorSymbol("<=");
                             node->setOperand1((Expr *) $1);
                             node->setOperand2((Expr *) $3);
                             $$ = node;
                             }
	| expr T_CMPG expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                            node->setOperatorSymbol(">");
                            node->setOperand1((Expr *) $1);
                            node->setOperand2((Expr *) $3);
                            $$ = node;
                        }
	| expr T_CMPGE expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                             node->setOperatorSymbol(">=");
                             node->setOperand1((Expr *) $1);
                             node->setOperand2((Expr *) $3);
                             $$ = node;
                             }
	| expr T_CMPE expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                            node->setOperatorSymbol("==");
                            node->setOperand1((Expr *) $1);
                            node->setOperand2((Expr *) $3);
                            $$ = node;
                            }
	| expr T_CMPNE expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                             node->setOperatorSymbol("!=");
                             node->setOperand1((Expr *) $1);
                             node->setOperand2((Expr *) $3);
                             $$ = node;
                             }
	| expr T_AND expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                           node->setOperatorSymbol("&&");
                           node->setOperand1((Expr *) $1);
                           node->setOperand2((Expr *) $3);
                           $$ = node;
                           }
	| expr T_OR expr {    ExprToBinaryOperation *node = new ExprToBinaryOperation();
                           node->setOperatorSymbol("||");
                           node->setOperand1((Expr *) $1);
                           node->setOperand2((Expr *) $3);
                           $$ = node;
                           }
	| T_NOT expr {    ExprToUnaryOperation *node = new ExprToUnaryOperation();
                 	  node->setOperatorSymbol("!");
                 	  node->setOperand((Expr *) $2);
                 	  $$ = node;
                 	  }
	| T_READINTEGER T_OP T_CP { ExprToReadInteger *node = new ExprToReadInteger();
	                            $$ = node;
	                            }
	| T_READLINE T_OP T_CP  {   ExprToReadLine *node = new ExprToReadLine();
	                            $$ = node;
	                            }
	| T_NEW T_ID    {   ExprToNew *node = new ExprToNew();
	                    $$ = node;
	                    }
	| T_NEWARRAY T_OP expr T_COMMA type T_CP {  ExprToNewArray *node = new ExprToNewArray();
	                                            node->setExpr((Expr *) $3);
	                                            node->setType((Type *) $5);
	                                            $$ = node;
	                                            }
	| T_ITOD T_OP expr T_CP {   ExprToITOD *node = new ExprToITOD();
	                            $$ = node;
	                            }
	| T_DTOI T_OP expr T_CP {   ExprToDTOI *node = new ExprToDTOI();
	                            $$ = node;
	                            }
	| T_ITOB T_OP expr T_CP {   ExprToITOB *node = new ExprToITOB();
	                            $$ = node;
	                            }
	| T_BTOI T_OP expr T_CP {   ExprToBTOI *node = new ExprToBTOI();
	                            $$ = node;
	                            }
;

lvalue: T_ID {  LValueToIdent *node = new LValueToIdent();
                node->setId(((Token *)$1)->getLexeme());
                $$ = node;
             }
	| expr T_DOT T_ID { LValueToFieldAccess *node = new LValueToFieldAccess();
	                    node->setExpr((Expr *) $1);
	                    node->setId(((Token *)$2)->getLexeme());
	                    $$ = node;
	                    }
	| expr T_OB expr T_CB { LValueToArray *node = new LValueToArray();
	                        node->setExprArrayName((Expr *) $1);
	                        node->setExprArrayIndex((Expr *) $3);
	                        $$ = node;
	                        }
;

call: T_ID  T_OP actuals T_CP {     CallToFunctionCall *node = new CallToFunctionCall();
                                    node->setFunctionId(((Token *)$1)->getLexeme());
                                    node->setActuals((Actuals *) $3);
                                    $$ = node;
                              }
	| expr T_DOT T_ID T_OP actuals T_CP {   CallToMethodCall *node = new CallToMethodCall();
	                                        node->setMethodIdent((Expr *) $1);
	                                        node->setActuals((Actuals *) $5);
	                                        $$ = node;
	                                        }

;

actuals: {  Actuals *node = nullptr;
            $$ = node;
            }
	| actuals1  {   Actuals *node = (Actuals *) $1;
	                $$ = node;
	                }
;

constant: T_INTLITERAL {    Constant *node = new Constant();
                            node->setConstantType(ConstantType::INT);
                            node->setConstantValue(((Token *)$1)->getLexeme());
                            $$ = node;
                        }
		| T_DOUBLELITERAL {    Constant *node = new Constant();
                               node->setConstantType(ConstantType::DOUBLE);
                               node->setConstantValue(((Token *)$1)->getLexeme());
                               $$ = node;
                           }
		| T_BOOLEANLITERAL {    Constant *node = new Constant();
                                node->setConstantType(ConstantType::BOOL);
                                node->setConstantValue(((Token *)$1)->getLexeme());
                                $$ = node;
                           }
		| T_STRINGLITERAL {    Constant *node = new Constant();
                               node->setConstantType(ConstantType::STRING);
                               node->setConstantValue(((Token *)$1)->getLexeme());
                               $$ = node;
                          }
		| T_NULL        {   Constant *node = new Constant();
		                    node->setConstantType(ConstantType::NULL_POINTER);
		                    node->setConstantValue(((Token *)$1)->getLexeme());
		                    $$ = node;
		                    }
;



%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	fprintf(output_file, "Syntax Error\n");
	exit(0);
}
