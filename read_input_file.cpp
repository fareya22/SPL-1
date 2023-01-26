#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
using namespace std;


string read_Input_Code()
{
      FILE *fp;
	string input_file, Orginal;
	char ch;

	fp = fopen( "Source_code.txt", "r" );

	if ( fp == NULL ){
		printf( "Error while opening the input file\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( fp ) ) != EOF )
      {
            input_file = input_file + ch;
      }

      Orginal = input_file;
      cout << "\n\n\t\t\tYour Input C Code:\n\n";
      cout <<  Orginal << "\n\n";

      return input_file;
}

int main()
{
 read_Input_Code();
}
