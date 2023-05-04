//
//  Token.h
//  Lab1
//
//  Created by Enotik on 27.04.2023.
//

#ifndef Token_h
#define Token_h

#include <string>
#include <map>
#include <vector>

class Token {
public:
    enum class Kind{
        NUMBER,
        INTEGER,
        FLOAT,
        STRING,
        SEMICOLON,      // ;
        DOT,            // .
        COMMA,          // ,
        COLON,          // :
        IDENTIFIER,
        COMMENT,        // /* */
        SLASH,          // /
        ASSIGN,         // =
        DOUBLE_EQUAL,   // ==
        NOT_EQUAL,      // !=
        EXCLAMATION_MARK,// !
        LEFT_PAREN,     // (
        RIGHT_PAREN,    // )
        LEFT_SQUARE,    // [
        RIGHT_SQUARE,   // ]
        LEFT_CURLY,     // {
        RIGHT_CURLY,    // }
        PLUS,           // +
        INCREMENT,      // ++
        MINUS,          // -
        DECREMENT,      // --
        PERCENTAGE,     // %
        ASTERISK,       // *
        LESS_THEN,      // <
        GREATER_THEN,   // >
        LESS_EQUAL_THEN,// <=
        GREATER_EQUAL_THEN,// >=
        AMPERSAND,      // &
        AND,            // &&
        PIPE,           // |
        OR,             // ||
        XOR,            // ^
        ONES_COMPLEMENT,// ~
        LEFT_SHIFT,     // <<
        LEFT_SHIFT_ASSIGN, // <<=
        RIGHT_SHIFT,    // >>
        RIGHT_SHIFT_ASSIGN, // >>=
        ADD,            // +=
        SUBTRACT,       // -=
        MULTIPLY,       // *=
        DIVIDE,         // /=
        TAKE_MODULUS,   // %=
        BITWISE_AND_ASSIGN, //&=
        BITWISE_OR_ASSIGN, //^=
        SINGLE_QUOTE,   // '
        DOUBLE_QUOTE,   // "
        PREPROCESSOR,
        SYMBOL,
        END,
        UNEXPECTED
    };
    Token(Kind kind, std::string const &lex) : _kind{kind}, _lexeme(lex) {}
    
    Token(Kind kind) : _kind{kind} {}
    
    bool is(Kind kind) {return _kind == kind;}
    //    Kind kind() const {return _kind;}
    std::string kind()  {
        auto itr = std::find(keyWords.begin(), keyWords.end(), _lexeme);
        if(_kind == Kind::IDENTIFIER && itr != keyWords.end()){
            std::string lex = "keyWord_" + _lexeme;
            return  lex;
        }
        return tokenMap.find(_kind)->second;
    }
    std::string const &lexeme() const {return _lexeme;}
    
private:
    Kind _kind{};
    std::string _lexeme{};
    std::map<Kind, std::string> tokenMap{
        {Kind::FLOAT, "FLOAT"},
        {Kind::INTEGER, "INTEGER"},
        {Kind::STRING, "STRING"},
        {Kind::UNEXPECTED, "UNEXPECTED"},
        {Kind::SEMICOLON, "SEMICOLON"},
        {Kind::DOT, "DOT"},
        {Kind::COMMA, "COMMA"},
        {Kind::COLON, "COLON"},
        {Kind::IDENTIFIER, "IDENTIFIER"},
        {Kind::COMMENT, "COMMENT"},
        {Kind::SLASH, "SLASH"},
        {Kind::ASSIGN, "ASSIGN"},
        {Kind::DOUBLE_EQUAL, "DOUBLE_EQUAL"},
        {Kind::NOT_EQUAL, "NOT_EQUAL"},
        {Kind::EXCLAMATION_MARK, "EXCLAMATION_MARK"},
        {Kind::LEFT_PAREN, "LEFT_PAREN"},
        {Kind::RIGHT_PAREN, "RIGHT_PAREN"},
        {Kind::LEFT_SQUARE, "LEFT_SQUARE"},
        {Kind::RIGHT_SQUARE, "RIGHT_SQUARE"},
        {Kind::LEFT_CURLY, "LEFT_CURLY"},
        {Kind::RIGHT_CURLY, "RIGHT_CURLY"},
        {Kind::PLUS, "PLUS"},
        {Kind::INCREMENT, "INCREMENT"},
        {Kind::MINUS, "MINUS"},
        {Kind::DECREMENT, "DECREMENT"},
        {Kind::PERCENTAGE, "PERCENTAGE"},
        {Kind::ASTERISK, "ASTERISK"},
        {Kind::LESS_THEN, "LESS_THEN"},
        {Kind::GREATER_THEN, "GREATER_THEN"},
        {Kind::LESS_EQUAL_THEN, "LESS_EQUAL_THEN"},
        {Kind::GREATER_EQUAL_THEN, "GREATER_EQUAL_THEN"},
        {Kind::AMPERSAND, "AMPERSAND"},
        {Kind::AND, "AND"},
        {Kind::PIPE, "PIPE"},
        {Kind::OR, "OR"},
        {Kind::XOR, "XOR"},
        {Kind::ONES_COMPLEMENT, "ONES_COMPLEMENT"},
        {Kind::LEFT_SHIFT, "LEFT_SHIFT"},
        {Kind::LEFT_SHIFT_ASSIGN, "LEFT_SHIFT_ASSIGN"},
        {Kind::RIGHT_SHIFT, "RIGHT_SHIFT"},
        {Kind::RIGHT_SHIFT_ASSIGN, "RIGHT_SHIFT_ASSIGN"},
        {Kind::ADD, "ADD"},
        {Kind::SUBTRACT, "SUBTRACT"},
        {Kind::MULTIPLY, "MULTIPLY"},
        {Kind::DIVIDE, "DIVIDE"},
        {Kind::TAKE_MODULUS, "TAKE_MODULUS"},
        {Kind::BITWISE_AND_ASSIGN, "BITWISE_AND_ASSIGN"},
        {Kind::BITWISE_OR_ASSIGN, "BITWISE_OR_ASSIGN"},
        {Kind::SINGLE_QUOTE, "SINGLE_QUOTE"},
        {Kind::DOUBLE_QUOTE, "DOUBLE_QUOTE"},
        {Kind::PREPROCESSOR, "PREPROCESSOR"},
        {Kind::SYMBOL, "SYMBOL"},
        {Kind::END, "END"},
    };
    std::vector<std::string> keyWords = {
        "auto",
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "NSObject",
        "@property",
        "weak",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "int",
        "@protocol",
        "NSInteger",
        "nonatomic", // ;?
        "unsafe_unretained", // ;?
        "long",
        "register",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "struct",
        "@interface",
        "NSNumber",
        "retain",
        "readwrite",
        "switch",
        "typedef",
        "union",
        "unsigned",
        "void",
        "volatile",
        "while",
        "_Packed",
        "@implementation",
        "CGFloat",
        "strong",
        "readonly"
        "@end",
        "@private",
        "@protected",
        "@public",
        "@try",
        "@throw",
        "@catch",
        "@finally",
        "@class",
        "@import",
        "BOOL",
        "@selector",
        "@protocol",
        "@encode",
        "@sunthesize",
        "@dynamic",
        "@synchronized",
        "@autoreleasepoll",
        "@compatibility_alias",
        "@defs",
        "NSArray",
        "NSLog",
        
        
    };
};

#endif /* Token_h */
