/************************************************************************* 
   scanner.cpp

   This scanner takes as input a program in a domain specific programming 
   language CDAL (Climate Data Analysis Language), recognizes the tokens 
   in the program, and returns them in a linked list. 

   Authors: Kevin Wang wang3224 and Dean Avery aver0002

**************************************************************************/


#include "scanner.h"
#include "regex.h"
#include <iostream>
using namespace std; 

int consumeWhiteSpaceAndComments (regex_t *whiteSpace, 
                                  regex_t *blockComment,
				  regex_t *lineComment,
                                  const char *text);

Token::Token() {
   lexeme = "";
   terminal = lexicalError;
   next = NULL;
}
Token::Token(std::string lexeme, tokenType terminal, Token* next) {
   this->lexeme = lexeme;
   this->terminal = terminal;
   this->next = next;
}

/* Initialize all makeRegexes */ 
Scanner::Scanner(){
   initializeMakeRegex();
}

Token* Scanner::scan (const char *text){

   /* Enumerated type to keep track of what kind of construct was matched */ 
   tokenEnumType matchType; 

   /* numMatchedChars is used to consume the leading white space, block comments and 
      line comments so that those can be ignored
    */
   int numMatchedChars = 0;
   numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockComment, lineComment, text);

   /* text is the character pointer passed to the scanner.  Adding numMatchedChars advances the
      pointer that many elements in the array so that it points to the current location in the
      input.
    */ 
   text = text + numMatchedChars;

   class Token* POINTER_TO_HEAD = new Token();
   class Token* CURSOR = POINTER_TO_HEAD;
  
   /* The main looping construct is used to match the incoming text argument to its tokenType.
      If a match is not found, that terminal is assigned as a lexical error.
    */ 
   while ( text[0] != '\0' ) {

      int maxNumMatchedChars = 0;
      matchType = lexicalError;     /* initialize matchType to lexicalError */
    
      /* This loops through regexArray matching text to its tokenType */
      int i;
      for(i = 0; i < 43; i++) {  
         if( (numMatchedChars = matchRegex(regexArray[i], text)) ) { 	
            if(numMatchedChars > maxNumMatchedChars) {
               maxNumMatchedChars = numMatchedChars;

	       /* makeRegex's are inserted into the regexArray in the same order as 
                  the enumerated tokenTypes; thus, matchtype can be simply matched 
                  from casting the looping i 
                */
	       matchType = (tokenType)i;    
            }
         }
      } 

      /* No valid tokenType was matched; thus, assign the terminal and lexeme 
         while skipping one character.
       */
      if (matchType == lexicalError){   
         CURSOR->terminal = lexicalError;
         CURSOR->lexeme = text[0]; 
         text = text + 1;
      }
    
      /* A valid tokenType was matched; thus, assign the terminal and lexeme accordingly while
         moving the text pointer the number of matched chars
       */
      else {
         CURSOR->terminal = matchType;
         CURSOR->lexeme = string(text,maxNumMatchedChars); 
         text = text + maxNumMatchedChars;
      }
	
      /* Reset numMatchedChars and text for the next iteration */
      numMatchedChars = consumeWhiteSpaceAndComments (whiteSpace, blockComment, lineComment, text) ;
      text = text + numMatchedChars;

      /* Create the next token */
      CURSOR->next = new Token(); 
      CURSOR = CURSOR->next;   	
   }

   CURSOR->terminal = endOfFile;
   CURSOR->next = NULL;  

   return POINTER_TO_HEAD;
}

/* Used to initialize all makeRegexes as it's required only once.  Inserts each of the 43 tokenTypes 
   into regexArray while also creating a regex for whiteSpace, blockComment, and lineComment.
 */
