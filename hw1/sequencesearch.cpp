#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	//Check the arguments
	if(argc < 3)
	{
		cerr << "You must pass by argument the input and output filenames!" << endl;
		return 0;
	}

	//The input
	ifstream input(argv[1]);
	if(!input.is_open())
	{
		cerr << "Unable to open input file!" << endl;
	}

	//The output file
	//Declare the ofstream
	ofstream output;
	output.open(argv[2]);

	//Check if the file could be open
	if(output.fail())
		cerr << "Could not open the output file!";
	
	//Number of rows;
	int nrows; 
	input >> nrows;
	//Number of collumns;
	int ncollumns = 0; 
	
	int * collumns = new int[nrows];
	int i;
	for(i = 0; i<nrows; i++)
	{
		input >> collumns[i];
		if(collumns[i] > ncollumns)
			ncollumns = collumns[i];
	}

	//Create the matrix
	double *** matrix = new double ** [nrows];
	for(int i = 0; i<nrows; i++)
	{
		matrix[i] = new double *[ncollumns];
	}

	//Populate the matrix
	for(int i = 0; i<nrows; i++)
	{
		for(int j = 0; j<ncollumns; j++)
		{
			if(j < collumns[i])
			{
				matrix[i][j] = new double;
				input >> *matrix[i][j];
			}
			else
			{
				matrix[i][j] = NULL;
			}

		}
	}

	int actualLenght = 0;
	int bestLenght = 0;
	double previous = 0.0;
	double previousWasNull = true;

	//Search horizontal sequences
	for(int i = 0; i < nrows; i++)
	{
		for(int j = 0; j < ncollumns; j++)
		{
			if(matrix[i][j] != NULL)
			{
				if(previousWasNull)
				{
					previousWasNull = false;
					actualLenght = 1;
					previous = *matrix[i][j];
					continue;
				}
				else if(*matrix[i][j] > previous)
				{
					actualLenght++;
					previous = *matrix[i][j];
					continue;
				}
			}
			previousWasNull = true;

			if(actualLenght > bestLenght)
			{
				bestLenght = actualLenght;
				actualLenght = 0;
			}
		}
	}

	//reset
	previousWasNull = true;
	if(actualLenght > bestLenght)
	{
		bestLenght = actualLenght;
		actualLenght = 0;
	}

	//Search reverse horizontal sequences
	for(int i = 0; i < nrows; i++)
	{
		for(int j = ncollumns-1; j >= 0; j--)
		{
			if(matrix[i][j])
			{
				if(previousWasNull)
				{
					previousWasNull = false;
					actualLenght = 1;
					previous = *matrix[i][j];
					continue;
				}
				else if(*matrix[i][j] > previous)
				{
					actualLenght++;
					previous = *matrix[i][j];
					continue;
				}
			}
			previousWasNull = true;

			if(actualLenght > bestLenght)
			{
				bestLenght = actualLenght;
				actualLenght = 0;
			}
		}
	}
	//reset
	previousWasNull = true;
	if(actualLenght > bestLenght)
	{
		bestLenght = actualLenght;
		actualLenght = 0;
	}

	//Search vertical sequences
	for(int i = 0; i < ncollumns; i++)
	{
		for(int j = 0; j < nrows; j++)
		{
			if(matrix[j][i])
			{
				if(previousWasNull)
				{
					previousWasNull = false;
					actualLenght = 1;
					previous = *matrix[j][i];
					continue;
				}
				else if(*matrix[j][i] > previous)
				{
					actualLenght++;
					previous = *matrix[j][i];
					continue;
				}
			}
			previousWasNull = true;

			if(actualLenght > bestLenght)
			{
				bestLenght = actualLenght;
				actualLenght = 0;
			}
		}
	}
	//reset
	previousWasNull = true;
	if(actualLenght > bestLenght)
	{
		bestLenght = actualLenght;
		actualLenght = 0;
	}


	//Search reverse vertical sequences
	for(int i = 0; i < ncollumns; i++)
	{
		for(int j = nrows-1; j >= 0; j--)
		{
			if(matrix[j][i])
			{
				if(previousWasNull)
				{
					previousWasNull = false;
					actualLenght = 1;
					previous = *matrix[j][i];
					continue;
				}
				else if(*matrix[j][i] > previous)
				{
					actualLenght++;
					previous = *matrix[j][i];
					continue;
				}
			}
			
			previousWasNull = true;

			if(actualLenght > bestLenght)
			{
				bestLenght = actualLenght;
				actualLenght = 0;
			}
		}
	}
	//reset
	previousWasNull = true;
	if(actualLenght > bestLenght)
	{
		bestLenght = actualLenght;
		actualLenght = 0;
	}


	//Output
	output << bestLenght;

	//Close the output file
	output.close();

	//Delete the collumns
	delete [] collumns;

	//Delete the matrix
	for(int i = 0; i<nrows; i++)
	{
		for(int j = 0; j <ncollumns; j++)
		{
			if(matrix[i][j])
				delete matrix[i][j];
		}
		delete []matrix[i];
	}
	delete []matrix;
}