			//JUMP.CPP
#include<fstream.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<time.h>
#include<stdio.h>

		/* This C++ program is single players game which aims to
		 provide recreation to its users. It maintains a user
		 account that stores and username, password and userid.
		 It also maintains usee highscore and a leader board. */




class player           // main account frame
{
	char name[60];
	char username[20];
	char password[30];
	int userid;
	unsigned int highscore;

	public:
		player(char name1[]=NULL, char user[], char pass[])  //Parameterized constructor
		{
			strcpy(name, name1);
			strcpy(username, user);
			strcpy(password, pass);
			userid=rand()%100;
			highscore=0;
		}

		void compare(int score)
		{
			if(score>highscore) highscore=score;
		}

		void change(char user[], char pass[])
		{
			if(user[0]!='*')
				strcpy(username, user);

			if(pass[0]!='*')
				strcpy(password, pass);

		}

		int retuserid()
		{
			return userid;
		}

		int rethigh()
		{
			return highscore;
		}

		char* retusername()
		{
			return username;
		}

		char* retpass()
		{
			return password;
		}

		char* retname()
		{
			return name;
		}



}p1,aadmin("admin","admin","admin"); 		//admin account created dynamically


void login();
void usermenu();
void adminmenu();


void funcwrite()      //function to over write existing account
{
fstream fp,fp1;
player pt;

fp.open("game_data.dat", ios::in|ios::out|ios::app|ios::binary);
fp1.open("temp.dat", ios::out|ios::app|ios::binary);

fp.read((char*)&pt,sizeof(player));

for(int t=0; !fp.eof() ; t++  )
{
	if(pt.retuserid()!=p1.retuserid())
	{
		fp1.write((char*)&pt,sizeof(player));
	}

	fp.read((char*)&pt,sizeof(player));

}

fp1.seekp(0,ios::end);
fp1.write((char*)&p1,sizeof(player));

fp1.close();
fp.close();


remove("game_data.dat");
rename("temp.dat" , "game_data.dat");
}


void deletep1()        //function to delete account
{
fstream fp,fp1;
player pt;

fp.open("game_data.dat", ios::in|ios::out|ios::app|ios::binary);
fp1.open("temp.dat", ios::out|ios::app|ios::binary);

do
{
	fp.read((char*)&pt,sizeof(player));
	if(pt.retuserid()!=p1.retuserid())
	{
		fp1.write((char*)&pt,sizeof(player));
	}

}while(!fp.eof());

fp.close();
fp1.close();

remove("game_data.dat");
rename("temp.dat" , "game_data.dat");

}


void deleteaccount()
{
int gd,gm;
gd=DETECT;
char i;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
clearviewport();

setbkcolor(3);
settextstyle(3,0,3);

outtextxy(20,20,"Are you sure you want to delete your account? (Y/N)");
i=getch();

if(i=='y'|| i=='Y')
	deletep1();

closegraph();

login();

}


void endgame(int score)                    //game over function
{
int gd,gm;
gd=DETECT;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
clearviewport();

setbkcolor(4);
settextstyle(0,0,3);
setcolor(12+BLINK);
gotoxy(50,50);
outtextxy(getmaxx()/2-120,getmaxy()/2-20,"GAME OVER!");

cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                 Your score is "<<score;

p1.compare(score);
funcwrite();

getch();
closegraph();
usermenu();

}


