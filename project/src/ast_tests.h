#include <cxxtest/TestSuite.h>
#include <iostream> 
#include "parser.h"
#include "readInput.h"

#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std ;

class AstTestSuite : public CxxTest::TestSuite 
{
public:

    Parser p ;
    ParseResult pr ;

    char **makeArgs ( const char *a0, const char *a1) {
        char **aa = (char **) malloc (sizeof(char *) * 2) ;
        aa[0] = (char *) malloc ( sizeof(char) * (strlen(a0) + 1) ) ;
        strcpy (aa[0], a0 ) ;
        aa[1] = (char *) malloc ( sizeof(char) * (strlen(a1) + 1) ) ;
        strcpy (aa[1], a1 ) ;
        return aa ;
    }

    void writeFile ( const string text, const string filename ) {
        ofstream out(filename.c_str()); 
        out << (string) text << endl ;
    }

    char *readFile ( const char *fn ) {
        return readInput (2, makeArgs("translator", fn) ) ;
    }



    void unparse_tests ( string file ) {
        string path = "../samples/" + file ; 

        //! 1. Test that the file can be parsed.
        ParseResult pr1 = p.parse ( 
            readInput (2, makeArgs("translator", path.c_str() ) ) 
          ) ;
        TSM_ASSERT ( file + " failed to parse.", pr1.ok ) ;

        //! 2. Verify that the ast field is not null
        TSM_ASSERT ( file + " failed to generate an AST.", pr1.ast != NULL );

        //! 3. Verify that the "unparsing" is non-empty.
        string up1 = pr1.ast->unparse() ;
        writeFile(up1,(path+"up1").c_str());
        TSM_ASSERT ( file + " failed to generate non-empty unparsing.", 
                     up1.length() > 0 ) ;

        //! 4. Verify that the un-parsed string can be parsed.
        ParseResult pr2 = p.parse ( up1.c_str() ) ;
        TSM_ASSERT ( file + " failed to parse the first un-parsing.", 
                     pr2.ok ) ;

        //! 5. Verify that the ast field is not null after first unparsing
        TSM_ASSERT ( file + " first unparsing failed to generate an AST.", 
                     pr2.ast != NULL );

        //! 6. Verify that this second unparsing can be parsed.
        string up2 = pr2.ast->unparse() ;
        writeFile(up2,(path+"up2").c_str());
        ParseResult pr3 = p.parse ( up2.c_str() ) ;
        TSM_ASSERT ( file + " failed to pares the second un-parsing.",
                     pr3.ok ) ;

        string up3 = pr3.ast->unparse() ;
        writeFile(up3,(path+"up3").c_str());
        //! 7. Verify that the first and second unparsings are the same.
        TSM_ASSERT_EQUALS ( file + " unparse-1 != unparse-2.", up1, up2 ) ;
        //! 8. Verifty that the second and third unparsings are the same.
        TSM_ASSERT_EQUALS ( file + " unparse-2 != unparse-3.", up2, up3 ) ;
    }

    /*! The approximate order in which the tests were implemented and passed:        
                                IMPLEMENTED    PASSED
	--------------------------------------------------------------------
        1) test_iter3_simple1     11/8/15      11/8/15
	2) test_mysample          11/8/15      11/8/15
        3) test_iter3_simple2     11/8/15      11/10/15
        4) test_sample_1          11/9/15      11/10/15
        5) test_iter3_simple3     11/9/15      11/11/15
        6) test_sample_2          11/10/15     11/11/15
        7) test_sample_3          11/11/15     11/11/15
        8) test_sample_4          11/11/15     11/11/15
        9) test_sample_5          11/11/15     11/12/15
       10) test_forest_loss       11/12/15     11/12/15
       11) test_sample_6          11/12/15     11/12/15

     */

    //! SIMPLE TESTS ADDED BY DEAN
    void xtest_iter3_simple1 ( void ) { unparse_tests ( "iter3_simple1.dsl" ); }
    void xtest_iter3_simple2 ( void ) { unparse_tests ( "iter3_simple2.dsl" ); }
    void xtest_iter3_simple3 ( void ) { unparse_tests ( "iter3_simple3.dsl" ); }

    void test_sample_1 ( void ) { unparse_tests ( "sample_1.dsl" ); }
    void test_sample_2 ( void ) { unparse_tests ( "sample_2.dsl" ); }
    void test_sample_3 ( void ) { unparse_tests ( "sample_3.dsl" ); }
    void test_sample_4 ( void ) { unparse_tests ( "sample_4.dsl" ); }
    void test_sample_5 ( void ) { unparse_tests ( "sample_5.dsl" ); }
    void test_mysample ( void ) { unparse_tests ( "mysample.dsl" ); }
    void test_forest_loss ( void ) { unparse_tests ( "forest_loss_v2.dsl" ); }

    void xtest_sample_6(void) { unparse_tests("sample_6.dsl"); }

} ;




