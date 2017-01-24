/*! A recursive descent parser with operator precedence.

   Author: Eric Van Wyk
   Modified: Robert Edge 
   Modified: Kevin Thomsen
   Modified: Dan Challou 

   Modified (student): Dean Avery aver0002
   Modified (student): Kevin Wang wang3224

   This algorithm is based on the work of Douglas Crockford in "Top
   Down Operator Precedence", a chapter in the book "Beautiful Code".
   Mr. Crockford describes in his chapter how his work is based on an
   algorithm described Vaughan Pratt in "Top Down Operator
   Precedence", presented at the ACM Symposium on Principles of
   Programming Languages.

   Douglas Crockford's chapter is available at 
   http://javascript.crockford.com/tdop/tdop.html

   Vaughan Pratt's paper is available at 
   http://portal.acm.org/citation.cfm?id=512931

   These are both quite interesting works and worth reading if you
   find the problem of parsing to be an interesting one.


   Last modified: Oct 19, 2015.

*/

#include "parser.h"
#include "scanner.h"
#include "extToken.h"
#include <stdio.h>
#include <assert.h>
using namespace std;

//! Parser destructor, uses 'delete' to free memory dynamically located on the heap
Parser::~Parser() {
    if (s) delete s;

    ExtToken *extTokenToDelete;
    currToken = tokens;
    while (currToken) {
        extTokenToDelete = currToken;
        currToken = currToken->next;
        delete extTokenToDelete;
    }

    Token *tokenToDelete;
    Token *currScannerToken = stokens;
    while (currScannerToken) {
        tokenToDelete = currScannerToken;
        currScannerToken = currScannerToken->next;
        delete tokenToDelete;
    }

}

//! Parser constructor initializes all nodes of the AST to NULL
Parser::Parser() {
    currToken = NULL;
    prevToken = NULL;
    tokens = NULL;
    s = NULL;
    stokens = NULL;
}

//! parse takes in a char *text dsl program and returns the parsed result
ParseResult Parser::parse(const char *text) {
    assert(text != NULL);

    ParseResult pr;
    try {
        s = new Scanner();
        stokens = s->scan(text);
        tokens = extendTokenList(this, stokens);

        assert(tokens != NULL);
        currToken = tokens;
        pr = parseProgram();
    }
    //! This is the catch for condition 2 in ast_tests.h 
    catch (string errMsg) {
        pr.ok = false;
        pr.errors = errMsg;
        pr.ast = NULL;
    }
    return pr;
}

/*!
 * parse methods for non-terminal symbols
 * --------------------------------------
 */


//! parseProgram is used to fully parse grammar line 1 and recursively 
//! build the abstract syntax tree (ast)
ParseResult Parser::parseProgram() {
    ParseResult pr;
    //! root
    //! Program ::= varName '(' ')' '{' Stmts '}' 
    //! Match helper function, throws exception if token doesn't match, 
    //! moves to next token if match is true
    match(variableName);   
	
    //! Direct initialization.  The string variable 'name' is initialized 
    //! to the lexeme of the dereferenced pointer 'prevToken'
    string name(prevToken->lexeme); 

    //! Initialize varname from grammar line 1 (i.e. "main")
    VarName* varname = new VarName(name);  
	
    match(leftParen);
    match(rightParen);
    match(leftCurly);
	
    //! Create Stmt Stmts nodes 
    ParseResult prStmts = parseStmts();

    //! Create a stmts root node for all the nodes recursively created 
    //! through prStmts above 
    Stmts* stmts = NULL;
    //! ast is a Node pointer found in parseResult.h
    if (prStmts.ast) {
        stmts = dynamic_cast<Stmts *>(prStmts.ast); 
        if (!stmts) { 
            throw ((string)"Bad cast of State in parseProgram");
	} 
    }

    match(rightCurly);
    match(endOfFile);
	
    //! Fully parsed program to be returned
    pr.ast = new Program(varname, stmts);	
	
    return pr;
}


