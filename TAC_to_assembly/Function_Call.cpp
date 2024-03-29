#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

ofstream outputFile ("ans.txt");
stringstream output;
map <string, int> frame_pointer_pos;
map <string, int> global_pointer_pos;
map <string, int> stack_pointer_pos;

vector <string> stringLiterals;

#define SIZE(x) ((int)(x).size())

int sp;

int gp;

int floatBranchLabelCnt;
int outputBooleanBranchLabelCnt;
int appendStringcnt;
int appendArraycnt;
int compareStringCnt;

const int string_size = 100;

int fp;
int fp_plus;
int fp_minus;

string current_func;
string current_label;
int current_func_size;

void beginSetFp() {

    fp_minus = -4;
    fp_plus = 0;
}

string convertIntegerToString(int z) {
    string ret = "";
    if (z == 0)
        ret = "0";
    bool isNeg = false;
    if (z < 0) {
        isNeg = true;
        z = abs(z);
    }
    while (z) {
        ret = char('0' + z%10) + ret;
        z /= 10;
    }
    if (isNeg)
        ret = "-" + ret;
    return ret;
}

void addToFramePointer(string label, string variable, int pos) {

    string temp = label + variable;
    frame_pointer_pos[temp] = pos;
    //cout << pos << "ejlali" << endl;
    //cout << frame_pointer_pos[temp] << " " << temp << endl;
}

void addToGlobal(string variable) {

    global_pointer_pos["global:" + variable] = gp;
}

string getPos(string variable, int offset) {


    if (offset == 1) {

        string temp = "global:";
        if (global_pointer_pos.count(temp + variable)) {
            return convertIntegerToString(global_pointer_pos[temp + variable])+"($gp)";
        }

        // If variable is global but was not added
        addToGlobal(variable);
        gp += 4;
        return convertIntegerToString(global_pointer_pos[temp + variable])+"($gp)";
    }
    string temp = "global:";

    // If variable is in current function's frame pointer
    if (frame_pointer_pos.count(current_func + variable)) {

        //output << "sw $t0 " << frame_pointer_pos[current_func.append(variable)] << "($fp) \n";
        return convertIntegerToString(frame_pointer_pos[current_func + variable] + offset)+"($fp)";
    }

    // If variable is a global variable
    else if (global_pointer_pos.count(temp + variable)) {

        //output << "sw $t0 " << global_pointer_pos[temp.append(variable)] << "($gp) \n";
        return convertIntegerToString(global_pointer_pos[temp + variable] + offset)+"($gp)";
    }

    // If variable is global but was not added
    else if (current_func == temp) {


        addToGlobal(variable);
        gp += 4;
        return convertIntegerToString(global_pointer_pos[temp + variable] + offset)+"($gp)";
    }

    // Variable is a new temporary variable
    else {

        addToFramePointer(current_func, variable, fp_minus);
        //cout << "here!!!!! " << current_func + variable << convertIntegerToString(frame_pointer_pos[current_func + variable])<< "\n";
        fp_minus -= 4;
        return convertIntegerToString(frame_pointer_pos[current_func + variable] + offset)+"($fp)";
    }
}


void getInt (string token) {

    output << "li $v0 5 \n";
    output << "syscall \n";
    output << "sw $v0 " << getPos(token, 0) << "\n";
}

void getFloat (string token) {

    output << "li $v0 6 \n";
    output << "syscall \n";
    output << "s.s $f0 " << getPos(token, 0) << "\n";
}

