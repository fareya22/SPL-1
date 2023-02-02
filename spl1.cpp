#include<bits/stdc++.h>
#include<fstream>
#include<stdbool.h>
#include<string.h>
using namespace std;
string tokenization(string input_file);


bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isDelimiter(str[0]) == true)
        return (false);
    return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str)
{
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") ||
        !strcmp(str, "break") ||
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto"))
        return (true);
    return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str)
{
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));

    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

// Parsing the input STRING.
void parse(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false)
            right++;

        if (isDelimiter(str[right]) == true && left == right) {
            if (isOperator(str[right]) == true)
                printf("'%c' IS AN OPERATOR\n", str[right]);

            right++;
            left = right;
        } else if (isDelimiter(str[right]) == true && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);

            if (isKeyword(subStr) == true)
                printf("'%s' IS A KEYWORD\n", subStr);

            else if (isInteger(subStr) == true)
                printf("'%s' IS AN INTEGER\n", subStr);

            else if (isRealNumber(subStr) == true)
                printf("'%s' IS A REAL NUMBER\n", subStr);

            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);

            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false)
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }

}



string read_Input_Code()
{
    FILE *fp;
	string input_file, Orginal;
	char ch;
    string word;
    vector<string>words;


	fp = fopen( "Source_code.txt", "r" );

	if ( fp == NULL )
    {
		printf( "Error while opening the input file\n" );
		exit( 0 );
	}

	while ( ( ch = fgetc( fp ) ) != EOF )
      {
            input_file = input_file + ch;
      }

      Orginal = input_file;
 //     cout << "\n\n\t\t\tYour Input C Code:\n\n";
 //     cout <<  Orginal << "\n\n";

      for ( int i = 0; i + 1 < input_file.size(); ++i ) {
                 int start = i;
                 if ( input_file[ i ] == '/' && input_file[ i + 1 ] == '/' )

                while ( i < input_file.size() && input_file[ i ] != '\n' )
                {
                    i++;
                }

               if ( input_file[ i ] == '/' && input_file[ i + 1 ] == '*' )
                  {
                  while ( i + 1 < input_file.size()  &&  ( input_file[ i ] != '*' || input_file[ i + 1 ] != '/' ) )
                  {
                        i++;
                  }

                  if ( i + 1 ==  input_file.size() && ( input_file[ i ] != '*' || input_file[ i + 1 ] != '/' ) ) {
                        int line_Number_Count = 1;

                        for ( int j = 0; j < start; ++j ) {
                              if ( Orginal[ j ] == '\n' ) {
                                    line_Number_Count++;
                              }
                        }

                        cout << "\n\n*** Unterminated comment issue on Line Number - " << line_Number_Count << "\n";

                        exit( 0 );
                  }

                  i++;
            }

            if ( start == i ) {
                  continue;
            }

            while ( start <= i ) {
                  if ( input_file[ start ] != '\n' ) {
                        input_file[ start] = ' ';
                  }

                  start++;
            }
      }

    // cout<< input_file;
  Orginal = input_file;
 return input_file;
}



int main()
{
   string s1;
    int totalLine =0;
     s1 = read_Input_Code(); //cout<<s1;
     const    char* c_str = s1.c_str();
    int len=strlen(c_str);
    char* s = new char[len+1];
    strcpy(s,c_str);
    parse(s);


}
