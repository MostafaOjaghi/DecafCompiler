#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

ofstream outputFile ("ans.txt");
map <string, int> frame_pointer_pos;
map <string, int> global_pointer_pos;
map <string, int> stack_pointer_pos;

int sp;

int gp;

int fp;
int fp_plus;
int fp_minus;
int fp_plus_prev;

string current_func;
string current_label;
int current_func_size;

void beginSetFp() {

    fp_plus_prev = fp_plus;
    fp_minus = -4;
    fp_plus = 0;
}

void endSetFp() {
    fp_plus = fp_plus_prev;
}

string convertIntegerToString(int z) {
    string ret = "";
    if (z == 0)
        ret = "0";
    while (z) {
        ret = char('0' + z%10) + ret;
        z /= 10;
    }
    return ret;
}

void addToFramePointer(string label, string variable, int pos) {

    string temp = label + variable;
    frame_pointer_pos[temp] = pos;
    cout << frame_pointer_pos[temp] << " " << temp << endl;
}

string getPos(string variable, int offset) {

    string temp = "global:";
    // If variable is in current function's frame pointer
    if (frame_pointer_pos.count(current_func + variable)) {

        //outputFile << "sw $t0 " << frame_pointer_pos[current_func.append(variable)] << "($fp) \n";
        return convertIntegerToString(frame_pointer_pos[current_func + variable] + offset)+"($fp)";
    }

        // If variable is a global variable
    else if (global_pointer_pos.count(temp + variable)) {

        //outputFile << "sw $t0 " << global_pointer_pos[temp.append(variable)] << "($gp) \n";
        return convertIntegerToString(global_pointer_pos[temp + variable] + offset)+"($gp)";
    }

        // Variable is a new temporary variable
    else {

        addToFramePointer(current_func, variable, fp_plus);
        cout << "here!!!!! " << current_func + variable << convertIntegerToString(frame_pointer_pos[current_func + variable])<< "\n";
        fp_plus += 4;
        //outputFile << "sw $t0 " << global_pointer_pos[current_func.append(v)] << "($fp) \n";
        return convertIntegerToString(frame_pointer_pos[current_func + variable] + offset)+"($fp)";
    }
}


void getInt (string token) {

    outputFile << "li $v0 5 \n";
    outputFile << "syscall \n";
    outputFile << "sw $v0 " << getPos(token, 0) << "\n";
}

void printInt (string token) {

    outputFile << "li $v0 1 \n";
    outputFile << "lw $t0 " << getPos(token, 0) << "\n";
    outputFile << "move $a0 $t0 \n";
    outputFile << "syscall \n";
}