//! MatrixDecl  
//! Identical purpose of parseDecl, handles special matrix syntax.  
ParseResult Parser::parseMatrixDecl() {
    ParseResult pr;
    match(matrixKwd);
    match(variableName);	
    string name(prevToken->lexeme);
    VarName* varname = new VarName(name);
	
    //! Decl ::= 'matrix' varName '[' Expr ':' Expr ']' varName ':' varName  '=' Expr ';'
    if (attemptMatch(leftSquare)){
        ParseResult prExpr1 = parseExpr(0);  
        match(colon);
        ParseResult prExpr2 = parseExpr(0);
        match(rightSquare);
        ParseResult prVar1 = parseVariableName();
        match(colon);
        ParseResult prVar2 = parseVariableName();
        match(assign);
        ParseResult prExpr3 = parseExpr(0);
        pr.ast = new MatrixDecl1(varname, (Expr *)prExpr1.ast, (Expr *)prExpr2.ast, \
                (Expr *)prVar1.ast, (Expr *)prVar2.ast, (Expr *)prExpr3.ast);
    }
    //! Decl ::= 'matrix' varName '=' Expr ';'
    else if (attemptMatch(assign)){
        ParseResult prExpr = parseExpr(0);
        pr.ast = new MatrixDecl2(varname, (Expr *)prExpr.ast);
    }
    else{
        throw ((string) "Bad Syntax of Matrix Decl in in parseMatrixDecl");
    }
    match(semiColon);

    return pr;
}

//! standardDecl
//! Decl ::= integerKwd varName | floatKwd varName | stringKwd varName | boolKwd varName
ParseResult Parser::parseStandardDecl(){
    ParseResult pr;
    //!ParseResult prType = parseType() ;

    std::string kwdType;

    if (attemptMatch(intKwd)) {
        //! Type ::= intKwd
        kwdType = "int";
    }
    else if (attemptMatch(floatKwd)) {
        //! Type ::= floatKwd
        kwdType = "float";
    }
    else if (attemptMatch(stringKwd)) {
        //! Type ::= stringKwd
        kwdType = "string";
    }
    else if (attemptMatch(boolKwd)) {
        //! Type ::= boolKwd
        kwdType = "bool";
    }
    match(variableName);
    //! From the current standard declaration, parse the variable name (as a string)
    std::string varName = (string)prevToken->lexeme;
    match(semiColon);

    //! Create the new standard declaration with the keyword type and variable name
    pr.ast = new StandardDecl(kwdType, varName);

    return pr;
}

//! Decl 
//! Determines whether to parse a standard declaration or a matrix declaration
ParseResult Parser::parseDecl() {
    ParseResult pr;
    //! Decl :: Matrix variableName ....
    if (nextIs(matrixKwd)){
        pr = parseMatrixDecl();
    }
    //! Decl ::= Type variableName semiColon
    else{
        pr = parseStandardDecl();
    }
    return pr;
}

//! parseStmts results in either a new 'stmt Stmts' or 'emptyStmts' (grammar lines 2 or 3)
ParseResult Parser::parseStmts() {
    ParseResult pr;
    if ( !nextIs(rightCurly) && !nextIs(inKwd) ) {
        //! Stmts ::= Stmt Stmts
        ParseResult prStmt = parseStmt();    //! Node for Stmt
        ParseResult prStmts = parseStmts();  //! Node for Stmts; recurse this function
        //! Create stmtStmts junction, the stmtStmts constructor expects pointers for the 
	//! Stmt and Stmts nodes
        pr.ast = new StmtStmts( (Stmt *)prStmt.ast, (Stmts *)prStmts.ast );
    }
    else {
        //! Stmts ::= 
        //! nothing to match.
        pr.ast = new EmptyStmts();    
    }
    return pr;

}

