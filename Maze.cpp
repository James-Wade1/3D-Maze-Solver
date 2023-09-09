//Relates to the recursive function
#define LEFT c, r - 1, l
#define RIGHT c, r + 1, l
#define UP c - 1, r, l
#define DOWN c + 1, r, l
#define OUT c, r, l - 1
#define IN c, r, l + 1

#include "Maze.h"

/** Output maze (same order as input maze)
  @return string of 2D layers
*/
std::string Maze::toString() const {
    std::ostringstream os;
    
    os << "Solve Maze:" << std::endl;
    os << printPlainMaze() << std::endl;
    
    if (maze[height - 1][width - 1][numLayers - 1] != EXIT) {
        os << "No Solution Exists!";
    }
    else {
        os << printSolvedMaze();
    }
    return os.str();
}

/** Recursive function to find maze path */
bool Maze::find_maze_path(int c, int r, int l) {
    if (c < 0 || c >= height || r < 0 || r >= width || l < 0 || l >= numLayers ) { return false; }
    if (maze[c][r][l] != OPEN) { return false; }
    if ((c == height - 1) && (r == width - 1) && (l == numLayers - 1)) {
        maze[c][r][l] = EXIT;
        return true;
    }
    maze[c][r][l] = L;
    if (find_maze_path(LEFT)) { return true; }
    
    maze[c][r][l] = R;
    if (find_maze_path(RIGHT)) { return true; }
    
    maze[c][r][l] = U;
    if (find_maze_path(UP)) { return true; }
    
    maze[c][r][l] = D;
    if (find_maze_path(DOWN)) { return true; }
    
    maze[c][r][l] = O;
    if (find_maze_path(OUT)) { return true; }
    
    maze[c][r][l] = I;
    if (find_maze_path(IN)) { return true; }
    
    maze[c][r][l] = VISITED;
    return false;
}

/** Returns original maze */
std::string Maze::printPlainMaze() const {
    std::ostringstream os;
    for (int k = 0; k < numLayers; k++) {
        os << "Layer " << k + 1 << std::endl;
        for (int i = 0; i < height; i++) {
            os << " ";
            for (int j = 0; j < width; j++) {
                (maze[i][j][k] != BLOCKED) ? os << '_' << " " : os << 'X' << " ";
            }
            os << std::endl;
        }
    }
    os << std::endl;
    return os.str();
}

/** Returns solved maze */
std::string Maze::printSolvedMaze() const {
    std::ostringstream os;
    os << "Solution:" << std::endl;
    for (int k = 0; k < numLayers; k++) {
        os << "Layer " << k + 1 << std::endl;
        for (int i = 0; i < height; i++) {
            os << " ";
            for (int j = 0; j < width; j++) {
                if (maze[i][j][k] == BLOCKED) {
                    os << 'X' << " ";
                }
                else if (maze[i][j][k] == VISITED || maze[i][j][k] == OPEN) {
                    os << '_' << " ";
                }
                else {
                    os << (char)maze[i][j][k] << " ";
                }
            }
            os << std::endl;
        }
    }
    return os.str();
}
