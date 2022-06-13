#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/iomanager.h"

void tokenize_file(const char* filename) {
    char* src = getInputFromFile(filename);
    Lexer* lexer = lexer_init(src);

    Token* t = 0;
    while(1) {
        t = lexer_read_token(lexer);
        if (t->type == token_EOF) break;
        token_print(t);
    }

    // token_free(t);
    // lexer_free(lexer);
    // free(src);
}


int main(int argc, const char *argv[]) {
    // Extrai as opcoes nos argumentos para o algoritmo
    if (argc < 2) fprintf(stderr, "Please provide adequate arguments.");
    
    tokenize_file(argv[1]);
    
    return 0;
}