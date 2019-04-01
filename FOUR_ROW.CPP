#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>

void Init(int size)
{
	int i=1,j=1,x1,x2,y1,y2;
	for (i=2;i<9;i++)
	{
		x1=i*size;
		x2=(i+1)*size;
		y1=size;
		y2=2*size;
		setcolor(BROWN);
		setfillstyle(SOLID_FILL,WHITE);
		int points1[]={x1,y1,x1,y2,x2,y2,x2,y1,x1,y1};
		fillpoly(5,points1);
	}
	for (i=2;i<9;i++)
		for (j=2;j<9;j++)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			x1=i*size;
			x2=(i+1)*size;
			y1=j*size;
			y2=(j+1)*size;
			setcolor(GREEN);
			int points[]={x1,y1,x1,y2,x2,y2,x2,y1,x1,y1};
			fillpoly(5,points);
		}
}

int Vert(int grid[7][7],int row,int col,int player)
{
	int flag=1;
	for (int i=0;i<4;i++)
	{
		if (grid[row+i][col]!=player+1)
		{
			flag=0;
			break;
		}
	}
	return flag;
}

int Hor(int grid[7][7],int row,int col,int player)
{
	int flag=1;
	for (int i=0;i<4;i++)
	{
		if (grid[row][col+i]!=player+1)
		{
			flag=0;
			break;
		}
	}

	return flag;
}

int Slant_LR(int grid[7][7],int row,int col,int player)
{
	int i,j,count=0,flag=1;
	for (i=row,j=col;count<4;count++)
	{
		if (grid[i][j]!=player+1)
		{
			flag=0;
			break;
		}
		i--;
		j++;
	}
	return flag;
}

int Slant_RL(int grid[7][7],int row,int col,int player)
{
	int i,j,count=0,flag=1;
	for (i=row,j=col;count<4;count++)
	{
		if (grid[i][j]!=player+1)
		{
			flag=0;
			break;
		}
		i--;
		j--;
	}
	return flag;
}

int check(int grid[7][7],int row,int col,int player)
{
	int r,c,v=0,h=0,slr=0,srl=0,result;
	if (row<4)
	{
		 v=Vert(grid,row,col,player);
	}
	c=0;
	if (col>3)
		c=col-3;
	for (int i=0;i<3;i++)
	{
		h=Hor(grid,row,c+i,player);
		if (h==1)
			break;
	}
	r=row;
	c=col;
	while(r<6 && c<6)
	{
		if (grid[r+1][c+1]==player+1)
		{
			r+=1;
			c+=1;
		}
		else
			break;
	}
	if (c>2)
	{
		srl=Slant_RL(grid,r,c,player);
	}
	r=row;
	c=col;
	while(r<6 && c>0)
	{
		if (grid[r+1][c-1]==player+1)
		{
			r+=1;
			c-=1;
		}
		else
			break;
	}
	if (c<4)
	{
		slr=Slant_LR(grid,r,c,player);
	}
	result=v+h+slr+srl;
	return result;
}

int move(int xc,int  yc,int size,int player,int full[7])
{
	char choice;
	int txc,tyc,i=0,j,flag=0;
	int points1[]={xc,yc,xc,yc+size,xc+size,yc+size,xc+size,yc,xc,yc};
	if (player%2==1)
			setfillstyle(XHATCH_FILL,MAGENTA);
		else
			setfillstyle(XHATCH_FILL,LIGHTBLUE);
	fillpoly(5,points1);
	while(1)
	{
		choice=getch();
		txc=xc;
		tyc=yc;
		switch(choice)
		{
			case 'a':if (xc>size*2)
				 xc-=size;
				 break;
			case 'd':if (xc<size*8)
				 xc+=size;
				 break;
		}
		int points_old[]={txc,tyc,txc,tyc+size,txc+size,tyc+size,txc+size,tyc,txc,tyc};
		setcolor(BROWN);
		setfillstyle(SOLID_FILL,WHITE);
		fillpoly(5,points_old);
		i=xc/size-2;
		if (full[i]==1)
		{
			flag=1;
			setfillstyle(XHATCH_FILL,RED);
		}
		else
		if (player%2==1)
			setfillstyle(XHATCH_FILL,MAGENTA);
		else
			setfillstyle(XHATCH_FILL,LIGHTBLUE);
		if (choice=='s')
		{
			if (flag==1)
			{
				xc=txc;
				setcolor(WHITE);
				outtextxy(500,250,"COLUMN FILLED");
			}
			else
			{
				setcolor(BLACK);
				outtextxy(500,250,"COLUMN FILLED");
				setcolor(WHITE);
				return i;
			}
		}
		flag=0;
		int points[]={xc,yc,xc,yc+size,xc+size,yc+size,xc+size,yc,xc,yc};
		fillpoly(5,points);
	}
}

void play(int grid[7][7],int size)
{
	int i,player=0,xcoin,ycoin,rcoin,y;
	int count=49;
	int col;
	int full[7]={0};
	while (count!=0)
	{
		col=move(50+size,50,size,player,full);
		for (i=6;i>=0;i--)
		{
			if (grid[i][col]==0)
			{
				grid[i][col]=player+1;
				if (i==0)
					full[col]=1;
				break;
			}
		}
		count-=1;
		int recolour=col+i+player;
		player=(player+1)%2;
		y=size*2+size/2;
		xcoin=size*2+col*size+size/2;
		ycoin=size*2+i*size+size/2;
		rcoin=int(size*0.35);
		while (y<=ycoin-size)
		{
			if (player%2==1)
			{
				setcolor(BLUE);
				setfillstyle(SOLID_FILL,BLUE);
				circle(xcoin,y,rcoin);
				floodfill(xcoin,y,BLUE);
			}
			else
			{
				setcolor(MAGENTA);
				setfillstyle(SOLID_FILL,MAGENTA);
				circle(xcoin,y,rcoin);
				floodfill(xcoin,y,MAGENTA);
			}
			delay(250);

			int xprev=xcoin-size/2;
			int yprev=y-size/2;
			setfillstyle(SOLID_FILL,YELLOW);
			int points[]={xprev,yprev,xprev,yprev+size,xprev+size,yprev+size,xprev+size,yprev,xprev,yprev};
			setcolor(GREEN);
			fillpoly(5,points);
			y+=size;
			recolour+=1;
		}
		if (player%2==1)
		{
			setcolor(BLUE);
			setfillstyle(SOLID_FILL,BLUE);
			circle(xcoin,y,rcoin);
			floodfill(xcoin,y,BLUE);
		}
		else
		{
			setcolor(MAGENTA);
			setfillstyle(SOLID_FILL,MAGENTA);
			circle(xcoin,y,rcoin);
			floodfill(xcoin,y,MAGENTA);
		}
		int chk=check(grid,i,col,(player+1)%2);
		if (chk==1)
			break;
	}
}

void main()
{
	int gm,size=50,i,j;
	int grid[7][7]={0};
	int gd=DETECT;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
	Init(size);
	play(grid,size);
	printf("\n");
	for (i=0;i<7;i++)
	{
		for (j=0;j<7;j++)
		{
			printf("%d ",grid[i][j]);
		}
		printf("\n");
	}
	//cleardevice();
	getch();
	closegraph();
}