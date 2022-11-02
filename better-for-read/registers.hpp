#include <iostream>
#include <string>
#include "includes.hpp"
#include "tokens.hpp"
#pragma once

namespace mov {
    map< string, unsigned char > reg() {
        map< string, unsigned char > regs;
        regs["cl"] = 0xb1;
        regs["dl"] = 0xb2;
        regs["bl"] = 0xb3;
        regs["ah"] = 0xb4;
        regs["ch"] = 0xb5;
        regs["dh"] = 0xb6;
        regs["bh"] = 0xb7;
        regs["eax"] = 0xb8;
        regs["ecx"] = 0xb9;
        regs["edx"] = 0xba;
        regs["ebx"] = 0xbb;
        regs["esp"] = 0xbc;
        regs["ebp"] = 0xbd;
        regs["edi"] = 0xbf;
        regs["esi"] = 0xbe;
        return regs;
    }
}

namespace push {
    map< string, unsigned char > reg() {
        map< string, unsigned char > regs;
        regs["ax"] = 0x50;
        regs["cx"] = 0x51;
        regs["dx"] = 0x52;
        regs["bx"] = 0x53;
        regs["sp"] = 0x54;
        regs["bp"] = 0x55;
        regs["si"] = 0x56;
        regs["di"] = 0x57;
        return regs;
    }
}

namespace pop {
    map< string, unsigned char > reg() {
        map< string, unsigned char > regs;
        regs["ax"] = 0x58;
        regs["cx"] = 0x59;
        regs["dx"] = 0x5a;
        regs["bx"] = 0x5b;
        regs["sp"] = 0x5c;
        regs["dp"] = 0x5d;
        regs["si"] = 0x5e;
        regs["di"] = 0x5f;
        return regs;
    }
}

namespace dec {
    map< string, unsigned char > reg() {
        map< string, unsigned char > regs;
        regs["ax"] = 0x48;
        regs["cx"] = 0x49;
        regs["dx"] = 0x4a;
        regs["bx"] = 0x4b;
        regs["sp"] = 0x4c;
        regs["dp"] = 0x4d;
        regs["si"] = 0x4e;
        regs["di"] = 0x4f;
        return regs;
    }
}

namespace inc {
    map< string, unsigned char > reg() {
        map< string, unsigned char > regs;
        regs["ax"] = 0x40;
        regs["cx"] = 0x41;
        regs["dx"] = 0x42;
        regs["bx"] = 0x43;
        regs["sp"] = 0x44;
        regs["bp"] = 0x45;
        regs["si"] = 0x46;
        regs["di"] = 0x47;
        return regs;
    }
}
