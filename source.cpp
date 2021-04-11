#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
int go=0;
char flag,flag1,flag2,flag3;
class player{
public:
	int x,y,life;
	void createPlayer(int a,int b,int lf){
		x=a;
		y=b;
		life=lf;
	}
	void resetPlayer(int checkpoint){
		if(checkpoint==0){
			x=1;
			y=18;
		}
	}
}me;
class enemy{
public:
	int x,y,speed;
	char dir,dim;
	bool alive;
	void createEnemy(int a,int b,char dr,char dm,int sp,bool t){
		x=a;
		y=b;
		dir=dr;
		dim=dm;
		speed=sp;
		alive=t;
	}
}normal[25];
class bullet{
public:
	int x,x1,y,y1,speed,wtime;
	char dir;
	bool alive;
	void createBullet(int a, int b, char dr,int sp,int wt,bool t){
		x=a;
		x1=a;
		y=b;
		y1=b;
		dir=dr;
		speed=sp;
		wtime=wt;
		alive=t;
	}
	void resetBullet(){
		alive=true;
		x=x1;
		y=y1;
	}
}bullet[50];
void createGameWindow(int height, int width){
	_COORD cord;
	cord.X=width;
	cord.Y=height;
	_SMALL_RECT rect;
	rect.Top=0;
	rect.Left=0;
	rect.Bottom=height-1;
	rect.Right=width-1;
	CONSOLE_CURSOR_INFO conf;
	conf.bVisible=false;
	SetConsoleScreenBufferSize(handle,cord);
	SetConsoleWindowInfo(handle,TRUE,&rect);
	SetConsoleCursorInfo(handle,&conf);
}

void SetPos(int x,int y){
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(handle,coord);
}

char getPosChar(){
	char a='\0';
	CONSOLE_SCREEN_BUFFER_INFO buf;
	if(GetConsoleScreenBufferInfo(handle,&buf)){
		DWORD read=0;
		if(!ReadConsoleOutputCharacterA(handle,&a,1,buf.dwCursorPosition,&read)||read!=1) a='\0';
		return a;
	}
}

