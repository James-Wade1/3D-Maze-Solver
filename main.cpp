/*
Project Name: 235 Lab 07 - 3D Maze
Description: Find a path through a 3-D Maze
*/

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <fstream>
#include "Maze.h"
using namespace std;

//enum { OPEN, BLOCKED };

int main(int argc, const char * argv[]) {
    
    VS_MEM_CHECK; //Checks for Memory Leaks
    
    //Opens files
    if (argc < 3)
    {
       cerr << "Please provide name of input and output files\n";
       return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in)
    {
       cerr << "Unable to open " << argv[1] << " for input\n";
       return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
       in.close();
       cerr << "Unable to open " << argv[2] << " for output\n";
    }
    
    int height;
    int width;
    int numLayers;
    int value;
    in >> height >> width >> numLayers;
    Maze maze(height, width, numLayers);
    
    //Sets values for maze
    for (int k = 0; k < numLayers; k++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                in >> value;
                if (value == 0) { maze.setValue(i, j, k, OPEN);}
                else { maze.setValue(i, j, k, BLOCKED); }
            }
        }
    }
    
    //Finds maze path, if possible and outputs original and solved maze
    maze.find_maze_path();
    out << maze;

    in.close();
    out.close();
    
    return 0;
}