int main() {

    string line;

    ifstream inputFile ("example_2.txt");

    current_func = "global:";

    if (inputFile.is_open()) {

        int global_flag = true;

        while ( getline(inputFile, line) ) {

            stringstream ss(line);
            string buf;
            vector <string> tokens;

            while (ss >> buf) {

                tokens.push_back(buf);
            }

            cout << line << " " << tokens[0] << endl;

            if (tokens[0] == "Label") {

                global_flag = false;
                current_label = tokens[1];
                outputFile << tokens[1] << "\n";

                if (tokens.size() >= 3) {
                    beginSetFp();
                }

                cout << "label! : " << current_label << endl;
            }

            if (global_flag) {

                // TODO
                // Put global variables in $gp
                continue;
            }

            if (tokens[0] == "Beginfunc") {

                beginSetFp();
                current_func = current_label;
                current_func_size = stoi(tokens[1]);

                int temp = 0;
                for (int i = 2; i < tokens.size(); i++) {
                    addToFramePointer(current_func, tokens[i], current_func_size + temp);
                    temp += 4;
                }

                outputFile << "addiu $sp $sp " << -current_func_size << "\n";
                outputFile << "sw $fp " << current_func_size - 4 << "($sp)\n";
                outputFile << "move $fp $sp\n";

            }

            else if (tokens[0] == "Load") {

                string base = tokens[3].substr(2);
                string v = tokens[5];
                string offset;
                int pos;

                if ((int)tokens.size() == 6) {

                    offset = tokens[5].substr(0, (int)tokens[3].size() - 1);
                }
                else if ((int)tokens.size() == 5) {

                    offset = "0";
                }

                outputFile << "lw $t0 " << getPos(base, stoi(offset)) << "\n";
                outputFile << "sw $t0 " << getPos(v, 0) << "\n";

                // TODO CHECK
            }

            else if (tokens[0] == "Store") {

                string base = tokens[1].substr(2);
                string offset, v;

                if ((int)tokens.size() == 6) {

                    offset = tokens[3].substr(0, (int)tokens[3].size() - 1);
                    v = tokens[5];
                    //cout << base << " " << stack[base] + stoi(offset) << endl;
                }
                else if((int)tokens.size() == 5) {

                    offset = "0";
                    v = tokens[3];
                    //cout << base << " " << stack[base] + stoi(offset) << endl;
                }

                outputFile << "lw $t0 " << getPos(base, stoi(offset)) << "\n";
                outputFile << "lw $t1 " << getPos(v, 0) << "\n";
                outputFile << "sw $t1 ($t0)";

                /*
                if (stack.count(v)) {

                    stack[v] = stack[base] + stoi(offset);
                }
                */

                // TODO
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

                outputFile << "lw $t0 " << getPos(tokens[1], 0) << "\n";
                outputFile << "beq $t0 0 " << tokens[3] << "\n";
            }
            else if (tokens[0] == "ifNZ") {

                outputFile << "lw $t0 " << getPos(tokens[1], 0) << "\n";
                outputFile << "bne $t0 0 " << tokens[3] << "\n";
            }

            else if (tokens[0] == "Assign") {

                // Assign x = t1 op t2

                // arithmatic|logical:
                // lw $t0 stack[t1]
                // lw $t1 stack[t2]
                // op $t0 $t0 $t1
                // if x has an address : sw $t0 stack[x]($sp)
                // else : sw $t0 stack[sp]($sp); sp+=4

                if (tokens.size() == 5) {

                    outputFile << "lw $t0 " << getPos(tokens[4], 0) << "\n";
                    if (tokens[3] == "-") {
                        outputFile << "mul $t0 $t0 -1\n";
                    }
                    else if (tokens[3] == "!") {
                        outputFile << "seq $t0 $t0 0\n";
                    }
                    outputFile << "sw $t0 " << getPos(tokens[1], 0) << "\n";
                    continue;
                }

                string t1 = tokens[3];
                string t2 = tokens[5];
                string op = tokens[4];
                string x = tokens[1];

                outputFile << "lw $t0 " << getPos(t1, 0) << "\n";
                outputFile << "lw $t1 " << getPos(t2, 0) << "\n";

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

                else if (op == "<") {
                    outputFile << "slt $t0 $t0 $t1\n";
                }

                else if (op == ">") {
                    outputFile << "sgt $t0 $t0 $t1\n";
                }

                else if (op == "<=") {
                    outputFile << "sle $t0 $t0 $t1\n";
                }

                else if (op == ">=") {
                    outputFile << "sge $t0 $t0 $t1\n";
                }

                else if (op == "==") {
                    outputFile << "seq $t0 $t0 $t1\n";
                }

                else if (op == "!=") {
                    outputFile << "sne $t0 $t0 $t1\n";
                }

                else if (op == "&&" || op == "&") {
                    outputFile << "and $t0 $t0 $t1\n";
                }

                else if (op == "||" || op == "|") {
                    outputFile << "or $t0 $t0 $t1\n";
                }

                outputFile << "sw $t0 " << getPos(x, 0) << "\n";
            }

            else if (tokens[0] == "Pushparam") {

                outputFile << "addi $sp $sp -4\n";
                outputFile << "lw $t0 " << getPos(tokens[1], 0) << "\n";
                outputFile << "sw $t0 0($sp)\n";
            }

            else if (tokens[0] == "Lcall") {

                outputFile << "jal " << tokens[1].substr(0, tokens[1].size()) << "\n";
                outputFile << "sw $v0 " << getPos(tokens[2], 0) << "\n";
            }

            else if (tokens[0] == "Popparams") {

                outputFile << "addi $sp $sp " << stoi(tokens[1]) << "\n";
            }

            else if (tokens[0] == "Endfunc") {

                sp -= current_func_size;

                endSetFp();


                if (tokens.size() == 2) {
                    outputFile << "sw $t0 " << getPos(tokens[1], 0) << "\n";
                    outputFile << "addi $v0 $t0 0\n";
                }
                outputFile << "move $sp $fp\n";
                outputFile << "lw $fp " << current_func_size - 4 << "($sp)\n";
                outputFile << "addiu $sp $sp " << current_func_size << "\n";
                if (current_func != "main:") {
                    outputFile << "jr $ra \n";
                }
                else {
                    outputFile << "j Exit\n";
                }

            }


        }
        inputFile.close();
    }

    else cout << "Unable to open file";

    outputFile << "Exit:\n";
    outputFile.close();

    return 0;

}