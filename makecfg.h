#include<bits/stdc++.h>
#include "tokenization.cpp"
using namespace std;

int totalLine = 0;

struct node_struct {
    int line_begin;
    int end_line;
    string keyword;
};

vector < string > word[ 100 ];
vector < string > word_Type[ 100 ];
vector < node_struct > struct_info;
vector < int > edge[ 100 ];


int str_to_integer( string str )
{
    int n = 0;
    for( int i = 0; i < str.size(); i++ )
      {
         n *= 10;
         n += str[ i ]-'0';
      }
    return n;
}

bool ifline( int LN )
{
    for ( int i = 0; i < struct_info.size(); ++i )
    {
        if ( struct_info[ i ].line_begin == LN )
        {
            return true;
        }
    }
    return false;
}

int findStarting( int LN )
{
    for ( int i = 0; i < struct_info.size(); ++i )
    {
        if ( struct_info[ i ].line_begin == LN )
        {
             return i;
        }

    }
}

int findEndingLine( int LN )
{
    int EL = struct_info[ findStarting( LN ) ].end_line;
    if ( ifline( EL + 1 ) && struct_info[ findStarting( EL + 1 ) ].keyword == "else" || struct_info[ findStarting( EL + 1 ) ].keyword == "else if" )
    {
          EL = findEndingLine( EL + 1 );
    }
    return EL;
}

void printGraph()
{

    cout<<"\n The control flow graph : \n";

    for ( int i = 1; i <= totalLine; ++i )
      {
        for ( int j = 0; j < edge[ i ].size(); ++j )
        {
            cout << i << "->" << edge[ i ][ j ] << "\n";
        }
      }
}

void edgeCreating( int SL, int EL )
{
    int node = SL;
    while ( node <= EL )
      {
        if ( ifline( node ) )
        {
            int id = findStarting( node );

            if ( struct_info[ id ].keyword == "for" || struct_info[ id ].keyword == "while" )
            {
                edge[ node ].push_back( node + 1 );
                edge[ node ].push_back( struct_info[ id ].end_line + 1 );

                edgeCreating( struct_info[ id ].line_begin + 1, struct_info[ id ].end_line - 1 );

                edge[ struct_info[ id ].end_line ].push_back( node );
                node = struct_info[ id ].end_line + 1;
            }

            else if ( struct_info[ id ].keyword == "if" || struct_info[ id ].keyword == "else if" || struct_info[ id ].keyword == "else" )
            {
                int last = findEndingLine( struct_info[ id ].line_begin ) + 1;
                edge[ node ].push_back( node + 1 );
                edge[ node ].push_back( struct_info[ id ].end_line + 1 );

                edgeCreating( struct_info[ id ].line_begin + 1, struct_info[ id ].end_line - 1 );

                edge[ struct_info[ id ].end_line ].push_back( last );
                node = struct_info[ id ].end_line + 1;
            }
        }
        else
             {
                  edge[ node ].push_back( node + 1 );
                  node++;
             }
    }
}

void analyze( int startLine, int endLine )
{
    stack < pair < int, string > > ss;
    pair < int, string > lastKeyword;

    for ( int LN = startLine; LN <= endLine; ++LN )
      {
        for ( int CL = 0; CL < word[ LN ].size(); ++CL )
         {
            if ( word_Type[ LN ][ CL ] == "keyword" )
            {
                lastKeyword.first = LN;
                lastKeyword.second = word[ LN ][ CL ];

                if ( CL > 0 && word[ LN ][ CL ] == "if" && word[ LN ][ CL - 1 ] == "else" )
                {
                      lastKeyword.second = "else if";
                }
            }

            if ( word[ LN ][ CL ] == "{" )
            {
                  ss.push( lastKeyword );
            }

            if ( word[ LN ][ CL ] == "}" )
            {
                  node_struct sc;
                  sc.line_begin = ss.top().first;
                  sc.keyword = ss.top().second;
                  sc.end_line = LN;
                  ss.pop();

                  struct_info.push_back( sc );
            }
        }
    }
}

void cfg()
{
    FILE *fp;
    string str;
    char ch;
    string code_Text;

    tokenizationCall();
    fp = fopen( "TokenFile.txt", "r" );

    while ( ( ch = fgetc( fp ) ) != EOF )
    {
          code_Text = code_Text + ch;
    }

    stringstream file1( code_Text );

    while ( getline( file1, str, '\n' ) )
     {
        string s1, s2, s3, s4;

        stringstream file2( str );
        getline( file2, s1, '\t' );
        getline( file2, s2, '\t' );
        getline( file2, s3, '\t' );
        getline( file2, s4, '\t' );
        int line = str_to_integer( s3 );

        word[ line ].push_back( s2 );
        word_Type[ line ].push_back( s1 );

        totalLine = max( totalLine, line );
     }

    analyze( 1, totalLine );

    edgeCreating( 1, totalLine );

   // printGraph();


  /*  vector<int>v1;
    vector<int>v2;

     for ( int i = 1; i <= totalLine; ++i )
      {
        for ( int j = 0; j < edge[ i ].size(); j++)
        {
            //cout <<" \t\t\t\t\t\t\t " << i << " " << edge[ i ][ j ] << "\n";
            if(j%2==0){
                v1.push_back(edge[ i ][ j ]);
            }
            else{
                 v2.push_back(edge[ i ][ j ]);
            }

        }
      }

      for(int i=0;i<v1.size();i++){
        if(v1[i]==v1[i+1]){
            cout<<v1[i]<<"-->"<<v2[i]<<" "<<v2[i+1]<<"\n";

        }
      }*/
}


