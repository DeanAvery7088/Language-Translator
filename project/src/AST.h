//!*************************************************************************************
//!AST.h

//!Authors: Dean Avery aver0002 and Kevin Wang wang3224

//!Classes built for parser.cpp

//!**************************************************************************************

#ifndef Node_H
#define Node_H

#include <string>
#include <iostream> 
#include "scanner.h"

class Node ;


//! Node
class Node {
	
public:
    /*! The unparse method is inherited by each class.  This node return should never execute.*/
    virtual std::string unparse ( ) { return " This should be pure virtual ";} ;
    virtual std::string cppCode ( ) { return " This should be pure virtual ";} ;
    virtual ~Node() { }
} ;

/*! Stmts, Stmt, Decl, Expr represent the non-terminal types used by our grammar.  Each 
   terminal type uses their respective non-terminal through inheritance. 
 */
class Stmts : public Node {} ;
class Stmt : public Node {} ;
class Decl : public Node {} ;
class Expr : public Node {} ;


//! The VarName constructor is passed the string name from prevToken->lexeme
class VarName : public Expr {
public:
    //! Constructor
    VarName(std::string lexeme) {
        varNameLexeme = lexeme;
    }
    //! Unparse returns the lexeme of the variable name as a string
    std::string unparse() {
        return(varNameLexeme);
    }
    //! Unparse cppCode
    std::string cppCode() {
        return(varNameLexeme);
    }
  
private:
    std::string varNameLexeme;
};


//!*************************************************************************************
//!    Program is the root of the AST                                                    
//!*************************************************************************************

//! Program ::= varName '(' ')' '{' Stmts '}' 
class Program : public Node {
public:
    Program(VarName* v, Stmts* s){
        varname = v;
        stmts = s;
    }

    /*! Unparse in the following format:
     * varname (e.g. 'main') () {
     *    << code here is handled recursively by stmts unparse >>
     * }
     */
    std::string unparse() {
        return( varname->unparse() + " () {\n" + stmts->unparse() +"}" );
    }

    std::string cppCode() {
        return( "#include <iostream>\n" \
    		"#include \"Matrix.h\"\n" \
    		"#include <math.h>\n" \
    		"using namespace std;\n" \
    		"int " + varname->cppCode() + " ( ) {\n" + stmts->cppCode() +"}" );
    }

private:  
    VarName *varname;	//! Ptr to varName from grammar line 1
    Stmts *stmts;	//! Ptr to Stmts from grammer line 1
};


//!*************************************************************************************
//!    Stmts Classes                                                               
//!*************************************************************************************

//! The constructor for stmtStmts is passed pointers for nodes stmt and stmts
//! Stmts ::= Stmt Stmts
class StmtStmts : public Stmts {
public:
    StmtStmts(Stmt* s, Stmts* ss) {
        this->stmt = s;
	    this->stmts = ss;
    }
    //! Unparses everything recursively between the curly brackets in main () { ... }
    std::string unparse() {
        return( stmt->unparse() + stmts->unparse() );
    }
    std::string cppCode() {
        return( stmt->cppCode() + stmts->cppCode() );
    }

private:
    Stmt *stmt;		//! Ptr to Stmt node
    Stmts *stmts;	//! Ptr to Stmts node
};

//! Stmts ::= 
//! nothing to match
class EmptyStmts : public Stmts {
public:
    EmptyStmts() {};
    //! Unparse an empty Stmts (grammar line 2)
    std::string unparse() {
        return("");  
    }
    std::string cppCode() {
        return("");
    } 
};



//!*************************************************************************************
//!    Stmt Classes                                                                
//!*************************************************************************************

//! Stmt ::= '{' Stmts '}' This is for while loops ex: while (Expr) stmt -> {Stmts}
class CurlyStmts : public Stmt {
public:
    CurlyStmts(Stmts* ss){
        stmts = ss;
    }
    //! Unparse the curly brackets and stmts (recursively) within
    std::string unparse() {
        return( "{ \n" + stmts->unparse() + "}" );
    }
    std::string cppCode() {
        return( "{ \n" + stmts->cppCode() + "}\n" ); 
    }

private:
    Stmts *stmts;
};

//! Stmt::= 'if' '('Expr')' Stmt
class IfStmt : public Stmt {
public:
    IfStmt(Expr* e, Stmt* s){
        expr = e;
        stmt = s;
    }
	//! Unparse in proper 'if' statement form as denoted in grammar
    std::string unparse() {
        return( "if (" + expr->unparse() + ") " + stmt->unparse() + "\n" );
    }
    std::string cppCode() {
        return( "if (" + expr->cppCode() + ") " + stmt->cppCode() + "\n" );
    }

private:
    Expr *expr;
    Stmt *stmt;
};

//! Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
class IfElseStmt : public Stmt {
public:
    IfElseStmt(Expr* e, Stmt* s1, Stmt* s2){
        expr = e;
	stmt1 = s1;
	stmt2 = s2;
    }
    //! Unparse in proper 'if else' form as denoted in grammar
    std::string unparse() {
        return( "if (" + expr->unparse() + ") " + stmt1->unparse() + " else " + stmt2->unparse() + "\n" );
    }
    //! If else same as if statement only with else curly brackets taken care of by the stmt token curly brackets
    std::string cppCode() {
        return( "if (" + expr->cppCode() + ") " + stmt1->cppCode() + " else " + stmt2->cppCode() );
    }

private:
    Expr *expr;
    Stmt *stmt1;
    Stmt *stmt2;
};

//! Stmt ::= varName '=' Expr ';'  
class AssignmentStmt : public Stmt {
public:
    AssignmentStmt(std::string v, Expr* e) {
        varName = v;
        expr = e;
    }
    //! Unparse in format "varName = 'Expression const';
    std::string unparse() {
        return( varName + " = " + expr->unparse() + ";\n" );
    }
    std::string cppCode() {
        return( varName + " = " + expr->cppCode() + ";\n\n" );
    }

private:
    std::string varName;
    Expr *expr;
};

//! Stmt ::= | varName '[' Expr ':' Expr ']' '=' Expr ';' matrix assignment
class AssignmentMatrixStmt : public Stmt {
public:
    AssignmentMatrixStmt(std::string v, Expr* e1, Expr* e2, Expr* e3){
	varName = v;
	expr1 = e1;
        expr2 = e2;
        expr3 = e3;
    }
    //! Unparse in proper 'matrix assignment' form as denoted in grammar
    std::string unparse() {
        return( varName + "[" + expr1->unparse() + ":" + expr2->unparse() + "] = " + expr3->unparse() + ";" );
    }
    std::string cppCode() {
 	return( "*(" + varName + ".access(" + expr2->cppCode() + ", " + expr3->cppCode() + ")) = " + expr1->cppCode() + " ;\n");
    }

private:
    std::string varName;
    Expr *expr1;
    Expr *expr2;
    Expr *expr3;
};

//! Stmt ::= 'print' '(' Expr ')' ';'
class PrintStmt : public Stmt {
public:
    PrintStmt(Expr* e){
        expr = e;
    }
    //! Unparse in proper 'print' form as denoted in grammar
    std::string unparse() {
        return( "print (" + expr->unparse() + ");\n" );
    }
    std::string cppCode() {
        return( "cout << " + expr->cppCode() + ";\n" );
    }

private:
    Expr *expr;
};

//! Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
class RepeatStmt : public Stmt {
public:
    RepeatStmt(std::string v, Expr* e1, Expr* e2, Stmt* s){
        varName = v;
        expr1 = e1;
        expr2 = e2;
        stmt = s;
    }
    //! Unparse in proper 'repeat' form as denoted in grammar
    std::string unparse() {
        return( "repeat (" + varName + " = " + expr1->unparse() + " to " + expr2->unparse() + ")" + stmt->unparse() + "\n" );
    }
    //! repeat statement becomes a for loop.  The for loop assigns the varname the integer assigned to expr1 and 
    //! will continue to the value of expr2 and then it will parse the actual loop itself in stmt->cppCode() 
    std::string cppCode() {
        return( "for (" +  varName + " = " + expr1->cppCode() + "; " + varName +  " <= " + expr2->cppCode() + "; " + varName + "++) " + stmt->cppCode() + "\n" );
    }

private:
    std::string varName;
    Stmt *stmt;
    Expr *expr1;
    Expr *expr2;
};

//! Stmt ::= 'while' '(' Expr ')' Stmt
class WhileStmt : public Stmt{
public:
    WhileStmt(Expr* e, Stmt* s){
        expr = e;
        stmt = s;
    }
    //! Unparse in proper 'while' statement form as denoted in grammar
    std::string unparse() {
        return( "while (" + expr->unparse() + ") " + stmt->unparse() + "\n" );
    }
    std::string cppCode() {
        return( "while (" + expr->cppCode() + ") " + stmt->cppCode() + "\n" );
    }

private:
    Expr *expr;
    Stmt *stmt;
};

