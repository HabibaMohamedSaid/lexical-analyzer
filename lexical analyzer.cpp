#include <stdio.h>
#include <ctype.h>

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LITERAL 10
#define IDENTIFIER 11
#define ASSIGN_OP 20
#define PLUS_OP 21
#define MINUS_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_BRACKET 25
#define RIGHT_BRACKET 26
#define SEMICOLON 27
#define END_OF_STRING -1

/* Global variables */
int characterType;
char currentWord[100];
char currentChar;
int wordLength;
int tokenCode;
int nextToken;
const char* inputString;  // Pointer to the string for lexical analysis
int currentPos = 0;       // Index for the current character in the string

/* Function Prototypes */
void appendChar();
void readChar();
void skipWhitespace();
int getToken();
int identifyChar(char symbol);
void printTokenType(int token);

int main() {
    // Hardcoded input string to analyze
    inputString = "int x = 10 + 5 ( y / z ) ; ";

    readChar();  // Initialize the first character
    do {
        getToken();
    } while (nextToken != END_OF_STRING);

    return 0;
}

/* Check for operators, semicolons, or brackets */
int identifyChar(char symbol) {
    switch (symbol) {
    case '(':
        appendChar();
        nextToken = LEFT_BRACKET;
        break;
    case ')':
        appendChar();
        nextToken = RIGHT_BRACKET;
        break;
    case '+':
        appendChar();
        nextToken = PLUS_OP;
        break;
    case '-':
        appendChar();
        nextToken = MINUS_OP;
        break;
    case '*':
        appendChar();
        nextToken = MULT_OP;
        break;
    case '/':
        appendChar();
        nextToken = DIV_OP;
        break;
    case '=':
        appendChar();
        nextToken = ASSIGN_OP;
        break;
    case ';':
        appendChar();
        nextToken = SEMICOLON;
        break;
    default:
        appendChar();
        nextToken = END_OF_STRING;
        break;
    }
    return nextToken;
}

/* Append character to the current word */
void appendChar() {
    if (wordLength <= 98) {
        currentWord[wordLength++] = currentChar;
        currentWord[wordLength] = '\0';
    }
    else {
        printf("Error - word is too long!\n");
    }
}

/* Read next character and identify its type */
void readChar() {
    if (inputString[currentPos] != '\0') {
        currentChar = inputString[currentPos++];
        if (isalpha(currentChar))
            characterType = LETTER;
        else if (isdigit(currentChar))
            characterType = DIGIT;
        else
            characterType = UNKNOWN;
    }
    else {
        characterType = END_OF_STRING;
    }
}

/* Skip spaces and tabs */
void skipWhitespace() {
    while (isspace(currentChar)) {
        readChar();
    }
}

/* Core Lexical Analyzer */
int getToken() {
    wordLength = 0;
    skipWhitespace();
    switch (characterType) {
    case LETTER:
        appendChar();
        readChar();
        while (characterType == LETTER || characterType == DIGIT) {
            appendChar();
            readChar();
        }
        nextToken = IDENTIFIER;
        break;

    case DIGIT:
        appendChar();
        readChar();
        while (characterType == DIGIT) {
            appendChar();
            readChar();
        }
        nextToken = INT_LITERAL;
        break;

    case UNKNOWN:
        identifyChar(currentChar);
        readChar();
        break;

    case END_OF_STRING:
        nextToken = END_OF_STRING;
        currentWord[0] = 'E';
        currentWord[1] = 'O';
        currentWord[2] = 'S';
        currentWord[3] = '\0';
        break;
    }

    printTokenType(nextToken);
    printf("Token: %d | Lexeme: %s\n", nextToken, currentWord);
    return nextToken;
}

/* Print the type of the lexeme */
void printTokenType(int token) {
    switch (token) {
    case IDENTIFIER:
        printf("[IDENTIFIER] ");
        break;
    case INT_LITERAL:
        printf("[INT_LITERAL] ");
        break;
    case ASSIGN_OP:
        printf("[ASSIGN_OP] ");
        break;
    case PLUS_OP:
        printf("[PLUS_OP] ");
        break;
    case MINUS_OP:
        printf("[MINUS_OP] ");
        break;
    case MULT_OP:
        printf("[MULT_OP] ");
        break;
    case DIV_OP:
        printf("[DIV_OP] ");
        break;
    case LEFT_BRACKET:
        printf("[LEFT_BRACKET] ");
        break;
    case RIGHT_BRACKET:
        printf("[RIGHT_BRACKET] ");
        break;
    case SEMICOLON:
        printf("[SEMICOLON] ");
        break;
    case END_OF_STRING:
        printf("[END_OF_STRING] ");
        break;
    default:
        printf("[UNKNOWN] ");
        break;
    }
}
