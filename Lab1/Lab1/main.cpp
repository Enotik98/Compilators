//
//  main.cpp
//  Lab1
//
//  Created by Enotik on 27.04.2023.
//

#include <iostream>
#include <fstream>
#include "Lexer.hpp"
using namespace::std;
//
//ostream& operator<<(ostream& os, const Token::Kind& kind){
//    static const char* const names[]{
//        "NUMBER",
//        "INTEGER",
//        "FLOAT",
//        "STRING",
//        "AUTO",
//        "BREAK",
//        "CASE",
//        "CHAR",
//        "CONST",
//        "CONTINUE",
//        "DEFAULT",
//        "SEMICOLON",
//        "DOT",
//        "COMMA",
//        "COLON",
//        "IDENTIFIER",
//        "COMMENT",
//        "SLASH",
//        "ASSIGN",
//        "DOUBLE_EQUAL",
//        "NOT_EQUAL",
//        "EXCLAMATION_MARK",
//        "LEFT_PAREN",     
//        "RIGHT_PAREN",
//        "LEFT_SQUARE",
//        "RIGHT_SQUARE",
//        "LEFT_CURLY",
//        "RIGHT_CURLY",  
//        "PLUS",
//        "INCREMENT",
//        "MINUS",
//        "DECREMENT",
//        "PERCENTAGE",
//        "ASTERISK",
//        "LESS_THEN",
//        "GREATER_THEN",
//        "LESS_EQUAL_THEN",
//        "GREATER_EQUAL_THEN",
//        "AMPERSAND",
//        "AND",
//        "PIPE",
//        "OR",
//        "XOR",            
//        "ONES_COMPLEMENT",
//        "LEFT_SHIFT",
//        "LEFT_SHIFT_ASSIGN",
//        "RIGHT_SHIFT",
//        "RIGHT_SHIFT_ASSIGN",
//        "ADD",
//        "SUBTRACT",
//        "MULTIPLY",
//        "DIVIDE",
//        "TAKE_MODULUS",
//        "BITWISE_AND_ASSIGN",
//        "BITWISE_OR_ASSIGN",
//        "END",
//        "UNEXPECTED"
//    };
//    return os << names[static_cast<int>(kind)];
//}

int main(int argc, const char * argv[]) {
    string filename = "/Users/enotik/Desktop/3course/java/Compilators/Lab1/files/input";
    
    
    Lexer lex(filename);
    
    for(auto token = lex.next(); !token.is(Token::Kind::END);token = lex.next()){
        cout  << setw(16)<< token.kind() << "\t| " << token.lexeme() << " |\n";
        if (token.is(Token::Kind::UNEXPECTED)){
            break;
        }
    }
    return 0;
    
}
