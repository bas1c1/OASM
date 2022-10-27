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
        cout << RED << "ERROR: Can't open file \"" << path << "\"!" << RESET<< endl;
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
        cout << RED << "ERROR: No first argument (path to file)" << RESET<< endl;
        system("pause");
        exit(1);
    }

    // path to file
    string path = argv[1];
    // get code
    string code = read_file(path);
    cout << 1 << endl;

    Lexer Lex;
    Parser Parse;
    cout << 2 << endl;

    vector< Function > lexems = Lex.lex(code);
    cout << 3 << endl;

    Parse.parse(lexems);

    // parse(lines, (char*)"boot.bin");
    return 0;
}