void getString (string token) {
    static int n = 0;

    output << "li $a0 " << string_size << "\n";
    output << "li $v0 9\n";
    output << "syscall\n";
    output << "sw $v0 " << getPos(token, 0) << "\n";

    output << "li $v0 8\n";
    output << "lw $a0 " << getPos(token, 0) << "\n";
    output << "li $a1 " << string_size << "\n";
    output << "syscall\n";

    string label = "__ReadLineLabel" + to_string(n++);
    string label2 = label + "_1";
    output << "li $t0 " << string_size << "\n";
    output << "add $t0 $t0 $a0\n";
    output << label << ":\n";
    output << "addi $t0 $t0 -1\n";
    output << "lb $t1 ($t0)\n";
    output << "li $t2 10\n";
    output << "bne $t1 $t2 " << label2 << "\n";
    output << "sb $0 ($t0)\n";
    output << label2 << ": beq $t1 $0 " << label << "\n";
}

void printInt (string token) {

    output << "li $v0 1 \n";
    output << "lw $t0 " << getPos(token, 0) << "\n";
    output << "move $a0 $t0 \n";
    output << "syscall \n";
}

void printFloat (string token) {

    output << "li $v0 2 \n";
    output << "l.s $f12 " << getPos(token, 0) << "\n";
    output << "syscall \n";
}

void printString (string token) {

    output << "lw $a0 " << getPos(token, 0) << "\n";
    output << "li $v0 4\n";
    output << "syscall \n";
}

void  printBool (string token) {

    output << "lw $t0 " << getPos(token, 0) << "\n";
    output << "bne $t0 0 _outputBoolIsTrue_" << outputBooleanBranchLabelCnt << "\n";
    output << "la $a0 false\n";
    output << "j _outputBoolContinue_" << outputBooleanBranchLabelCnt << "\n";
    output << "_outputBoolIsTrue_" << outputBooleanBranchLabelCnt << ":\n";
    output << "la $a0 true\n";
    output << "_outputBoolContinue_" << outputBooleanBranchLabelCnt << ":\n";
    output << "li $v0 4\n";
    output << "syscall\n";
    outputBooleanBranchLabelCnt++;
}

void convertFloatToInt(string a, string b) {

    output << "l.s $f0 " << getPos(b, 0) << "\n";
    output << "cvt.w.s $f0 $f0\n";
    output << "mfc1 $t0 $f0\n";
    output << "sw $t0 " << getPos(a, 0) << "\n";
}

void convertIntToFloat(string a, string b) {

    output << "lw $t0 " << getPos(b, 0) << "\n";
    output << "mtc1 $t0 $f0\n";
    output << "cvt.s.w $f0 $f0\n";
    output << "s.s $f0 " << getPos(a, 0) << "\n";
}

void appendString(string a, string b, string c) {

    // t0 is the address of b
    output << "lw $t0 " << getPos(b, 0) << "\n";
    // t1 is the address of c
    output << "lw $t1 " << getPos(c, 0) << "\n";
    // allocate space for result
    output << "li $a0 " << string_size << "\n";
    output << "li $v0 9\n";
    output << "syscall\n";
    output << "sw $v0 " << getPos(a, 0) << "\n";

    // $t2 is the address of a
    output << "lw $t2 " << getPos(a, 0) << "\n";

    output << "_appendStringLoop1_" << appendStringcnt << "_:\n";
    output << "lb $t3 ($t0)\n";
    output << "beq $t3 0 _appendStringExit1_" << appendStringcnt << "_\n";
    output << "sb $t3 ($t2)\n";
    output << "addi $t0 $t0 1\n";
    output << "addi $t2 $t2 1\n";
    output << "j _appendStringLoop1_" << appendStringcnt << "_\n";
    output << "_appendStringExit1_" << appendStringcnt << "_:\n";
    output << "_appendStringLoop2_" << appendStringcnt << "_:\n";
    output << "lb $t3 ($t1)\n";
    output << "beq $t3 0 _appendStringExit2_" << appendStringcnt << "_\n";
    output << "sb $t3 ($t2)\n";
    output << "addi $t1 $t1 1\n";
    output << "addi $t2 $t2 1\n";
    output << "j _appendStringLoop2_" << appendStringcnt << "_\n";
    output << "_appendStringExit2_" << appendStringcnt << "_:\n";


    appendStringcnt++;
}

