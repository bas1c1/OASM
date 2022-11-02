#include <iostream>
#include <string>
#include <limits>
#include <fcntl.h>
#include <unistd.h>
#include "includes.hpp"
#include "tokens.hpp"
#include "registers.hpp"
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
            string f = NowInstruction.FunctionV;

            easy_inst(f, "hlt", 0xf4);
            easy_inst(f, "pusha", 0x60);
            easy_inst(f, "popa", 0x61);
            easy_inst(f, "retf", 0xcb);
            easy_inst(f, "ret", 0xc3);
            easy_inst2(true, f, values[0], "mempush", 0xFF);
            easy_inst2(true, f, values[0], "mempop", 0x8F);
            easy_inst2(false, f, values[0], "db", 0x00);
            easy_inst2(true, f, values[0], "cmpal", 0x3c);
            easy_inst2(true, f, values[0], "calln", 0xe8);
            easy_inst2(true, f, values[0], "jze", 0x74);
            easy_inst2(true, f, values[0], "jmps", 0xeb);
            easy_inst2(true, f, values[0], "int", 0xcd);
            easy_inst2(true, f, values[0], "aladd", 0x04);
            easy_inst2(true, f, values[0], "axadd", 0x05);
            easy_inst2(true, f, values[0], "alsub", 0x2c);
            easy_inst2(true, f, values[0], "axsub", 0x2d);
            easy_inst2(true, f, values[0], "alor", 0x0c);
            easy_inst2(true, f, values[0], "axor", 0x0d);
            easy_inst2(true, f, values[0], "axxor", 0x35);
            easy_inst2(true, f, values[0], "alxor", 0x34);
            easy_inst2(true, f, values[0], "jс", 0x72);

            if (f == "setAA55") {
                stack[510] = 0x55;
                stack[511] = 0xaa;
            }
            else if (f == "dw") {
                if (values[0][0]!='\'')
                    stack[count] = stouc(values[0]);
                else
                    stack[count] = (unsigned char)(values[0][1]);
                count++;
            }
            else if (f == "resb") {
                for (int i = 0; i <= stoi(values[0]); i++) {
                    count++;
                }
            }
            else if (f == "#opst") {
                string v = values[0];
                if (v == "next") count++;
                else if (v == "goto") count = stoi(values[1]);
                else if (v == "back") for (int i = 0; i <= stoi(values[1]); i++) count--;
            }
            else if (f == "incbin") {
                string binname = values[0];
                int skip = stoi(values[1]);
                int siz = stoi(values[2]);
                int fil = open(binname.c_str(), O_RDONLY);
                unsigned char temp;

                for (int i = 0; i < skip; i++) {
                    read(fil, &temp, sizeof(temp));
                }

                for (int i = skip+1; i <= siz; i++) {
                    unsigned char c;
                    read(fil, &c, sizeof(c));
                    stack[count]=c;
                    count++;
                }

                close(fil);
            }
            else if (f == "mov") {
                map< string, unsigned char > movreg = mov::reg();
                spec_inst(values[0], movreg);
            }
            else if (f == "push") {
                map< string, unsigned char > pushreg = push::reg();
                spec_inst(values[0], pushreg);
            }
            else if (f == "pop") {
                map< string, unsigned char > popreg = pop::reg();
                spec_inst(values[0], popreg);
            }
            else if (f == "dec") {
                map< string, unsigned char > popreg = dec::reg();
                spec_inst(values[0], popreg);
            }
            else if (f == "inc") {
                map< string, unsigned char > pushreg = inc::reg();
                spec_inst(values[0], pushreg);
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
    void easy_inst(string f, string name, unsigned char set_v) {
        if (f==name) {
            stack[count] = set_v;
            count++;
        }
    }
    void easy_inst2(bool first, string f, string v, string name, unsigned char set_v) {
        if (f==name) {
            if (first) {
                stack[count] = set_v;
                count++;
            }
            stack[count] = stouc(v);
            count++;
        }
    }
    void spec_inst(string val, map< string, unsigned char > regs) {
        if (regs.find(val) == regs.end()) {
            stack[count] = regs[val];
            count++;
        } else {
            cout << "This reg is not supported: " << val << endl;
            exit(1);
        }
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