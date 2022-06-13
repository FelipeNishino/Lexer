#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include "macros.h"

#define FOREACH_TOKEN(TOKEN) \
        TOKEN(Fecha_Parenteses)   \
        TOKEN(Abre_Parenteses)   \
        TOKEN(Numero)   \
        TOKEN(Soma)   \
        TOKEN(Multiplicacao)   \
        TOKEN(Divisao)   \
        TOKEN(Subtracao)   \
        TOKEN(token_EOF)   \

typedef enum TokenType {
    FOREACH_TOKEN(GENERATE_ENUM)
} TokenType;

//https://stackoverflow.com/questions/8312168/static-const-char-defined-but-not-used
static const char * const TOKEN_STRING[] = {
    FOREACH_TOKEN(GENERATE_STRING)
};
/*
#define FOREACH_RESERVED_WORD(RESERVED_WORD) \
        RESERVED_WORD(RW_let) \
        RESERVED_WORD(RW_var) \
        RESERVED_WORD(RW_if) \
        RESERVED_WORD(RW_else) \
        RESERVED_WORD(RW_for) \
        RESERVED_WORD(RW_while) \
        RESERVED_WORD(RW_do) \
        RESERVED_WORD(RW_return) \
        RESERVED_WORD(RW_Int) \
        RESERVED_WORD(RW_Float) \
        RESERVED_WORD(RW_String) \
        RESERVED_WORD(RW_Bool) \

typedef enum ReservedWord {
    FOREACH_RESERVED_WORD(GENERATE_ENUM)
} ReservedWord;

static const char* const RESERVED_WORD_STRING[] = {
    FOREACH_RESERVED_WORD(GENERATE_STRING)
};
*/

typedef struct token {
    char* value;
    TokenType type;
    unsigned int line;
    unsigned int col;
} Token;

void token_print(Token* t);
Token* token_init(char* value, TokenType type, unsigned int line, unsigned int col);
void token_free(Token* t);
int token_is_grouper(Token* t);
int token_is_type(TokenType t1, TokenType t2);

#endif //COMPILER_TOKEN_H
