/**
	localizer.cpp

	Purpose: implements a 2-dimensional histogram filter
	for a robot living on a colored cyclical grid by 
	correctly implementing the "initialize_beliefs", 
	"sense", and "move" functions.

	This file is incomplete! Your job is to make these
	functions work. Feel free to look at localizer.py 
	for working implementations which are written in python.
*/

#include "localizer.h"
#include "helpers.h"
#include <stdlib.h>
#include "debugging_helpers.h"

using namespace std;

/**
	TODO - implement this function 
    
    Initializes a grid of beliefs to a uniform distribution. 

    @param grid - a two dimensional grid map (vector of vectors 
    	   of chars) representing the robot's world. For example:
    	   
    	   g g g
    	   g r g
    	   g g g
		   
		   would be a 3x3 world where every cell is green except 
		   for the center, which is red.

    @return - a normalized two dimensional grid of floats. For 
           a 2x2 grid, for example, this would be:

           0.25 0.25
           0.25 0.25
*/
vector< vector <float> > initialize_beliefs(vector< vector <char> > grid) {

    // your code here
    // Declaring variables
    int grid_h = grid.size(); // grid_h represents height of newGrid
    int grid_w = grid[0].size(); // grid_w represents width of newGrid
    vector < vector<float> > newGrid(grid_h, vector<float>(grid_w, 0));
    int zone = grid_h * grid_w; // Height per Width area
    float cell_belief = 1.0 / zone; // initialize belief

    //Adding beliefs to each cell in the grid
	for(int h = 0; h < grid_h; h++){
        vector <float> line;         
        for(int w = 0; w <grid_w; w++){
            line.push_back(cell_belief); // function used to push elements into a vector from the back
        }
        newGrid.push_back(line);
	}

	
	
	return newGrid;
}

/**
  TODO - implement this function 
    
    Implements robot motion by updating beliefs based on the 
    intended dx and dy of the robot. 

    For example, if a localized robot with the following beliefs

    0.00  0.00  0.00
    0.00  1.00  0.00
    0.00  0.00  0.00 

    and dx and dy are both 1 and blurring is 0 (noiseless motion),
    than after calling this function the returned beliefs would be

    0.00  0.00  0.00
    0.00  0.00  0.00
    0.00  0.00  1.00 

  @param dy - the intended change in y position of the robot

  @param dx - the intended change in x position of the robot

    @param beliefs - a two dimensional grid of floats representing
         the robot's beliefs for each cell before sensing. For 
         example, a robot which has almost certainly localized 
         itself in a 2D world might have the following beliefs:

         0.01 0.98
         0.00 0.01

    @param blurring - A number representing how noisy robot motion
           is. If blurring = 0.0 then motion is noiseless.

    @return - a normalized two dimensional grid of floats 
         representing the updated beliefs for the robot. 
*/
vector< vector <float> > move(int dy, int dx, 
  vector < vector <float> > beliefs,
  float blurring) 
{

    vector < vector <float> > newGrid;

    int belief_h = beliefs.size();
    int belief_w = beliefs[0].size();

    newGrid = zeros(belief_h, belief_w);

  
    for (int h = 0; h < belief_h; h++) {
        for (int w = 0; w < belief_h; w++) {
            int updated_h = (h + dy + belief_h) % belief_h;
            int updated_w = (w + dx + belief_w) % belief_w;
            newGrid[updated_h][updated_w] = beliefs[h][w];
        }
    }

  return blur(newGrid, blurring);
}


/**
	TODO - implement this function 
    
    Implements robot sensing by updating beliefs based on the 
    color of a sensor measurement 

	@param color - the color the robot has sensed at its location

	@param grid - the current map of the world, stored as a grid
		   (vector of vectors of chars) where each char represents a 
		   color. For example:

		   g g g
    	   g r g
    	   g g g

   	@param beliefs - a two dimensional grid of floats representing
   		   the robot's beliefs for each cell before sensing. For 
   		   example, a robot which has almost certainly localized 
   		   itself in a 2D world might have the following beliefs:

   		   0.01 0.98
   		   0.00 0.01

    @param p_hit - the RELATIVE probability that any "sense" is 
    	   correct. The ratio of p_hit / p_miss indicates how many
    	   times MORE likely it is to have a correct "sense" than
    	   an incorrect one.

   	@param p_miss - the RELATIVE probability that any "sense" is 
    	   incorrect. The ratio of p_hit / p_miss indicates how many
    	   times MORE likely it is to have a correct "sense" than
    	   an incorrect one.

    @return - a normalized two dimensional grid of floats 
    	   representing the updated beliefs for the robot. 
*/
vector< vector <float> > sense(char color, 
	vector< vector <char> > grid, 
	vector< vector <float> > beliefs, 
	float p_hit,
	float p_miss) 
{
	vector< vector <float> > newGrid;
    int belief_h = beliefs.size();
    int belief_w = beliefs[0].size();
    int h = 0;
    int w = 0;


	// your code here
    for (h = 0; h < belief_h; h++) {
        for (w = 0; w < belief_w; w++) {
            newGrid[h][w] = beliefs[h][w];
            if (grid[h][w] == color) {
                newGrid[h][w] *= p_hit;
            }
            else {
                newGrid[h][w] *= p_miss;
            }
        }
    }

	return normalize(newGrid);
}