//! Stmt ::= ';' 
class SemiColonStmt : public Stmt{
public:
    SemiColonStmt(){}

    std::string unparse() {
        return(";");
    }
    std::string cppCode() {
        return(";");
    }
};


//!**************************************************************************************
//!    Decl Classes                                                               
//! *************************************************************************************

//! Decl ::= integerKwd varName | floatKwd varName | stringKwd varName | boolKwd varName
class StandardDecl : public Decl {
public:
    StandardDecl(std::string kwd, std::string varName) {
        kwdType = kwd;
        varString = varName;
    }

    //! Unparse standard declaration in format: "type varName;"
    std::string unparse() {
        return( kwdType + " " + varString + ";\n" );
    }
    std::string cppCode() {
        return( kwdType + " " + varString + ";\n" );
    }

private:
    std::string kwdType;
    std::string varString;
};

//! Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr ';'
class MatrixDecl1 : public Decl{
public:
    MatrixDecl1(Expr* v1, Expr* e1, Expr* e2, Expr* v2, Expr* v3, Expr* e3){
        varName1 = v1;
        expr1 = e1;
        expr2 = e2;
        varName2 = v2;
        varName3 = v3;
        expr3 = e3;
    }
    //! Unparse in proper 'matrix declaration' version 1 form as denoted in grammar
    std::string unparse() {
        return( "matrix " + varName1->unparse() + " [" + expr1->unparse() \
	       + ":" + expr2->unparse() + "] " + varName2->unparse() + ": " \
	       + varName3->unparse() + " = " + expr3->unparse() + ";\n" );
    }
    std::string cppCode() {
        return( "matrix " + varName1->cppCode() + " (" + expr1->cppCode() + "," + expr2->cppCode() + ");\n" \
		+ "for (int " + varName2->cppCode() + " = 0; " + varName2->cppCode() + " < " + expr1->cppCode() + "; " + varName2->cppCode() + "++) {\n" \
		    + "for (int " + varName3->cppCode() + " = 0; " + varName3->cppCode() + " < " + expr2->cppCode() + "; " + varName3->cppCode() + "++) {\n" \
		        + "*(" + varName1->cppCode() + ".access(" + varName2->cppCode() + ", " + varName3->cppCode() + ")) = " + expr3->cppCode() + "; \n} }\n\n" );  
    }
   
private:
    Expr *varName1;
    Expr *varName2;
    Expr *varName3;
    Expr *expr1;
    Expr *expr2;
    Expr *expr3;
};

//! Decl ::= 'matrix' varName '=' Expr ';'
class MatrixDecl2 : public Decl{
public:
    MatrixDecl2(Expr* v, Expr* e) {
        varName = v;
        expr = e;
    }
    //! Unparse in proper 'matrix declaration' version 2 form as denoted in grammar
    std::string unparse() {
        return( "matrix " + varName->unparse() + " = " + expr->unparse() + ";\n" );
    }
    std::string cppCode() {  
        return( "matrix " + varName->cppCode() + " ( matrix::" + expr->cppCode() + " ) ; \n\n");
    }

private:
    Expr *varName;
    Expr *expr;
};


//!*************************************************************************************
//!    Expr Classes                                                                
//!*************************************************************************************

//! Expr ::= intConst | floatConst | stringConst
class ConstExpr : public Expr {
public:
    ConstExpr(std::string cs) {
        constStr = cs;
    }
    //! Unparse the integerConst | floatConst | stringConst as a string
    std::string unparse() {
        return(constStr);
    }
    std::string cppCode() {
        return(constStr);
    }

private:
    std::string constStr;
};

//! Expr ::= 'true' | 'false'
class TrueOrFalseExpr : public Expr{
public:
    TrueOrFalseExpr(std::string trueorfalse){
        tf = trueorfalse;
    }
    //! Unparse 'true' or 'false' as a string
    std::string unparse() {
        return(tf);
    }
    std::string cppCode() {
        return(tf);
    }

private:
    std::string tf;
};

//! Handles bitwise operators (+, -, *, /)
class BitwiseOperator : public Expr {
public:
    BitwiseOperator (Expr* e1, std::string op, Expr* e2) {
        expr1 = e1;
        expr2 = e2;
        bwOper = op;
    }
    //! Unparse expression one and expression two separated by the proper bitwise operator
    std::string unparse() {
        return( expr1->unparse() + " " + bwOper + " " + expr2->unparse() );
    }
    std::string cppCode() {
        return( "(" + expr1->cppCode() + " " + bwOper + " " + expr2->cppCode() + ")" );
    }

private:
    Expr *expr1;
    Expr *expr2;
    std::string bwOper;
};

