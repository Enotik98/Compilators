//
//  Lexer.hpp
//  Lab1
//
//  Created by Enotik on 27.04.2023.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <stdio.h>
#include <fstream>
#include <string>
#include "Token.hpp"

class Lexer{
private:
    std::fstream input;
    bool is_space(char);
    bool is_number(char);
    bool is_letter(char);
    
    Token string();
    Token number();
    Token idetifier();
    Token comment();
    Token tokenNext(char, Token::Kind, Token::Kind);
    Token tokenNext(char, char, Token::Kind, Token::Kind, Token::Kind);
    Token preprocessor();
    
public:
    Lexer(std::string);
    ~Lexer();
    
    Token next();
    
    char peek();
    char get();
    
    
};

#endif /* Lexer_hpp */