void jumphigh(int &p, int q, int rate, int buildingheight, int score)        //used to make the ball jump high
{

int x,y;
x=15;
y=getmaxy()-26;
char ch;
int a,flag=0;

for(a=-rate;flag<2;y+=a,p-=rate)     //loop for building moving and ball jumping

	{
	clearviewport();
	bar(p,q-buildingheight,p+20,q);  //building
	bar(0,getmaxy()-12,getmaxx(),getmaxy()-10);  //bottonline

	for(int i=1;i<10;i++)        //ball
		circle(x,y,i+2);

	gotoxy(50,1);
	cout<<"SCORE : "<<score;

	gotoxy(1,1);
	cout<<"PRESS X TO EXIT!!";

	delay(50);                    //to control fps

	if(y>=getmaxy()-26)            // ball going up
		flag++;
	if (y<=getmaxy()-100)          // ball coming down
		a=rate;


       if( p<x+10 && p+20>x-10 )               //condition for collision
		{

		if( y+10 > q-30 )
			{
			closegraph();
			endgame(score);
			}
		}
       }
}



void jumplow(int &p,int q, int rate, int buildingheight,int score)           //used to make the ball jump low
{

int x,y;
x=15;
y=getmaxy()-26;
char ch;
int a,flag=0;

for(a=-rate;flag<2;y+=a,p-=rate)     //loop for building moving and ball jumping
{
	clearviewport();
	bar(p,q-buildingheight,p+20,q);  //building
	bar(0,getmaxy()-12,getmaxx(),getmaxy()-10);        //bottomline

	for(int i=1;i<10;i++)             //ball
		circle(x,y,i+2);

	gotoxy(50,1);
	cout<<"SCORE : "<<score;

	gotoxy(1,1);
	cout<<"PRESS X TO EXIT!!";
	delay(50); 			//to control fps

	if(y>=getmaxy()-26)                   // ball going up
		flag++;
	if (y<=getmaxy()-73)                  // ball coming down
		a=rate;

	if( p < x+10 && p+20 > x-10 )                //check for collision
	{
		if(q-30<y+10)
		{
			closegraph();
			endgame(score);
		}
	}
}

}


void game()             //main game function
{
int gd,gm;
gd=DETECT;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

gotoxy(1,1);
cout<<"PRESS X TO EXIT!!";
int score=0;
char choice;
int rate=6;                           // The rate determines the speed of the incoming building

for(int cnt=0;;cnt++,score++,rate+=3) //loop for number of times building come
 {
	int p=getmaxx()-40;
	int q=getmaxy()-13;
	int buildingheight;
	int l;

	time_t t;
	t=time(NULL);
	srand(t);
	l=rand();

	if(l%2==0)                     //to get random building heights
		buildingheight=30;
	else
		buildingheight=20;


	for(;p>1;p-=rate)      //loop for building moving
	{
		clearviewport();
		for(int z=1;z<10;z++)
			circle(15,getmaxy()-26,z+2);

		gotoxy(50,1);
		cout<<"SCORE : "<<score;

		gotoxy(1,1);
		cout<<"PRESS X TO EXIT!!";

		bar(0,getmaxy()-12,getmaxx(),getmaxy()-10);    //bottomline
		bar(p,q-buildingheight,p+20,q);   //building
		delay(50);			//to control FPS

		if(kbhit())
		{
			choice=getch();
			if(choice=='x')
			{
				closegraph();
				endgame(score);
			}
			else if(choice=='m'||choice=='M')
			{
				jumplow(p,q,rate,buildingheight,score);
				p+=rate;
			}
			else if(choice=='n'||choice=='N')
			{
				jumphigh(p,q,rate,buildingheight,score);
				p+=rate;
			}
			else
			{
				gotoxy(10,10);
				cout<<"Invalid Choice";
			}

		}

		if(getmaxy()-25>q-30)
		{
			if( p<28 && p+19>0 )
			{
				closegraph();
				endgame(score);
			}
		}

	}

   }


}

void showdetails(player p)                 //function to display user details
{

cout<<"    Username : "<<p.retusername()<<"\n    UserID : "<<p.retuserid()<<"\n    Highscore : "<<p.rethigh()<<endl;

}


