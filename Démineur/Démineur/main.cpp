#include <iostream>
#include <random>

#include "grid.h"

using namespace std;

int l;
int c;

double per;

int tl;
int tc;

random_device rd;
mt19937 gen(rd());


int AskInt(int min, int max, string s)
{
	int n;
	cout << s << endl;
	cin >> n;

	if (n < min)
	{
		cout << "Nombre trop petit ! Minimum est de : " << min << endl;
		return AskInt(min, max, s);
	}

	else if (max < n)
	{
		cout << "Nombre trop grand ! Maximum est de : " << max << endl;
		return AskInt(min, max, s);
	}

	return n;
}


void ChooseDifficulty()
{
	int dif;
	cout << "Quelle difficulte voulez-vous ?" << endl << "Facile : tapez 1" << endl << "Moyen : tapez 2" << endl << "Difficile : tapez 3" << endl << "Customise : tapez 4" << endl;
	cin >> dif;

	switch (dif)
	{
	case 1:
		l = 9, c = 9;
		per = 0.1;
		break;
	case 2:
		l = 15, c = 15;
		per = 0.15;
		break;
	case 3:
		l = 25, c = 25;
		per = 0.2;
		break;
	case 4:
		l = AskInt(1, 57, "Nombre de lignes ?");
		c = AskInt(1, 57, "Nombre de colonnes ?");
		per = AskInt(0, 100, "Pourcentage de mines ?");
		per /= 100;
		break;
	}
}


Grid CreateGrid()
{
	Grid grid;
	grid.lines = l;
	grid.columns = c;

	Cell cell;
	cell.isMine = 0;
	cell.revealed = 0;
	cell.flagged = 0;
	cell.adj = 0;
	cell.dangerous = 0;

	grid.array = (Cell**)malloc(sizeof(Cell*) * c);
	for (int i = 0; i < c; i++)
	{
		grid.array[i] = (Cell*)malloc(sizeof(Cell) * l);

		for (int j = 0; j < l; j++)
		{
			grid.array[i][j] = cell;
		}
	}
	return grid;
}


void Display(Grid grid)
{
	system("cls");


	cout << endl << "     ";

	for (int i = 0; i < c; i++)
	{
		if (i < 10)
		{
			cout << "  " << i << " ";
		}

		else
		{
			cout << " " << i << " ";
		}
	}

	cout << endl;

	for (int i = 0; i < l; i++)
	{
		cout << "     ";
		
		for (int j = 0; j < l; j++)
		{
			cout << "+---";
		}

		cout << "+" << endl;

		if (i < 10)
		{
			cout << "   " << i << " ";
		}

		else
		{
			cout << "  " << i << " ";
		}
		


		for (int j = 0; j < c; j++)
		{
			cout << "|";
			if (grid.array[i][j].flagged != 0)
			{
				switch(grid.array[i][j].flagged)
				{
					case 1:
						cout << " \033[31mF\033[0m ";
						break;
					case 2:
						cout << "\033[31mFF\033[0m ";
						break;
					case 3:
						cout << "\033[31mFFF\033[0m";
						break;
					case -1:
						cout << " \033[36mF\033[0m ";
						break;
				}
			}
			
			else if (grid.array[i][j].revealed)
			{
				if (grid.array[i][j].isMine)
				{
					switch (grid.array[i][j].isMine)
					{
						case 1:
							cout << " \033[31mX\033[0m ";
							break;
						case 2:
							cout << "\033[31mXX\033[0m ";
							break;
						case 3:
							cout << "\033[31mXXX\033[0m";
							break;
						case -1:
							cout << " \033[36mX\033[0m ";
							break;
					}
				}

				else if (grid.array[i][j].dangerous > 0)
				{
					switch (grid.array[i][j].adj)
					{
						case 0:
							cout << " 0 ";
							break;

						case 1:
							cout << " \033[34m1\033[0m ";
							break;
						case 2:
							cout << " \033[32m2\033[0m ";
							break;
						case 3:
							cout << " \033[31m3\033[0m ";
							break;
						case 4:
							cout << " \033[35m4\033[0m ";
							break;
						case 5:
							cout << " \033[31;2m5\033[0m ";
							break;
						case 6:
							cout << " \033[36m6\033[0m ";
							break;

						case -1:
							cout << "\033[94m-1\033[0m ";
							break;
						case -2:
							cout << "\033[92m-2\033[0m ";
							break;
						case -3:
							cout << "\033[91m-3\033[0m ";
							break;
						case -4:
							cout << "\033[95m-4\033[0m ";
							break;
						case -5:
							cout << "\033[91;2m-5\033[0m ";
							break;
						case -6:
							cout << "\033[96m-6\033[0m ";
							break;
						case -7:
							cout << "-7 ";
							break;
						case -8:
							cout << "-8 ";
							break;
					}

					if (grid.array[i][j].adj > 7)
					{
						cout << " " << grid.array[i][j].adj << " ";
					}
				}

				else
				{
					cout << "   ";
				}
				
			}

			else
			{
				cout << " ? ";
			}
		}

		cout << "|" << endl;
	}

	cout << "     ";

	for (int i = 0; i < l; i++)
	{
		cout << "+---";
	}

	cout << "+" << endl;

}