//! Stmt
ParseResult Parser::parseStmt() {
    ParseResult pr;

    //! Stmt ::= Decl
    if (nextIs(intKwd) || nextIs(floatKwd) || nextIs(matrixKwd) || nextIs(stringKwd)|| nextIs(boolKwd)) {
        pr = parseDecl(); 
    }

    //! Stmt ::= '{' Stmts '}'
    else if (attemptMatch(leftCurly)){
        ParseResult prStmts = parseStmts();
        match(rightCurly);
        pr.ast = new CurlyStmts((Stmts *)prStmts.ast);
    }
    //! Stmt ::= 'if' '(' Expr ')' Stmt
    //! Stmt ::= 'if' '(' Expr ')' Stmt 'else' Stmt
    else if (attemptMatch(ifKwd)){
        match(leftParen);
        ParseResult prExpr = parseExpr(0);
        match(rightParen);
        ParseResult prStmt = parseStmt();

	//! Handle if/else statement
        if (attemptMatch(elseKwd)){
            ParseResult prElseStmt = parseStmt();
            pr.ast = new IfElseStmt((Expr *)prExpr.ast, (Stmt *)prStmt.ast, (Stmt *)prElseStmt.ast);
        }
		//! Handle only if statement
		else {
		    pr.ast = new IfStmt((Expr*)prExpr.ast, (Stmt*)prStmt.ast);
		}
    }
    //! Stmt ::= varName '=' Expr ';'  | varName '[' Expr ':' Expr ']' '=' Expr ';'
    else if (attemptMatch(variableName)) {
        std::string varName = prevToken->lexeme.c_str();
        bool matrix = false;
        ParseResult prMatrixExpr1;
        ParseResult prMatrixExpr2;

        //! Determine whether it's a regular assignment or matrix assignment 
        if (attemptMatch(leftSquare)) {
            matrix = true;
            prMatrixExpr1 = parseExpr(0);   //! Parse the first matrix expression
            match(colon);
            prMatrixExpr2 = parseExpr(0);   //! Parse the second matrix expression
            match(rightSquare);
        }
        match(assign);
        ParseResult prExpr = parseExpr(0);
        Expr* expr = NULL;
        //! ast is the pointer to the Node of prExpr (ParseResult)
        if (prExpr.ast) {
            expr = dynamic_cast<Expr *>(prExpr.ast); 
            if (!expr) { 
                throw ((string)"Bad cast of State in parseStatement"); 
	    }
        }

        match(semiColon);
	//! Handle matrix assignment statement
        if (matrix){
            pr.ast = new AssignmentMatrixStmt(varName, (Expr*)prExpr.ast, (Expr*)prMatrixExpr1.ast, \
					      (Expr*)prMatrixExpr2.ast);
        }
	//! Handle regular assignment statement
        else {
            pr.ast = new AssignmentStmt(varName, expr);
        }
    }

    //! Stmt ::= 'print' '(' Expr ')' ';'
    else if (attemptMatch(printKwd)) {
        match(leftParen);
        ParseResult prExpr = parseExpr(0);
        match(rightParen);
        match(semiColon);
        pr.ast = new PrintStmt((Expr *)prExpr.ast);
    }
    //! Stmt ::= 'repeat' '(' varName '=' Expr 'to' Expr ')' Stmt
    else if (attemptMatch(repeatKwd)) {
        match(leftParen);
        match(variableName);
        std::string varName = prevToken->lexeme;
        match(assign);
        ParseResult prExpr1 = parseExpr(0);
        match(toKwd);
        ParseResult prExpr2 = parseExpr(0);
        match(rightParen);
        ParseResult prStmt = parseStmt();
        pr.ast = new RepeatStmt(varName, (Expr *)prExpr1.ast, (Expr *)prExpr2.ast, (Stmt *)prStmt.ast);
    }
    //! Stmt ::= 'while' '(' Expr ')' Stmt
    else if (attemptMatch(whileKwd)) {
        match(leftParen);
        ParseResult prExpr = parseExpr(0);
        match(rightParen);
        ParseResult prStmt = parseStmt();
        pr.ast = new WhileStmt((Expr*)prExpr.ast, (Stmt*)prStmt.ast);
    }
    //! Stmt ::= ';
    else if (attemptMatch(semiColon)) {
        //! parsed a skip
        pr.ast = new SemiColonStmt();
    }
    else{
        throw (makeErrorMsg(currToken->terminal) + " while parsing a statement");
    }
    //! Stmt ::= variableName assign Expr semiColon
    return pr;
}

