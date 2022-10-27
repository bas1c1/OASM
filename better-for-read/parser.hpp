#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cstdlib>
#include "includes.hpp"
#include "tokens.hpp"
#pragma once

class Parser
{
public:
    void parse(vector< Function > lexems)
    {
        FILE *file = fopen("boot.bin", "wb+");

        for (int i = 0; i < 512; i++) stack[i] = 0x00;
        for (int i = 0; i < lexems.size(); i++) {
            if (count >= 511) {
                cout << "ERROR: Out of 512 bytes" << endl;
                system("pause");
                exit(1);
            }
            Function NowInstruction = lexems[i];
            vector< string > values = NowInstruction.ValuesV;

            if (NowInstruction.FunctionV == "setAA55") {
                stack[510] = 0x55;
                stack[511] = 0xaa;
            }
            else if (NowInstruction.FunctionV == "mov") {
                string v = values[0];
                if (value_parse(v,"al", 0xb0)) continue;
                else if (value_parse(v,"cl", 0xb1)) continue;
                else if (value_parse(v,"dl", 0xb2)) continue;
                else if (value_parse(v,"bl", 0xb3)) continue;
                else if (value_parse(v,"ah", 0xb4)) continue;
                else if (value_parse(v,"ch", 0xb5)) continue;
                else if (value_parse(v,"dh", 0xb6)) continue;
                else if (value_parse(v,"bh", 0xb7)) continue;
                else if (value_parse(v,"eax", 0xb8)) continue;
                else if (value_parse(v,"ecx", 0xb9)) continue;
                else if (value_parse(v,"edx", 0xba)) continue;
                else if (value_parse(v,"ebx", 0xbb)) continue;
                else if (value_parse(v,"esp", 0xbc)) continue;
                else if (value_parse(v,"ebp", 0xbd)) continue;
                else if (value_parse(v,"edi", 0xbf)) continue;
                else if (value_parse(v,"esi", 0xbe)) continue;
                else {
                    cout << "This reg is not supported: " << v << '\n';
                    exit(1);
                }

                if (values[1][0]!='\'')
                    stack[count] = stouc(values[1]);
                else
                    stack[count] = (unsigned char)(values[1][1]);
                
                count++;
            }
            else if (NowInstruction.FunctionV == "int") {
                stack[count] = 0xcd;
                count++;
                string value1 = values[0];
                value1.pop_back();
                stack[count] = stouc(value1);
                count++;
            }
            else if (NowInstruction.FunctionV == "#macro") {
                if (values[0] == "setbyte") {
                    stack[count] = stouc(values[1]);
                    count++;
                } 
                else if (values[0] == "skipbyte") {
                    count++;
                } 
                else if (values[0] == "back") {
                    count--;
                }
            }
        }
        for (int i = 0; i < 512; i++) {
            unsigned char curr = stack[i];
            fwrite (&curr, 1, 1, file);
        }
        fclose(file);
        cout << count+2 << " bytes used\n";
    }
private:
    unsigned char stouc(string hexs) {
        return (unsigned char)stoi( hexs.substr(0, 2), nullptr, 16 );
    }
    bool value_parse(string value, string if_it_this, unsigned char set_value) {
        if (value==if_it_this) {
            stack[count] = set_value;
            count++;
            return true;
        }
        return false;
    }
    unsigned char stack[512];
    int count = 0;
};