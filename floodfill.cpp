/*
 * FLOOD FILL RELATED
 * Distributes the weight for each cell based on the wall information
 * that has been gathered at the time the function was called.
 */

/*
 * Initialize the potential array
 */
void initPotential()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      potential[i][j] = BOARD_MAX*BOARD_MAX+1;
    }
  }
	// Set goal cell
	potential[GOAL_Y][GOAL_X] = 0;
	potential[GOAL_Y+1][GOAL_X] = 0;
	potential[GOAL_Y][GOAL_X+1] = 0;
	potential[GOAL_Y+1][GOAL_X+1] = 0;
}

/*
 * Initialize the potential array so the mouse can return
 * to its original location
 */
void initPotentialHoming()
{
  for(int i=0; i<BOARD_MAX; i++)
  {
    for(int j=0; j<BOARD_MAX; j++)
    {
      potential[i][j] = BOARD_MAX*BOARD_MAX+1;
    }
  }
	// Set goal cell
	potential[BOARD_MAX-1][0] = 0;
}

/*
 * Updates the potential map to create new step map
 */
void updatePotential()
{
	int upBound = BOARD_MAX*BOARD_MAX+1;
	bool foundFlag = false;

	// Make the potential map
	for(int i=0; i<upBound-1; i++)
	{
		foundFlag = false;
		// look for where the potential is i
		for(int j=0; j<BOARD_MAX; j++)
		{
			for(int k=0; k<BOARD_MAX; k++)
			{
				if(potential[j][k] == i)
				{
					foundFlag = true;
					temp = traversal[j][k];
					// look at north
					// cond. true if ther si no wall or we haven't travelled there yet
					if(j>0 && potential[j-1][k]==upBound && (temp&0x01)!=0x01)
						potential[j-1][k] = potential[j][k]+1;
					// look at east
					if(k<BOARD_MAX-1 && potential[j][k+1]==upBound && (temp&0x02)!=0x02)
						potential[j][k+1] = potential[j][k]+1;
					// look at south
					if(j<BOARD_MAX-1 && potential[j+1][k]==upBound && (temp&0x04)!=0x04)
						potential[j+1][k] = potential[j][k]+1;
					// look at west
					if(k>0 && (potential[j][k-1]==upBound) && (temp&0x08)!=0x08)
						potential[j][k-1] = potential[j][k]+1;
				}
			}
		}
	}
	if(!foundFlag) break;
}