//! Expr
ParseResult Parser::parseExpr(int rbp) {
    /*! Examine current token, without consuming it, to call its associated 
       parse methods.  The ExtToken objects have 'nud' and 'led' methods 
       that are dispatchers that call the appropriate parse methods.
     */
    ParseResult left = currToken->nud();

    while (rbp < currToken->lbp()) {
        left = currToken->led(left);
    }
    return left;
}


/*!
 * parse methods for Expr productions
 * ----------------------------------
 */

//! Expr ::= trueKwd
ParseResult Parser::parseTrueKwd() {
    ParseResult pr;
    match(trueKwd);
    pr.ast = new TrueOrFalseExpr(prevToken->lexeme.c_str());
    return pr;
}

//! Expr ::= falseKwd
ParseResult Parser::parseFalseKwd() {
    ParseResult pr;
    match(falseKwd);
    pr.ast = new TrueOrFalseExpr(prevToken->lexeme.c_str());
    return pr;
}

//! Expr ::= intConst
ParseResult Parser::parseIntConst() {
    ParseResult pr;
    match(intConst);
    pr.ast = new ConstExpr(prevToken->lexeme.c_str());
    return pr;
}

//! Expr ::= floatConst
ParseResult Parser::parseFloatConst() {
    ParseResult pr;
    match(floatConst);
    pr.ast = new ConstExpr(prevToken->lexeme.c_str());
    return pr;
}

//! Expr ::= stringConst
ParseResult Parser::parseStringConst() {
    ParseResult pr;
    match(stringConst);
    pr.ast = new ConstExpr(prevToken->lexeme.c_str());
    return pr;
}

//! Expr ::= variableName .....
ParseResult Parser::parseVariableName() {
    ParseResult pr;
    match(variableName);
	
    string name(prevToken->lexeme);
    VarName* varname = new VarName(name);

    //! Expr ::= variableName '[' Expr ':' Expr ']'
    //! MatrixRef
    if (attemptMatch(leftSquare)){
        ParseResult prExpr1 = parseExpr(0);
        match(colon);
        ParseResult prExpr2 = parseExpr(0);
        match(rightSquare);
        pr.ast = new MatrixRef(varname, (Expr *)prExpr1.ast, (Expr *)prExpr2.ast);
    }
    //! Expr ::= varableName '(' Expr ')'  
    //! NestedOrFunctionCall
    else if (attemptMatch(leftParen)){
        ParseResult prExpr3 = parseExpr(0);
        match(rightParen);
        pr.ast = new NestedOrFuncCall(varname, (Expr *)prExpr3.ast);
    }
    //! Expr := variableName
    else{
        //! variable 
        pr.ast = new VarName((std::string)(prevToken->lexeme.c_str()));
    }

    return pr;
}


//! Expr ::= '(' Expr ')'
ParseResult Parser::parseNestedExpr() {
    ParseResult pr;
    match(leftParen);
    ParseResult prExpr = parseExpr(0);
    match(rightParen);
    pr.ast = new ParenExpr((Expr *)prExpr.ast);
    return pr;
}

//! Expr ::= 'if' Expr 'then' Expr 'else' Expr  
ParseResult Parser::parseIfExpr(){
    ParseResult pr;
    match(ifKwd);
    ParseResult prExpr1 = parseExpr(0);
    match(thenKwd);
    ParseResult prExpr2 = parseExpr(0);
    match(elseKwd);
    ParseResult prExpr3 = parseExpr(0);	
    pr.ast = new IfThenElseExpr((Expr *)prExpr1.ast, (Expr *)prExpr2.ast, (Expr *)prExpr3.ast);
    return pr;
}

