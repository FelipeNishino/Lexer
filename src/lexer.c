#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "include/lexer.h"
#include "include/token.h"

Lexer* lexer_init(char* src) {
	Lexer* lexer = (Lexer*) malloc(sizeof(Lexer));
	
	lexer->src = src;
	lexer->src_size = strlen(src);
	lexer->c = lexer->src[0];
	lexer->i = 0;
	lexer->t_pos = (text_position*) malloc(sizeof(text_position));
	lexer->t_pos->line = 1;
	lexer->t_pos->col = 1;

	return lexer;
}

void lexer_free(Lexer* lexer) {
	free(lexer->t_pos);
	free(lexer);
}

void lexer_next(Lexer* lexer) {
	if (lexer->i < lexer->src_size) {
		lexer->i++;
		lexer->c = lexer->src[lexer->i];
	}
}

char lexer_peek(Lexer* lexer, int offset) {
	return lexer->src[offset > 0 ? MAX(lexer->i + offset, 0) : MIN(lexer->i + offset, lexer->src_size)];	
}

void lexer_skip_whitespace(Lexer* lexer) {
	int is_whitespace = 1;
	while (is_whitespace && lexer->c != 0) {
		switch (lexer->c) {
			case '\t':
				lexer->t_pos->col += 4;
				break;
			case 10:
				lexer->t_pos->line++;
				lexer->t_pos->col = 1;
				break;
			case 32:
				lexer->t_pos->col++;
				break;
			default:
				is_whitespace = 0;
				continue;
		}
		lexer_next(lexer);
	}
}

Token* lexer_tokenize(Lexer* lexer, TokenType type) {
	return lexer_n_tokenize(lexer, 1, type);
}

Token* lexer_n_tokenize(Lexer* lexer, int n, TokenType type) {
	int i;
	char* val = calloc(n + 1, sizeof(char));
	strncpy(val, &lexer->src[lexer->i], n);
	
	// lexer->t_pos->col += n;
	Token* token = token_init(val, type, lexer->t_pos->line, lexer->t_pos->col);
	
	if (token->type != token_EOF){
		for (i = 0; i < n; i++)
			lexer_next(lexer);
	}

	// free(val);
	return token;
}

Token* lexer_read_number_literal(Lexer* lexer) {
	// ([0-9]*)\.([0-9]*)((e)[\-\+][0-9]+)?
	int n = 1;
	char next = lexer_peek(lexer, n);
	int is_exponent = 0;

	while (isdigit(next) || next == 'e' || next == '.' || (is_exponent && (next == '-' || next == '+'))) {
		if (!is_exponent && next == 'e') is_exponent = 1;
		n++;
		next = lexer_peek(lexer, n);
	}

	return lexer_n_tokenize(lexer, n, Numero);
}

Token* lexer_read_token(Lexer* lexer) {
	// int reserved_word_i, reserved_word_n;

	lexer_skip_whitespace(lexer);

	if (isdigit(lexer->c)) return lexer_read_number_literal(lexer);		
	
	switch(lexer->c) {
		case '.': return lexer_read_number_literal(lexer);
		case '+': return lexer_tokenize(lexer, Soma);
		case '-': return lexer_tokenize(lexer, Subtracao);
		case '/': return lexer_tokenize(lexer, Divisao);
		case '*': return lexer_tokenize(lexer, Multiplicacao);
		case '(': return lexer_tokenize(lexer, Abre_Parenteses);
		case ')': return lexer_tokenize(lexer, Fecha_Parenteses);
		case '\0': return lexer_tokenize(lexer, token_EOF);
		default: 
			fprintf(stderr, "[Lexer.c]: unexpected symbol {%c}, value {%d}\n", lexer->c, lexer->c);
			lexer_free(lexer);
			exit(1);
	}
	
}