//! Handles logic operators (>, >=, <, <=, ==, !=, &&, ||)
class LogicOperator : public Expr {
public:
    LogicOperator(Expr* e1, std::string op, Expr* e2) {
        expr1 = e1;
        expr2 = e2;
        logicOper = op;
    }
    //! Unparse expression one and expression two separated by the proper logic operator
    std::string unparse() {
        return( expr1->unparse() + " " + logicOper + " " + expr2->unparse() );
    }
    std::string cppCode() {
        return( expr1->cppCode() + " " + logicOper + " " + expr2->cppCode() );
    }

private:
    Expr *expr1;
    Expr *expr2;
    std::string logicOper;
};

//! Expr ::= varName '[' Expr ':' Expr ']'   //MatrixREf
class MatrixRef : public Expr{
public:
    MatrixRef(Expr* v, Expr* e1, Expr* e2){
        varName = v;
        expr1 = e1;
        expr2 = e2;
    }
    //! Unparse in proper 'Matrix Ref' form as denoted in grammar
    std::string unparse() {
        return( varName->unparse() + " [" + expr1->unparse() + ":" + expr2->unparse() + "]" );
    }
    std::string cppCode() {  
        return( "*(" + varName->cppCode() + ".access(" + expr1->cppCode() + ", " + expr2->cppCode () + "))" );
    }

private:
    Expr *varName;
    Expr *expr1;
    Expr *expr2;
};

//! Expr ::= varName '(' Expr ')'        //NestedOrFunctionCall
class NestedOrFuncCall : public Expr{
public:
    NestedOrFuncCall(Expr* v, Expr* e){
        varName = v;
        expr = e;
    }
    //! Unparse in proper 'Nested Or Function Call' form as denoted in grammar
    std::string unparse() {
        return( varName->unparse() + "(" + expr->unparse() + ")" );
    }
    std::string cppCode() {
        //if (expr->cppCode() != "data") { <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        if (varName->cppCode() == "matrixRead" || varName->cppCode() == "ceil"){
            return( varName->cppCode() + "(" + expr->cppCode() + ")" );
	}
        else {
            return(expr->cppCode() + "." + varName->cppCode() + "()");
	}
    } 

private:
    Expr *varName;
    Expr *expr;
};

//! Expr ::= '(' Expr ')'              
class ParenExpr : public Expr{
public:
    ParenExpr(Expr* e){
        expr = e;
    }
    //! Unparse the paren brackets and expression (recursively) within
    std::string unparse() {
        return( "(" + expr->unparse() + ")" );
    }
    std::string cppCode() {
        return( expr->cppCode() );
    } 

private:
    Expr *expr;
};

//! Expr ::= 'let' Stmts 'in' Expr 'end'  //LetExpr
class LetExpr : public Expr{
public:
    LetExpr(Stmts* ss, Expr* e){
        stmts = ss;
        expr = e;
    }
    //! Unparse in proper 'Let Expr' form as denoted in grammar
    std::string unparse() {
        return( "\nlet " + stmts->unparse() + "in " + expr->unparse() + " end" );
    }   
    std::string cppCode() {
      return("({" +  stmts->cppCode() + expr->cppCode() + "; }) " );
    }

private:
    Stmts *stmts;
    Expr *expr;
};

//! Expr ::= 'if' Expr 'then' Expr 'else' Expr    //IfExpr
class IfThenElseExpr : public Expr{
public:
    IfThenElseExpr(Expr* e1, Expr* e2, Expr* e3){
        expr1 = e1;
        expr2 = e2;
        expr3 = e3;
    }
    //! Unparse in proper 'If Then Else' form as denoted in grammar
    std::string unparse() {
        return( "if " + expr1->unparse() + " then " + expr2->unparse() + " else " + expr3->unparse() );
    }
    std::string cppCode() {
	return("( (" + expr1->cppCode() + ") ? " + expr2->cppCode() + " : " + expr3->cppCode() + ")");
    }

private:
    Expr *expr1;
    Expr *expr2;
    Expr *expr3;
};

//! Expr ::= '!' Expr            
class NotExpr : public Expr{
public:
    NotExpr(Expr* e){
        expr = e;
    }
    //! Unparse exclamation mark followed by the expression
    std::string unparse() {
        return( "!" + expr->unparse() );
    }
    std::string cppCode() {
        return( "!" + expr->cppCode() );
    } 

private:
  Expr *expr;
};


#endif
