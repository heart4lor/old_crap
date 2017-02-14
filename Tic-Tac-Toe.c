#include <stdio.h>
#include <conio.h>

int system(const char *string);

int main()
{
	system("mode con cols=20 lines=11");

	void prt(int (*map)[3]);
	int ai(int (*map)[3]);
	int score(int ai_switch);

	while (1)
	{
		int i,j;
		int player = 0;
		int cnt = 0;
		int win = -1;
		int locate = 0;

		int map[3][3] = {32,32,32,32,32,32,32,32,32};
		printf (" Player %d :\n", player + 1);
		prt(map);
		
		while (win == -1 && cnt < 9)
		{
			if (player + 1 % 2 == 1)
				locate = getch();
			else
				locate = ai(map);
			cnt++;
			switch (locate)
			{
				case '1': map[2][0] = player; break;
				case '2': map[2][1] = player; break;
				case '3': map[2][2] = player; break;
				case '4': map[1][0] = player; break;
				case '5': map[1][1] = player; break;
				case '6': map[1][2] = player; break;
				case '7': map[0][0] = player; break;
				case '8': map[0][1] = player; break;
				case '9': map[0][2] = player; break;
			}
			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					if (map[i][j] == 0)
						map[i][j] = 79;
					if (map[i][j] == 1)
						map[i][j] = 88;
				}
			}
			system("cls");
			if (win == -1)
				player = !player;
			printf (" Player %d :\n", player + 1);
			prt(map);
			if (cnt >= 5)
			{
				for (i = 0 ; i < 3; i++)
				{
					if (map[i][0] != 32 && map[i][0] == map[i][1] && map[i][1] == map[i][2])
						win = !(map[i][0] % 2);
				}
				for (j = 0 ; j < 3; j++)
				{
					if (map[0][j] != 32 && map[0][j] == map[1][j] && map[1][j] == map[2][j])
						win = !(map[0][j] % 2);
				}
				if (map[0][0] != 32 && map[0][0] == map[1][1] && map[1][1] == map[2][2])
						win = !(map[1][1] % 2);
				if (map[0][2] != 32 && map[0][2] == map[1][1] && map[1][1] == map[2][0])
						win = !(map[1][1] % 2);
			}
		}
		if (win != -1)
			printf("  Player %d is win!", win + 1);
		else if (win == -1)
			printf("    Nobody win.");
		getchar();
	}

	return 0;
}

void prt(int (*map)[3])
{
	printf ("\n");
	printf ("    -----------\n");
	printf ("   | %c | %c | %c |\n",map[0][0],map[0][1],map[0][2]);
	printf ("   |---+---+---|\n");
	printf ("   | %c | %c | %c |\n",map[1][0],map[1][1],map[1][2]);
	printf ("   |---+---+---|\n");
	printf ("   | %c | %c | %c |\n",map[2][0],map[2][1],map[2][2]);
	printf ("    -----------\n");
}

int ai(int (*map)[3])
{
	int vote[3][3] = {0};
	int ai_switch = 0;
	int i = 0, j = 0;
	int result = 0;
	int highest = 0;

	vote[1][1]++;
	here:
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (map[i][j] != 32)
				continue;
			ai_switch = map[i][0] + map[i][1] + map[i][2];
			vote[i][j] += score(ai_switch);
			ai_switch = map[0][j] + map[1][j] + map[2][j];
			vote[i][j] += score(ai_switch);
			if (i == j)
			{
				ai_switch = map[0][0] + map[1][1] + map[2][2];
				vote[i][j] += score(ai_switch);
			}
			else if (i + j == 2)
				ai_switch = map[2][0] + map[1][1] + map[0][2];
				vote[i][j] += score(ai_switch);
			if (i == 1)
				vote[i][j]++;
			if (j == 1)
				vote[i][j]++;
			if (vote[i][j] > highest)
			{
				highest = vote[i][j];
				result = (2 - i) * 3 + j + 49;
				//convert coord to int to char.
			}
		}
	}
	return result;
}

int score(int ai_switch)
{
	int O = 79, X = 88;
	switch (ai_switch)
	{
		case 208: return 1000; break;
		case 190: return 900; break;
		case 152: return 100; break;
		case 143: return 90; break;
		case 96: return 10; break;
	}
}

/*
Player: O, AI: X

ASCII: O=79,X=88

sample:
 -----------
| O | X |   |
|---+---+---|
|   | O |   |
|---+---+---|
|   | X | O |
 -----------

*/
