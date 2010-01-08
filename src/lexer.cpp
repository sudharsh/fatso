#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

static std::string IdentifierStr;
static double NumVal;

/* All of this shamelessly copied from the kaleidescope
   tutorial. Just building on top of that
*/

enum Token {
    tok_eof = -1,

    // Commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5
};


int gettok() {
    static int LastChar = ' ';

    //Skip whitespace
    while(isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while(isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;
        if (IdentifierStr == "def") return tok_def;
        if (IdentifierStr == "extern") return tok_extern;
        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    if (LastChar == '#') {
        do
            LastChar = getchar();
        while(LastChar != EOF && LastChar != '\n' && LastChar != '\r');
            if (LastChar != EOF)
                return gettok();
    }
            
}


int main()
{
    std::string Identifier;
    cout << gettok();
    
}
