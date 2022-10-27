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
        string b;
        unsigned char stack[512];
        int count = 0;
        for (int i = 0; i < 512; i++) stack[i] = 0x00;
        for (int i = 0; i < lexems.size(); i++) {
            cout << "testtttt" << endl;
            if (count >= 511) {
                cout << RED << "ERROR: Out of 512 bytes" << RESET << endl;
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
                if (values[0] == "al") {
                    stack[count] = 0xb0;
                    count++;
                }
                else if (values[0] == "cl") {
                    stack[count] = 0xb1;
                    count++;
                }
                else if (values[0] == string("dl")) {
                    stack[count] = 0xb2;
                    count++;
                }
                else if (values[0] == string("bl")) {
                    stack[count] = 0xb3;
                    count++;
                } 
                else if (values[0] == string("ah")) {
                    stack[count] = 0xb4;
                    count++;
                }else if (values[0] == string("ch")) {
                    stack[count] = 0xb5;
                    count++;
                }else if (values[0] == string("dh")) {
                    stack[count] = 0xb6;
                    count++;
                }
                else if (values[0] == string("bh")) {
                    stack[count] = 0xb7;
                    count++;
                }
                else if (values[0] == string("eax")) {
                    stack[count] = 0xb8;
                    count++;
                }
                else if (values[0] == string("ecx")) {
                    stack[count] = 0xb9;
                    count++;
                }
                else if (values[0] == string("edx")) {
                    stack[count] = 0xba;
                    count++;
                } 
                else if (values[0] == string("ebx")) {
                    stack[count] = 0xbb;
                    count++;
                }
                else if (values[0] == string("esp")) {
                    stack[count] = 0xbc;
                    count++;
                }
                else if (values[0] == string("ebp")) {
                    stack[count] = 0xbd;
                    count++;
                }
                else if (values[0] == string("esi")) {
                    stack[count] = 0xbe;
                    count++;
                }
                else if (values[0] == string("edi")) {
                    stack[count] = 0xbf;
                    count++;
                }
                else {
                    cout <<
                        RED << "ERROR: reg is not supported>> " << RESET <<
                        values[0] << endl;
                    system("pause");
                    exit(1);
                }

                if (values[1][0]!='\'')
                    stack[count] = stouc(values[1]);
                else
                    stack[count] = (unsigned char)(values[1][1]);
                
                count++;
            }
            else if (NowInstruction.FunctionV == "int") {
                // why... code must be cd10, but is is ff00...
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
                else if (b == string("skipbyte")) {
                    count++;
                } 
                else if (b == string("back")) {
                    count--;
                }
            }
            cout << "test" << endl;
        }
        cout << 99 << endl;
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
};