void Scanner::initializeMakeRegex() {

   /* Keywords */
   regexArray[intKwd] = makeRegex("^int");
   regexArray[floatKwd] = makeRegex("^float");
   regexArray[boolKwd] = makeRegex("^bool");
   regexArray[trueKwd] = makeRegex("^true");
   regexArray[falseKwd] = makeRegex("^false");
   regexArray[stringKwd] = makeRegex("^string");
   regexArray[matrixKwd] = makeRegex("^matrix");
   regexArray[letKwd] = makeRegex("^let");
   regexArray[inKwd] = makeRegex("^in");
   regexArray[endKwd] = makeRegex("^end");
   regexArray[ifKwd] = makeRegex("^if");                         
   regexArray[thenKwd] = makeRegex("^then");                       
   regexArray[elseKwd] = makeRegex("^else"); 
   regexArray[repeatKwd] = makeRegex("^repeat");                     
   regexArray[whileKwd] = makeRegex("^while");                    
   regexArray[printKwd] = makeRegex("^print");                     
   regexArray[toKwd] = makeRegex("^to");                       

   /* Constants */
   regexArray[intConst] = makeRegex("^[0-9]+");                // intConst
   regexArray[floatConst] = makeRegex("^[0-9]*\\.[0-9]+");     // floatConst
   regexArray[stringConst] = makeRegex("(^\"[^\"]*\")");       // stringConst

   /* Variable Name */
   regexArray[variableName] = makeRegex("^[_A-Za-z]+[_A-Za-z0-9]*");  

   /* Punctuation */
   regexArray[leftParen] = makeRegex("^\\(");
   regexArray[rightParen] = makeRegex("^\\)");
   regexArray[leftCurly] = makeRegex("^\\{");
   regexArray[rightCurly] = makeRegex("^\\}"); 
   regexArray[leftSquare] = makeRegex("^\\[");
   regexArray[rightSquare] = makeRegex("^\\]");
   regexArray[semiColon] = makeRegex("^;");
   regexArray[colon] = makeRegex("^:");

   /* Operators */
   regexArray[assign] = makeRegex("^=");
   regexArray[plusSign] = makeRegex("^\\+");
   regexArray[star] = makeRegex("^\\*");
   regexArray[dash] = makeRegex("^\\-");
   regexArray[forwardSlash] = makeRegex("^/");
   regexArray[lessThan] = makeRegex("^<");
   regexArray[lessThanEqual] = makeRegex("^<=");
   regexArray[greaterThan] = makeRegex("^>");
   regexArray[greaterThanEqual] = makeRegex("^>=");
   regexArray[equalsEquals] = makeRegex("^==");
   regexArray[notEquals] = makeRegex("^!=");
   regexArray[andOp] = makeRegex("^&&");
   regexArray[orOp] = makeRegex("^\\|\\|");
   regexArray[notOp] = makeRegex("^!");

   /* Regex_t's to match white spaces, block comments and line comments */  
   whiteSpace = makeRegex ("^[\n\t\r ]+") ;
   blockComment = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
   lineComment = makeRegex ("^//[^\n]*\n");
}

/* Consume and return the total number of white space, block comment and line comment chars */

int consumeWhiteSpaceAndComments (regex_t *whiteSpace, 
				  regex_t *blockComment,
				  regex_t *lineComment,
				  const char *text) {

   int numMatchedChars = 0 ;
   int totalNumMatchedChars = 0 ;
   int stillConsumingWhiteSpace = 0;

   do {
      stillConsumingWhiteSpace = 0 ;  /* exit loop if not reset by a match */

      /* Try to match white space */
      numMatchedChars = matchRegex (whiteSpace, text) ;
      totalNumMatchedChars += numMatchedChars ;
      if (numMatchedChars > 0) {
         text = text + numMatchedChars ;
         stillConsumingWhiteSpace = 1 ;
      }

      /* Try to match block comments */
      numMatchedChars = matchRegex (blockComment, text) ;
      totalNumMatchedChars += numMatchedChars ;
      if (numMatchedChars > 0) {
         text = text + numMatchedChars ;
         stillConsumingWhiteSpace = 1 ;
      }

      /* Try to match line comments */
      numMatchedChars = matchRegex (lineComment, text) ;
      totalNumMatchedChars += numMatchedChars ;
      if (numMatchedChars > 0) {
         text = text + numMatchedChars ;
         stillConsumingWhiteSpace = 1 ;
      }

   } while ( stillConsumingWhiteSpace ) ;    

   return totalNumMatchedChars ;
}


