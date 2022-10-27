#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "includes.hpp"
#include "tokens.hpp"
#include "lexer.hpp"
#include "parser.hpp"

string read_file(string path) {
    string buff, code;
    ifstream file(path);

    // if can't open the file
    if ( !file.is_open() )
    {
        cout << "ERROR: Can't open file \"" << path << "\"!" << endl;
        system("pause");
        exit(1);
    }

    // Read file
    while( !file.eof() )
    {
        getline( file, buff );
        code += buff;
        if ( !file.eof() ) {
            code += '\n';
        }
    }
    // close file
    file.close();
    return code;
}

int main(int argc, char* argv[]) {
    if ( argc == 1 )
    {
        cout << "ERROR: No first argument (path to file)" << endl;
        system("pause");
        exit(1);
    }

    // path to file
    string path = argv[1];
    // get code
    string code = read_file(path);

    Lexer Lex;
    Parser Parse;

    vector< Function > lexems = Lex.lex(code);

    Parse.parse(lexems);

    // parse(lines, (char*)"boot.bin");
    return 0;
}
