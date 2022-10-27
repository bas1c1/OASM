#include <iostream>
#include <vector>
#include <string>
#include "includes.hpp"
#include "tokens.hpp"
using namespace std;
#pragma once

vector<string> split(string str, char symbol)
{
    string buff;
    vector<string> res_r;

    for (int i = 0; str[i]!='\0'; i++)
    {
        if (str[i]==symbol)
        {
            res_r.push_back(buff);
            buff = "";
        }
        else {
            buff += str[i];
        }
    }
    res_r.push_back(buff);

    return res_r;
};

class Lexer
{
    private:
        vector< Function > TokensResult;
        void AddToken(string FunctionV, vector< string > Values) {
            Function tmptoken = Function(FunctionV, Values);
            TokensResult.push_back(tmptoken);
        }
    public:
        vector< Function > lex(string code)
        {
            // read all code
            vector<string> lines = split(code, '\n');
            for (int l = 0; l<lines.size(); l++)
            {
                // this line
                string line = lines[l];
                
                vector<string> words, values;
                words = split(line, ' ');
                // cout << "words: " << words.size() << endl;
                
                string instruction = words[0];
                words.erase(words.begin());
                
                for (int w = 0; w<words.size(); w++)
                {
                    string word = words[w];

                    values.push_back(word);
                }
                
                AddToken(instruction, values);
            }

            return TokensResult;
        }
};