void appendArray(string a, string b, string c) {

    // t0 is the address of b
    output << "lw $t0 " << getPos(b, 0) << "\n";
    // t1 is the address of c
    output << "lw $t1 " << getPos(c, 0) << "\n";

    output << "lw $t4 ($t0)\n";
    output << "lw $t5 ($t1)\n";
    output << "addi $t0 $t0 4\n";
    output << "addi $t1 $t1 4\n";

    // allocate space for result
    output << "add $a0 $t4 $t5\n";
    output << "addi $a0 $a0 1\n";
    output << "sll $a0 $a0 2\n";
    output << "li $v0 9\n";
    output << "syscall\n";
    output << "srl $a0 $a0 2\n";
    output << "li $t7 1\n";
    output << "sub $a0 $a0 $t7\n";
    output << "sw $a0 ($v0)\n";
    output << "sw $v0 " << getPos(a, 0) << "\n";

    // $t2 is the address of a
    output << "lw $t2 " << getPos(a, 0) << "\n";
    output << "li $t6 0\n";
    output << "addi $t2 $t2 4\n";

    output << "_appendArrayLoop1_" << appendArraycnt << "_:\n";
    output << "lw $t3 ($t0)\n";
    output << "beq $t6 $t4 _appendArrayExit1_" << appendArraycnt << "_\n";
    output << "sw $t3 ($t2)\n";
    output << "addi $t6 $t6 1\n";
    output << "addi $t0 $t0 4\n";
    output << "addi $t2 $t2 4\n";
    output << "j _appendArrayLoop1_" << appendArraycnt << "_\n";
    output << "_appendArrayExit1_" << appendArraycnt << "_:\n";

    output << "li $t6 0\n";
    output << "_appendArrayLoop2_" << appendArraycnt << "_:\n";
    output << "lw $t3 ($t1)\n";
    output << "beq $t6 $t5 _appendArrayExit2_" << appendArraycnt << "_\n";
    output << "sw $t3 ($t2)\n";
    output << "addi $t6 $t6 1\n";
    output << "addi $t1 $t1 4\n";
    output << "addi $t2 $t2 4\n";
    output << "j _appendArrayLoop2_" << appendArraycnt << "_\n";
    output << "_appendArrayExit2_" << appendArraycnt << "_:\n";


    appendArraycnt++;
}

void compareString(string b, string s1, string s2, string op) {

    // s1 address
    output << "lw $t0 " << getPos(s1, 0) << "\n";
    // s2 address
    output << "lw $t1 " << getPos(s2, 0) << "\n";

    output << "_compareStringLoop_" << compareStringCnt << "_:\n";
    output << "lb $t2 ($t0)\n";
    output << "lb $t3 ($t1)\n";
    output << "beq $t2 0 _compareStringEnd1_" << compareStringCnt << "_\n";
    output << "beq $t3 0 _compareStringGreater_" << compareStringCnt << "_\n";
    output << "blt $t2 $t3 _compareStringLess_" << compareStringCnt << "_\n";
    output << "addi $t0 $t0 1\n";
    output << "addi $t1 $t1 1\n";
    output << "beq $t2 $t3 _compareStringLoop_" << compareStringCnt << "_\n";
    output << "j _compareStringGreater_" << compareStringCnt << "_\n";

    output << "_compareStringEnd1_" << compareStringCnt << "_:\n";
    output << "beq $t3 0 _compareStringEqual_" << compareStringCnt << "_\n";
    output << "j _compareStringLess_" << compareStringCnt << "_\n";
    output << "_compareStringLess_" << compareStringCnt << "_:\n";
    if (op == "<")
        output << "li $t4 1\n";
    else
        output << "li $t4 0\n";
    output << "j _compareStringFinal_" << compareStringCnt << "_\n";
    output << "_compareStringGreater_" << compareStringCnt << "_:\n";
    output << "li $t4 0\n";
    output << "j _compareStringFinal_" << compareStringCnt << "_\n";
    output << "_compareStringEqual_" << compareStringCnt << "_:\n";
    if (op == "<")
        output << "li $t4 0\n";
    else
        output << "li $t4 1\n";
    output << "_compareStringFinal_" << compareStringCnt << "_:\n";
    output << "sw $t4 " << getPos(b, 0) << "\n";

    compareStringCnt++;
}

