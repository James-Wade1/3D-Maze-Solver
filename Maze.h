#ifndef MAZE_H
#define MAZE_H

#include "MazeInterface.h"
#include <sstream>

//Enumerated values, with the L/R/D/etc's #s corresponding to their character's ASCII values
enum { OPEN, BLOCKED, PATH, EXIT = 69, VISITED, L = 76, R = 82, D = 68, U = 85, O = 79, I = 73 };

class Maze : public MazeInterface {
public:
    /** Constructor, initializes space for the maze */
    Maze(int height, int width, int numLayers) : height(height), width(width), numLayers(numLayers) {
        maze = new int**[height];
        for (int i = 0; i < height; i++) {
            maze[i] = new int*[width];
            for (int j = 0; j < width; j++) {
                maze[i][j] = new int[numLayers];
            }
        }
    }
    
    /** Deletes maze memory */
    ~Maze() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                delete[] maze[i][j];
            }
            delete[] maze[i];
        }
        delete[] maze;
    }

    /** Set maze value
       @parm height
       @parm width
       @parm layer
       @parm value
    */
    virtual void setValue(int height, int width, int layer, int value) { maze[height][width][layer] = value; }

    /** Solve maze, wrapper function
       @return true if solveable, else false
    */
    virtual bool find_maze_path() { return find_maze_path(0, 0, 0); }

    /** Output maze (same order as input maze)
      @return string of 2D layers
    */
    virtual std::string toString() const;
    
    friend std::ostream& operator<< (std::ostream& os, Maze& maze) { return os << maze.toString(); }
    
private:
    int*** maze;
    int height;
    int width;
    int numLayers;
    
    /** Recursive function to find path */
    bool find_maze_path(int c, int r, int l);
    
    /** Prints oroginal maze */
    std::string printPlainMaze() const;
        
    /** Prints solved maze */
    std::string printSolvedMaze() const;
};

#endif /* MAZE_H */