void leaderboard()		     //displays personal highscore and top five scores
{
int gd,gm;
gd=DETECT;
char i;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
clearviewport();
settextstyle(0,0,2);
setbkcolor(8);
outtextxy((getmaxx()/2-100),30,"Leaderboard") ;
char high[10];
settextstyle(0,0,1);

itoa(p1.rethigh(), high, 10) ;   				 // to convert int highscore to char
outtextxy((getmaxx()/2-120),50,"Your highest score : ") ;
outtextxy((getmaxx()/2)+43,50,high);

player temp;
player arr[100],t;


fstream fp("game_data.dat",ios::in|ios::app|ios::binary);

fp.read((char*)&temp,sizeof(player));


for( int b=0 ; !fp.eof() ; b++ )
{
	arr[b]=temp;
	fp.read((char*)&temp,sizeof(player));

}
fp.close();

for(int e=0;e<b;e++)  			//code for bubble sort of array of high scores
{
	for(int d=0;d<(b-e-1);d++)
	{
		if(arr[d].rethigh() < arr[d+1].rethigh())
		{
			t=arr[d];
			arr[d]=arr[d+1];
			arr[d+1]=t;
		}
	}
}

cout<<"\n\n\n\n\n";

for(e=0;e<b&&e<5;e++)
	{
	cout<<e+1<<".";showdetails(arr[e]);
	cout<<"\n";
	}

getch();

closegraph();
}



void displayall()       //function to display all user details
{
int gd,gm;
gd=DETECT;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

setbkcolor(3);
clearviewport();
settextstyle(0,0,3);

fstream fp;
fp.open("game_data.dat", ios::in|ios::binary|ios::app);
player temp;

fp.read((char*)&temp, sizeof(player));

if(fp.eof())
	{
	outtextxy(20,20, "No Records");
	getch();
	closegraph();
	fp.close();
	adminmenu();
	}

outtextxy(225,10, "Details");

cout<<"\n\n\n\n\n";

for(;!fp.eof();)
{
	showdetails(temp);
	cout<<endl;
	fp.read((char*)&temp, sizeof(player));
}
fp.close();

getch();

closegraph();
adminmenu();
}


void welcome()                           //welcome screen
{
int gd,gm;
gd=DETECT;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
int i,j,n;

for(i=1,n=1;!kbhit();i++,n++)
	{
	if(i==6)           //to get contrast background and foreground colours
		i=1;

	j=i+8;

	setbkcolor(j);
	setcolor(i);
	clearviewport();
	settextstyle(0,0,7);

	outtextxy((getmaxx()/4)-30,(getmaxy()/2)-40,"Welcome");
	settextstyle(0,0,2);
	if(n>4)
		outtextxy((getmaxx()/4-30),(getmaxy()-20),"Press any key to continue");
	delay(350);
	}

getch();

closegraph();

}


void deleteall()                           //delete records of all users
{
int gd,gm;
gd=DETECT;
char i;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
settextstyle(0,0,3);
setbkcolor(3);
clearviewport();
settextstyle(3,0,3);

outtextxy(20,20,"Are you sure you want to delete all accounts? (Y/N)");
i=getch();

if(i=='y'|| i=='Y')
	remove("game_data.dat");


closegraph();
adminmenu();

}

void adminmenu()                          //Menu for admin login
{
int gd,gm;
gd=DETECT;
char i;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
clearviewport();
setbkcolor(3);

settextstyle(0,0,3);
outtextxy((getmaxx()/2-60),30,"Welcome") ;

settextstyle(0,0,1);

outtextxy(0,100,"1.Leaderboard ") ;
outtextxy(0,140,"2.Display All  ")  ;
outtextxy(0,180,"3.Delete All  ")  ;
outtextxy(0,220,"4.Sign out ")  ;

i=getch();
closegraph();

switch(i)
	{
	case '1' : leaderboard();adminmenu(); break;
	case '2' : displayall();adminmenu(); break;
	case '3' : deleteall();break;
	case '4' : login(); break;
	default: {

			initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
			setbkcolor(3);
			settextstyle(0,0,2);
			setbkcolor(3);
			outtextxy(120,200,"Invalid Choice. Try again") ;
			delay(1000);
			closegraph();
			adminmenu();
		 }
       }

}