string tacToAssembly(istream &inputFile) {
    output.clear();

    stringstream vtables;
    string line;
    current_func = "global:";

    int global_flag = true;


    //macro:
    /*
    output << ".macro printBool(%s0)\n";
    output << "bne %s0 0 outputBoolIsTrue\n";
    output << "la $a0 false\n";
    output << "j outputBoolContinue\n";
    output << "outputBoolIsTrue:\n";
    output << "la $a0 true\n";
    output << "outputBoolContinue:\n";
    output << "li $v0 4\n";
    output << "syscall\n";
    output << ".end_macro\n";
    */

    while ( getline(inputFile, line) ) {

        stringstream ss(line);
        string buf;
        vector <string> tokens;

        if (line.empty()) {
            continue;
        }

        while (ss >> buf) {

            tokens.push_back(buf);
        }

        //cout << line << " " << tokens[0] << endl;

        if (tokens[0] == "Label") {

            global_flag = false;
            current_label = tokens[1];
            output << tokens[1] << "\n";

            //cout << "label! : " << current_label << endl;

            int temp = 8;
            for (int i = 2; i < SIZE(tokens); i++) {
                addToFramePointer(current_label, tokens[i], temp);
                temp += 4;
            }
        } else if (tokens[0] == "Beginfunc") {

            beginSetFp();
            current_func = current_label;
            current_func_size = stoi(tokens[1]);

            output << "addiu $sp $sp " << -current_func_size << "\n";

        } else if (tokens[0] == "Addr") {

            string variable = tokens[3].substr(1);
            string address = tokens[1];

            output << "la $t0 " << getPos(variable, 0) << "\n";
            output << "sw $t0 " << getPos(address, 0) << "\n";
        } else if (tokens[0] == "Load") {

            string base;
            string v = tokens[1];
            string offset;
            int pos;

            if (SIZE(tokens) == 6) {

                base = tokens[3].substr(2, SIZE(tokens[3]) - 1);
                offset = tokens[5].substr(0, SIZE(tokens[5]) - 1);
                //cout << "LOOOOK!!!" << offset << endl << endl;
//                cout << "1\n";
            } else if (SIZE(tokens) == 4) {

                base = tokens[3].substr(2, SIZE(tokens[3]) - 3);
                offset = "0";
//                cout << "2\n";
            }

//            cout << base << " base " << offset << " offset " << v << " v\n" ;

            output << "lw $t0 " << getPos(base, 0) << "\n";
            output << "lw $t1 " << stoi(offset) * 4 << "($t0)\n";
            output << "sw $t1 " << getPos(v, 0) << "\n";
            /*
            output << "lw $t0 " << getPos(base, stoi(offset)) << "\n";
            output << "sw $t0 " << getPos(v, 0) << "\n";
            */

            // TODO CHECK
        } else if (tokens[0] == "Store") {

            string base;
            string offset, v;

            if (SIZE(tokens) == 6) {

                base = tokens[1].substr(2, SIZE(tokens[1]) - 1);
                offset = tokens[3].substr(0, SIZE(tokens[3]) - 1);
                //cout <<  "aa" << tokens[3].substr(0, SIZE(tokens[3]) - 1) << "aa " << SIZE(tokens[3]) << endl;
                v = tokens[5];
//                cout << "3\n";
                //cout << base << endl;
            } else if (SIZE(tokens) == 4) {

                offset = "0";
                v = tokens[3];
//                cout << "4\n";
                //string s = "01234567\n";
                //cout << s.substr(2, 2) << endl;
                //cout <<  "aa  " << tokens[1].substr(2, SIZE(tokens[1]) - 1) << "  aa " << SIZE(tokens[1]) << endl;
                base = tokens[1].substr(2, SIZE(tokens[1]) - 3);
                //cout << base << " " << stack[base] + stoi(offset) << endl;
            }

//            cout << base << " base " << offset << " offset " << v << " v\n" ;

            output << "lw $t0 " << getPos(base, 0) << "\n";
            output << "lw $t1 " << getPos(v, 0) << "\n";
            output << "sw $t1 " << stoi(offset) * 4 << "($t0)\n";

            /*
            output << "lw $t0 " << getPos(base, stoi(offset)) << "\n";
            output << "lw $t1 " << getPos(v, 0) << "\n";
            output << "sw $t1 ($t0)";


            if (stack.count(v)) {

                stack[v] = stack[base] + stoi(offset);
            }
            */

            // TODO
        } else if (tokens[0] == "LoadF") {

            string base;
            string v = tokens[1];
            string offset;
            int pos;

            if (SIZE(tokens) == 6) {

                base = tokens[3].substr(2, SIZE(tokens[3]) - 1);
                offset = tokens[5].substr(0, SIZE(tokens[5]) - 1);
            } else if (SIZE(tokens) == 4) {

                base = tokens[3].substr(2, SIZE(tokens[3]) - 3);
                offset = "0";
            }

            output << "lw $t0 " << getPos(base, 0) << "\n";
            output << "l.s $f0 " << stoi(offset) * 4 << "($t0)\n";
            output << "s.s $f0 " << getPos(v, 0) << "\n";
        } else if (tokens[0] == "StoreF") {

            string base;
            string offset, v;

            if (SIZE(tokens) == 6) {

                base = tokens[1].substr(2, SIZE(tokens[1]) - 1);
                offset = tokens[3].substr(0, SIZE(tokens[3]) - 1);
                v = tokens[5];
            } else if (SIZE(tokens) == 4) {

                offset = "0";
                v = tokens[3];
                base = tokens[1].substr(2, SIZE(tokens[1]) - 3);
            }

            output << "lw $t0 " << getPos(base, 0) << "\n";
            output << "l.s $f0 " << getPos(v, 0) << "\n";
            output << "s.s $f0 " << stoi(offset) * 4 << "($t0)\n";

        } else if (tokens[0] == "Input") {

            // getting an input
            // storing it as token[1] in stack pointer

            getInt(tokens[1]);
        } else if (tokens[0] == "InputS") {

            getString(tokens[1]);
        } else if (tokens[0] == "InputF") {

            getFloat(tokens[1]);
        } else if (tokens[0] == "OutputF") {

            printFloat(tokens[1]);
        } else if (tokens[0] == "OutputS") {

                printString(tokens[1]);
        } else if (tokens[0] == "Output") {

            // print whats in token[1]

            printInt(tokens[1]);
        } else if (tokens[0] == "OutputB") {

            printBool(tokens[1]);
        } else if (tokens[0] == "IfZ") {

            output << "lw $t0 " << getPos(tokens[1], 0) << "\n";
            output << "beq $t0 0 " << tokens[3] << "\n";
        } else if (tokens[0] == "IfNZ") {

            output << "lw $t0 " << getPos(tokens[1], 0) << "\n";
            output << "bne $t0 0 " << tokens[3] << "\n";
        } else if (tokens[0] == "Assign") {

            // Assign x = t1 op t2

            // arithmetic | logical:
            // lw $t0 stack[t1]
            // lw $t1 stack[t2]
            // op $t0 $t0 $t1
            // if x has an address : sw $t0 stack[x]($sp)
            // else : sw $t0 stack[sp]($sp); sp+=4

            if (SIZE(tokens) == 4) {

                if (tokens[3][0] <= '9' && tokens[3][0] >= '0') {

                    output << "li $t0 " << tokens[3] << "\n";
                }
                else {
                    output << "lw $t0 " << getPos(tokens[3], 0) << "\n";
                }
                output << "sw $t0 " << getPos(tokens[1], 0) << "\n";
                continue;
            } else if (SIZE(tokens) == 5) {

                output << "lw $t0 " << getPos(tokens[4], 0) << "\n";
                if (tokens[3] == "-") {
                    output << "mul $t0 $t0 -1\n";
                } else if (tokens[3] == "!") {
                    output << "seq $t0 $t0 0\n";
                }
                output << "sw $t0 " << getPos(tokens[1], 0) << "\n";
                continue;
            }

            string t1 = tokens[3];
            string t2 = tokens[5];
            string op = tokens[4];
            string x = tokens[1];

            if (t1[0] <= '9' && t1[0] >= '0') {
                output << "li $t0 " << t1 << "\n";
            } else {
                output << "lw $t0 " << getPos(t1, 0) << "\n";
            }
            if (t2[0] <= '9' && t2[0] >= '0') {
                output << "li $t1 " << t2 << "\n";
            } else {
                output << "lw $t1 " << getPos(t2, 0) << "\n";
            }

            if (op == "+") {
                output << "add $t0 $t0 $t1\n";
            } else if (op == "-") {
                output << "sub $t0 $t0 $t1\n";
            } else if (op == "*") {
                output << "mul $t0 $t0 $t1\n";
            } else if (op == "/") {
                output << "div $t0 $t0 $t1\n";
            } else if (op == "%") {
                output << "rem $t0 $t0 $t1\n";
            } else if (op == "<") {
                output << "slt $t0 $t0 $t1\n";
            } else if (op == ">") {
                output << "sgt $t0 $t0 $t1\n";
            } else if (op == "<=") {
                output << "sle $t0 $t0 $t1\n";
            } else if (op == ">=") {
                output << "sge $t0 $t0 $t1\n";
            } else if (op == "==") {
                output << "seq $t0 $t0 $t1\n";
            } else if (op == "!=") {
                output << "sne $t0 $t0 $t1\n";
            } else if (op == "&&" || op == "&") {
                output << "and $t0 $t0 $t1\n";
            } else if (op == "||" || op == "|") {
                output << "or $t0 $t0 $t1\n";
            }

            output << "sw $t0 " << getPos(x, 0) << "\n";
        } else if (tokens[0] == "AssignS") {

            string temp = "__string_";
            temp += tokens[1];
            temp += "_: .asciiz ";
            temp += line.substr(11 + SIZE(tokens[1]), SIZE(line));
            temp += "\n";
            stringLiterals.push_back(temp);
            string addressLabel = "__string_" + tokens[1] + "_";
            output << "la $t0 " << addressLabel << "\n";
            output << "sw $t0 " << getPos(tokens[1], 0) << "\n";
        } else if (tokens[0] == "CompareS") {

            compareString(tokens[1], tokens[3], tokens[5], tokens[4]);
        } else if (tokens[0] == "AppendS") {

            appendString(tokens[1], tokens[3], tokens[5]);
        } else if (tokens[0] == "AppendA") {

            appendArray(tokens[1], tokens[3], tokens[5]);
        } else if (tokens[0] == "AssignF") {

            if (SIZE(tokens) == 4) {

                if (tokens[3][0] <= '9' && tokens[3][0] >= '0') {

                    output << "li.s $f0 " << tokens[3] << "\n";
                }
                else {
                    output << "l.s $f0 " << getPos(tokens[3], 0) << "\n";
                }
                output << "s.s $f0 " << getPos(tokens[1], 0) << "\n";
                continue;
            } else if (SIZE(tokens) == 5) {

                output << "l.s $f0 " << getPos(tokens[4], 0) << "\n";
                if (tokens[3] == "-") {
                    output << "neg.s $f0 $f0\n";
                }
                output << "s.s $f0 " << getPos(tokens[1], 0) << "\n";
                continue;
            }

            string t1 = tokens[3];
            string t2 = tokens[5];
            string op = tokens[4];
            string x = tokens[1];

            if (t1[0] <= '9' && t1[0] >= '0') {
                output << "li.s $f0 " << t1 << "\n";
            } else {
                output << "l.s $f0 " << getPos(t1, 0) << "\n";
            }
            if (t2[0] <= '9' && t2[0] >= '0') {
                output << "li.s $f1 " << t2 << "\n";
            } else {
                output << "l.s $f1 " << getPos(t2, 0) << "\n";
            }


            int immediate = 0;
            int not_immediate = 1;
            bool compareFlag = true;

            if (op == "+") {
                output << "add.s $f0 $f0 $f1\n";
                compareFlag = false;
            } else if (op == "-") {
                output << "sub.s $f0 $f0 $f1\n";
                compareFlag = false;
            } else if (op == "*") {
                output << "mul.s $f0 $f0 $f1\n";
                compareFlag = false;
            } else if (op == "/") {
                output << "div.s $f0 $f0 $f1\n";
                compareFlag = false;
            } else if (op == "<") {
                output << "c.lt.s $f0 $f1\n";
            } else if (op == ">") {
                output << "c.lt.s $f1 $f0\n";
            } else if (op == "<=") {
                output << "c.le.s $f0 $f1\n";
            } else if (op == ">=") {
                output << "c.le.s $f1 $f0\n";
            } else if (op == "==") {
                output << "c.eq.s $f0 $f1\n";
            } else if (op == "!=") {
                output << "c.eq.s $f0 $f1\n";
                immediate = 1;
                not_immediate = 0;
            }

            if (compareFlag) {
                output << "li $t0 " << immediate <<"\n";
                output << "bc1t _floatFlagCompareIsTrue_" << floatBranchLabelCnt << "\n";
                output << "j _floatFlagCompareContinue_" << floatBranchLabelCnt << "\n";;
                output << "_floatFlagCompareIsTrue_" << floatBranchLabelCnt << ":\n";
                output << "li $t0 "<< not_immediate << "\n";
                output << "_floatFlagCompareContinue_" << floatBranchLabelCnt << ":\n";
                output << "sw $t0 " << getPos(x, 0) << "\n";
                floatBranchLabelCnt++;
                continue;
            }
            output << "s.s $f0 " << getPos(x, 0) << "\n";
        } else if (tokens[0] == "FTOI") {

            convertFloatToInt(tokens[1], tokens[3]);
        } else if (tokens[0] == "ITOF") {

            convertIntToFloat(tokens[1], tokens[3]);
        } else if (tokens[0] == "Vtable") {

            vtables << "li $a0 " << 4 * (SIZE(tokens) - 3) << "\n";
            vtables << "li $v0 9\nsyscall\n";
            vtables << "sw $v0 " << getPos(tokens[1], 1) << "\n"; // code for vtable

            int cnt = 0;

            vtables << "lw $t1 " << getPos(tokens[1], 1) << "\n";
            vtables << "li $t0 " << tokens[3] << "\n";
            vtables << "sw $t0 " << cnt * 4 << "($t1)\n";
            cnt++;
            for (int i = 4; i < SIZE(tokens); i++) {
                vtables << "la $t0 " << tokens[i] << "\n";
                vtables << "sw $t0 " << cnt * 4 << "($t1)\n";
                cnt++;
            }
            /*
            string temp = "";
            temp += tokens[1];
            temp += ": .word ";
            temp += line.substr(10 + SIZE(tokens[1]), SIZE(line));
            temp += "\n";

            vtables.push_back(temp);
            */
        } else if (tokens[0] == "Pushparam") {

            output << "addi $sp $sp -4\n";
            output << "lw $t0 " << getPos(tokens[1], 0) << "\n";
            output << "sw $t0 0($sp)\n";
        } else if (tokens[0] == "PushparamF") {

            output << "addi $sp $sp -4\n";
            output << "l.s $f0 " << getPos(tokens[1], 0) << "\n";
            output << "s.s $f0 0($sp)\n";
        } else if (tokens[0] == "Lcall") {

            output << "addi $sp $sp -4\n";
            output << "sw $ra ($sp)\n";
            output << "addi $sp $sp -4\n";
            output << "sw $fp ($sp)\n";
            output << "move $fp $sp\n";
            output << "jal " << tokens[1] << "\n";
            output << "lw $fp ($sp)\n";
            output << "addi $sp $sp 4\n";
            output << "lw $ra ($sp)\n";
            output << "addi $sp $sp 4\n";
            if (SIZE(tokens) == 4) {
                output << "sw $v0 " << getPos(tokens[3], 0) << "\n";
            }
        } else if (tokens[0] == "Acall") {

            output << "lw $t0 " << getPos(tokens[1], 0) << "\n";
            output << "addi $sp $sp -4\n";
            output << "sw $ra ($sp)\n";
            output << "addi $sp $sp -4\n";
            output << "sw $fp ($sp)\n";
            output << "move $fp $sp\n";
            output << "jalr $t0\n";
            output << "lw $fp ($sp)\n";
            output << "addi $sp $sp 4\n";
            output << "lw $ra ($sp)\n";
            output << "addi $sp $sp 4\n";
            if (SIZE(tokens) == 4) {
                output << "sw $v0 " << getPos(tokens[3], 0) << "\n";
            }
        } else if (tokens[0] == "Alloc") {
            if (tokens[2][0] <= '9' && tokens[2][0] >= '0')
                output << "li $a0 " << stoi(tokens[2]) << "\n";
            else
                output << "lw $a0 " << getPos(tokens[2], 0) << "\n";
            output << "sll $a0 $a0 2\n";
            output << "li $v0 9\nsyscall\n";
            output << "sw $v0 " << getPos(tokens[1], 0) << "\n";
        } else if (tokens[0] == "Popparams") {

            output << "addi $sp $sp " << 4 * stoi(tokens[1]) << "\n";
        } else if (tokens[0] == "Endfunc") {

            sp -= current_func_size;


            if (SIZE(tokens) == 2) {
                output << "lw $t0 " << getPos(tokens[1], 0) << "\n";
                output << "addi $v0 $t0 0\n";
            }
            output << "addiu $sp $sp " << current_func_size << "\n";
            output << "jr $ra \n";
        } else if (tokens[0] == "Goto") {
            output << "j " << tokens[1] << "\n";
        }
        else if (tokens[0] == "Endl") {

            output << "li $v0 4\n";
            output << "la $a0 newline\n";
            output << "syscall\n";
        } else if (tokens[0] == "Exit") {
                output << "li $v0 10\n";
                output << "syscall\n";
        }

    }
    output << ".data\n";
    output << "newline: .asciiz \"\\n\"\n";
    output << "true: .asciiz \"true\"\n";
    output << "false: .asciiz \"false\"\n";

    // Adding string literals to .data segment

    for (int i = 0; i < SIZE(stringLiterals); i++) {
        output << stringLiterals[i];
    }

    /*
    for (int i = 0; i < SIZE(vtables); i++) {
        output << vtables[i];
    }
     */

    std::string program = ".text\nmain:\n" + vtables.str() + output.str();
    return program;
}

#ifndef TAC_TO_ASSEMBLY_IN_PROJECT
int main() {
    ifstream inputFile ("log5.txt");


    if (inputFile.is_open()) {
        outputFile << tacToAssembly(inputFile);
        inputFile.close();
    }
    else cout << "Unable to open file";

    outputFile.close();

    return 0;

}
#endif