//! Expr ::= 'let' Stmts 'in' Expr 'end' 
ParseResult Parser::parseLetExpr(){
    ParseResult pr;
    match(letKwd);	
    ParseResult prStmts = parseStmts();
    match(inKwd);	
    ParseResult prExpr = parseExpr(0);
    match(endKwd);
    pr.ast = new LetExpr((Stmts *)prStmts.ast, (Expr *)prExpr.ast);
    return pr;
}

//! Expr ::= '!' Expr 
ParseResult Parser::parseNotExpr() {
    ParseResult pr;
    match(notOp);
    ParseResult prExpr = parseExpr(0);
    pr.ast = new NotExpr((Expr *)prExpr.ast);
    return pr;
}
//! Expr ::= Expr '+' Expr
ParseResult Parser::parseAddition(ParseResult prLeft) {
    //! parser has already matched left expression 
    ParseResult pr;
    //! Create the node for the left expression 
    Expr* leftExpr = NULL; 
    if (prLeft.ast) {
        leftExpr = dynamic_cast<Expr *>(prLeft.ast);  
        if (!leftExpr) { 
            throw ((string)"Bad cast of State in parseAddition"); 
	}
    }
    match ( plusSign ) ;
    //! Create the node and set up the right expression
    ParseResult prRight = parseExpr(prevToken->lbp());
    Expr* rightExpr = NULL ; 
    if (prRight.ast) {
        rightExpr = dynamic_cast<Expr *>(prRight.ast) ; 
        if (!rightExpr) {
            throw ((string)"Bad cast of State in parseAddition"); 
	}
    }
    pr.ast = new BitwiseOperator(leftExpr, "+", rightExpr);
    return pr ;
}

//! Expr ::= Expr '*' Expr
ParseResult Parser::parseMultiplication(ParseResult prLeft) {
    //! parser has already matched left expression 
    ParseResult pr;
    //! Create the node for the left expression 
    Expr* leftExpr = NULL;
    if (prLeft.ast) {
        leftExpr = dynamic_cast<Expr *>(prLeft.ast);
        if (!leftExpr) {
            throw ((string)"Bad cast of State in parseMultiplication");
	}
    }
    match(star);
    //! Create the node and set up the right expression
    ParseResult prRight = parseExpr(prevToken->lbp());
    Expr* rightExpr = NULL;
    if (prRight.ast) {
        rightExpr = dynamic_cast<Expr *>(prRight.ast);
        if (!rightExpr) {
            throw ((string)"Bad cast of State in parseMultiplication");
	}
    }
    pr.ast = new BitwiseOperator(leftExpr, "*", rightExpr);
    return pr;
}

//! Expr ::= Expr '-' Expr
ParseResult Parser::parseSubtraction(ParseResult prLeft) {
    //! parser has already matched left expression 
    ParseResult pr;
    //! Create the node for the left expression 
    Expr* leftExpr = NULL;
    if (prLeft.ast) {
        leftExpr = dynamic_cast<Expr *>(prLeft.ast);
        if (!leftExpr) {
            throw ((string)"Bad cast of State in parseSubtraction");
	}
    }
    match(dash);
    //! Create the node and set up the right expression
    ParseResult prRight = parseExpr(prevToken->lbp());
    Expr* rightExpr = NULL;
    if (prRight.ast) {
        rightExpr = dynamic_cast<Expr *>(prRight.ast);
        if (!rightExpr) {
            throw ((string)"Bad cast of State in parseSubtraction");
	}
    }
    pr.ast = new BitwiseOperator(leftExpr, "-", rightExpr);
    return pr;
}

