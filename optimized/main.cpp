#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fcntl.h>
#include <regex>
#include <unistd.h>
#include <map>

int stacksize = 512;
using namespace std;

vector<string> lex(string code) {
    string buff;
    vector<string> Res;
    replace(code.begin(), code.end(), '\n', ' ');
    stringstream code_r(code);
    while (getline(code_r, buff, ' ')) Res.push_back(buff);
    return Res;
}

map<string, int> mapfm;

unsigned char stouc(string hexs) { return (unsigned char)stoi(hexs.substr(0, 2), nullptr, 16); }

void parse(vector<string> v, char *fname) {
    FILE *file = fopen(fname, "wb+");
    string b;
    unsigned char stack[stacksize];
    int count = 0;
    for (int i = 0; i < stacksize; i++) stack[i] = 0x00;
    for (int i = 0; i < v.size(); i++) {
        b = v[i];
        if (b == string("proc")) {
            i++;
            b = v[i];
            mapfm[b] = count;
        }
        if (b == string("format_win_console")) {
            string binname = string("win.exe");
            int siz = 513;
            int fil = open(binname.c_str(), O_RDONLY);
            unsigned char temp;
            for (int i = 0; i <= siz; i++) { if (i == 118) { stack[count]=0x0d; count++; continue;}unsigned char c; read(fil, &c, sizeof(c)); stack[count]=c; count++; }
            close(fil);
        }
        if (b == string("setAA55")) {
            stack[510] = 0x55;
            stack[511] = 0xaa;
            count += 2;
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
        if (b == string("dec")) {
            i++;
            b = v[i];
            if (b == string("ax")) {
                stack[count] = 0x48;
                count++;
            } else if (b == string("cx")) {
                stack[count] = 0x49;
                count++;
            } else if (b == string("dx")) {
                stack[count] = 0x4a;
                count++;
            } else if (b == string("bx")) {
                stack[count] = 0x4b;
                count++;
            } 
            else if (b == string("sp")) {
                stack[count] = 0x4c;
                count++;
            } else if (b == string("bp")) {
                stack[count] = 0x4d;
                count++;
            } else if (b == string("si")) {
                stack[count] = 0x4e;
                count++;
            } else if (b == string("di")) {
                stack[count] = 0x4f;
                count++;
            }
            else {
                cout << "This reg is not supported: " << b << '\n';
                exit(1);
            }
            continue;
        }
        if (b == string("inc")) {
            i++;
            b = v[i];
            if (b == string("ax")) {
                stack[count] = 0x40;
                count++;
            } else if (b == string("cx")) {
                stack[count] = 0x41;
                count++;
            } else if (b == string("dx")) {
                stack[count] = 0x42;
                count++;
            } else if (b == string("bx")) {
                stack[count] = 0x43;
                count++;
            } 
            else if (b == string("sp")) {
                stack[count] = 0x44;
                count++;
            } else if (b == string("bp")) {
                stack[count] = 0x45;
                count++;
            } else if (b == string("si")) {
                stack[count] = 0x46;
                count++;
            } else if (b == string("di")) {
                stack[count] = 0x47;
                count++;
            }
            else {
                cout << "This reg is not supported: " << b << '\n';
                exit(1);
            }
            continue;
        }
        if (b == string("push")) {
            i++;
            b = v[i];
            if (b == string("ax")) {
                stack[count] = 0x50;
                count++;
            } else if (b == string("cx")) {
                stack[count] = 0x51;
                count++;
            } else if (b == string("dx")) {
                stack[count] = 0x52;
                count++;
            } else if (b == string("bx")) {
                stack[count] = 0x53;
                count++;
            } 
            else if (b == string("sp")) {
                stack[count] = 0x54;
                count++;
            } else if (b == string("bp")) {
                stack[count] = 0x55;
                count++;
            } else if (b == string("si")) {
                stack[count] = 0x56;
                count++;
            } else if (b == string("di")) {
                stack[count] = 0x57;
                count++;
            }
            else {
                i++;
                b = v[i];
                stack[count] = stouc(b);
                count++;
            }
            continue;
        }
        if (b == string("pop")) {
            i++;
            b = v[i];
            if (b == string("ax")) {
                stack[count] = 0x58;
                count++;
            } else if (b == string("cx")) {
                stack[count] = 0x59;
                count++;
            } else if (b == string("dx")) {
                stack[count] = 0x5a;
                count++;
            } else if (b == string("bx")) {
                stack[count] = 0x5b;
                count++;
            } 
            else if (b == string("sp")) {
                stack[count] = 0x5c;
                count++;
            } else if (b == string("bp")) {
                stack[count] = 0x5d;
                count++;
            } else if (b == string("si")) {
                stack[count] = 0x5e;
                count++;
            } else if (b == string("di")) {
                stack[count] = 0x5f;
                count++;
            }
            else {
                cout << "This reg is not supported: " << b << '\n';
                exit(1);
            }
            continue;
        }
        if (b == string("hlt")) {
            stack[count] = 0xf4;
            count++;
            continue;
        }
        if (b == string("pusha")) {
            stack[count] = 0x60;
            count++;
            continue;
        }
        if (b == string("popa")) {
            stack[count] = 0x61;
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
        if (b == string("jmps")) {
            stack[count] = 0xeb;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("jmpl")) {
            unsigned char final = 0xfe;
            stack[count] = 0xeb;
            i++;
            b = v[i];
            int temp = count;
            //int offset = count-mapfm[b];
            //cout << offset;
            count++;
            //for (int i = 0; i < offset-1; i++) {
            //    final -= 0x02;
            //}
            while (temp != mapfm[b]) {
                temp -= 2;
                final-=0x02;
            }
            stack[count] = final;
            continue;
        }
        if (b == string("ret")) {
            stack[count] = 0xc3;
            count++;
            continue;
        }
        if (b == string("retf")) {
            stack[count] = 0xcb;
            count++;
            continue;
        }
        if (b == string("calln")) {
            stack[count] = 0xe8;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("cmpal")) {
            stack[count] = 0x3c;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("aladd")) {
            stack[count] = 0x04;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("axadd")) {
            stack[count] = 0x05;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("alsub")) {
            stack[count] = 0x2c;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("axsub")) {
            stack[count] = 0x2d;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("alor")) {
            stack[count] = 0x0c;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("axor")) {
            stack[count] = 0x0d;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("alxor")) {
            stack[count] = 0x34;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("axxor")) {
            stack[count] = 0x35;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("jze")) {
            stack[count] = 0x74;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("jс")) {
            stack[count] = 0x72;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("mempush")) {
            stack[count] = 0xFF;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("mempop")) {
            stack[count] = 0x8F;
            count++;
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("db")) {
            i++;
            b = v[i];
            stack[count] = stouc(b);
            count++;
            continue;
        }
        if (b == string("dw")) {
            i++;
            b = v[i];
            if (b[0]!='\'') stack[count] = stouc(b);
            else stack[count] = (unsigned char)(b[1]);
            count++;
            continue;
        }
        if (b == string("incbin")) {
            i++;
            b = v[i];
            string binname = b;
            i++;
            b = v[i];
            int skip = stoi(b);
            i++;
            b = v[i];
            int siz = stoi(b);
            int fil = open(binname.c_str(), O_RDONLY);
            unsigned char temp;
            for (int i = 0; i < skip; i++) {read(fil, &temp, sizeof(temp));}
            for (int i = skip+1; i <= siz; i++) { unsigned char c; read(fil, &c, sizeof(c)); stack[count]=c; count++; }
            close(fil);
            continue;
        }
        if (b == string("resb")) {
            i++;
            b = v[i];
            for (int i = 0; i <= stoi(b); i++) {
                count++;
            }
            continue;
        }
        if (b == string("#opst")) {
            i++;
            b = v[i];
            if (b == string("next")) {
                i++;
                b = v[i];
                for (int i = 0; i <= stoi(b); i++) {
                    count++;
                }
                continue;
            }
            if (b == string("goto")) {
                i++;
                b = v[i];
                count = stoi(b);
                continue;
            } 
            if (b == string("back")) {
                i++;
                b = v[i];
                for (int i = 0; i <= stoi(b); i++) {
                    count--;
                }
                continue;
            }
            continue;
        }
    }
    for (int i = 0; i < stacksize; i++) { unsigned char curr = stack[i]; fwrite (&curr, 1, 1, file); }
    fclose(file);
    cout << count << " bytes used\n";
}

int main(int argc, char*argv[]) {
    string line;
    string code;
    if (argc>2) stacksize = stoi(argv[2]);
    ifstream in(argv[1]);
    if (in.is_open()) while (getline(in, line)) code += line + ' ';
    in.close();
    regex r("\/\*([\s\S\n\t]+?)\*\/");
    code = regex_replace(code, r, "");
    vector<string> lines = lex(code);
    parse(lines, (char*)argv[3]);
    return 0;
}
