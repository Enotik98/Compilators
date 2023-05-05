//
//  main.cpp
//  Lab1
//
// Lexer for Objective-C
//
//  Created by Enotik on 27.04.2023.
//

#include <iostream>
#include <fstream>
#include "Lexer.hpp"
using namespace::std;


int main(int argc, const char * argv[]) {
    string filename = "/Users/enotik/Desktop/3course/java/Compilators/Lab1/files/input";
    
    
    Lexer lex(filename);
    
    for(auto token = lex.next(); !token.is(Token::Kind::END);token = lex.next()){
        cout  << setw(16)<< token.kind() << "\t| " << token.lexeme() << " |\n";
        if (token.is(Token::Kind::UNEXPECTED) || token.is(Token::Kind::UNEXPECTED_COMMET) || token.is(Token::Kind::UNEXPECTED_STRING) || token.is(Token::Kind::UNEXPECTED_SYMBOL)){
            break;
        }
    }
    return 0;
    
}
