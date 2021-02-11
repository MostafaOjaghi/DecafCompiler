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

    yyin = fopen(input_file_path, "r");
    output_file = fopen(output_file_path, "w");

//    yydebug = 1;
    cout << "---------- Parsing: ----------" << endl;
    yyparse();
    cout << "---------- Handle Scope: ----------" << endl;
    root.handleScope();
    cout << "---------- Cgen: ----------" << endl;
    string tac = root.cgen().code;
    cout << tac << endl;
    cout << "---------- asm: ----------" << endl;
    string assembly = TacToAssembly::toAssembly(tac);
    cout << assembly << endl;
//    fprintf(output_file, "main:\nli $v0, 10\nsyscall\n");
    fprintf(output_file, "%s", assembly.c_str());
    fclose(output_file);
    return 0;
}
