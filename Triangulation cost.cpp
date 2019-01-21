#include <iostream>
#include <math.h>
#define MAX 10000

using namespace std;

//Every point has a x & y co-ordinate
struct co_ords
{
	int x, y;
};

//Euclidian Distance Formula to calculate distance
float calc_dist(co_ords p1, co_ords p2)
{
	float dist;
	dist = sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2));
	return dist;
}

//Calculates the perimeter of the triangles
float perimeter(co_ords points[], int i, int j, int k)
{
	co_ords p1 = points[i], p2 = points[j], p3 = points[k];
	return calc_dist(p1, p2) + calc_dist(p2, p3) + calc_dist(p3, p1);
}


float min_cost(co_ords points[], int n)
{

// A matrix of n * n, where n is the number of vertices specified. to store results of subproblems. The entry table[0][n-1] stores the final result.
float m[n][n];

// There must be at least 3 vertices to form a triangle, failing which the problem statement is not valid.
if (n < 3)
	return 0;

//Filling the matrix
for (int  p = 0; p < n; p++)
{
	for (int i = 0, j = p; j < n; i++, j++)
	{
		if (j < i+2)                                   //Diagonal elements
			m[i][j] = 0;
		else
		{
			m[i][j] = MAX;
			for (int k = i+1; k < j; k++)
			{
				float value = m[i][k] + m[k][j] + perimeter(points,i,j,k);  //Formula
				if (m[i][j] > value)
					m[i][j] = value;
			}
		}
	}
}
return m[0][n-1];  //The row that stores the result
}

int main()
{
    //Vertices for a polygon with 20 vertices
	co_ords p20[] = {{71, 0}, {94, 4}, {114, 14}, {129, 30}, {142, 50},
	{147, 72}, {142, 94}, {129, 114}, {114, 130}, {94, 140},
	{71, 145}, {48, 140}, {28, 130}, {13, 114}, {3, 94},
	{72, 0}, {2, 50}, {13, 30}, {28, 14}, {48, 4}
	};

	cout <<"For a polygon with 20 vertices, the minimum cost of triangulation would be :   "<<min_cost(p20, 20);

	cout<<"\n \n \n";

	//Vertices for a polygon with 40 vertices.
	co_ords p40[] = {{71,0}, {74,0}, {77,1}, {81,2}, {84,4},
	{86,7}, {89,9}, {91,11}, {92,14}, {92,17},
	{92,20}, {91,23}, {89,26}, {86,28}, {84,31},
	{81,34}, {77,38}, {74,40}, {71,41}, {68,42},
	{64,42}, {61,42}, {58,41}, {55,40}, {52,38},
	{50,34}, {48,31}, {47,28}, {46,26}, {46,23},
	{46,20}, {47,17}, {48,14}, {50,11}, {52,9},
	{55,7}, {58,4}, {61,2}, {64,1}, {68,0}};

	cout <<" For a polygon with 40 vertices the minimum cost of triangulation would be :   "<<min_cost(p40, 40);

	cout<<"\n \n \n";

	//Vertices for a polygon with 60 vertices
	co_ords p60[] = {{71,0}, {75,0}, {80,1}, {84,2}, {88,4}, {91,6},
	{95,9}, {98,12}, {101,15}, {103,18}, {108,22}, {109,26},
	{111,30}, {112,34}, {113,35}, {113,35}, {112,35}, {111,39},
	{109,43}, {108,46}, {103,49}, {101,52}, {98,55}, {95,58},
	{91,61}, {88,64}, {84,66}, {80,67}, {75,69}, {71,70},
	{64,70}, {60,70}, {56,69}, {52,67}, {48,66}, {44,64},
	{40,61}, {39,58}, {38,55}, {37,52}, {36,49}, {35,46},
	{34,43}, {34,39}, {34,35}, {35,35}, {36,35}, {37,34},
	{38,30}, {39,26}, {39,22}, {40,18}, {41,15}, {44,12},
	{48,9}, {52,6}, {56,4}, {60,2}, {64,1}, {68,0}};

	cout<<"\n For a polygon with 60 vertices, the minimum cost of triangulation would be : "<<min_cost(p60, 60);

	cout<<"\n";

    return 0;
}
