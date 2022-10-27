#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#pragma once

std::vector< std::string > lex(std::string code) {
    std::string buff;
    std::vector< std::string > Res;
    std::replace(code.begin(), code.end(), '\n', ' ');
    std::stringstream code_r(code);
    while (std::getline(code_r, buff, ' ')) Res.push_back(buff);
    return Res;
}
