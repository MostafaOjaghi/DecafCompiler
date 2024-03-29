#include <iostream>
#include <cstdio>
#include "parser.tab.h"

#include "SyntaxTree/SyntaxTree.h"
#include "TacToAssembly.h"

extern FILE *yyin, *output_file;

using namespace std;

SyntaxTree::ProgramNode root;

int main(int argc, char* argv[]) {
    if (argc < 5 ){
        cerr<< "Usage: " << argv[0] << " -i <input> -o <output>" << endl ;
        return 1;
    }

    char *input_file_path = argv[2];
    char *output_file_path = argv[4];

    std::string input = "tests/";
    input += input_file_path;
    std::string output = "out/";
    output += output_file_path;
    yyin = fopen(input.c_str(), "r");
    output_file = fopen(output.c_str(), "w");

//    yydebug = 1;
    cout << "---------- Parsing: ----------" << endl;
    yyparse();
    cout << "---------- Handle Scope: ----------" << endl;
    root.handleScope();
    cout << "---------- Class Hierarchy ----------" << endl;
    root.handleClassHierarchy();
//    cout << "=== scope check ===\n";
//    for (auto scope : SymbolTable::Scope::getDefinedScopes()) {
//        std::cout << scope->getName() << ' ';
//        if (scope->getPar() != nullptr)
//            std::cout << scope->getPar()->getName();
//        std::cout << std::endl;
//        cout << ":: ";
//        for (auto y: scope->getEntries())
//            cout << y->getUniqueId() << " ";
//        cout << endl;
//        cout << endl;
//    }
    cout << "---------- Cgen: ----------" << endl;
    string tac = root.cgen().code;
//    cout << tac << endl;
    cout << "---------- asm: ----------" << endl;
    string assembly = TacToAssembly::toAssembly(tac);
//    cout << assembly << endl;
    fprintf(output_file, "%s", assembly.c_str());
    fclose(output_file);
    return 0;
}