void signin()			//sign in
{
clrscr();
fstream fp;
fp.open("game_data.dat", ios::in|ios::app|ios::binary);
char username[20],pass[30];
cout<<"\n\n\t\t\tSign in ";
cout<<"\n\nEnter username : ";
gets(username);

cout<<"\nPassword : ";
for (int z=0; ;z++ )    //code to get hidden password
 {
	bck :
	pass[z]=getch();

	if(pass[z]==13)
	{
		pass[z]='\0';
		break;
	}
	else if (pass[z]==8)
	{
		cout<<"\b \b"; z--; goto bck;
	}
	else
	cout<<"*";
  }

int flag=0;
player pt;

fp.read((char*)&pt,sizeof(player));
for(;!fp.eof();)
 {
	if(strcmp(pt.retusername(),username)==0)
	{
		if(strcmp(pt.retpass(),pass)==0)
		{
			fp.close();
			cout<<"\nLogging in...";
			delay(1000);
			p1=pt;
			usermenu();
		}
		else
		{
		fp.close();
		cout<<"\nPassword is incorrect. Try again.";
		getch();
		login();
		}

	flag=1;
	}
	fp.read((char*)&pt,sizeof(player));
 }
fp.close();


if(flag==0)
 {
	cout<<"\n\nUsername does not exist. ";
	getch();
 }

login();

}


void signup()                     //sign up
{
cout<<"\t\t\t\tSign Up";
char name[60], username[20], pass[30], passt[30];
cout<<"\n\n  Enter Full Name : "; gets(name);
cout<<"\n\n\n  Enter Username : "; gets(username);

player pt;

fstream fp("game_data.dat",ios::in|ios::out|ios::app|ios::binary);
fp.read((char*)&pt,sizeof(player));
for(;!fp.eof();)
 {
	if(strcmp(pt.retusername(),username)==0)
	{
		fp.close();
		cout<<"\n\n Username already exists.\n\n Try a different username or try signing in";
		getch();
		login();
	}
	fp.read((char*)&pt,sizeof(player));
 }
fp.close();
cout<<"\n\n  Enter Password : ";cin>>pass;
cout<<"\n\n  Re-enter Password : ";cin>>passt;

if (strcmp(pass,passt)!=0)
	{
	cout<<"\n\nPassword does not match.";
	getch();
	login();
	}


player p(name,username,pass);
fstream fp1;
fp1.open("game_data.dat", ios::in|ios::out|ios::ate|ios::binary);
fp1.write((char*)&p, sizeof(player));
fp1.close();

cout<<"\n\n\nYour account is created.\n\nYour used ID is : "<<p.retuserid();
getch();

login();
}

void adminlogin()			//login for admin
{
clrscr();
char username[30],pass[15];
cout<<"\n\n\t\t\tSign in ";
cout<<"\n\nEnter username : ";
gets(username);
cout<<"\nPassword : ";
for (int z=0; ;z++ )
 {
	bck :
	pass[z]=getch();
	if(pass[z]==13)
	{
		pass[z]='\0';
		break;
	}
	else if (pass[z]==8)
	{
		cout<<"\b \b"; z--; goto bck;
	}
	else
	cout<<"*";
 }

player pt;
if(strcmp("admin",username)==0)
{
	if(strcmp("admin",pass)==0)
	{
		cout<<"\nLogging in...";
		delay(1000);
		p1=aadmin;
		adminmenu();
	}
	else
	{
	cout<<"\nPassword is incorrect. Try again.";
	getch();
	login();
	}

}
else
{
	cout<<"\n\nInvalid Username ";
	getch();
}


login();

}


