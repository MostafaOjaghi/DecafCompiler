//
// Created by mostafa on 2/6/21.
//

#include "Token.h"

#include <utility>

SyntaxTree::Token::Token(std::string lexeme) : lexeme(std::move(lexeme)) {}

const std::string &SyntaxTree::Token::getLexeme() const {
    return lexeme;
}

void SyntaxTree::Token::setLexeme(const std::string &lexeme) {
    Token::lexeme = lexeme;
}
