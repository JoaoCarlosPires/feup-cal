/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}

void  Labirinth::printVisited()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            if (visited[i][j]) {
                cout << "X" << " ";
            } else {
                cout << "  ";
            }
        cout << endl;
    }
}

bool Labirinth::findGoal(int x, int y)
{
    initializeVisited();
    return findGoalRec(x,y);
}

bool Labirinth::findGoalRec(int x, int y) {
    bool to_return = false;
    if (this->labirinth[x+1][y] == 2 || this->labirinth[x][y+1] == 2 || this->labirinth[x-1][y] == 2 || this->labirinth[x][y-1] == 2 ) {
        return true;
    } else {
        if (this->labirinth[x+1][y] == 1 && !this->visited[x+1][y]) {
            this->visited[x+1][y] = true;
            to_return |= findGoalRec(x+1, y);
        }
        if (this->labirinth[x][y+1] == 1 && !this->visited[x][y+1]) {
            this->visited[x][y+1] = true;
            to_return |= findGoalRec(x, y+1);
        }
        if (this->labirinth[x-1][y] == 1 && !this->visited[x-1][y]) {
            this->visited[x-1][y] = true;
            to_return |= findGoalRec(x-1, y);
        }
        if (this->labirinth[x][y-1] == 1 && !this->visited[x][y-1]) {
            this->visited[x][y-1] = true;
            to_return |= findGoalRec(x, y-1);
        }
    }

    return to_return;
}


