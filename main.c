#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Token types
typedef enum {
    OPERATOR,
    NUMBER,
    PARENTHESIS
} token_type;

// Token structure
typedef struct Token {
    token_type type;
    char value;
    struct Token *next;
} Token;

Token *token_list = NULL;

// Function to bind a new token to the token_list
void bind_token(token_type type, char value) {
    Token *new_token = (Token *)malloc(sizeof(Token));
    new_token->type = type;
    new_token->value = value;
    new_token->next = NULL;

    if (token_list == NULL) {
        token_list = new_token;
    } else {
        Token *current = token_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_token;
    }
}

// Function to free the memory of the token_list
void free_tokens() {
    Token *current = token_list;
    while (current != NULL) {
        Token *temp = current;
        current = current->next;
        free(temp);
    }
}

// Function to display tokens
void show_tokens() {
    Token *current = token_list;
    while (current != NULL) {
        printf("Type: %d, Value: %c\n", current->type, current->value);
        current = current->next;
    }
}

// Function to tokenize the input expression
void lex_expression(const char *expression) {
    int i = 0;
    while (expression[i] != '\0') {
        char current_char = expression[i];

        if (isspace(current_char)) {
            i++;
            continue;
        }

        if (current_char == '+' || current_char == '-' || current_char == '*' || current_char == '/') {
            bind_token(OPERATOR, current_char);
        } else if (isdigit(current_char)) {
            bind_token(NUMBER, current_char);
        } else if (current_char == '(' || current_char == ')') {
            bind_token(PARENTHESIS, current_char);
        }

        i++;
    }
}

int main() {
    char expression[100];

    printf("Enter a mathematical expression: ");
    fgets(expression, sizeof(expression), stdin);

    lex_expression(expression);
    show_tokens();
    free_tokens();

    return 0;
}
