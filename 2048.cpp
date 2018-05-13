#include<iostream>
#include<conio.h>
#include<windows.h>
#include<cstdlib> 
#include<ctime>
#include<iomanip>
using namespace std;

void HideCursor()	//清除光标的函数
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//隐藏输入符号
}

void gotoxy(int x,int y)//类似于清屏函数，光标移动到原点位置进行重画
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

int main()
{
	HideCursor();
	int a[4][4]={0};
	srand((unsigned)time(0));
	
	int b=rand()%16;
//	cout<<b<<endl;
	int m=rand()%4;		//请在此处修改概率！！！ 
	if(m==0)
		a[b/4][b%4]=4;
	else
		a[b/4][b%4]=2;	//2、4出现概率1:3，下同 

	int bb=rand()%15+1;
	int nmh=0;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(a[i][j]==0)
			{
				bb--;
				if(bb==0)
				{
					int l=rand()%4;
					if(l==0)
						a[i][j]=4;
					else
						a[i][j]=2;
				}
			}
		}
	}

	cout<<endl<<"\t Score: 0"<<endl<<"\t┌───┬───┬───┬───┐"<<endl<<"\t│      │      │      │      │"<<endl;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(j==0)
				cout<<"\t│";
			if(a[i][j]==0)
				cout<<"      ";		//如果为0，输出空格 
			if(a[i][j]!=0)
				cout<<setw(4)<<a[i][j]<<"  ";
			cout<<"│";
		}
		if(i!=3)
		{
			cout<<endl<<"\t│      │      │      │      │";
			cout<<endl<<"\t├───┼───┼───┼───┤";
			cout<<endl<<"\t│      │      │      │      │"<<endl;	
		}
	}
	cout<<endl<<"\t│      │      │      │      │"<<endl<<"\t└───┴───┴───┴───┘";
	
	char c;
	int score=0; 
	
	while(1)
	{
		Sleep(120);
		c=getch();
		
//		system("cls");
		gotoxy(0,0); 
		
		int t[4][4];
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				t[i][j]=a[i][j];
			}
		}
		
		if(c==72)	//up
		{
			for(int j=0;j<4;j++)
			{
				for(int i=0;i<3;i++)
				{
					if(a[i][j]!=0)
					{
						int co=0;
						for(int h=i+1;h<4;h++)
						{
							if(a[h][j]!=0&&a[h][j]!=a[i][j])
								co++;
							if(a[h][j]==a[i][j]&&co==0)		//如果从上往下有非零的两个相等的数，上面的*2，下面的改为0
							{
								a[i][j]=a[i][j]*2;
								score+=a[i][j];		//合并得到的数是多少，分数加多少 
								a[h][j]=0;
								i=h;
								break;
							}
						}
					}
				}
				//所有数往上移动 
				int k=0;
				for(int i=0;i<4;i++)
				{
					if(a[i][j]!=0)
					{
						a[k][j]=a[i][j];
						k++;
					}
				}
				for(int i=k;i<4;i++)
				{
					a[i][j]=0;
				}
			}
		}
		
		if(c==80)	//down
		{
			for(int j=3;j>=0;j--)
			{
				for(int i=3;i>0;i--)
				{
					if(a[i][j]!=0)
					{
						int co=0;
						for(int h=i-1;h>=0;h--)
						{
							if(a[h][j]!=0&&a[h][j]!=a[i][j])
								co++;
							if(a[h][j]==a[i][j]&&co==0)
							{
								a[i][j]=a[i][j]*2;
								score+=a[i][j];
								a[h][j]=0;
								i=h;
								break;
							}
						}
					}
				}
				int k=3;
				for(int i=3;i>=0;i--)
				{
					if(a[i][j]!=0)
					{
						a[k][j]=a[i][j];
						k--;
					}
				}
				for(int i=k;i>=0;i--)
				{
					a[i][j]=0;
				}
			}
		}
		
		if(c==75)	//left
		{
			for(int j=0;j<4;j++)
			{
				for(int i=0;i<3;i++)
				{
					if(a[j][i]!=0)
					{
						int co=0;
						for(int h=i+1;h<4;h++)
						{
							if(a[j][h]!=0&&a[j][h]!=a[j][i])
								co++;
							if(a[j][h]==a[j][i]&&co==0)
							{
								a[j][i]=a[j][i]*2;
								score+=a[j][i];
								a[j][h]=0;
								i=h;
								break;
							}
						}
					}
				}
				int k=0;
				for(int i=0;i<4;i++)
				{
					if(a[j][i]!=0)
					{
						a[j][k]=a[j][i];
						k++;
					}
				}
				for(int i=k;i<4;i++)
				{
					a[j][i]=0;
				}
			}
		}
		
		if(c==77)	//right
		{
			for(int j=3;j>=0;j--)
			{
				for(int i=3;i>0;i--)
				{
					if(a[j][i]!=0)
					{
						int co=0;
						for(int h=i-1;h>=0;h--)
						{
							if(a[j][h]!=0&&a[j][h]!=a[j][i])
								co++;
							if(a[j][h]==a[j][i]&&co==0)
							{
								a[j][i]=a[j][i]*2;
								score+=a[j][i];
								a[j][h]=0;
								i=h;
								break;
							}
						}
					}
				}
				int k=3;
				for(int i=3;i>=0;i--)
				{
					if(a[j][i]!=0)
					{
						a[j][k]=a[j][i];
						k--;
					}
				}
				for(int i=k;i>=0;i--)
				{
					a[j][i]=0;
				}
			}
		}
		

		int sum=0,xjw=0;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(t[i][j]==a[i][j])
					xjw++; 
				if(a[i][j]==0)
					sum++;
			}
		}
		
		sum--; 
		int d;
		if(sum!=0) 
			d=rand()%sum;
		else
			d=0;
//		cout<<d<<endl;
		
		int e=-1;
		cout<<endl<<"\t Score: "<<score<<endl<<"\t┌───┬───┬───┬───┐"<<endl<<"\t│      │      │      │      │"<<endl;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(j==0)
					cout<<"\t│";
				if(xjw==16)
				{
					if(a[i][j]==0)
						cout<<"      │";
					else
					{
						if(a[i][j]<100)
							cout<<setw(4)<<a[i][j]<<"  │";
						else
							cout<<setw(5)<<a[i][j]<<" │";
					}	//没变化继续移动，不生成新的数
					continue;
				}
				if(a[i][j]==0)
				{
					e++;
					if(e==d)
					{
						int n=rand()%4;		//请在此处修改概率！！ 
						if(n==0) 
							a[i][j]=4;
						else
							a[i][j]=2;	//移动后生成一个 
					}
					else
					{
						cout<<"      │";
						continue;
					}
				}
				if(a[i][j]<100)
					cout<<setw(4)<<a[i][j]<<"  │";
				else
					cout<<setw(5)<<a[i][j]<<" │";	//输出结果 
			}
			if(i!=3)
			{
				cout<<endl<<"\t│      │      │      │      │";
				cout<<endl<<"\t├───┼───┼───┼───┤";
				cout<<endl<<"\t│      │      │      │      │"<<endl;
			}
		}
		cout<<endl<<"\t│      │      │      │      │"<<endl<<"\t└───┴───┴───┴───┘";
		
		//上下左右不相等则gameover 
		int hth=0;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(a[i][j]==a[i][j+1])
					hth++;
			}
		}
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(a[i][j]==a[i+1][j])
					hth++; 
			}
		}
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(a[i][j]==0)
					hth++; 
			}
		}
		if(hth==0)
		{
			cout<<endl<<"\t ~ Gameover ~ ";
			break;
		}
	}
	system("pause");
}