Grid AddMine(Grid grid, int n)
{
	uniform_int_distribution<> distl(0, l - 1);
	int al = distl(gen);

	uniform_int_distribution<> distc(0, c - 1);
	int ac = distc(gen);

	if (grid.array[al][ac].isMine or (al == tl and ac == tc))
	{
		AddMine(grid, n);
	}

	/*
	else if (tl > 0)
	{
		if ((al == (tl - 1) and ac == tc))
		{
			AddMine(grid, n);
		}
	}

	
	else if (tl < l - 1)
	{
		if ((al == tl + 1 and ac == tc))
		{
			AddMine(grid, n);
		}
	}

	else if (tc > 0)
	{
		if ((al == tl and ac == tc - 1))
		{
			AddMine(grid, n);
		}
	}

	else if (tc < c - 1)
	{
		if ((al == tl and ac == tc + 1))
		{
			AddMine(grid, n);
		}
	}
	
	else if (tl > 0 and tc > 0)
	{
		if ((al == tl - 1 and ac == tc - 1))
		{
			AddMine(grid, n);
		}
	}

	else if (tl < l - 1 and tc > 0)
	{
		if ((al == tl + 1 and ac == tc - 1))
		{
			AddMine(grid, n);
		}
	}

	else if (tl > 0 and tc < c - 1)
	{
		if ((al == tl - 1 and ac == tc + 1))
		{
			AddMine(grid, n);
		}
	}

	else if (tl < l - 1 and tc < c - 1)
	{
		if ((al == tl + 1 and ac == tc + 1))
		{
			AddMine(grid, n);
		}
	}
	*/

	else
	{
		grid.array[al][ac].isMine = n;
	}

	return grid;
}


