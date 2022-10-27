#include "includes.hpp"
#pragma once

class Function {
    public:
        string FunctionV;
        vector< string > ValuesV;

        Function(string Function, vector< string > Values)
        {
            FunctionV = Function;
            ValuesV = Values;
        }
};
