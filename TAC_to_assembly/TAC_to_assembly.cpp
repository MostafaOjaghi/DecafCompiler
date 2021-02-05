#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

ofstream outputFile ("ans.txt");
map <string, int> stack;
int sp;

void getInt (string token) {
    
    outputFile << "li $v0 5 \n";
    outputFile << "syscall \n";
    
    if(!stack.count(token)) {
        outputFile << "sw $v0 " << sp << "($sp)\n";
        stack[token] = sp;
        sp += 4;
    }
    else {
        outputFile << "sw $v0 " << stack[token] << "($sp)\n";
    }
}

void printInt (string token) {

    outputFile << "li $v0 1 \n";
    outputFile << "lw $t0 " << stack[token] << "($sp)\n";
    outputFile << "move $a0 $t0 \n";
    outputFile << "syscall \n";
}

int main () {
    
    string line;
    
    ifstream inputFile ("example.txt");
    
    
    if (inputFile.is_open()) {
        
        while ( getline(inputFile, line) ) {
            
            stringstream ss(line);
            string buf;
            vector <string> tokens;
            
            while (ss >> buf) {
                
                tokens.push_back(buf);
            }
            
             cout << line << " " << tokens[0] << endl;
            
            // The line is split by spaces. Its words are kept in "tokens".
            
            if (tokens[0] == "Label") {
                
                outputFile << tokens[1] << "\n";
            }
            
            else if (tokens[0] == "Load") {
                
                string base = tokens[3].substr(2);
                string v = tokens[5];
                string offset;
                
                if ((int)tokens.size() == 6) {
                    
                    offset = tokens[5].substr(0, (int)tokens[3].size() - 1);
                }
                else if ((int)tokens.size() == 5) {
                    
                    offset = "0";
                }
                
                outputFile << "lw $t0 " << stack[base] + stoi(offset) << "($sp) \n";
                outputFile << "sw $t0 " << stack[v] << "($sp) \n";
            }
            
            else if (tokens[0] == "Store") {
                
                string base = tokens[1].substr(2);
                string offset, v;
                
                if ((int)tokens.size() == 6) {

                    offset = tokens[3].substr(0, (int)tokens[3].size() - 1);
                    v = tokens[5];
                    
                    cout << base << " " << stack[base] + stoi(offset) << endl;
                }
                else if((int)tokens.size() == 5) {
                    
                    offset = "0";
                    v = tokens[3];
                    
                    cout << base << " " << stack[base] + stoi(offset) << endl;
                }
                    
                outputFile << "lw $t0 " << stack[base] + stoi(offset) << "($sp) \n";
                outputFile << "lw $t1 " << stack[v] << "($sp) \n";
                outputFile << "sw $t1 ($t0)";
                
                if (stack.count(v)) {
                    
                    stack[v] = stack[base] + stoi(offset);
                }
            }
            
            else if (tokens[0] == "Input") {
                
                // getting an input
                // storing it as token[1] in stack pointer
                
                getInt(tokens[1]);
            }
            
            else if (tokens[0] == "Output") {
                
                // print whats in token[1]

                printInt(tokens[1]);
            }
            
            else if (tokens[0] == "ifZ") {
                
                outputFile << "lw $t0 " << stack[tokens[1]] << "($sp)\n";
                outputFile << "beq $t0 0 " << tokens[3] << "\n";
            }
            else if (tokens[0] == "ifNZ") {
                
                outputFile << "lw $t0 " << stack[tokens[1]] << "($sp)\n";
                outputFile << "bne $t0 0 " << tokens[3] << "\n";
                cout << "here!";
            }
            
            else if (tokens[0] == "Assign") {
                
                // Assign x = t1 op t2
                
                // lw $t0 stack[t1]
                // lw $t1 stack[t2]
                // op $t0 $t0 $t1
                // if x has an address : sw $t0 stack[x]($sp)
                // else : sw $t0 stack[sp]($sp); sp+=4
                
                string t1 = tokens[3];
                string t2 = tokens[5];
                string op = tokens[4];
                string x = tokens[1];
                
                outputFile << "lw $t0 " << stack[t1] << "($sp) \n";
                outputFile << "lw $t1 " << stack[t2] << "($sp) \n";
                
                if (op == "+") {
                    outputFile << "add $t0 $t0 $t1\n";
                }
                else if (op == "-") {
                    outputFile << "sub $t0 $t0 $t1\n";
                }
                else if (op == "*") {
                    outputFile << "mul $t0 $t0 $t1\n";
                }
                else if (op == "/") {
                    outputFile << "div $t0 $t0 $t1\n";
                }
                else if (op == "%") {
                    outputFile << "rem $t0 $t0 $t1\n";
                }
                if (stack.count(x)) {
                    outputFile << "sw $t0 " << stack[x] << "($sp) \n";
                }
                else {
                    outputFile << "sw $t0 " << sp << "($sp) \n";
                    stack[x] = sp;
                    sp += 4;
                }
            }
        }
        inputFile.close();
    }
    
    else cout << "Unable to open file";
    
    outputFile.close();
    
    return 0;
}