void CountAllAdj(Grid grid)
{
	int nAdj;

	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < c; j++)
		{
			nAdj = grid.array[i][j].isMine;
			if (grid.array[i][j].isMine != 0)
			{
				grid.array[i][j].dangerous = 1;
			}


			if (i < l - 1)
			{
				nAdj += grid.array[i + 1][j].isMine;
				if (grid.array[i + 1][j].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (i > 0)
			{
				nAdj += grid.array[i - 1][j].isMine;
				if (grid.array[i - 1][j].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (j < c - 1)
			{
				nAdj += grid.array[i][j + 1].isMine;
				if (grid.array[i][j + 1].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (j > 0)
			{
				nAdj += grid.array[i][j - 1].isMine;
				if (grid.array[i][j - 1].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (i < l - 1 and j < c - 1)
			{
				nAdj += grid.array[i + 1][j + 1].isMine;
				if (grid.array[i + 1][j + 1].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (i < l - 1 and j > 0)
			{
				nAdj += grid.array[i + 1][j - 1].isMine;
				if (grid.array[i + 1][j - 1].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (i > 0 and j < c - 1)
			{
				nAdj += grid.array[i - 1][j + 1].isMine;
				if (grid.array[i - 1][j + 1].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			if (i > 0 and j > 0)
			{
				nAdj += grid.array[i - 1][j - 1].isMine;
				if (grid.array[i - 1][j - 1].isMine != 0)
				{
					grid.array[i][j].dangerous = 1;
				}
			}

			grid.array[i][j].adj = nAdj;
		}
	}
}


void RevealSafe(Grid grid)
{
	for(int r = 0; r < l * c; r++)
	{
		for (int i = 0; i < l; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (grid.array[i][j].revealed == 1 and grid.array[i][j].dangerous == 0)
				{
					if (i < l - 1)
					{
						grid.array[i + 1][j].revealed = 1;
					}

					if (i > 0)
					{
						grid.array[i - 1][j].revealed = 1;
					}

					if (j < c - 1)
					{
						grid.array[i][j + 1].revealed = 1;
					}

					if (j > 0)
					{
						grid.array[i][j - 1].revealed = 1;
					}

					if (i < l - 1 and j < c - 1)
					{
						grid.array[i + 1][j + 1].revealed = 1;
					}

					if (i < l - 1 and j > 0)
					{
						grid.array[i + 1][j - 1].revealed = 1;
					}

					if (i > 0 and j < c - 1)
					{
						grid.array[i - 1][j + 1].revealed = 1;
					}

					if (i > 0 and j > 0)
					{
						grid.array[i - 1][j - 1].revealed = 1;
					}
				}
			}
		}
	}
}


void Game()
{
	ChooseDifficulty();
	Grid grid;

	grid = CreateGrid();

	
	int ttom = 0;
	bool mine1 = false;
	bool mine2 = false;
	bool mine3 = false;
	bool mineA1 = false;
	bool ans;

	cout << "Inclure les mines ?" << endl;
	cin >> ans;
	if (ans)
	{
		mine1 = true;
		ttom++;
	}

	cout << "Inclure les double mines ?" << endl;
	cin >> ans;
	if (ans)
	{
		mine2 = true;
		ttom++;
	}

	cout << "Inclure les triple mines ?" << endl;
	cin >> ans;
	if (ans)
	{
		mine3 = true;
		ttom++;
	}

	cout << "Inclure les anti mines ?" << endl;
	cin >> ans;
	if (ans)
	{
		mineA1 = true;
		ttom++;
	}

	if (ttom == 0)
	{
		cout << "Veuillez choisir au moins un type de mines !" << endl;
		Game();
	}

	
	
	Display(grid);


	int st = 2;



	while (st != 0)
	{
		tl = AskInt(0, l, "Ligne ?");
		tc = AskInt(0, c, "Colonne ?");
		st = AskInt(-1, 3, "Reveler ou drapeau ?");

		if (st != 0)
		{
			switch (grid.array[tl][tc].flagged)
			{
			case 0:
				grid.array[tl][tc].flagged = st;
				break;
			case 1 or 2 or 3 or -1:
				grid.array[tl][tc].flagged = 0;
				break;
			}
		}

		else
		{
			// ajouter les mines apres que la premiere case est devoilee
			if(mine1)
			{
				for (int i = 0; i < ((l * c * per) / ttom); i++)
				{
					AddMine(grid, 1);
				}
			}

			if (mine2)
			{
				for (int i = 0; i < ((l * c * per) / ttom); i++)
				{
					AddMine(grid, 2);
				}
			}

			if (mine3)
			{
				for (int i = 0; i < ((l * c * per) / ttom); i++)
				{
					AddMine(grid, 3);
				}
			}

			if (mineA1)
			{
				for (int i = 0; i < ((l * c * per) / ttom); i++)
				{
					AddMine(grid, -1);
				}
			}

			CountAllAdj(grid);

			grid.array[tl][tc].revealed = 1;
			if (grid.array[tl][tc].dangerous == 0)
			{
				RevealSafe(grid);
			}
		}

		Display(grid);
	}


	

	while (grid.array[tl][tc].isMine == 0 or st != 0)
	{
		tl = AskInt(0, l, "Ligne ?");
		tc = AskInt(0, c, "Colonne ?");
		st = AskInt(-1, 3, "Reveler ou drapeau ?");

		if (grid.array[tl][tc].isMine != 0 and st == 0)
		{
			grid.array[tl][tc].revealed = 1;
			Display(grid);
			cout << "Mine revelee ! Vous avez perdu !" << endl;

			bool pa;
			cout << "Voulez vous rejouer ?" << endl;
			cin >> pa;
			if (pa)
			{
				Game();
			}
		}

		else if (st != 0)
		{
			switch (grid.array[tl][tc].flagged)
			{
			case 0:
				grid.array[tl][tc].flagged = st;
				break;
			case 1 or 2 or 3 or -1:
				grid.array[tl][tc].flagged = 0;
				break;
			}
		}

		else
		{
			grid.array[tl][tc].revealed = 1;
			if (grid.array[tl][tc].dangerous == 0)
			{
				RevealSafe(grid);
			}
		}

		Display(grid);

		cout << "";
	}

}


int main()
{
	/*
	int** array2D = (int**)malloc(sizeof(int*) * 5);

	for (int i = 0; i < 5; i++)
	{
		array2D[i] = (int*)malloc(sizeof(int) * 5);

		for (int j = 0; j < 5; j++)
		{
			array2D[i][j] = 0;
		}
	}
	*/


	//cout << "Bienvenue dans le jeu du Demineur !" << endl;


	Game();
}