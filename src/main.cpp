#include <iostream>
#include <cstdio>

#include "parser.tab.h"
#include "SyntaxTree/SyntaxTree.h"

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
    yyparse();
    fprintf(output_file, "main:\nli $v0, 10\nsyscall\n");
    fclose(output_file);
    return 0;
}
