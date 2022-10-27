/* LEXER */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> lex(string code) {
    string buff;
    vector<string> Res;
    replace(code.begin(), code.end(), '\n', ' ');
    stringstream code_r(code);
    while (getline(code_r, buff, ' ')) Res.push_back(buff);
    return Res;
}
/* END LEXER */
unsigned char stouc(string hexs) { return (unsigned char)stoi(hexs.substr(0, 2), nullptr, 16); }

void parse(vector<string> v, char *fname) {
    FILE *file = fopen(fname, "wb+");
    string b;
    unsigned char stack[512];
    int count = 0;
    for (int i = 0; i < 512; i++) stack[i] = 0x00;
    for (int i = 0; i < v.size(); i++) {
        b = v[i];
        if (count >= 511) {
            cout << "Out of 512 bytes\n";
            exit(1);
        }
        if (b == string("setAA55")) {
            stack[510] = 0x55;
            stack[511] = 0xaa;
            continue;
        }
        if (b == string("mov")) {
            i++;
            b = v[i];
            if (b == string("al")) {
                stack[count] = 0xb0;
                count++;
            } else if (b == string("cl")) {
                stack[count] = 0xb1;
                count++;
            } else if (b == string("dl")) {
                stack[count] = 0xb2;
                count++;
            } else if (b == string("bl")) {
                stack[count] = 0xb3;
                count++;
            } 
            else if (b == string("ah")) {
                stack[count] = 0xb4;
                count++;
            } else if (b == string("ch")) {
                stack[count] = 0xb5;
                count++;
            } else if (b == string("dh")) {
                stack[count] = 0xb6;
                count++;
            } else if (b == string("bh")) {
                stack[count] = 0xb7;
                count++;
            }
            else if (b == string("eax")) {
                stack[count] = 0xb8;
                count++;
            } else if (b == string("ecx")) {
                stack[count] = 0xb9;
                count++;
            } else if (b == string("edx")) {
                stack[count] = 0xba;
                count++;
            } else if (b == string("ebx")) {
                stack[count] = 0xbb;
                count++;
            }
            else if (b == string("esp")) {
                stack[count] = 0xbc;
                count++;
            } else if (b == string("ebp")) {
                stack[count] = 0xbd;
                count++;
            } else if (b == string("esi")) {
                stack[count] = 0xbe;
                count++;
            } else if (b == string("edi")) {
                stack[count] = 0xbf;
                count++;
            }
            else {
                cout << "This reg is not supported: " << b << '\n';
                exit(1);
            }
            i++;
            b = v[i];
            if (b[0]!='\'') stack[count] = stouc(b);
            else stack[count] = (unsigned char)(b[1]);
            count++;
            continue;
        }
        if (b == string("int")) {
            stack[count] = 0xcd;
            count++;
            i++;
            b = v[i];
            b.pop_back();
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("#macro")) {
            i++;
            b = v[i];
            if (b == string("setbyte")) {
                i++;
                b = v[i];
                stack[count] = stouc(b);
                count++;
                continue;
            } 
            if (b == string("skipbyte")) {
                count++;
                continue;
            } 
            if (b == string("back")) {
                count--;
                continue;
            }
            continue;
        }
    }
    for (int i = 0; i < 512; i++) { unsigned char curr = stack[i]; fwrite (&curr, 1, 1, file); }
    fclose(file);
    cout << count+2 << " bytes used\n";
}

int main(int argc, char*argv[]) {
    string line;
    string code;
 
    ifstream in(argv[1]);
    if (in.is_open()) while (getline(in, line)) code += line + ' ';
    in.close();
    vector<string> lines = lex(code);
    parse(lines, (char*)"boot.bin");
    return 0;
}