//! Expr ::= Expr '/' Expr
ParseResult Parser::parseDivision(ParseResult prLeft) {
    //! parser has already matched left expression 
    ParseResult pr;
    //! Create the node for the left expression 
    Expr* leftExpr = NULL;
    if (prLeft.ast) {
        leftExpr = dynamic_cast<Expr *>(prLeft.ast);
        if (!leftExpr) {
            throw ((string)"Bad cast of State in parseDivision");
	}
    }
    match(forwardSlash);
    //! Create the node and set up the right expression
    ParseResult prRight = parseExpr(prevToken->lbp());
    Expr* rightExpr = NULL;
    if (prRight.ast) {
        rightExpr = dynamic_cast<Expr *>(prRight.ast);
        if (!rightExpr) {
            throw ((string)"Bad cast of State in parseDivision");
	}
    }
    pr.ast = new BitwiseOperator(leftExpr, "/", rightExpr);
    return pr;
}

//! Expr ::= Expr equalEquals Expr
//! Expr ::= Expr lessThanEquals Expr
//! Expr ::= Expr greaterThanEquals Expr
//! Expr ::= Expr notEquals Expr
//! Expr ::= Expr leftAngle Expr
//! Expr ::= Expr rightAngle Expr
/*! Notice that for relational operators we use just one parse
   function.  This shows another possible means for implementing
   expressions, as opposed to the method used for arithmetic
   expressions in which each operation has its own parse method.  It
   will depend on what we do in iteration 3 in building an abstract
   syntax tree to decide which method is better.
*/
ParseResult Parser::parseRelationalExpr(ParseResult prLeft) {
    //! parser has already matched left expression 
    ParseResult pr;
    //! Create the node for the left expression
    Expr* leftExpr = NULL;
    if (prLeft.ast) {
        leftExpr = dynamic_cast<Expr *>(prLeft.ast);
        if (!leftExpr) {
            throw ((string)"Bad cast of State in parseRelationalExpr");
	}
    }
    nextToken();
    //! just advance token, since examining it in parseExpr caused
    //! this method being called.
    string logicOp = prevToken->lexeme;
    //! Create the node and set up the right expression
    ParseResult prRight = parseExpr(prevToken->lbp());
    Expr* rightExpr = NULL;
    if (prRight.ast) {
        rightExpr = dynamic_cast<Expr *>(prRight.ast);
        if (!rightExpr) {
            throw ((string)"Bad cast of State in parseRelationalExpr");
	}
    }
    pr.ast = new LogicOperator(leftExpr, logicOp, rightExpr);
    return pr;
}


//! Helper function used by the parser.

void Parser::match(tokenType tt) {
    if (!attemptMatch(tt)) {
        throw (makeErrorMsgExpected(tt));
    }
}

//! Verify that the token matches, if so, advance to the next token
bool Parser::attemptMatch(tokenType tt) {
    if (currToken->terminal == tt) {
        nextToken();
        return true;
    }
    return false;
}

bool Parser::nextIs(tokenType tt) {
    return currToken->terminal == tt;
}

//! Advance prevToken and currToken if no errors are found
void Parser::nextToken() {
    if (currToken == NULL)
        throw (string("Internal Error: should not call nextToken in unitialized state"));
    else
        if (currToken->terminal == endOfFile && currToken->next == NULL) {
            prevToken = currToken;
        }
    else if (currToken->terminal != endOfFile && currToken->next == NULL) {
        throw (makeErrorMsg("Error: tokens end with endOfFile"));
    }
    else {
        prevToken = currToken;
        currToken = currToken->next;
    }
}

string Parser::terminalDescription(tokenType terminal) {
    Token *dummyToken = new Token("", terminal, NULL);
    ExtToken *dummyExtToken = extendToken(this, dummyToken);
    string s = dummyExtToken->description();
    delete dummyToken;
    delete dummyExtToken;
    return s;
}

string Parser::makeErrorMsgExpected(tokenType terminal) {
    string s = (string) "Expected " + terminalDescription(terminal) +
               " but found " + currToken->description();
    return s;
}

string Parser::makeErrorMsg(tokenType terminal) {
    string s = "Unexpected symbol " + terminalDescription(terminal);
    return s;
}

string Parser::makeErrorMsg(const char *msg) {
    return msg;
}

