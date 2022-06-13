#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/token.h"

void token_print(Token* t) { 
    switch(t->type) {
        case Numero:
            fprintf(stdout, "<%s(%s)>\n", TOKEN_STRING[t->type], t->value);
            break;
        case Abre_Parenteses:
        case Fecha_Parenteses:
            fprintf(stdout, "<%s(%s)>\n", "Pontuacao", TOKEN_STRING[t->type]);
            break;
        default:
            fprintf(stdout, "<%s(%s)>\n", "Operador", TOKEN_STRING[t->type]);
    }   
}

Token*
token_init(char* value, TokenType type, unsigned int line, unsigned int col) {
    Token* token = calloc(1, sizeof(Token));

    token->value = calloc(strlen(value) + 1, sizeof(char));
    strcpy(token->value, value);
    token->type = type;
    token->line = line;
    token->col = col;

    return token;
}

void
token_free(Token* t) {
    free(t->value);
    free(t);
}

int
token_is_grouper(Token* t) {
    return t->type == Abre_Parenteses || t->type == Fecha_Parenteses;
}

int
token_is_type(TokenType t1, TokenType t2) {
    return t1 == t2;
}