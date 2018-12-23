#include<stdio.h>
#include<dos.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream.h>
#define TOP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#include <fstream.h>

struct highscore
{
	char name[32];
	int score;
	struct highscore *next;
};
struct highscore *head = NULL;
int sz;
int song();
void score(int s=1)
{
	static unsigned long sc=0;
	window(70,22,78,23);
	textcolor(WHITE);
	if(s)
	{
		cprintf("      ");
		window(70,22,78,23);
		cprintf("%ld",sc);
		sc=sc+100;
	}
	else
		sc=0;
	//return sc;
}

char readf(char filename[256])
{
  string line;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( myfile.good() )
    {
      getline (myfile,line);
      cout << line << endl;
    }
    myfile.close();
  }

  else cout << "Unable to open file";

  return 0;
}

void record (int k)
{
	char plname[20],nplname[20],cha,c,n[32];
   int i,j,px,h;
	struct highscore *link = (struct highscore*) malloc(sizeof(struct highscore));
	struct highscore *ptr=head;
   px=(k-6)*100;
   FILE *info;
   info=fopen("record.txt","a+");
   getch();
   system("cls");
   printf("Enter your name\n");
   scanf("%[^\n]",plname);
   //************************
   for(j=0;plname[j]!='\0';j++){ //to convert the first letter after space to capital
   nplname[0]=toupper(plname[0]);
   if(plname[j-1]==' '){
   nplname[j]=toupper(plname[j]);
   nplname[j-1]=plname[j-1];}
   else nplname[j]=plname[j];
   }
   nplname[j]='\0';
   //*****************************
   //sdfprintf(info,"\t\t\tPlayers List\n");
   fprintf(info,"%s %d\n",nplname, px);
	//**************************
   for(i=0;i<=50;i++)
   fprintf(info,"%c",'_');
   fprintf(info,"\n");
   fclose(info);
   printf("wanna see past records press 'y'\n");
   cha=getch();
   system("cls");
   if(cha=='y'){
   info=fopen("record.txt","r");
   for (int i=0;i<10;i++)
   		{
		   fscanf(info, "%s %d",&n, &h);
		   strcpy(link->name,n);
		   link->score = h;
			link->next = head;
			head = link;}
	fclose(info);
	int e=0;
	while(ptr!= NULL){
		printf ("%d. %s %f",e+1,ptr->name, ptr->score);
		ptr = ptr->next;
	}
}
}
void status(char *s,int c=RED)
{
	window(70,23,78,25);
	textcolor(c);
	cprintf("%s",s);
	for(int x=strlen(s);x<7;x++)
	cprintf(" ");
	textcolor(WHITE);
}

void life (int s=1)
{
	static unsigned long li=3;
	window(15,24,23,24);
	if (s)
		{
			textcolor(RED);
			cprintf("      ");
			window(15,24,23,24);
			cprintf("%ld",li);
			li=li-1;
		}
}

