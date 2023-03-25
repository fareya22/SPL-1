#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MakeGraph.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./program_name source_file_name" << endl;
        return 0;
    }

    string filename(argv[1]);
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Could not open file " << filename << endl;
        return 0;
    }

    vector<string> lines;
    string line;
    while (getline(input, line)) {
        lines.push_back(line);
    }

    MakeGraph graph(lines);
    graph.start();
    //graph.printGraph();

    return 0;
}

