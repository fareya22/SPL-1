#include<bits/stdc++.h>
using namespace std;

struct eachlinestruct {
    int line_no;
    string word;
};

eachlinestruct each_line[ 2000 ];

bool isDigit( char ch )
{
    return ch >= '0' && ch <= '9';
}

bool isOperator( char ch )
{
    if (  ch == '{' || ch == '}' ||
        ch == '[' || ch == ']' ||
        ch == '(' || ch == ')' ||
        ch == '#' || ch == ';' ||
        ch == ':' || ch == '?' ||
        ch == '+' || ch == '-' ||
        ch == '*' || ch == '/' ||
        ch == '%' || ch == '^' ||
        ch == '&' ||ch ==  '|' ||
        ch == '!' || ch == '=' ||
        ch == '<' || ch == '>' ||
        ch == ',' ) {
        return true;
    }
    else {
        return false;
    }
}

bool checkOperator( char ch )
{
    if ( ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' ) {
        return true;
    }
    else {
        return false;
    }
}

bool isInteger( string check )
{
    for ( int i = 0; i <check.size(); ++i ) {
        if ( !isDigit( check[ i ] ) ) {
                return false;
        }
    }

    return true;
}

bool isDouble( string check )
{
    int dot = 0;

    for ( int i = 0; i < check.size(); ++i ) {
        if ( isDigit( check[ i ] ) ) {
                continue;
        }

        if ( check[ i ] == '.' ) {
                dot++;
        }
        else {
                return false;
        }
    }

    return dot <= 1;
}


string PrintString( string item, int l, int col )
{
    string toReal;

    if ( isInteger( item ) ) {
        toReal = "integer\t" + item + "\t" + to_string( each_line[ l ].line_no ) + "\t";
        toReal += to_string( col - ( item.size() ) + 1 ) + "\n";
    }
    else if ( isDouble( item ) ) {
        toReal = "double\t" + item + "\t" + to_string( each_line[ l ].line_no ) + "\t";
        toReal +=  to_string( col - ( item.size() ) + 1 ) + "\n";
    }
    else {
        toReal = "identifier\t" + item + "\t" + to_string( each_line[ l ].line_no ) + "\t";
        toReal += to_string( col - ( item.size() ) + 1 ) + "\n";
    }

    return toReal;
}

string keyword_Identifier( int l, int col, string &item )
{
    if ( item.size() == 0 ) {
        return "";
    }

    string keywords[50] = {     "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                                                    "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                                                    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
                                         };

    for ( int k = 0; k < 50; k++ ) {
        if ( item.compare( keywords[ k ] ) == 0 ) {
                string toR = "keyword\t" + item + "\t" + to_string( each_line[ l ].line_no ) + "\t";
                toR += to_string( col - ( item.size() ) + 1 ) + "\n";
                item = "";
                return toR;
        }
    }

    string toR = PrintString( item, l, col );

    item = "";
    return toR;
}

int inputCodeInLineByLine( string inputFile )
{
    int totalLine = 0;
    string part;

    stringstream X( inputFile );
    while ( getline( X, part, '\n' ) ) {
        each_line[ totalLine ].word = part + " ";
        each_line[ totalLine++ ].line_no = totalLine;
    }

    return totalLine;
}

void tokenization( int totalLine )
{
    ofstream file( "TokenFile.txt" );
    string word;

    for ( int i = 0; i < totalLine; i++ ) {
        int length_per_line = each_line[ i ].word.size();

        for ( int j = 0; j < length_per_line; ) {
            if ( isOperator( each_line[ i ].word[ j ] ) && checkOperator( each_line[ i ].word[ j + 1 ] ) ) {
                string toR = keyword_Identifier( i, j, word );
                file << toR;

                file << "operator\t" << each_line[ i ].word[ j ] << each_line[ i ].word[ j + 1 ] << "\t";
                file << each_line[ i ].line_no << "\t" << j + 1 << "\n";
                j += 2;
            }
            else if ( isOperator( each_line[ i ].word[ j ] ) ) {
                string toR = keyword_Identifier( i, j, word );
                file << toR;

                file << "operator\t" << each_line[ i ].word[ j ] << "\t";
                file << each_line[ i ].line_no << "\t" << j + 1 << "\n";
                j += 1;
            }
            else if ( each_line[ i ].word[ j ] == '\\' ) {
                string toR = keyword_Identifier( i, j, word );
                file << toR;

                file << "character\t" << each_line[ i ].word[ j ] << each_line[ i ].word[ j + 1 ] << "\t";
                file << each_line[ i ].line_no << "\t" << j + 1 << "\n";
                j += 2;
            }
            else if ( each_line[ i ].word[ j ] == '"' ) {
                string toR = keyword_Identifier( i, j, word );
                file << toR;

                j++;
                int temp = j;
                string strg;

                while ( each_line[ i ].word[ j ] != '"' ) {
                        strg = strg + each_line[ i ].word[ j ];
                        j++;
                }

                j++;
                file << "string\t" << strg  << "\t";
                file << each_line[ i ].line_no << "\t" << temp + 1 << "\n";
            }
            else if ( each_line[ i ].word[ j ] == ' ' || each_line[ i ].word[ j ] == '\n' ) {
                string toR = keyword_Identifier( i, j, word );
                file << toR;

                j++;
            }
            else {
                word = word + each_line[ i ].word[ j++ ];
            }
        }
    }

    file.close();
}

string readInputCode()
{
    FILE *fp;
	string inputFile, orginal;
	char ch;

	fp = fopen( "enfa.cpp", "r" );

	if ( fp == NULL ){
		printf( "Error while opening the input file\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( fp ) ) != EOF ) {
        inputFile = inputFile + ch;
    }

    orginal = inputFile;
    cout << "\n\n\t\t\tYour Input C Code:\n\n";
    cout <<  orginal << "\n\n";

    for ( int i = 0; i + 1 < (int) inputFile.size(); ++i ) {
        int begining = i;
        if ( inputFile[ i ] == '/' && inputFile[ i + 1 ] == '/' ) {
                while ( i < (int) inputFile.size() && inputFile[ i ] != '\n' ) {
                    i++;
                }

                i--;
        }

        if ( inputFile[ i ] == '/' && inputFile[ i + 1 ] == '*' ) {
                while ( i + 1 < (int) inputFile.size() && ( inputFile[ i ] != '*' || inputFile[ i + 1 ] != '/' ) ) {
                    i++;
                }

                if ( i + 1 == (int) inputFile.size() && ( inputFile[ i ] != '*' || inputFile[ i + 1 ] != '/' ) ) {
                    int lineNumberCount = 1;

                    for ( int j = 0; j < begining; ++j ) {
                            if ( orginal[ j ] == '\n' ) {
                                lineNumberCount++;
                            }
                    }

                    cout << "\n\n*** Unterminated comment issue on Line Number - " << lineNumberCount << "\n";

                    exit( 0 );
                }

                i++;
        }

        if ( begining == i ) {
                continue;
        }

        while ( begining <= i ) {
                if ( inputFile[ begining ] != '\n' ) {
                    inputFile[ begining ] = ' ';
                }

                begining++;
        }
    }

    return inputFile;
}

void sourceCodeMakeToken()
{
    string codeText;

	codeText = readInputCode();
	int total_line = inputCodeInLineByLine( codeText );
    tokenization( total_line );
}

int main()
{
    sourceCodeMakeToken();
}