void editaccount()                               //function to edit account
{
clrscr();
char uname[20],pword[30];
cout<<"\n\t\t\t Edit Account ";
cout<<"\n\n1. Enter new username (Press * to keep the old one) " ;
gets(uname);
player pt;
fstream fp("game_data.dat",ios::in|ios::out|ios::app|ios::binary);
fp.read((char*)&pt,sizeof(player));
for(;!fp.eof();)
 {
	if(strcmp(pt.retusername(),uname)==0)
	{
		fp.close();
		cout<<"\n\n Username already exists.\n\n Try a different username or try signing in";
		getch();
		login();
	}
	fp.read((char*)&pt,sizeof(player));
 }
fp.close();

cout<<"\n\n2. Enter new password (Press * to keep the old one) " ;

gets(pword);

p1.change(uname,pword);

funcwrite();

login();
}


void exitscreen()                           //exit screen
{

int gd,gm;
gd=DETECT;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
setcolor(4);
setbkcolor(12);
settextstyle(0,0,7);

outtextxy((getmaxx()/4)-30,(getmaxy()/2)-40,"Goodbye");
delay(3000);

closegraph();

exit(0);
}

void instructions()                                      //function for instruction display
{
int gm,gd=DETECT;
initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

settextstyle(0,0,3);
setbkcolor(3);
outtextxy((getmaxx()/2-100),30,"Instructions") ;

settextstyle(5,0,1);
setcolor(2);
cout<<"\n\n\n\n\n\n\nThis is a single player game. Your aim is to jump over as many buildings as you can.\n\nThe frequency of buildings increases as the player continues to play.\n\nThe ball can be made to jump using the 'M' and 'N' keys.\n\n\nM -> Low Jump \n\nN -> High Jump\n\nX -> Exit\n\n\n\nPress any key to go back to main menu!";
getch();

closegraph();

usermenu();
}


void login()                             //login screen
{

int gd,gm;
gd=DETECT;
char i;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
settextstyle(0,0,3);
outtextxy((getmaxx()/2-60),30,"Welcome") ;

settextstyle(0,0,1);
setbkcolor(3);
outtextxy(0,100,"1.Sign in ");
outtextxy(0,140,"2.Sign up ") ;
outtextxy(0,180,"3.Admin ")  ;
outtextxy(0,220,"4.Exit ")  ;
i=getch();
closegraph();

switch(i)
	{
	case '1' : signin(); break;
	case '2' : signup(); break;
	case '3' : adminlogin() ; break;
	case '4' : exitscreen(); break;
	default: {
			initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
			settextstyle(0,0,2);
			setbkcolor(3);

			outtextxy(120,200,"Invalid Choice. Try again") ;
			delay(1000);
			closegraph();

			login();
		 }
       }
}

void usermenu()                          //menu for user
{
int gd,gm;
gd=DETECT;
char i;

initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
clearviewport();
settextstyle(0,0,3);
outtextxy((getmaxx()/2-60),30,"Welcome") ;

settextstyle(0,0,1);
setbkcolor(3);

do
{
outtextxy(0,100,"1.Play ");
outtextxy(0,140,"2.Instructions ") ;
outtextxy(0,180,"3.Leaderboard ") ;
outtextxy(0,220,"4.Edit Account ")  ;
outtextxy(0,260,"5.Delete Account ")  ;
outtextxy(0,300,"6.Sign out ")  ;

i=getch();

closegraph();
switch(i)
	{
	case '1' : game(); break;
	case '2' : instructions(); break;
	case '3' : leaderboard(); usermenu(); break;
	case '4' : editaccount(); break;
	case '5' : deleteaccount(); break;
	case '6' : funcwrite();login(); break;
	default: {
			initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");
			settextstyle(0,0,2);
			setbkcolor(3);
			outtextxy(120,200,"Invalid Choice. Try again") ;
			delay(1000);
			closegraph();

			usermenu();
		 }
       }

}while(1);


}


void main()
{
clrscr();
welcome();
login();
}