char ReadChar(int x,int y){
	SetPos(x,y);
	return getPosChar();
}
void printMap(){
	ifstream base("F:\\gbase.txt");
	string line;
	SetConsoleTextAttribute(handle,15);
	if(base.is_open()){
		while(!base.eof()){
			getline(base,line);
			cout<<line<<endl;
		}
	}
	base.close();
}
void loadobjects(){
	SetConsoleTextAttribute(handle,4);
	SetPos(22,16);
	cout<<"-";
	SetPos(43,17);
	cout<<"-";
	SetPos(67,13);
	cout<<"-";
	SetPos(67,14);
	cout<<"-";
	SetPos(67,15);
	cout<<"-";
	SetPos(44,2);
	cout<<"-";
	SetPos(68,2);
	cout<<"-";
	SetPos(31,10);
	cout<<"-";
	SetPos(31,13);
	cout<<"-";
	SetPos(16,14);
	cout<<"|";
	SetConsoleTextAttribute(handle,2);
	SetPos(59,6);
	cout<<"%";
	SetPos(65,8);
	cout<<"%";
	SetPos(63,10);
	cout<<"%";
	SetConsoleTextAttribute(handle,3);
	SetPos(72,2);
	cout<<"+";
	SetPos(6,6);
	cout<<"+";
	SetConsoleTextAttribute(handle,14);
	SetPos(30,16);
	cout<<"E";
}
void GameSetup(){
	me.createPlayer(1,18,2);
	normal[0].createEnemy(12,18,'d','h',15,true);
	normal[1].createEnemy(45,10,'d','h',12,true);
	normal[2].createEnemy(45,8,'a','h',12,true);
	normal[3].createEnemy(45,6,'d','h',12,true);
	normal[4].createEnemy(33,1,'a','h',15,true);
	normal[5].createEnemy(17,6,'a','h',12,true);
	normal[6].createEnemy(17,11,'d','h',12,true);
	normal[7].createEnemy(26,15,'w','v',15,true);
	bullet[0].createBullet(21,16,'a',15,100,true);
	bullet[1].createBullet(44,17,'d',10,100,true);
	bullet[2].createBullet(66,13,'a',1,1,true);
	bullet[3].createBullet(66,14,'a',1,1,true);
	bullet[4].createBullet(66,15,'a',1,1,true);
	bullet[5].createBullet(45,2,'d',12,12,true);
	bullet[6].createBullet(67,2,'a',12,12,true);
	bullet[7].createBullet(16,13,'w',12,12,true);
	bullet[8].createBullet(30,10,'a',12,12,true);
	bullet[9].createBullet(30,13,'a',12,12,true);
	system("CLS");
	printMap();
	loadobjects();
	SetPos(me.x,me.y);
	SetConsoleTextAttribute(handle,7);
	cout<<"@";
}
void GameOver(){
	system("CLS");
	SetPos(31,13);
	SetConsoleTextAttribute(handle,12);
	cout<<"Game Over\n\t\t\t";
}
int objdetect(int gx,int gy,char drs){
	if(ReadChar(gx,gy)=='$'|| ReadChar(gx,gy)=='o') return 2;
	else if((ReadChar(gx+1,gy)=='%' && drs=='d' ) || (ReadChar(gx-1,gy)=='%' && drs=='a') || (ReadChar(gx,gy-1)=='%' && drs=='w') || (ReadChar(gx,gy+1)=='%' && drs=='s')) return 3;
	else if((ReadChar(gx+1,gy)=='#' && drs=='d' ) || (ReadChar(gx-1,gy)=='#' && drs=='a') || (ReadChar(gx,gy-1)=='#' && drs=='w') || (ReadChar(gx,gy+1)=='#' && drs=='s') || (ReadChar(gx+1,gy)=='-' && drs=='d' ) || (ReadChar(gx-1,gy)=='-' && drs=='a') || (ReadChar(gx,gy-1)=='|' && drs=='w') || (ReadChar(gx,gy+1)=='|' && drs=='s') || (ReadChar(gx+1,gy)=='|' && drs=='d' ) || (ReadChar(gx-1,gy)=='|' && drs=='a') || (ReadChar(gx,gy-1)=='-' && drs=='w') || (ReadChar(gx,gy+1)=='-' && drs=='s')) return 1;
	else return 0;
}

void logics(){

	//Normals......

	if(normal[0].x!=70 || normal[0].y!=18) flag='n';
	if(normal[0].x==70 && normal[0].y==18 && flag=='n'){
		flag='y';
		if(normal[0].dim=='h'){
			normal[0].dim='v';
			normal[0].dir='w';
			normal[0].speed=30;
		}
		else if(normal[0].dim=='v'){
			normal[0].dim='h';
			normal[0].dir='a';
			normal[0].speed=15;
		}
	}

	if(normal[4].x!=33 || normal[4].y!=1) flag1='n';
	if(normal[4].x==33 && normal[4].y==1 && flag1=='n'){
		flag1='y';
		if(normal[4].dir=='d') normal[4].dir='a';
	}

	if(normal[4].x!=2 || normal[4].y!=1) flag2='n';
	if(normal[4].x==2 && normal[4].y==1 && flag2=='n'){
		flag2='y';
		if(normal[4].dim=='h'){
			normal[4].dim='v';
			normal[4].dir='s';
			normal[4].speed=30;
		}
		else if(normal[4].dim=='v'){
			normal[4].dim='h';
			normal[4].dir='d';
			normal[4].speed=15;
		}
	}

	if(normal[4].x!=2 || normal[4].y!=3) flag3='n';
	if(normal[4].x==2 && normal[4].y==3 && flag3=='n'){
		flag3='y';
		if(normal[4].dim=='h'){
			normal[4].dim='v';
			normal[4].dir='w';
			normal[4].speed=30;
		}
		else if(normal[4].dim=='v'){
			normal[4].dim='h';
			normal[4].dir='d';
			normal[4].speed=15;
		}
	}

	//Player Logics...........

	if(objdetect(me.x,me.y,'w')==2){
		me.life-=1;
		Sleep(1500);
		SetPos(28,24);
		SetConsoleTextAttribute(handle,5);
	    cout<<"Player Life: "<<me.life;
		me.resetPlayer(0);
		SetPos(me.x,me.y);
		SetConsoleTextAttribute(handle,7);
		cout<<"@";
	}
	if((me.x==72 && me.y==2)||(me.x==6 && me.y==6)){
		me.life+=1;
		SetPos(28,24);
		cout<<"Player Life: "<<me.life;
	}
}

