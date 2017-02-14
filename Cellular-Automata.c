#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int system(const char *string);

int lod(int x,int y)
{
	if (x==3)
		return 1;
	else if (x==2)
		return y;
	else
		return 0;
}

int main()
{
	int h=50,l=80,s=50;
	system("mode con cols=160 lines=52");
	int lod (int x,int y);
	int arr1[h][l],arr2[h][l],temp[h][l];
	int i,j,n=0,counter=0,alive_old,alive=0;
	srand((unsigned)time(NULL));
	for (i=0; i<h; i++)
	{
		for (j=0; j<l; j++)
		{
			arr1[i][j]=rand()/16384;
			if (arr1[i][j]==1)
				alive++;
		}
	}
	int number=alive;
	printf ("Info:    Speed:%d    Room:%d    Generations:0    Alive:%d    Dead:0    State:Instable\n",s,h*l,alive);
	for (i=0; i<h; i++)
	{
		for (j=0; j<l; j++)
		{
			if (arr1[i][j]==0)
				printf ("  ");
			else
				printf ("■");
		}
	}
	//Sleep(1000/s);
	system("cls");

	while(1)
	{
		//左上
		n=0;
		if (arr1[1][0]==1) n++;
		if (arr1[0][1]==1) n++;
		if (arr1[1][1]==1) n++;
		arr2[0][0] = lod(n,arr1[0][0]);
		//右上
		n=0;
		if (arr1[0][l-2]==1) n++;
		if (arr1[1][l-2]==1) n++;
		if (arr1[1][l-1]==1) n++;
		arr2[0][l-1] = lod(n,arr1[0][l-1]);
		//左下
		n=0;
		if (arr1[h-2][0]==1) n++;
		if (arr1[h-2][1]==1) n++;
		if (arr1[h-1][1]==1) n++;
		arr2[h-1][0] = lod(n,arr1[h-1][0]);
		//右下
		n=0;
		if (arr1[h-2][l-2]==1) n++;
		if (arr1[h-1][l-2]==1) n++;
		if (arr1[h-2][l-1]==1) n++;
		arr2[h-1][l-1] = lod(n,arr1[h-1][l-1]);

		//上
		for (j=1; j<l-1; j++)
		{
			n=0;
			if (arr1[0][j-1]==1) n++;
			if (arr1[0][j+1]==1) n++;
			if (arr1[1][j-1]==1) n++;
			if (arr1[1][j]==1) n++;
			if (arr1[1][j+1]==1) n++;
			arr2[0][j] = lod(n,arr1[0][j]);
		}
		//下
		for (j=1; j<l-1; j++)
		{
			n=0;
			if (arr1[h-1][j-1]==1) n++;
			if (arr1[h-1][j+1]==1) n++;
			if (arr1[h-2][j-1]==1) n++;
			if (arr1[h-2][j]==1) n++;
			if (arr1[h-2][j+1]==1) n++;
			arr2[h-1][j] = lod(n,arr1[h-1][j]);
		}
		//左
		for (i=1; i<h-1; i++)
		{
			n=0;
			if (arr1[i-1][0]==1) n++;
			if (arr1[i+1][0]==1) n++;
			if (arr1[i-1][1]==1) n++;
			if (arr1[i][1]==1) n++;
			if (arr1[i+1][1]==1) n++;
			arr2[i][0] = lod(n,arr1[i][0]);
		}
		//右
		for (i=1; i<h-1; i++)
		{
			n=0;
			if (arr1[i-1][l-1]==1) n++;
			if (arr1[i+1][l-1]==1) n++;
			if (arr1[i-1][l-2]==1) n++;
			if (arr1[i][l-2]==1) n++;
			if (arr1[i+1][l-2]==1) n++;
			arr2[i][l-1] = lod(n,arr1[i][l-1]);
		}

		//中
		for (i=1; i<h-1; i++)
		{
			for (j=1; j<l-1; j++)
			{
				n=0;
				if (arr1[i-1][j-1]==1) n++;
				if (arr1[i-1][j]==1) n++;
				if (arr1[i-1][j+1]==1) n++;
				if (arr1[i][j-1]==1) n++;
				if (arr1[i][j+1]==1) n++;
				if (arr1[i+1][j-1]==1) n++;
				if (arr1[i+1][j]==1) n++;
				if (arr1[i+1][j+1]==1) n++;
				arr2[i][j] = lod(n,arr1[i][j]);
			}
		}
		counter++,alive_old=alive,alive=0;
		for (i=0; i<h; i++)
		{
			for (j=0; j<l; j++)
			{
				if (arr2[i][j]==1)
					alive++;
			}
		}
		printf ("Info:    Speed:%d    Room:%d    Generations:%d    Alive=%d    Dead:%d    ",s,h*l,counter,alive,number-alive);
		if (alive==alive_old)
			printf ("State:Stable");
		else
			printf ("State:Instable");
		printf ("\n");
		for (i=0; i<h; i++)
		{
			for (j=0; j<l; j++)
			{
				if (arr2[i][j]==0)
					printf ("  ");
				else
					printf ("■");
			}
		}
//exchange
		for (i=0; i<h; i++)
		{
			for (j=0; j<l; j++)
			{
				temp[i][j]=arr2[i][j];
				arr2[i][j]=arr1[i][j];
				arr1[i][j]=temp[i][j];
			}
		}
		//Sleep(1000/s);
		system("cls");
	}
	return 0;
}
