//
//  Lexer.cpp
//  Lab1
//
//  Created by Enotik on 27.04.2023.
//

#include "Lexer.hpp"

Lexer::Lexer(std::string filename){
    input.open(filename);
}
Lexer::~Lexer(){
    input.close();
}

char Lexer::peek(){
    return input.peek();
}
char Lexer::get(){
    return input.get();
}
bool Lexer::is_space(char c){
    return std::isspace(static_cast<unsigned char>(c));
}
bool Lexer::is_number(char c){
    return std::isalnum(static_cast<unsigned char>(c)) && !is_letter(c);
}
bool Lexer::is_letter(char c){
    return std::isalpha(static_cast<unsigned char>(c));
}

Token Lexer::string(){
    std::string lex{ get()};
    char prev_char = peek();
    int count_quote = 1;
    for (char current_char = peek(); count_quote > 0 ; current_char = peek()) {
        if (current_char == '"' && prev_char != '\\') {
            count_quote --;
        }
        if (current_char == '\xff') {
            return Token(Token::Kind::UNEXPECTED, lex);
        }
        lex += get();
        prev_char = current_char;
    }
    return Token(Token::Kind::STRING, lex);
}

Token Lexer::number(){
    std::string lex;
    char prev_char = peek();
    Token::Kind token = Token::Kind::INTEGER;
    int pos = 0;
    while (is_number(peek()) || peek() == '.') {
        lex += get();
        if ((peek() == '.' && prev_char == '.') || (pos == 0 && prev_char == '.')) {
            return Token(Token::Kind::UNEXPECTED, lex);
        }
        if (peek() == '.') {
            token = Token::Kind::FLOAT;
        }
        prev_char = peek();
    }
    return Token(token, lex);
}

Token Lexer::idetifier(){
    std::string lex;
    
    if (peek() == '@'){
        lex += get();
        int count = 1;
        char str = peek();
        for (char c; count > 0; c = peek()){
            if (c == '\xff') {
                return Token(Token::Kind::UNEXPECTED, lex);
            }
            if (!isnumber(str) && !is_letter(str)) {
                if ((str == '(' && c == ')') || (str == '"' && c == '"') || (str == '\'' && c == '\'') || (str == '{' && c == '}') || (str == '[' && c == ']')){
                    count--;
                }
            }else{
                c = peek();
                // пока с число чи строка
                if (!isnumber(c) && !is_letter(c) && c != '.') {
                    count--;
                }
            }
            lex += get();
        }
    }else{
        for (char c = peek(); is_number(c) || is_letter(c) || c == '_'; c = peek()) {
            lex += get();
        }
    }
    return Token(Token::Kind::IDENTIFIER, lex);
}


Token Lexer::comment(){
    std::string lex{get()};
    if (peek() == '*') {
        int count_comment = 1;
        char prev_char = peek();
        for (char curr_char = get(); count_comment > 0; curr_char = get()) {
            if (prev_char == '*' && curr_char == '/') count_comment--;
            if (curr_char == '\xff') {
                return Token(Token::Kind::UNEXPECTED, lex);
            }

            lex += curr_char;
            prev_char = curr_char;
        }
        return Token(Token::Kind::COMMENT, lex);
    }else if (peek() == '/'){
        while (peek() != '\n') {
            lex += get();
        }
        return Token(Token::Kind::COMMENT, lex);
    }else{
        return Token(Token::Kind::SLASH);
    }

}
Token Lexer::tokenNext(char c, Token::Kind tk1, Token::Kind tk2){
    std::string lex{get()};
    if (peek() == c) {
        lex += get();
        return Token(tk1, lex);
    }else{
        return Token(tk2, lex);
    }
}

Token Lexer::tokenNext(char c1, char c2, Token::Kind tk1, Token::Kind tk2, Token::Kind tk3){
    std::string lex{ get()};
    
    if (peek() == c1) {
        lex += get();
        return Token(tk1, lex);
    }else if (peek() == c2){
        lex += get();
        return Token(tk2, lex);
    }else{
        return Token(tk3, lex);
    }
}
Token Lexer::preprocessor(){
    std::string lex{get()};
    std::vector<std::string> preprocessors = {
        "include", "import", "define", "ifdef", "ifndef", "endif",
        "if", "elif", "pragrma"
    };
    std::string str ;
    while (is_space(peek())) {
        lex += get();
    }
    while (peek() != '<' && peek() != '"' && !is_space(peek())) {
            str += peek();
            lex += get();
    }
    auto itr = std::find(preprocessors.begin(), preprocessors.end(), str);
    if (itr != preprocessors.end()) {
        while (is_space(peek()) || peek() == '"') {
            lex += get();
        }
        while (peek() != '>' && peek() != '"' && peek() != '\n'){
            lex += get();
        }
        lex += get();
        return Token(Token::Kind::PREPROCESSOR, lex);
    }else{
        return Token(Token::Kind::UNEXPECTED, lex);
    }
}