void maingame()
{
	clrscr();
	_setcursortype(_NOCURSOR);
	textcolor(WHITE);
	printf("\n   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
	for(int i=0;i<17;i++)
	printf("   ³                                                                         ³  ");
	printf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
	printf("   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿                                ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ");
	printf("   ³  S N A K E  G A M E  ³   Press SPACE to Pause & Play  ³ SCORE : 0       ³  ");
	printf("   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ                                ³ STATUS: Playing ³  ");
	printf("      LIFE  : 3                                            ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ");
	life();
	int snkx[20],snky[20],d=LEFT,p=0,restart=1,start=1, li=3, state=1;
	sz=6;
	while(state)
	{
		if(start)
		{
			for(i=0;i<6;i++)
			snkx[i]=30+i*2;
			for(i=6;i<20;i++)
			snkx[i]=0;
			for(i=0;i<20;i++)
			snky[i]=9;
			sz=6;
			p=0;
			d=LEFT;
			start=0;
			score();
			window(6,3,76,19);
			for(i=0;i<610;i++)
			cprintf("  ");
		}
		if(restart)
		{
			for(i=0;i<10;i++)
			snkx[i]=30+i*2;
			for(i=10;i<20;i++)
			snkx[i]=0;
			for(i=0;i<20;i++)
			snky[i]=9;
			p=0;
			d=LEFT;
			restart=0;
			window(6,3,76,19);
			for(i=0;i<610;i++)
			cprintf("  ");
		}
		int x,y;
		if(p!=1)
		{
			randomize();
			do{
						x=random(70)+6;
					}while(x%2==1);
					y=random(16)+3;
			p=1;
			window(x,y,x+1,y+1);
			textcolor(LIGHTGREEN);
			cprintf("%c",236);
			textcolor(WHITE);
		}
		while(!kbhit())
		{
			status("Playing",LIGHTGREEN);
			window(snkx[sz-1],snky[sz-1],snkx[sz-1]+2,snky[sz-1]+2);
			cprintf(" ");
			for(i=0;i<sz-1;i++)
			{
				window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
				cprintf("");
			}
			for(i=sz-1;i>=1;i--)
			{
				snkx[i]=snkx[i-1];
				snky[i]=snky[i-1];
			}
			switch(d)
			{
				case RIGHT : snkx[0]+=2; break;
				case LEFT  : snkx[0]-=2; break;
				case TOP   : snky[0]-=1; break;
				case DOWN  : snky[0]+=1;
			}
			delay(200);
			if(x==snkx[0] && y==snky[0])
			{
				int f=0;
				do{
					do{
						x=random(70)+6;
					}while(x%2==1);
					y=random(16)+3;
					for(i=0;i<sz;i++)
						if(snkx[i]==x && snky[i]==y)
							f=1;
				}while(f);
				p=1;
				window(x,y,x+1,y+1);
				textcolor(LIGHTGREEN);
				cprintf("%c",236);
				textcolor(WHITE);
				score();
				sound(250);
				delay(50);
				nosound();
				sz++;

				switch(d)
				{
					case RIGHT : snkx[sz-1]+=2;
								 snky[sz-1]=snky[sz-2];
								 break;
					case LEFT  : snkx[sz-1]-=2;
								 snky[sz-1]=snky[sz-2];
								 break;
					case TOP   : snky[sz-1]-=1;
								 snkx[sz-1]=snkx[sz-2];
								 break;
					case DOWN  : snky[sz-1]+=1;
								 snkx[sz-1]=snkx[sz-2];
				}
			}
			int sflag=0;
			for(i=0;i<sz-1;i++)
				if(snkx[sz-1]==snkx[i] && snky[sz-1]==snky[i])
				{
					sflag=1;
					break;
				}
			if(snkx[0]<5 || snkx[0]>76 || snky[0]<3 || snky[0]>19)
				sflag=1;
			if(sflag)
			{
				textcolor(LIGHTRED);
				for(i=1;i<sz;i++)
				{
					window(snkx[i],snky[i],snkx[i]+1,snky[i]+1);
					cprintf("");
				}
				status("Stoped",LIGHTRED);
				life();
				restart=1;
				li=li-1;
				break;
			}
		}
		char ch=getch();
		switch(tolower(ch))
		{
			case ' ' :
						status("Paused");
						getch();
						break;
			case 0 : {
						char chh=getch();
						switch(chh)
						{
							case 72 :{
									if(d==LEFT || d== RIGHT)
									d=TOP;
									} break;
							case 80 :{
									if(d==LEFT || d== RIGHT)
									d=DOWN;
									} break;
							case 75 :{
									if(d==TOP || d==DOWN)
									d=LEFT;
									} break;
							case 77 :{
									if(d==TOP || d==DOWN)
									d=RIGHT;
									}
						}
					}break;
					//new_High_Score();
		}
		if (li == 0)
		{
			state= 0;
		}
	}
	printf("\n");
	system("pause");
	system ("cls");
	record(sz);
	getch();
}

void load()
{
	int i;
	char ch=177,ce=178;
	textcolor(WHITE);
	clrscr();
	gotoxy(34,9);
	printf("LOADING...");
	gotoxy(20,10);
	for(i=0;i<=35;i++)
	{
		printf("%c",ch);
	}
	gotoxy(20,10);
	for(i=0;i<=35;i++)
	{
		delay(200);
		printf("%c",ce);
	}
	gotoxy(30,12);
	printf("Enter any key to start...");
	getch();
}

void main()
{
	system("cls");
	int opsi;
	gotoxy(24,4); printf("Welcome to Snake Game\n");
	gotoxy(22,6); printf("What do you want to do?");
	gotoxy(25,7); printf("1. Play the game\n");
	gotoxy(25,8); printf("2. Discailmer\n");
	gotoxy(25,9); printf("3. How to play\n");
	gotoxy(25,10); printf("4. Exit");
	gotoxy(26,12); printf("\nYour choice is ");
	scanf("%d",&opsi);
	switch(opsi)
		{
			case 1:
				system("cls");
				load();
				maingame();
				main();
			case 2:
				system("cls");
				readf("Disclaimer.txt");
				printf("\n\n");
				system("pause");
				main();
			case 3:
				system("cls");
				readf("Help.txt");
				printf("\n\n");
				system("pause");
				main();
			case 4:
				system("cls");
				return;
			case 0:
				system("cls");
				main();
		}
}


int song()
{
 sound(330);delay(100);
 sound (330);delay(300);
 sound (330);delay(300);
 sound (262);delay(100);
 sound (330);delay(300);
 sound (392);delay(700);
 sound (196);delay(700);
 sound (262);delay(300);
 sound (196);delay(300);
 sound (164);delay(300);
 sound (220);delay(100);
 sound (246);delay(300);
 sound (233);
 sound (220);delay(300);
 sound (196);delay(150);
 sound (330);delay(150);
 sound (392);delay(150);
 sound (440);delay(300);
 sound (349);delay(100);
 sound (392);delay(300);
 sound (330);delay(300);
 sound (262);delay(100);
 sound (294);delay(100);
 sound (247);delay(500);
 sound (262);delay(300);
 sound (196);delay(300);
 sound (164);delay(300);
 sound (220);delay(100);
 sound (246);delay(300);
 sound (233);
 sound (220);delay(300);
 sound (196);delay(150);
 sound (330);delay(150);
 sound (392);delay(150);
 sound (440);delay(300);
 sound (349);delay(100);
 sound (392);delay(300);
 sound (330);delay(300);
 sound (262);delay(100);
 sound (294);delay(100);
 sound (247);delay(900);
 sound (392);delay(100);
 sound (370);delay(100);
 sound (349);delay(100);
 sound (311);delay(300);
 sound (330);delay(300);
 sound (207);delay(100);
 sound (220);delay(100);
 sound (262);delay(300);
 sound (220);delay(100);
 sound (262);delay(100);
 sound (294);delay(500);
 sound (392);delay(100);
 sound (370);delay(100);
 sound (349);delay(100);
 sound (311);delay(300);
 sound (330);delay(300);
 sound (523);delay(300);
 sound (523);delay(100);
 sound (523);delay(1100);
 sound (392);delay(100);
 sound (370);delay(100);
 sound (349);delay(100);
 sound (311);delay(300);
 sound (330);delay(300);
 sound (207);delay(100);
 sound (220);delay(100);
 sound (262);delay(300);
 sound (220);delay(100);
 sound (262);delay(100);
 sound (294);delay(500);
 sound (311);delay(300);
 sound (296);delay(300);
 sound (262);delay(1300);
 sound (262);delay(100);
 sound (262);delay(300);
 sound (262);delay(300);
 sound (262);delay(100);
 sound (294);delay(300);
 sound (330);delay(50);
 sound (262);delay(50);
 sound (220);delay(50);
 sound (196);delay(700);
 sound (262);delay(100);
 sound (262);delay(300);
 sound (262);delay(300);
 sound (262);delay(100);
 sound (294);delay(100);
 sound (330);delay(700);
 sound (440);delay(300);
 sound (392);delay(500);
 sound (262);delay(100);
 sound (262);delay(300);
 sound (262);delay(300);
 sound (262);delay(100);
 sound (294);delay(300);
 sound (330);delay(50);
 sound (262);delay(50);
 sound (220);delay(50);
 sound (196);delay(700);

 sound (330);delay(100);
 sound (330);delay(300);
 sound (330);delay(300);
 sound (262);delay(100);
 sound (330);delay(300);
 sound (392);delay(700);
 sound (196);delay(700);
 sound (196);delay(125);
 sound (262);delay(125);
 sound (330);delay(125);
 sound (392);delay(125);
 sound (523);delay(125);
 sound (660);delay(125);
 sound (784);delay(575);
 sound (660);delay(575);
 sound (207);delay(125);
 sound (262);delay(125);
 sound (311);delay(125);
 sound (415);delay(125);
 sound (523);delay(125);
 sound (622);delay(125);
 sound (830);delay(575);
 sound (622);delay(575);
 sound (233);delay(125);
 sound (294);delay(125);
 sound (349);delay(125);
 sound (466);delay(125);
 sound (587);delay(125);
 sound (698);delay(125);
 sound (932);delay(575);
 sound (932);delay(125);
 sound (932);delay(125);
 sound (932);delay(125);
 sound (1046);

 nosound();
 return 0;
}

