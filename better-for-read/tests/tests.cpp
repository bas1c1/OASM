// comments...
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
using namespace std;

int main()
{
    // code, code, code...
    string code = read_file();

    regex r("\/\/\*([\s\S]+?)\*\/\/");
    string code_res = regex_replace(code, r, "");

    return 0;
}