Token Lexer::next(){
    while (is_space(peek())) {
        get();
    }
    char c = peek();
    
    if (is_number(c)) {
        return number();
    }else if (is_letter(c) || c == '@' || c == '_'){
        return idetifier();
    }
    
    switch (c) {
        case '"':
            return string();
        case '#':
            return preprocessor();
        case '\'':
            return Token(Token::Kind::SINGLE_QUOTE, std::string{get()});
        case ';':
            return Token(Token::Kind::SEMICOLON, std::string{get()});
        case ':':
            return Token(Token::Kind::COLON, std::string{get()});
        case '.':
            return Token(Token::Kind::DOT, std::string{get()});
        case ',':
            return Token(Token::Kind::COMMA, std::string{get()});
        case '/':
            return comment();
        case '=':
            return tokenNext('=', Token::Kind::DOUBLE_EQUAL, Token::Kind::ASSIGN);
        case '!': //
            return tokenNext('=', Token::Kind::NOT_EQUAL, Token::Kind::EXCLAMATION_MARK);
        case '(':
            return Token(Token::Kind::LEFT_PAREN, std::string{get()});
        case ')':
            return Token(Token::Kind::RIGHT_PAREN, std::string{get()});
        case '[':
            return Token(Token::Kind::LEFT_SQUARE, std::string{get()});
        case ']':
            return Token(Token::Kind::RIGHT_SQUARE, std::string{get()});
        case '{':
            return Token(Token::Kind::LEFT_CURLY, std::string{get()});
        case '}':
            return Token(Token::Kind::RIGHT_CURLY, std::string{get()});
        case '+': // ++ += +
            return tokenNext('+', '=', Token::Kind::INCREMENT, Token::Kind::ADD, Token::Kind::PLUS);
        case '-': // -- -= -
            return tokenNext('-', '=', Token::Kind::DECREMENT, Token::Kind::SUBTRACT, Token::Kind::MINUS);
        case '%': // %= %
            return tokenNext('=', Token::Kind::TAKE_MODULUS, Token::Kind::PERCENTAGE);
        case '*': // *= *
            return tokenNext('=', Token::Kind::MULTIPLY, Token::Kind::ASTERISK);
        case '<': // <<= << <= <
        {
            std::string lex {get()};
            
            if (peek() == '<') {
                lex += get();
                if (peek() == '=') {
                    lex += get();
                    return Token(Token::Kind::LEFT_SHIFT_ASSIGN, lex);
                }else{
                    return Token(Token::Kind::LEFT_SHIFT, lex);
                }
            }else if (peek() == '='){
                lex += get();
                return Token(Token::Kind::LESS_EQUAL_THEN, lex);
            }else{
                return Token(Token::Kind::LESS_THEN, lex);
            }
        }
        case '>': // >>= >> >= >
        {
            std::string lex {get()};
            
            if (peek() == '>') {
                lex += get();
                if (peek() == '=') {
                    lex += get();
                    return Token(Token::Kind::RIGHT_SHIFT_ASSIGN, lex);
                }else{
                    return Token(Token::Kind::RIGHT_SHIFT, lex);
                }
            }else if (peek() == '='){
                lex += get();
                return Token(Token::Kind::GREATER_EQUAL_THEN, lex);
            }else{
                return Token(Token::Kind::GREATER_THEN, lex);
            }
        }
        case '&': // && &= &
            return tokenNext('&', '=', Token::Kind::AND, Token::Kind::BITWISE_AND_ASSIGN,Token::Kind::AMPERSAND);
        case '|':
            return tokenNext('|', Token::Kind::OR, Token::Kind::PIPE);
        case '^':
            return tokenNext('=', Token::Kind::BITWISE_OR_ASSIGN, Token::Kind::XOR);
        case '~':
            return Token(Token::Kind::ONES_COMPLEMENT, std::string{ get()});
            
        case '\xff':
            return Token(Token::Kind::END, std::string{ get() });
        
        default:
            return Token(Token::Kind::UNEXPECTED, std::string{get()});
    }
    
    return Token(Token::Kind::END);
}

