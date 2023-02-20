/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages. 
 * Pearson, 10th edition.
 *
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
//#include "front.h"
//#include "parser.h"
/*Defining all the token name with its code*/
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 2
/* Token codes */
#define INT_LIT 3
#define IDENT 4
#define EQUAL_OP 5
#define ASSIGN_OP 6
#define ADD_OP 7
#define SUB_OP 8
#define MULT_OP 9
#define DIV_OP 10
#define LEFT_PAREN 11
#define RIGHT_PAREN 12
#define MOD_OP 13
#define LESSER_OP 14
#define GREATER_OP 15
#define NEQUAL_OP 16
#define LEQUAL_OP 17
#define GEQUAL_OP 18
#define SEMICOLON 19
#define LEFT_CBRACE 20
#define RIGHT_CBRACE 21
#define KEY_READ 22
#define KEY_PRINT 23
#define KEY_WHILE 24
#define KEY_DO 25

/* Global Variable */
int nextToken;
char prev;
int lex();
/* Local Variables */
static int charClass;
static char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;
/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

/******************************************************/
/* main driver */
int main(int argc, char *argv[]) 
{
    /* Open the input data file and process its contents */
    printf("DanC Analyzer :: R11704958\n\n");
  
    if ((in_fp = fopen(argv[1], "r")) == NULL) {
        printf("ERROR - cannot open front.in \n");
    } else {
        getChar(); //gets initial character
      do {
          lex(); //starts the lexical analyzer
          //expr();
        } while (nextToken != EOF);
      }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the 
 * token */
static int lookup(char ch) {
      switch (ch) {
        case '=':
            addChar();
            getChar();
            if (nextChar == '='){
              addChar();
              nextToken = EQUAL_OP;
            }
            else{
              ungetc(nextChar,in_fp); //moves a character pointer behind if it does not matches with = or >
              nextToken = ASSIGN_OP;
            }
            break;
        case '<':
            addChar();
            getChar();
            if (nextChar == '='){
              addChar();
              nextToken = LEQUAL_OP;
            }
            else if (nextChar == '>'){
              addChar();
              nextToken = NEQUAL_OP;
            }
            else{
              ungetc(nextChar,in_fp);
              nextToken = LESSER_OP;
            }
            break;
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
        case '>':
            addChar();
            getChar();
            if (nextChar == '='){
              addChar();
              nextToken = GEQUAL_OP;
            }
            else{
              ungetc(nextChar,in_fp);
              nextToken = GREATER_OP;
              }
            break;
        case ';':
            addChar();
            nextToken = SEMICOLON;
            break;
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        case '{':
            addChar();
            nextToken = LEFT_CBRACE;
            break;
        case '}':
            addChar();
            nextToken = RIGHT_CBRACE;
            break;
        default:
            addChar();
            nextToken = UNKNOWN;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its 
 * character class */
static void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar)){
            charClass = LETTER;
          }
        else if (isdigit(nextChar)){
            charClass = DIGIT;
      }
        else {
          charClass = UNKNOWN;
          }
    } else {
        charClass = EOF;
    }
}


/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace 
 * character */
static void getNonBlank() {
    while (isspace(nextChar)) getChar();
}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
  /*2D array storing name of each token ID*/
  char array[26][200];
  strcpy(array[0],"LETTER");
  strcpy(array[1],"DIGIT");
  strcpy(array[2],"UNKNOWN");
  strcpy(array[3],"INT_LIT");
  strcpy(array[4],"IDENT");
  strcpy(array[5],"EQUAL_OP");
  strcpy(array[6],"ASSIGN_OP");
  strcpy(array[7],"ADD_OP");
  strcpy(array[8],"SUB_OP");
  strcpy(array[9],"MULT_OP");
  strcpy(array[10],"DIV_OP");
  strcpy(array[11],"LEFT_PAREN");
  strcpy(array[12],"RIGHT_PAREN");
  strcpy(array[13],"MOD_OP");
  strcpy(array[14],"LESSER_OP");
  strcpy(array[15],"GREATER_OP");
  strcpy(array[16],"NEQUAL_OP");
  strcpy(array[17],"LEQUAL_OP");
  strcpy(array[18],"GEQUAL_OP");
  strcpy(array[19],"SEMICOLON");
  strcpy(array[20],"LEFT_CBRACE");
  strcpy(array[21],"RIGHT_CBRACE");
  strcpy(array[22],"KEY_READ");
  strcpy(array[23],"KEY_PRINT");
  strcpy(array[25],"KEY_DO");
  strcpy(array[24],"KEY_WHILE");
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            /*Checking of KEYWORDS*/
            if(strncmp(lexeme, "while",strlen(lexeme))==0){
              nextToken = KEY_WHILE;
            }
            else if(strncmp(lexeme, "do",strlen(lexeme))==0){
              nextToken = KEY_DO;
            }
            else if(strncmp(lexeme, "print",strlen(lexeme))==0){
              nextToken = KEY_PRINT;
            }
            else if(strncmp(lexeme, "read",strlen(lexeme))==0){
              nextToken = KEY_READ;
            }
            else{
                nextToken = IDENT;
            }
            break;


        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
    if(nextToken != -1){
      printf("%s\t\t%s\n",lexeme,array[nextToken]); //prints the character with token name
      }
  
    return nextToken;
} /* End of function lex */

