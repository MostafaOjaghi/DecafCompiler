//
// Created by mostafa on 2/6/21.
//

#ifndef DECAFCOMPILER_TOKEN_H
#define DECAFCOMPILER_TOKEN_H

#include <string>
#include "Node.h"

namespace SyntaxTree {
    class Token : public Node {
    private:
        std::string lexeme;
    public:
        Token(std::string lexeme);

        const std::string &getLexeme() const;

        void setLexeme(const std::string &lexeme);
    };
}


#endif //DECAFCOMPILER_TOKEN_H
