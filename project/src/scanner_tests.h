/****************************************************************************
   scanner_test.h

   cxxTesting on our CDAL (Climate Data Analysis Language) scanner

   Authors: Dean Avery aver0002 and Kevin Wang wang3224

*****************************************************************************/


#include <cxxtest/TestSuite.h>
#include "readInput.h"
#include "scanner.h"
#include <stdio.h>
using namespace std ;    
 
class ScannerTestSuite : public CxxTest::TestSuite 
{
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    Scanner *s ;
    void test_setup_code ( ) {
        s = new Scanner() ;
    }


    /* At least one separate test case for each terminal symbol follows below.
       Each test passes or fails based solely on the regular expression
       (and its corresponding code) for each terminal symbol.  These serve
       as test cases for each element of the enumerated type tokenTypes.
    */

    /* Testing keywords */ 

    void test_terminal_intKwd () { 
        Token *tks = s->scan ("int") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, intKwd) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "int"); 
	tks = tks->next; 	 
	TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
	TS_ASSERT (tks->next == NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "\0") ; 
    }
    void test_terminal_floatKwd () { 
        Token *tks = s->scan ("float") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, floatKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "float"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_boolKwd () { 
        Token *tks = s->scan ("bool") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, boolKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "bool"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_trueKwd () { 
        Token *tks = s->scan ("true") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, trueKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "true"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_falseKwd () { 
        Token *tks = s->scan ("false") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, falseKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "false"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_stringKwd () { 
        Token *tks = s->scan ("string") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, stringKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "string"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_matrixKwd () { 
        Token *tks = s->scan ("matrix") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, matrixKwd) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "matrix"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_letKwd () { 
        Token *tks = s->scan ("let") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, letKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "let"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_inKwd () { 
        Token *tks = s->scan ("in") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, inKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "in"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_endKwd () { 
        Token *tks = s->scan ("end") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, endKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "end"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_ifKwd () { 
        Token *tks = s->scan ("if") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, ifKwd) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "if"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_thenKwd () { 
        Token *tks = s->scan ("then") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, thenKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "then"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_elseKwd () { 
        Token *tks = s->scan ("else") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, elseKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "else"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_repeatKwd () { 
        Token *tks = s->scan ("repeat") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, repeatKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "repeat"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_whileKwd () { 
        Token *tks = s->scan ("while") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, whileKwd) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "while"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_printKwd () { 
        Token *tks = s->scan ("print") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, printKwd) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "print"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_toKwd () { 
        Token *tks = s->scan ("to") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, toKwd) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "to"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
      
      
    /* Testing constants */ 

    void test_terminal_intConst () { 
        Token *tks = s->scan ("7089453") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, intConst) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme,"7089453"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_floatConst () { 
        Token *tks = s->scan ("3.14159") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, floatConst) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "3.14159"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_stringConst () { 
        Token *tks = s->scan ("\"This_String\"") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, stringConst) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "\"This_String\""); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
     }


     /* Testing variable names */

    void test_terminal_variableName1 () { 
        Token *tks = s->scan ("The_Lannisters") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, variableName) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "The_Lannisters"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_variableName2 () { 
        Token *tks = s->scan ("_theLannisters") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, variableName) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "_theLannisters"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_variableName3 () { 
        Token *tks = s->scan ("7_theLannisters") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_DIFFERS (tks->terminal, variableName) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_DIFFERS (tks->lexeme, "7_theLannisters"); 
	TS_ASSERT_DIFFERS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next != NULL) ;
	TS_ASSERT_DIFFERS (tks->next->lexeme, "\0") ; 
    }


    /* Testing punctuation */ 

    void test_terminal_leftParen() { 
        Token *tks = s->scan ("(") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, leftParen) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "("); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_rightParen () { 
        Token *tks = s->scan (")") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, rightParen) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, ")"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_leftCurly () { 
        Token *tks = s->scan ("{") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, leftCurly) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "{"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_rightCurly() { 
        Token *tks = s->scan ("}") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, rightCurly) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "}"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_leftSquare () { 
        Token *tks = s->scan ("[") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, leftSquare) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "["); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_rightSquare () { 
        Token *tks = s->scan ("]") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, rightSquare) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "]"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_semiColon () { 
        Token *tks = s->scan (";") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, semiColon) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, ";"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_colon () { 
        Token *tks = s->scan (":") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, colon) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, ":"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_assign () { 
        Token *tks = s->scan ("=") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, assign) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "="); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_plusSign () { 
        Token *tks = s->scan ("+") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, plusSign) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "+"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_star () { 
        Token *tks = s->scan ("*") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, star) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "*"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_dash () { 
        Token *tks = s->scan ("-") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, dash) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "-"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_forwardSlash () { 
        Token *tks = s->scan ("/") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, forwardSlash) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "/"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_lessThan () { 
        Token *tks = s->scan ("<") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, lessThan) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "<"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_lessThanEqual () { 
        Token *tks = s->scan ("<=") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, lessThanEqual) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "<="); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_greaterThan () { 
        Token *tks = s->scan (">") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, greaterThan) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, ">"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_greaterThanEqual () { 
        Token *tks = s->scan (">=") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, greaterThanEqual) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, ">="); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_equalsEquals () { 
        Token *tks = s->scan ("==") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, equalsEquals) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "=="); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_notEquals () { 
        Token *tks = s->scan ("!=") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, notEquals) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "!="); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }


    /* Testing operators */

    void test_terminal_andOp () { 
        Token *tks = s->scan ("&&") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, andOp) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "&&"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_orOp () { 
        Token *tks = s->scan ("||") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, orOp) ; 
	TS_ASSERT (tks->next != NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "||"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }
    void test_terminal_notOp () { 
        Token *tks = s->scan ("!") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, notOp) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "!"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }


    /* Testing special terminal types */

    void test_terminal_endOfFile () { 
        Token *tks = s->scan ("\0") ; 
	TS_ASSERT (tks !=NULL) ; 
	TS_ASSERT_EQUALS (tks->terminal, endOfFile) ; 
	TS_ASSERT (tks->next == NULL) ; 
	TS_ASSERT_EQUALS (tks->lexeme, "\0"); 

    }
    void test_terminal_lexicalError () { 
        Token *tks = s->scan ("@") ;
	TS_ASSERT (tks !=NULL) ;
	TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
	TS_ASSERT (tks->next != NULL) ;
	TS_ASSERT_EQUALS (tks->lexeme, "@"); 
	TS_ASSERT_EQUALS (tks->next->terminal, endOfFile) ;
	TS_ASSERT (tks->next->next == NULL) ;
	TS_ASSERT_EQUALS (tks->next->lexeme, "\0") ; 
    }



    // Tests for "scan"
    // --------------------------------------------------

    /* Below are some helper functions and sample tests for testing the 
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors (Token *tks) {
        Token *currentToken = tks ;
        while (currentToken != NULL) {
            if (currentToken->terminal == lexicalError) {
                printf("priblem: %s\n",currentToken->lexeme.c_str());
				return false ;
            }
            else {
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned. 
    */
    void scanFileNoLexicalErrors ( const char* filename ) {
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT (noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks ;
        int termIndex = 0 ;
        while (currentToken != NULL && termIndex < numTerms ) {
            if (currentToken->terminal != ts[termIndex]) {
            printf("%i: %i should be %i\n",termIndex,currentToken->terminal , ts[termIndex]);
			fflush(stdout);
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }


    /* Below are the provided test files that your code should also
       pass.
       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.
    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty ( ) {
        Token *tks = s->scan ("  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    void test_scan_empty_comment ( ) {
        Token *tks = s->scan (" /* a comment */ ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }

    // When a lexical error occurs, the scanner creates a token with a 
    // single-character lexeme and lexicalError as the terminal.
   void test_scan_lexicalErrors ( ) {
        Token *tks = s->scan ("$&1  ") ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "$");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
        TS_ASSERT_EQUALS (tks->lexeme, "&");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, intConst) ;
        TS_ASSERT_EQUALS (tks->lexeme, "1");
        tks = tks->next ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
        TS_ASSERT (tks->next == NULL) ;
    }


    // A test for scanning numbers and a variable.
    void test_scan_nums_vars ( ) {
        Token *tks = s->scan (" 123 x 12.34 ") ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { intConst, variableName, floatConst, endOfFile } ;
        TS_ASSERT ( sameTerminals ( tks, 4, ts ) ) ;
    }



    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexemes
       are correct.
     */
    
    void test_scan_bad_syntax_good_tokens ( ) {
        const char *filename = "../samples/bad_syntax_good_tokens.dsl" ;
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        tokenType ts[] = { 
            intConst, intConst, intConst, intConst, 

            stringConst, stringConst, stringConst,

            floatConst, floatConst, floatConst,

                   matrixKwd,



            semiColon, colon,
            leftCurly, leftParen, rightCurly, rightParen,

            plusSign, star, dash, forwardSlash, 

            equalsEquals, lessThanEqual, 
            greaterThanEqual, notEquals, 
            assign,

            variableName, variableName, variableName, variableName, 
            variableName, variableName, variableName,


            intKwd, floatKwd,  stringKwd, 

            endOfFile
       } ;
        int count = 38; 
        TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }

    void test_scan_sample_forestLoss ( ) {
        scanFileNoLexicalErrors ("../samples/forest_loss_v2.dsl") ;
    }


} ;
