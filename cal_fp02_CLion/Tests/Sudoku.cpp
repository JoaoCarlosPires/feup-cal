/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtém o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}

int howManyPossibilities(int i, int j) {
    int to_return = 0;
    return to_return;
};

bool validity_check(int sudoku[9][9],int n,int p,int q)
{
    for(int i=0;i<9;i++)
    {
        if(sudoku[p][i]==n && q!=i)
        {
            return false;
        }
    }
    for(int i=0;i<9;i++)
    {
        if(sudoku[i][q]==n && p!=i)
        {
            return false;
        }
    }
    int bx=q/3;
    int by=p/3;
    for(int i=by*3;i<by*3+3;i++)
    {
        for(int j=bx*3;j<bx*3+3;j++)
        {
            if(sudoku[i][j]==n && i!=p && j!=q)
            {
                return false;
            }
        }
    }
    return true;
}

int blank(int sudoku[9][9],int *r,int *c)
{
    for(*r=0;*r<9;(*r)++)
    {
        for(*c=0;*c<9;(*c)++)
        {
            if(sudoku[*r][*c]==0)
            {
                return 1;
            }
        }
    }
    return 0;
}

bool solver(int sudoku[9][9])
{
    int row=0,col=0;
    int x=-1,y=-1;

    if (!blank(sudoku, &row, &col)){
        return 1;
    }
    for(int i=1;i<=9;i++)
    {
        if(validity_check(sudoku,i,row,col))
        {
            sudoku[row][col]=i;
            if(solver(sudoku))
            {
                return true;
            }
            sudoku[row][col]=0;
        }
    }
    return false;
}


/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve()
{
    int ret[9][9];

    for (int i = 0; i < 9; i++)
    {
        for (int a = 0; a < 9; a++)
            ret[i][a] = numbers[i][a];
    }

    return solver(ret);
    /*
    if (isComplete()) return true;
	int minimumPossibilities = howManyPossibilities(0,0);
	int start_row = 0;
	int start_col = 0;
    for (int i = 0; i < 9; i++) {
	    for (int j = 0; j < 9; j++) {
	        if (howManyPossibilities(i, j) < minimumPossibilities && howManyPossibilities(i, j) != 0) {
	            minimumPossibilities = howManyPossibilities(i, j);
	            start_row = i;
	            start_col = j;
	        }
	    }
	}
    return false;
     */
}





/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
