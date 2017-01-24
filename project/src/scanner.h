/***********************************************************************
   scanner.h

   Authors: Dean Avery aver0002 and Kevin Wang wang3224 

************************************************************************/

#ifndef SCANNER_H
#define SCANNER_H

#include <regex.h>
#include <string>

class Token ;

/* This enumerated type is used to keep track of what kind of
   construct was matched. 
 */
enum tokenEnumType { 

   /* Keywords */
   intKwd, floatKwd, boolKwd,
   trueKwd, falseKwd, stringKwd, matrixKwd,
   letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd,
   repeatKwd, whileKwd, printKwd, toKwd,

   /* Constants */
   intConst, floatConst, stringConst, 

   /* Names */
   variableName,

   /* Punctuation */
   leftParen, rightParen, 
   leftCurly, rightCurly, 
   leftSquare, rightSquare,
   semiColon, colon,

   /* Operators */
   assign, 
   plusSign, star, dash, forwardSlash,
   lessThan, lessThanEqual, greaterThan, greaterThanEqual,
   equalsEquals, notEquals,
   andOp, orOp, notOp,

   /* Special terminal types */
   endOfFile,
   lexicalError,
};

typedef enum tokenEnumType tokenType;

class Token {

public:
   Token();
   Token(std::string lexeme, tokenType terminal, Token* next);   
   tokenType terminal;
   std::string lexeme;
   Token* next;			    
};

class Scanner {

public:
   Scanner();
   Token* scan (const char* text);
   regex_t* regexArray[43];      /* Array to hold all tokenTypes */
   regex_t* whiteSpace;          /* Used to ignore white spaces */
   regex_t* blockComment;        /* Used to ignore block comments */
   regex_t* lineComment;         /* Used to ignore line comments */
   void initializeMakeRegex();
};

#endif /* SCANNER_H */

