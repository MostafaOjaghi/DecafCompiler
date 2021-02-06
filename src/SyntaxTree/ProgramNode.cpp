//
// Created by mostafa on 2/5/21.
//

#include "ProgramNode.h"

#include "Decl.h"

void SyntaxTree::ProgramNode::addDecl(Decl *decl) {
    declerations.push_back(decl);
}

SyntaxTree::Cgen SyntaxTree::ProgramNode::cgen() {
    std::string variables;
    std::string text;
    Cgen cgen;
    for (Decl *decl : declerations) {
        if (dynamic_cast<DeclToVariableDecl *>(decl))
            variables += decl->cgen().code;
        else
            text += decl->cgen().code;
    }
    cgen.code = variables +
            "LCall main\n" +
            "Goto exit\n" +
            text;
    return cgen;
}