void update(int sf){
	int i;
	for(i=0;i<10;i++){

		//Normal Enemy.......................

		if(normal[i].alive!='\0'){
		if(normal[i].dim=='h'){
			if(ReadChar(normal[i].x+1,normal[i].y)=='#'||ReadChar(normal[i].x+1,normal[i].y)=='%') normal[i].dir='a';
			else if(ReadChar(normal[i].x-1,normal[i].y)=='#'||ReadChar(normal[i].x-1,normal[i].y)=='%') normal[i].dir='d';
			if((sf%normal[i].speed==0) && (normal[i].dir=='d')){
				SetPos(normal[i].x,normal[i].y);
				cout<<" ";
				normal[i].x+=1;
				SetPos(normal[i].x,normal[i].y);
				SetConsoleTextAttribute(handle,11);
				cout<<"$";
			}
			if((sf%normal[i].speed==0) && (normal[i].dir=='a')){
				SetPos(normal[i].x,normal[i].y);
				cout<<" ";
				normal[i].x-=1;
				SetPos(normal[i].x,normal[i].y);
				SetConsoleTextAttribute(handle,11);
				cout<<"$";
			}
		}
		if(normal[i].dim=='v'){
			if(ReadChar(normal[i].x,normal[i].y+1)=='#'||ReadChar(normal[i].x,normal[i].y+1)=='%') normal[i].dir='w';
			else if(ReadChar(normal[i].x,normal[i].y-1)=='#'||ReadChar(normal[i].x,normal[i].y-1)=='%') normal[i].dir='s';
			if((sf%normal[i].speed==0) && (normal[i].dir=='s')){
				SetPos(normal[i].x,normal[i].y);
				cout<<" ";
				normal[i].y+=1;
				SetPos(normal[i].x,normal[i].y);
				SetConsoleTextAttribute(handle,11);
				cout<<"$";
			}
			if((sf%normal[i].speed==0) && (normal[i].dir=='w')){
				SetPos(normal[i].x,normal[i].y);
				cout<<" ";
				normal[i].y-=1;
				SetPos(normal[i].x,normal[i].y);
				SetConsoleTextAttribute(handle,11);
				cout<<"$";
			}
		}
		}

		//Shooter.........

		if(bullet[i].wtime!='\0'){
		if(bullet[i].alive==false){
			if(sf%bullet[i].wtime==0) bullet[i].resetBullet();
		}
		if(bullet[i].alive==true){
			if(sf%bullet[i].speed==0){
				if(bullet[i].dir=='d'){
					if(ReadChar(bullet[i].x+1,bullet[i].y)=='#'||ReadChar(bullet[i].x+1,bullet[i].y)=='%'){
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].alive=false;
					}
					else{
					SetPos(bullet[i].x,bullet[i].y);
					cout<<" ";
					bullet[i].x+=1;
					SetPos(bullet[i].x,bullet[i].y);
					SetConsoleTextAttribute(handle,4);
					cout<<"o";
					}
				}
				if(bullet[i].dir=='a'){
					if(ReadChar(bullet[i].x-1,bullet[i].y)=='#'||ReadChar(bullet[i].x-1,bullet[i].y)=='%'){
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].alive=false;
					}
					else{
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].x-=1;
						SetPos(bullet[i].x,bullet[i].y);
						SetConsoleTextAttribute(handle,4);
						cout<<"o";
					}
				}
				if(bullet[i].dir=='w'){
					if(ReadChar(bullet[i].x,bullet[i].y-1)=='#'||ReadChar(bullet[i].x,bullet[i].y-1)=='%'){
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].alive=false;
					}
					else{
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].y-=1;
						SetPos(bullet[i].x,bullet[i].y);
						SetConsoleTextAttribute(handle,4);
						cout<<"o";
					}
				}
				if(bullet[i].dir=='s'){
					if(ReadChar(bullet[i].x,bullet[i].y+1)=='#'||ReadChar(bullet[i].x,bullet[i].y+1)=='%'){
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].alive=false;
					}
					else{
						SetPos(bullet[i].x,bullet[i].y);
						cout<<" ";
						bullet[i].y+=1;
						SetPos(bullet[i].x,bullet[i].y);
						SetConsoleTextAttribute(handle,4);
						cout<<"o";
					}
				}
			}
		}
		}
	}
}
void moveMe(int x,int y,int sg){
	if(sg%15==0){
		if(GetKeyState('W')<0 && objdetect(me.x,me.y,'w')==0){SetPos(me.x,me.y); cout<<" "; me.y-=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@";}
		if(GetKeyState('S')<0 && objdetect(me.x,me.y,'s')==0){SetPos(me.x,me.y); cout<<" "; me.y+=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@";}
		if(GetKeyState('A')<0 && objdetect(me.x,me.y,'a')==0){SetPos(me.x,me.y); cout<<" "; me.x-=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@";}
		if(GetKeyState('D')<0 && objdetect(me.x,me.y,'d')==0){SetPos(me.x,me.y); cout<<" "; me.x+=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@";}
		if(GetKeyState('W')<0 && objdetect(me.x,me.y,'w')==3){if(objdetect(me.x,me.y-1,'w')==0){SetPos(me.x,me.y); cout<<" "; me.y-=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@"; SetPos(me.x,me.y-1); SetConsoleTextAttribute(handle,2); cout<<"%";}}
		if(GetKeyState('S')<0 && objdetect(me.x,me.y,'s')==3){if(objdetect(me.x,me.y+1,'s')==0){SetPos(me.x,me.y); cout<<" "; me.y+=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@"; SetPos(me.x,me.y+1); SetConsoleTextAttribute(handle,2); cout<<"%";}}
		if(GetKeyState('A')<0 && objdetect(me.x,me.y,'a')==3){if(objdetect(me.x-1,me.y,'a')==0){SetPos(me.x,me.y); cout<<" "; me.x-=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@"; SetPos(me.x-1,me.y); SetConsoleTextAttribute(handle,2); cout<<"%";}}
		if(GetKeyState('D')<0 && objdetect(me.x,me.y,'d')==3){if(objdetect(me.x+1,me.y,'d')==0){SetPos(me.x,me.y); cout<<" "; me.x+=1; SetPos(me.x,me.y); SetConsoleTextAttribute(handle,7); cout<<"@"; SetPos(me.x+1,me.y); SetConsoleTextAttribute(handle,2); cout<<"%";}}
	}
}
void drawLegends(){
	SetPos(0,20);
	SetConsoleTextAttribute(handle,1);
	cout<<"---------------------------------------------------------------------------";
	SetPos(26,21);
	SetConsoleTextAttribute(handle,5);
	cout<<"\"w,a,s,d\" to move";
	SetPos(28,22);
	cout<<"Player Life: "<<me.life;
	SetPos(2,23);
	cout<<"\'%\' are movable objects you can push them to block bullets and enemies.";
	SetPos(14,24);
	cout<<"\'+\' are lifes, get them to increase your life.";
	SetPos(22,25);
	cout<<"Get to \'E\' to complete the game.";
}

int main(){
	int height=27,width=76,n=1;
	createGameWindow(height,width);
	system("echo off");
	system("CLS");
	SetPos(34,12);
	SetConsoleTextAttribute(handle,14);
	cout<<"?Start?";
	getchar();
	GameSetup();
	drawLegends();
	while(true){
	logics();
	update(n);
	moveMe(me.x,me.y,n);
	n++;
	if(n==20000) n=1;
	Sleep(1);
	if(me.life==0) {GameOver(); break;}
	if(me.x==30 && me.y==16){
		system("CLS");
		SetPos(31,13);
		cout<<"You Win!!!\n\t\t\t";
		break;
	}
	}
	return 0;
}
