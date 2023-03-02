//====================:========================================================
// Group Member 1:     Muhammad Aqeel Afzal
// Roll Number:        i190650
// 
// Group Member 2:     Maria Hassan
// Roll Number:        i190478
//============================================================================


#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include <pthread.h>
#include <semaphore.h>
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> 
#include<cstdlib>
#include<ctime>
#include<unistd.h>
#include<fstream>
using namespace std;

// Diffrent Functions
void turn(int n);
void Turn_Decider(int x);			   //Decides the turn rundomly
void Red_Tokan_move(int z);				  //For movement of RED Tokans
void Blue_Tokan_move(int z);			         //For movement of Blue Tokans
void Yellow_Tokan_move(int z);			 //For movement of yellow Tokans
void Green_Tokan_move(int z);			//For movement of Green Tokans
void Kill_Fun(int u);				 // killing the opponants
void Dice_Fun();				        // Dice Rolling 
void won();				      	//Winnig 
void update_score();				//update the scoreds

//Tokan win bools
bool Red1_Wins=false, Red2_Wins=false, Red3_Wins=false, Red4_Wins=false;
bool Blue1_Wins=false, Blue2_Wins=false, Blue3_Wins=false, Blue4_Wins=false;
bool Yellow1_Wins=false, Yellow2_Wins=false, Yellow3_Wins=false, Yellow4_Wins=false;
bool Green1_Wins=false, Green2_Wins=false, Green3_Wins=false, Green4_Wins=false;
bool r_won = false, b_won = false, g_won = false, y_won = false;

//hitting condition for entering in to home
bool red_lock=true, blue_lock=true, yellow_lock=true, green_lock=true;
sem_t Dice_Roll;
sem_t Board;


//Menu variables
int screen=0,temp=0;

//thread cancelation variables
bool active1=false,active2=false,active3=false,active4=false;
int hit_player1[2],hit_player2[20],hit_player3[20],hit_player4[20];
int index1=0,index2=0,index3=0,index4=0;


//Positions Of tokans
bool grid_var=false;    //sharable variable

//axis of tokans
	int dice_value=0;
	int Red_Tokan[4][2] = { {200,200},{400,200},{200,400},{400,400}};
	int Blue_Tokan[4][2] = { {1100,200},{1300,200},{1100,400},{1300,400}};
	int Green_Tokan[4][2] = { {200,1100},{400,1100},{200,1300},{400,1300}};
	int Yellow_Tokan[4][2] = { {1100,1100},{1300,1100},{1100,1300},{1300,1300}};
	
	int red_init[4][2] = { {200,200},{400,200},{200,400},{400,400}};
	int blue_init[4][2] = { {1100,200},{1300,200},{1100,400},{1300,400}};
	int green_init[4][2] = { {200,1100},{400,1100},{200,1300},{400,1300}};
	int yellow_init[4][2] = { {1100,1100},{1300,1100},{1100,1300},{1300,1300}};


int six_count1=0,six_count2=0,six_count3=0,six_count4=0;

//Turn Decider
int t,turn_count=0;
bool t_lock = false;

//Home Position
int rhx = 650, rhy= 150, bhx = 1350, bhy = 650, yhx = 850 , yhy = 1350 , ghx = 150 , ghy = 850;

//Safe Position
int rsx = 850, rsy= 250, bsx = 1250, bsy = 850, ysx = 650 , ysy = 1250 , gsx = 250 , gsy = 650;

//Safe Position2
//int rsx1 = 850, rsy1= 250, bsx1 = 1250, bsy1 = 850, ysx1 = 650 , ysy1 = 1250 , gsx1 = 250 , gsy1 = 650;

//Won Position
int rwx = 750, rwy= 650, bwx = 850, bwy = 750, ywx = 750 , ywy = 850 , gwx = 650 , gwy = 750;

//Checking if Spacebar Pressed
bool dicee=false;

//Scores
int red_score = 0, blue_score = 0, green_score = 0, yellow_score = 0;
bool rh_lock=false, bh_lock=false, gh_lock=false, yh_lock=false;

//Won
int red_wins = 0, blue_wins = 0, green_wins = 0, yellow_wins = 0;

//Name of Players
string name1, name2, name3, name4;
bool n1=false, n2=false, n3=false, n4=false;
bool enter=false;
char ch;

//Extras
int r[4]={5,5,5,5}, b[4]={5,5,5,5}, g[4]={5,5,5,5}, y[4]={5,5,5,5}, h=0, j=0, k=0, l=0, c=0, d=0, rd, bd, gd, yd;


void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); 
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void Turn_Decider(int x){
cout<<"Turn_Decider call "<<endl;
turn_count=0;
	if(x==3){

	t = rand()%4+1;

	}
	
	else if(x==2){
	
	t = rand()%3+1;
	
	}
	
	else if(x==1){
	
	t = rand()%2+1;

	}

}

void Dice_Fun(){


	//srand(time(0));
	int n= dice_value;    //rand()%6+1;
	int adition1=0,adition2=0;
	DrawString(1000, 1550, to_string(n) , colors[BLACK]);

	if(n==1){
			DrawCircle(1000,1750,10,colors[WHITE]);		//Drawing One Dots

	}
	
	else if(n==2){
	    adition1=0;

			for(int i=0;i<n;i++,adition1+=50)
			DrawCircle(980+adition1,1750,10,colors[WHITE]);		//Drawing Two Dots
			

	}
	
	else if(n==3){
			 
			adition1=0;
			for(int i=0;i<n;i++,adition1+=50)
			{
				DrawCircle(1000,1700+adition1,10,colors[WHITE]);		//Drawing Three Dots
			}
				

	}

	else if(n==4){
	 adition1=0;
			for(int i=0;i<n-2;i++,adition1+=50)
			DrawCircle(980,1717+adition1,10,colors[WHITE]);		//Drawing Four Dots
			
 adition1=0;
			for(int i=0;i<n-2;i++,adition1+=50)
			DrawCircle(1030,1717+adition1,10,colors[WHITE]);
			

	}

	else if(n==5){
	
                        
			
                                  
		        DrawCircle(980,1700,10,colors[WHITE]);		//Drawing Five Dots	
			DrawCircle(980,1750,10,colors[WHITE]);
			DrawCircle(1030,1700,10,colors[WHITE]);
			DrawCircle(1030,1750,10,colors[WHITE]);
			DrawCircle(1005,1800,10,colors[WHITE]);
	

	}
	
	else if(n==6){
			adition2=0;
			adition1=0;
			for(int i=0;i<n;i++)
			{
				if(i%2==0)
				{
				DrawCircle(980,1700+adition2,10,colors[WHITE]);		//Drawing Six Dots
				
				adition2+=50;

                                }
				else
				{
                                
                                DrawCircle(1030,1700+adition1,10,colors[WHITE]);
				adition1+=50;
				}

			}
			

			}
			
		dice_value=n;	


	}
string mode_strs[4]={"Press O For Two Players Mode","Press T For Three Players Mode","Press F For Four Players Mode","Press H For High Scores"};
int y_axis=0;
void NameDisplay1()
{
DrawString(780,1250,"Enter Name of Player 1",colors[BLACK]);
		DrawRoundRect(780,1075,405,105,colors[BLACK],20);
		DrawString(830,1100,name1,colors[WHITE]);
}
void NameDisplay2()
{
		NameDisplay1();
		DrawString(780,950,"Enter Name of Player 2",colors[BLACK]);
		DrawRoundRect(780,770,410,105,colors[BLACK],20);
		DrawString(830,800,name2,colors[WHITE]);
}
void NameDisplay3()
{
		NameDisplay1();
		NameDisplay2();
		DrawString(780,650,"Enter Name of Player 3",colors[BLACK]);
		DrawRoundRect(780,470,410,105,colors[BLACK],20);
		DrawString(830,500,name3,colors[WHITE]);
}
void NameDisplay4()
{

		NameDisplay1();
		NameDisplay2();
		NameDisplay3();
		DrawString(780,350,"Enter Name of Player 4",colors[BLACK]);
		DrawRoundRect(780,170,410,105,colors[BLACK],20);
		DrawString(830,200,name4,colors[WHITE]);
}
void LineDisplay()
{
DrawLine( 0 , 1500 , 2000, 1500 , 40 ,colors[BLACK] );
	DrawLine( 0 , 2000 , 2000, 2000 , 40 ,colors[BLACK] );

	DrawLine( 0 , 0 , 2000, 0 , 40 ,colors[BLACK] );
	
	DrawLine( 0, 0 ,0, 2000, 40 ,colors[BLACK] );
	DrawLine( 500 , 0 , 500, 2000 , 40 ,colors[BLACK] );
	DrawLine( 1500, 0 ,1500, 2000, 40 ,colors[BLACK] );
	DrawLine( 2000 , 0 , 2000, 2000 , 40 ,colors[BLACK] );
}
void grid()
{

//Centre
	DrawTriangle( 600, 600 , 600, 900 , 750 , 750, colors[LAWN_GREEN] ); 
	DrawTriangle( 600, 600 , 900, 600 , 750 , 750, colors[RED] ); 
	DrawTriangle( 900, 600 , 900, 900 , 750 , 750, colors[BLUE] ); 
	DrawTriangle( 600, 900 , 900, 900 , 750 , 750, colors[OLIVE] ); 
	
	
	//4 Colour Sides
	DrawSquare( 0 ,     0 ,600,colors[RED]); 
	DrawSquare( 0 ,   900 ,600,colors[LAWN_GREEN]); 
	DrawSquare( 900 ,   0 ,600,colors[BLUE]); 
	DrawSquare( 900 , 900 ,600,colors[OLIVE]); 
	
	//4 Colour Sides Internal Squares
	DrawSquare( 100 ,   100 ,400,colors[WHITE]); 
	DrawSquare( 100 ,  1000 ,400,colors[WHITE]); 
	DrawSquare( 1000 ,  100 ,400,colors[WHITE]); 
	DrawSquare( 1000 , 1000 ,400,colors[WHITE]); 
	
	//Display Score
	DrawString( 50, 800, "Score=0", colors[BLACK]);
	
	// Green Moving Area

	DrawSquare(   0 , 600 ,100,colors[WHITE]); 
	DrawSquare(   0 , 700 ,100,colors[WHITE]); 
	DrawSquare(   0 , 800 ,100,colors[WHITE]); 

	DrawSquare( 100 , 600 ,100,colors[WHITE]); 
	DrawSquare( 100 , 700 ,100,colors[LAWN_GREEN]); 
	DrawSquare( 100 , 800 ,100,colors[LAWN_GREEN]);
 
	DrawSquare( 200 , 600 ,100,colors[LAWN_GREEN]); 
	DrawSquare( 200 , 700 ,100,colors[LAWN_GREEN]); 
	DrawSquare( 200 , 800 ,100,colors[WHITE]); 
for(int i=300;i<=500;i+=100)
{
        DrawSquare( i , 600 ,100,colors[WHITE]); 
	DrawSquare( i, 700 ,100,colors[LAWN_GREEN]); 
	DrawSquare( i, 800 ,100,colors[WHITE]);
}
	
	// RED Moving Area
	DrawSquare( 600 ,   0 ,100,colors[WHITE]); 
	DrawSquare( 700 ,   0 ,100,colors[WHITE]); 
	DrawSquare( 800 ,   0 ,100,colors[WHITE]); 
	DrawSquare( 600 , 100 ,100,colors[RED]); 
	DrawSquare( 700 , 100 ,100,colors[RED]); 
	DrawSquare( 800 , 100 ,100,colors[WHITE]); 

	DrawSquare( 600 , 200 ,100,colors[WHITE]); 
	DrawSquare( 700 , 200 ,100,colors[RED]); 
	DrawSquare( 800 , 200 ,100,colors[RED]); 
for(int i=300;i<=500;i+=100)
	{
	DrawSquare( 600 , i ,100,colors[WHITE]); 
	DrawSquare( 700 , i ,100,colors[RED]); 
	DrawSquare( 800 , i ,100,colors[WHITE]);
 }
	
	// Yellow Moving Area
	DrawSquare( 600 , 900 ,100,colors[WHITE]); 
	DrawSquare( 700 , 900 ,100,colors[OLIVE]); 
	DrawSquare( 800 , 900 ,100,colors[WHITE]); 
	DrawSquare( 600 , 1000 ,100,colors[WHITE]); 
	DrawSquare( 700 , 1000 ,100,colors[OLIVE]); 
	DrawSquare( 800 , 1000 ,100,colors[WHITE]); 
	DrawSquare( 600 , 1100 ,100,colors[WHITE]); 
	DrawSquare( 700 , 1100 ,100,colors[OLIVE]); 
	DrawSquare( 800 , 1100 ,100,colors[WHITE]); 
	DrawSquare( 600 , 1200 ,100,colors[OLIVE]); 
	DrawSquare( 700 , 1200 ,100,colors[OLIVE]); 
	DrawSquare( 800 , 1200 ,100,colors[WHITE]); 
	DrawSquare( 600 , 1300 ,100,colors[WHITE]); 
	DrawSquare( 700 , 1300 ,100,colors[OLIVE]); 
	DrawSquare( 800 , 1300 ,100,colors[OLIVE]); 
	DrawSquare( 600 , 1400 ,100,colors[WHITE]); 
	DrawSquare( 700 , 1400 ,100,colors[WHITE]); 
	DrawSquare( 800 , 1400 ,100,colors[WHITE]); 
	
	// Blue Moving Area
	DrawSquare( 900 , 600 ,100,colors[WHITE]); 
	DrawSquare( 900 , 700 ,100,colors[BLUE]); 
	DrawSquare( 900 , 800 ,100,colors[WHITE]); 
	DrawSquare( 1000 , 600 ,100,colors[WHITE]); 
	DrawSquare( 1000 , 700 ,100,colors[BLUE]); 
	DrawSquare( 1000 , 800 ,100,colors[WHITE]); 
	DrawSquare( 1100 , 600 ,100,colors[WHITE]); 
	DrawSquare( 1100, 700 ,100,colors[BLUE]); 
	DrawSquare( 1100 , 800 ,100,colors[WHITE]); 
	DrawSquare( 1200 , 600 ,100,colors[WHITE]); 
	DrawSquare( 1200 , 700 ,100,colors[BLUE]); 
	DrawSquare( 1200 , 800 ,100,colors[BLUE]); 
	DrawSquare( 1300 , 600 ,100,colors[BLUE]); 
	DrawSquare( 1300 , 700 ,100,colors[BLUE]); 
	DrawSquare( 1300 , 800 ,100,colors[WHITE]); 
	DrawSquare( 1400 , 600 ,100,colors[WHITE]); 
	DrawSquare( 1400 , 700 ,100,colors[WHITE]); 
	DrawSquare( 1400 , 800 ,100,colors[WHITE]); 
}
string str1[4]={"1","2","3","4"};
void Mode2_Tokans()
{
//RED Gottis
cout<<"index1-------------------------------->"<<index1<<endl;
if(screen==2&&index1==20)
	{

for(int i=0;i<4;i++)
	DrawCircle(Yellow_Tokan[i][0],Yellow_Tokan[i][1],40,colors[ORANGE_RED]);
	
	for(int i=0;i<4;i++)
	DrawString(Yellow_Tokan[i][0]-2,Yellow_Tokan[i][1]-10,str1[i],colors[WHITE]);
	
	//BLUE Gottis
	for(int i=0;i<4;i++)
	DrawCircle(Blue_Tokan[i][0],Blue_Tokan[i][1],40,colors[DEEP_SKY_BLUE]);
	
	for(int i=0;i<4;i++)
	DrawString(Blue_Tokan[i][0]-2,Blue_Tokan[i][1]-10,str1[i],colors[WHITE]);
	}



else if(screen==2&&index2==20)
	{for(int i=0;i<4;i++)
	DrawCircle(Yellow_Tokan[i][0],Yellow_Tokan[i][1],40,colors[ORANGE_RED]);
	
	for(int i=0;i<4;i++)
	DrawString(Yellow_Tokan[i][0]-2,Yellow_Tokan[i][1]-10,str1[i],colors[WHITE]);
	
	//BLUE Gottis
	for(int i=0;i<4;i++)
	DrawCircle(Red_Tokan[i][0],Red_Tokan[i][1],40,colors[RED]);
	
	for(int i=0;i<4;i++)
	DrawString(Red_Tokan[i][0]-2,Red_Tokan[i][1]-10,str1[i],colors[WHITE]);
	}

else if(screen==2&&index3==20)
	{for(int i=0;i<4;i++)
	DrawCircle(Blue_Tokan[i][0],Blue_Tokan[i][1],40,colors[DEEP_SKY_BLUE]);
	
	for(int i=0;i<4;i++)
	DrawString(Blue_Tokan[i][0]-2,Blue_Tokan[i][1]-10,str1[i],colors[WHITE]);
	
	//BLUE Gottis
	for(int i=0;i<4;i++)
	DrawCircle(Red_Tokan[i][0],Red_Tokan[i][1],40,colors[RED]);
	
	for(int i=0;i<4;i++)
	DrawString(Red_Tokan[i][0]-2,Red_Tokan[i][1]-10,str1[i],colors[WHITE]);
	}
else
{
for(int i=0;i<4;i++)
	DrawCircle(Yellow_Tokan[i][0],Yellow_Tokan[i][1],40,colors[ORANGE_RED]);
	
	for(int i=0;i<4;i++)
	DrawString(Yellow_Tokan[i][0]-2,Yellow_Tokan[i][1]-10,str1[i],colors[WHITE]);
	
	//BLUE Gottis
	for(int i=0;i<4;i++)
	DrawCircle(Blue_Tokan[i][0],Blue_Tokan[i][1],40,colors[DEEP_SKY_BLUE]);
	
	for(int i=0;i<4;i++)
	DrawString(Blue_Tokan[i][0]-2,Blue_Tokan[i][1]-10,str1[i],colors[WHITE]);
for(int i=0;i<4;i++)
   DrawCircle(Red_Tokan[i][0],Red_Tokan[i][1],40,colors[RED]);
	
	for(int i=0;i<4;i++)
	DrawString(Red_Tokan[i][0]-2,Red_Tokan[i][1]-10,str1[i],colors[WHITE]);



}


}
void Mode3_Tokans()
{
Mode2_Tokans();
{
for(int i=0;i<4;i++)
   DrawCircle(Green_Tokan[i][0],Green_Tokan[i][1],40,colors[GREEN]);
	
	for(int i=0;i<4;i++)
	DrawString(Green_Tokan[i][0]-2,Green_Tokan[i][1]-10,str1[i],colors[WHITE]);


}
	
	
}
void Mode4_Tokans()
{
Mode3_Tokans();
//YELLOW Gottis
	for(int i=0;i<4;i++)
	DrawCircle(Red_Tokan[i][0],Red_Tokan[i][1],40,colors[FIREBRICK]);
	
	for(int i=0;i<4;i++)
	DrawString(Red_Tokan[i][0]-2,Red_Tokan[i][1]-10,str1[i],colors[WHITE]);	

}

void Lines()
{
	
	//Lines
	for(int i=0,j=600,k=1500;i<3;i++,j+=100,k=600)
	DrawLine( 0 , j , k, j , 2 ,colors[BLACK] );
	DrawLine( 900 , 700 , 1500, 700 , 2 ,colors[BLACK] );
	DrawLine( 900 , 800 , 1500, 800 , 2 ,colors[BLACK] );
	DrawLine( 0 , 900 , 1500, 900 , 2 ,colors[BLACK] );
	DrawLine( 600 , 0 , 600, 1500 , 2 ,colors[BLACK] );
	DrawLine( 700 , 0 , 700, 600 , 2 ,colors[BLACK] );
	DrawLine( 800 , 0 , 800, 600 , 2 ,colors[BLACK] );
	DrawLine( 700 , 900 , 700, 1500 , 2 ,colors[BLACK] );
	DrawLine( 800 , 900 , 800, 1500 , 2 ,colors[BLACK] );
	DrawLine( 900 , 0 , 900, 1500 , 2 ,colors[BLACK] );
	
	for(int i=0,j=0;i<7;i++,j+=100)
	DrawLine( j   , 600 , j  , 900 , 2 ,colors[BLACK] );	
	for(int i=0,j=900;i<7;i++,j+=100)
	DrawLine( j   , 600 , j  , 900 , 2 ,colors[BLACK] );

	for(int i=0,j=0;i<7;i++,j+=100)
	DrawLine( 600   , j , 900  , j , 2 ,colors[BLACK] );
	for(int i=0,j=1000;i<6;i++,j+=100)
	DrawLine( 600   , j , 900  , j , 2 ,colors[BLACK] );

	DrawLine( 600 , 600 , 900, 600 , 2 ,colors[BLACK] );
	DrawLine( 600 , 900 , 900, 900 , 2 ,colors[BLACK] );
	DrawLine( 600 , 600 , 600, 900 , 2 ,colors[BLACK] );
	DrawLine( 900 , 600 , 900, 900 , 2 ,colors[BLACK] );

	DrawLine( 0 , 1500 , 2000, 1500 , 40 ,colors[ORANGE_RED] );
	DrawLine( 0 , 2000 , 2000, 2000 , 40 ,colors[BLACK] );
	DrawLine( 1500 , 0 , 1500, 2000 , 40 ,colors[DEEP_SKY_BLUE] );
	
	DrawLine( 600 , 600 , 900, 900 , 2 ,colors[BLACK] );
	DrawLine( 600 , 900 , 900, 600 , 2 ,colors[BLACK] );
	
	DrawLine( 900 , 3 , 1500, 3 , 40 ,colors[DEEP_SKY_BLUE] );
	DrawLine( 900 , 0 , 900, 600 , 40 ,colors[DEEP_SKY_BLUE] );
	DrawLine( 900 , 600 , 1500, 600 , 40 ,colors[DEEP_SKY_BLUE] );
	DrawLine( 1500 , 0 , 1500, 600 , 40 ,colors[DEEP_SKY_BLUE] );
	
	DrawLine( 1000 , 100 , 1400, 100, 40 ,colors[DEEP_SKY_BLUE] );
	DrawLine( 1000 , 100 , 1000, 500 , 40 ,colors[DEEP_SKY_BLUE] );
	DrawLine( 1000 , 500 , 1400, 500 , 40 ,colors[DEEP_SKY_BLUE] );
	DrawLine( 1400 , 100 , 1400, 500 , 40 ,colors[DEEP_SKY_BLUE] );
	
	DrawLine( 0 , 3 , 600, 3 , 40 ,colors[FIREBRICK] );
	DrawLine( 3 , 0, 3, 600 , 40 ,colors[FIREBRICK] );
	DrawLine( 0 , 600 , 600, 600 , 40 ,colors[FIREBRICK] );
	DrawLine( 600 , 0 , 600, 600 , 40 ,colors[FIREBRICK] );
	
	DrawLine( 100 , 100 , 500, 100 , 40 ,colors[FIREBRICK] );
	DrawLine( 100 , 100, 100, 500 , 40 ,colors[FIREBRICK] );
	DrawLine( 100 , 500 , 500, 500 , 40 ,colors[FIREBRICK] );
	DrawLine( 500 , 100 , 500, 500 , 40 ,colors[FIREBRICK] );
	
	DrawLine( 900 , 900 , 1500, 900 , 40 ,colors[ORANGE_RED] );
	DrawLine( 900 , 900 , 900, 1500 , 40 ,colors[ORANGE_RED] );
	DrawLine( 900 , 1500 , 1500, 1500 , 40 ,colors[ORANGE_RED] );
	DrawLine( 1500 , 900 , 1500, 1500 , 40 ,colors[ORANGE_RED] );
	
	DrawLine( 1000 , 1000 , 1400, 1000 , 40 ,colors[ORANGE_RED] );
	DrawLine( 1000 , 1000 , 1000, 1400 , 40 ,colors[ORANGE_RED] );
	DrawLine( 1000 , 1400 , 1400, 1400 , 40 ,colors[ORANGE_RED] );
	DrawLine( 1400 , 1000 , 1400, 1400 , 40 ,colors[ORANGE_RED] );

	DrawLine( 0 , 900 , 600, 900 , 40 ,colors[GREEN] );
	DrawLine( 3 , 900 , 3, 1500 , 40 ,colors[GREEN] );
	DrawLine( 0 , 1500 , 600, 1500 , 40 ,colors[GREEN] );
	DrawLine( 600 , 900 , 600, 1500 , 40 ,colors[GREEN] );
	
	DrawLine( 100 , 1000 , 500, 1000 , 40 ,colors[GREEN] );
	DrawLine( 100 , 1000 , 100, 1400 , 40 ,colors[GREEN] );
	DrawLine( 100 , 1400 , 500, 1400 , 40 ,colors[GREEN] );
	DrawLine( 500 , 1000 , 500, 1400 , 40 ,colors[GREEN] );
	
	DrawLine( 500 , 1500 , 500, 2000 , 40 ,colors[BLACK] );
	DrawLine( 1500 , 1500 , 1500, 2000 , 40 ,colors[BLACK] );
	DrawLine( 1500 , 1500 , 2000, 1500 , 40 ,colors[BLACK] );
	
	DrawString(1705, 1900, "Scores", colors [BLACK]); 
	DrawString(1550, 1700, "Blue: ", colors [BLACK]); 	
	DrawString(1800, 1700, "Red: ", colors [BLACK]); 
	
	DrawString(1650, 1700, to_string(blue_score), colors [BLACK]); 	
	DrawString(1900, 1700, to_string(red_score), colors [BLACK]); 
	
	
	DrawString(160, 1900, "Gottis Finished", colors [BLACK]); 
	DrawString(50, 1700, "Blue: ", colors [BLACK]); 
	DrawString(300, 1700, "Red: ", colors [BLACK]); 
 
	
	DrawString(150, 1700, to_string(blue_wins), colors [BLACK]);  	
	DrawString(400, 1700, to_string(red_wins), colors [BLACK]); 
	
	DrawString(1700, 1400, "4 Players", colors [BLACK]); 
	DrawString(1600, 1200, "Spacebar For Roll Dice", colors [BLACK]); 
	DrawString(1620, 1100, "Press 1,2,3,4 to Move ", colors [BLACK]); 
		
	DrawString(920, 1900, "Turn : ", colors [BLACK]); 
	
}

void GameDisplay(){

		glClearColor(.7, .5,1, 0 ); 
		glClear (GL_COLOR_BUFFER_BIT);
cout<<"screen in display "<<screen<<endl;
	
	if(screen == 0){	  // ------> Menu
	
		
	glClear (GL_COLOR_BUFFER_BIT); 
	
	int a=600, b=850;
//200,1100

int ab=600;

DrawCircle(910,990,500,colors[BLACK]);
		for(int i=0;i<5;i++)
		{
			
			Torus2d(900+25,1000+25,0+ab,200,450,150,5,colors[MAROON]);
			ab=ab+100;
                        Torus2d(1000,1000,0+ab,200,850,150,5,colors[MAROON]);
			ab=ab+100;
		}
	
	
	

	
	
	//Menu Options
        for(int i=0;i<4;i++,y_axis=y_axis+200)
	DrawString(670,700+y_axis,mode_strs[i],colors[WHITE]);
y_axis=0;
	

	}
	
	
	
	
	
	
	else if(screen==7){
	
	if(n1==true){
	
		NameDisplay1();
		
	}
	
	if(n2==true){
		
		NameDisplay2();

	}
	
	}
	
	else if(screen==8){
	LineDisplay();
	
	if(n1==true)
		NameDisplay1();
	if(n2==true)
		NameDisplay2();
	if(n3==true)
		NameDisplay3();
	}
	
	else if(screen==9){
	if(n1==true)
		NameDisplay1();
	if(n2==true)
		NameDisplay2();
	if(n3==true)
		NameDisplay3();
	if(n4==true)
		NameDisplay4();
	
	}

		 
	else if(screen ==1 ){       // -----> 2 Players
	
	if(t_lock==false){
		Turn_Decider(screen);
		t_lock = true;
	
	}
grid();
Mode2_Tokans();
Lines();
	DrawString(250,530,name1,colors[BLACK]);
	DrawString(1150,530,name2,colors[BLACK]);

	if(t==1)
		DrawString(1000, 1900, "BLUE", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "RED", colors [BLACK]); 

	
	DrawRoundRect(900,1650,200,200,colors[BLACK]);
	

	if(red_wins==4){


		 DrawString(200, 300, "RED has Won!!!", colors [BLACK]); 
		 DrawString(1100, 300, "BLUE has LOST!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
	}
	
	if(blue_wins==4){

	
		 DrawString(1100, 300, "BLUE has Won!!!", colors [BLACK]); 
		 DrawString(200, 300, "RED has Lost!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
	}


	

	Dice_Fun();
	
						
	}	
	
	else if(screen == 2 ){         // -----> 3 Players
	
	
		if(t_lock==false){
		Turn_Decider(screen);
		t_lock = true;
	
	}
	
	//cout<<"3 playes are playing>>>>>>>>>>>>>>>>>>>>>>"<<endl;
grid();

	Mode3_Tokans();
Lines();
	DrawString(250,530,name1,colors[BLACK]);
	DrawString(1150,530,name2,colors[BLACK]);
	DrawString(1150,1430,name3,colors[BLACK]);
        cout<<"turn scrren "<<t<<endl;
		
	DrawString(920, 1900, "Turn : ", colors [BLACK]); 
cout<<"index1  "<<index1<<endl;
        if(index1==20)
	{if(t==1)
		DrawString(1000, 1900, "BLUE", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "YELLOW", colors [BLACK]); 
	if(t==3)
		DrawString(1000, 1900, "GREEN", colors [BLACK]); 
	}

      else if(index2==20)
	{if(t==1)
		DrawString(1000, 1900, "RED", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "YELLOW", colors [BLACK]); 
	if(t==3)
		DrawString(1000, 1900, "GREEN", colors [BLACK]); 
	}
else if(index3==20)
	{if(t==1)
		DrawString(1000, 1900, "RED", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "BLUE", colors [BLACK]); 
	if(t==3)
		DrawString(1000, 1900, "GREEN", colors [BLACK]); 
	}
else if(index4==20)
	{if(t==1)
		DrawString(1000, 1900, "RED", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "YELLOW", colors [BLACK]); 
	if(t==3)
		DrawString(1000, 1900, "GREEN", colors [BLACK]); 
	}
        else
	{
	if(t==1)
		DrawString(1000, 1900, "BLUE", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "YELLOW", colors [BLACK]); 
	if(t==3)
		DrawString(1000, 1900, "RED", colors [BLACK]);


	}

	DrawRoundRect(900,1650,200,200,colors[BLACK]);
	
	if(red_wins==4){
		if(r_won == false){
			d++;
			rd=d;}
			
		if(rd==1)
		 DrawString(200, 300, "RED Has Finished 1st!!!", colors [BLACK]); 
		else if(rd==2){
		 DrawString(200, 300, "RED Has Finished 2nd!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
}
		 r_won = true;
	}
	
	if(blue_wins==4){
		if(b_won == false){
			d++;
			bd=d;}
	
		if(bd==1)
		 DrawString(1050, 300, "BLUE Has Finished 1st!!!", colors [BLACK]); 
		else if(bd==2){
		 DrawString(1050, 300, "BLUE Has Finished 2nd!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]); 
		 update_score();
}
		 b_won = true;
	}
	
	if(yellow_wins==4){
		if(y_won == false){	
			d++;
			yd=d;}
			
		if(yd==1)
		 DrawString(1050, 1200, "YELLOW Has Finished 1st!!!", colors [BLACK]); 
		else if(yd==2){
		 DrawString(1050, 1200, "YELLOW Has Finished 2nd!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
}
		 y_won = true;
	}
	

	

	Dice_Fun();
	
							

	
	}
	
	else if(screen== 3 ){				// ----->  4 Players
	
		if(t_lock==false){
		Turn_Decider(screen);
		t_lock = true;
	
	}
	
	//cout<<"in game play dice vale is --> "<<dice_value<<endl;
	
grid();

	Mode4_Tokans();
Lines();

	DrawString(250,530,name1,colors[BLACK]);
	DrawString(1150,530,name2,colors[BLACK]);
	DrawString(1150,1430,name3,colors[BLACK]);
	DrawString(250,1430,name4,colors[BLACK]);
		
	DrawString(920, 1900, "Turn : ", colors [BLACK]); 

//cout<<"in game display--------------> "<<dice_value<<"----->turn "<<t<<endl;
	if(t==1)
		DrawString(1000, 1900, "BLUE", colors [BLACK]); 
	if(t==2)
		DrawString(1000, 1900, "YELLOW", colors [BLACK]); 
	if(t==3)
		DrawString(1000, 1900, "GREEN", colors [BLACK]); 
	if(t==4)
		DrawString(1000, 1900, "RED", colors [BLACK]); 
	
	DrawRoundRect(900,1650,200,200,colors[BLACK]);
	
	if(red_wins==4){
		if(r_won == false){
			d++;
			rd=d;}
			
		if(rd==1)
		 DrawString(200, 300, "RED Has Finished 1st!!!", colors [BLACK]); 
		else if(rd==2)
		 DrawString(150, 300, "RED Has Finished 2nd!!!", colors [BLACK]); 
		else if(rd==3){
		 DrawString(150, 300, "RED Has Finished 3rd!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
}
		 r_won = true;
	}
	
	if(blue_wins==4){
		if(b_won == false){
			d++;
			bd=d;}
	
		if(bd==1)
		 DrawString(1050, 300, "BLUE Has Finished 1st!!!", colors [BLACK]); 
		else if(bd==2)
		 DrawString(1050, 300, "BLUE Has Finished 2nd!!!", colors [BLACK]); 
		else if(bd==3){
		 DrawString(1050, 300, "BLUE Has Finished 3rd!!!", colors [BLACK]);
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]); 
		 update_score();
}
		 b_won = true;
	}
	
	if(yellow_wins==4){
		if(y_won == false){	
			d++;
			yd=d;}
			
		if(yd==1)
		 DrawString(1050, 1200, "YELLOW Has Finished 1st!!!", colors [BLACK]); 
		else if(yd==2)
		 DrawString(1050, 1200, "YELLOW Has Finished 2nd!!!", colors [BLACK]); 
		else if(yd==3){
		 DrawString(1050, 1200, "YELLOW Has Finished 3rd!!!", colors [BLACK]); 
		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
}
		 y_won = true;
	}
	
	if(green_wins==4){
		if(g_won == false){
			d++;
			gd=d;}
		
		if(gd==1)
		 DrawString(150, 1200, "GREEN Has Finished 1st!!!", colors [BLACK]); 
		else if(gd==2)
		 DrawString(150, 1200, "GREEN Has Finished 2nd!!!", colors [BLACK]); 
		else if(gd==3){
		 DrawString(150, 1200, "GREEN Has Finished 3rd!!!", colors [BLACK]); 
 		 DrawString(1650, 700, "Game has Ended", colors [BLACK]); 
		 DrawString(1650, 600, "Press Esc to Exit", colors [BLACK]);
		 update_score();
 }
		 g_won = true;
	}

	Dice_Fun();

}
	else if(screen == 5){
	
		int high_scores[11]={0};
		
		
		DrawLine( 0 , 1500 , 2000, 1500 , 40 ,colors[BLACK] );
		DrawLine( 0 , 2000 , 2000, 2000 , 40 ,colors[BLACK] );
		DrawLine( 0 , 500 , 2000, 500 , 40 ,colors[BLACK] );
		DrawLine( 0 , 0 , 2000, 0 , 40 ,colors[BLACK] );
		
		DrawLine( 0, 0 ,0, 2000, 40 ,colors[BLACK] );
		DrawLine( 500 , 0 , 500, 2000 , 40 ,colors[BLACK] );
		DrawLine( 1500, 0 ,1500, 2000, 40 ,colors[BLACK] );
		DrawLine( 2000 , 0 , 2000, 2000 , 40 ,colors[BLACK] );
		
		DrawSquare( 0 ,   0 , 500,colors[RED]); 
		DrawSquare( 0 ,  1500 ,500,colors[OLIVE]); 
		DrawSquare( 1500 ,  0 ,500,colors[BLUE]); 
		DrawSquare( 1500 , 1500 ,500,colors[LAWN_GREEN]);
		
		DrawRectangle( 0 , 500 ,500,1000,colors[BLACK]);
		DrawRectangle( 1500 , 500 ,500,1000,colors[BLACK]);
		DrawRectangle( 500 , 0 ,1000,500,colors[BLACK]);
		
		DrawString(900, 1420, "HIGH SCORES", colors[BLACK]);
		
		ifstream file;
		file.open("highscores.txt");
		
		int index=0;
		while (file)
		{
			int temp;
			file>>temp;
			high_scores[index]=temp;
			index++;
		}
		file.close();
		
	int Q=1300;
		for(int N=0; N<10; N++){
		
		DrawString(900, Q,to_string(N+1)+"-->", colors[BLACK]);
		DrawString(1010, Q,to_string(high_scores[N+1]), colors[BLACK]);
		
			Q-=70;
		}
		

	}
	
	
	glutSwapBuffers(); 

}


void NonPrintableKeys(int key, int x, int y) {
	
	glutPostRedisplay();

}


void PrintableKeys(unsigned char key, int x, int y) {
cout<<"key-------> "<<key<<endl;
	if (key == 27)  
		exit(0);


	if(screen==7){
	
		if(key==13){
			if(n1==true){
				n1=false;
				n2=true;
				}
				
			else if(n2==true){
				screen=1;
			
			}
			else
				n1=true;
		}
		
		if(n1==true)
			name1+=key;
			
		else if(n2==true)
			name2+=key;

	}
	
	else if(screen==8){
	
		if(key==13){
			if(n1==true){
				n1=false;
				n2=true;
				}
				
			else if(n2==true){
				n2=false;
				n3=true;
			
			}
			
			else if(n3==true){
				screen=2;
			
			}
			else
				n1=true;
		}
		
		if(n1==true)
			name1+=key;
			
		else if(n2==true)
			name2+=key;
			
		else if(n3==true)
			name3+=key;

	}
	
	else if(screen==9){
	
		if(key==13){
			if(n1==true){
				n1=false;
				n2=true;
				}
				
			else if(n2==true){
				n2=false;
				n3=true;
			
			}
			
			else if(n3==true){
				n3=false;
				n4=true;
			
			}
			
			else if(n4==true){
				screen=3;
			
			}

		}
		
		if(n1==true)
			name1+=key;
			
		else if(n2==true)
			name2+=key;
			
		else if(n3==true)
			name3+=key;
			
		else if(n4==true)
			name4+=key;
		
		

	}
	
	
	else{

	
	

	if(key == 49&& dice_value!=6){ 

			if(t==4){
				Red_Tokan_move(0);
			}
			else if(t==1){
				Blue_Tokan_move(0);
			}
			else if(t==2){
				Yellow_Tokan_move(0);
			}
			else if(t==3){
				Green_Tokan_move(0);
			}
		Kill_Fun(0);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  49   not 6 ----->"<<dice_value<<endl;
//turn(dice_value);
//dice_value=0;
		}
		



		
	if(key == 50 && dice_value!=6 ){ 

			if(t==4){
				Red_Tokan_move(1);
			}
			else if(t==1){
				Blue_Tokan_move(1);
			}
			else if(t==2){
				Yellow_Tokan_move(1);
			}
			else if(t==3){
				Green_Tokan_move(1);
			}	
		Kill_Fun(1);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  50   not 6 ----->"<<dice_value<<endl;
//turn(dice_value);
//dice_value=0;
		}
		

	
		
	if(key == 51 && dice_value!=6 ){ 
			if(t==4){
				Red_Tokan_move(2);
			}
			else if(t==1){
				Blue_Tokan_move(2);
			}
			else if(t==2){
				Yellow_Tokan_move(2);
			}
			else if(t==3){
				Green_Tokan_move(2);
			}
		Kill_Fun(2);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  51 not 6----->"<<dice_value<<endl;
//turn(dice_value);
//dice_value=0;

		}
		

		
	if(key == 52 && dice_value!=6) {

			if(t==4){
				Red_Tokan_move(3);
			}
			else if(t==1){
				Blue_Tokan_move(3);
			}
			else if(t==2){
				Yellow_Tokan_move(3);
			}
			else if(t==3){
				Green_Tokan_move(3);
			}
		Kill_Fun(3);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  52   not 6 ----->"<<dice_value<<endl;
//turn(dice_value);
//dice_value=0;
		}

		
	
	if(key == 49 && dice_value==6 && screen==3){ 
		
		if(t==1){
			Blue_Tokan_move(0);
		}
		else if(t==2){
			Yellow_Tokan_move(0);

		}
		else if(t==3){
			Green_Tokan_move(0);

		}
		else if(t==4){
			Red_Tokan_move(0);
	
		}	
		Kill_Fun(0);
		won();
//cout<<"-------->>>>>>>>>>>  49    6 ----->"<<dice_value<<"  turn is "<<t<<endl;
//dice_value=0;

		}

		
	if(key == 50 && dice_value==6 && screen==3){ 
		

		if(t==1){
			Blue_Tokan_move(1);
	
		}
		else if(t==2){
			Yellow_Tokan_move(1);

		}
		else if(t==3){
			Green_Tokan_move(1);

		}
		else if(t==4){
			Red_Tokan_move(1);

		}	
		Kill_Fun(1);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  50   6 ----->"<<dice_value<<endl;
//dice_value=0;
		}
		
	if(key == 51 && dice_value==6 && screen==3){ 

		if(t==1){
			Blue_Tokan_move(2);

		}
		else if(t==2){
			Yellow_Tokan_move(2);

		}
		else if(t==3){
			Green_Tokan_move(2);

		}
		else if(t==4){
			Red_Tokan_move(2);

		}
		Kill_Fun(2);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  51    6 ----->"<<dice_value<<endl;
//dice_value=0;
		}
		
	if(key == 52 && dice_value==6 && screen==3){ 
		

		if(t==1){
			Blue_Tokan_move(3);

		}
		else if(t==2){
			Yellow_Tokan_move(3);

		}
		else if(t==3){
			Green_Tokan_move(3);

		}
		else if(t==4){
			Red_Tokan_move(3);

		}	
		Kill_Fun(3);
		won();
//cout<<"-------->>>>>>>>>>>>>>>>>>>>>>  52   6 ----->"<<dice_value<<endl;
//dice_value=0;
		}
		
	if(key == 49 && dice_value==6 && screen==2){ 
		

		if(t==1){
			Blue_Tokan_move(0);
		}
		else if(t==2){
			Yellow_Tokan_move(0);

		}
		else if(t==3){
			Red_Tokan_move(0);

		}

		Kill_Fun(0);
		won();


		}

		
	if(key == 50 && dice_value==6 && screen==2){ 
		

		if(t==1){
			Blue_Tokan_move(1);
	
		}
		else if(t==2){
			Yellow_Tokan_move(1);

		}

		else if(t==3){
			Red_Tokan_move(1);

		}	
		Kill_Fun(1);
		won();
		}
		
	if(key == 51 && dice_value==6 && screen==2){ 

		if(t==1){
			Blue_Tokan_move(2);

		}
		else if(t==2){
			Yellow_Tokan_move(2);

		}

		else if(t==3){
			Red_Tokan_move(2);

		}
		Kill_Fun(2);
		won();
		}
		
	if(key == 52 && dice_value==6 && screen==2){ 
		

		if(t==1){
			Blue_Tokan_move(3);

		}
		else if(t==2){
			Yellow_Tokan_move(3);

		}

		else if(t==3){
			Red_Tokan_move(3);

		}	
		Kill_Fun(3);
		won();
		}
		
	if(key == 49 && dice_value==6 && screen==1){ 
		

		if(t==1){
			Blue_Tokan_move(0);
		}

		else if(t==2){
			Red_Tokan_move(0);

		}

		Kill_Fun(0);
		won();


		}

		
	if(key == 50 && dice_value==6 && screen==1){ 
		

		if(t==1){
			Blue_Tokan_move(1);
	
		}

		else if(t==2){
			Red_Tokan_move(1);

		}	
		Kill_Fun(1);
		won();
		}
		
	if(key == 51 && dice_value==6 && screen==1){ 

		if(t==1){
			Blue_Tokan_move(2);

		}
		else if(t==2){
			Red_Tokan_move(2);

		}
		Kill_Fun(2);
		won();
		}
		
	if(key == 52 && dice_value==6 && screen==1){ 
		

		if(t==1){
			Blue_Tokan_move(3);

		}

		else if(t==2){
			Red_Tokan_move(3);

		}	
		Kill_Fun(3);
		won();
		}
		

		
	if(key==32)
		dicee=true;
		
		
	if(key=='O' || key=='o'){

		if(screen==0)
			screen=7;
			n1=true;}
	
	if(key=='T' || key=='t'){

		if(screen==0)
			screen=8;
			n1=true;}
	
	if(key=='F' || key=='f'){

		if(screen==0)
			screen=9;
			n1=true;}
		
	if(key=='H' || key=='h'){
		
		if(screen==0)
			screen=5;}

/*
if(dice_value==6)
 {            	++six_count1;
cout<<" In inner function dice_v---->  "<<dice_value<<"    turn "<<t<<endl;

	
cout<<"six count 1 in inner function "<<six_count1<<endl;
}
	if(six_count1>=3||six_count2>=3||six_count3>=3)
	{
	cout<<"changed "<<endl;
	t++;
	six_count1=0,six_count2=0,six_count3=0;
	dice_value=0;
	}
	if(six_count4>=3)
	{
	t=1;
	six_count4=0;
	dice_value=0;
	}
*/
//sleep(1);
cout<<"screen before turn change "<<screen<<endl;
if(dice_value!=6&&key==32&&screen==3)
{
cout<<"turn chaging "<<t<<endl;

turn(dice_value);
dice_value=0;

}



if(dice_value==6&&key==32&&screen==3)
{
dice_value=0;
}

if(dice_value!=6&&key==32&&screen==2)
{
//cout<<"turn chaging "<<t<<endl;

turn(dice_value);
dice_value=0;

}



if(dice_value==6&&key==32&&screen==2)
{
dice_value=0;
}






if(turn_count==4)
t_lock=false;

temp=dice_value;	
	}		
	glutPostRedisplay();
}

void Timer(int m) {

	glutTimerFunc(1000.0, Timer, 0);
}

void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void turn(int n)
{
turn_count++;
//cout<<"in turn"<<endl;
if(screen==3 && n!=6){	
					//Changing Turns if Dice Value !=6

		if(t==1||t==2||t==3)
			{t++;
			six_count1=0,six_count2=0,six_count3=0;
			}
		else if(t==4)
			{ 
			t=1;
			six_count4=0;
			}
		}
	if(screen==3 && n==6)
	{

	//cout<<"sixer"<<endl;

	}

if(screen==2&& n!=6){	
					//Changing Turns if Dice Value !=6

		if(t==1||t==2)
			{t++;
			six_count1=0,six_count2=0;
			}
		else if(t==3)
			{ 
			t=1;
			six_count3=0;
			}
		}
	if(screen==2 && n==6)
	{

	//cout<<"sixer"<<endl;

	}
if(screen==1&& n!=6){	
					//Changing Turns if Dice Value !=6

		if(t==1)
			{t++;
			six_count1=0;
			}
		else if(t==2)
			{ 
			t=1;
			six_count2=0;
			}
		}
	if(screen==1 && n==6)
	{

	//cout<<"sixer"<<endl;

	}


}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
cout<<"x "<<x<<"           y "<<y<<endl;
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN &&(x>=1525&&x<=1715) && (y>=770 && y<= 910)) {}
			

	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN &&(x>=150&&x<=220) && (y>=850 && y<= 910)) {}
			

	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN &&(x>=330&&x<=410) && (y>=850 && y<= 910)) {}
			

	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN &&(x>=150&&x<=220) && (y>=720 && y<= 775)) {}
			

	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN &&(x>=330&&x<=410 ) && (y>=720 && y<= 775)) {}
		
	else if (button == GLUT_RIGHT_BUTTON) 
			{

	}
	glutPostRedisplay();
}
bool flag=false;

 void* player1(void* arg)
{

int id=pthread_self();
cout<<"thread 1: "<<id<<endl;
	while(true)
	{
		
		 sem_wait(&Dice_Roll);// Dice_Roll

		if(dicee)
		{
		
		  for(int i=0;i<3;i++)
		{	
		srand(time(0));	
		dice_value=rand()%6+1;
		}
		dicee=false;
		if(dice_value==0)
		dice_value=rand()%6+1;

 cout<<"player 1: "<<id<<endl;
if(dice_value==6)
active1=true;

if(active1==false)
{	
	hit_player1[index1]=1;
	index1++;
	if(index1==20)
	{
		screen=2;
		sem_post(&Dice_Roll);
		cout<<"thread 1 cancalled"<<endl;
		goto start;
	}
}

cout<<"player1--->"<<endl;
cout<<"screen "<<screen<<endl;
	}	
start:
	if(index1>=20)
	{
	cout<<"in if"<<index1<<endl;

			sem_wait(&Board);    //Board
			
			glutDisplayFunc(GameDisplay);
			sem_post(&Board);
	break;

	}
		
		sem_post(&Dice_Roll);   //	
	}


pthread_exit(NULL);
}

void* player2(void* arg)
{
int id=pthread_self();
cout<<"thread 2: "<<id<<endl;
	while(true)
	{
		
		 sem_wait(&Dice_Roll);
		if(dicee)
		{
		
		  for(int i=0;i<3;i++)
		{	
		srand(time(0));	
		dice_value=rand()%6+1;
		
		}
		dicee=false;
		if(dice_value==0)
		dice_value=rand()%6+1;	                    
cout<<"player 2: "<<id<<endl;
if(dice_value==6)
active2=true;
if(active2==false)
{
	hit_player2[index2]=1;
	index2++;
	if(index2==20)
	{
		screen=2;
		sem_post(&Dice_Roll);
		goto start;
	}
}

cout<<"player2--->"<<endl;

	}	
start:
	if(index2>=20)
	{


		sem_wait(&Board);    //Board
			
		glutDisplayFunc(GameDisplay);
		sem_post(&Board);
	         break;

	}
		
		sem_post(&Dice_Roll);   //	
	}
pthread_exit(NULL);
}



void* player3(void* arg)
{

int id=pthread_self();
cout<<"thread 3: "<<id<<endl;
	while(true)
	{
		
		 sem_wait(&Dice_Roll);
		
		if(dicee)
		{
		
		  for(int i=0;i<3;i++)
		{	
			srand(time(0));
		dice_value=rand()%6+1;
		}
		dicee=false;
		if(dice_value==0)
		dice_value=rand()%6+1;
		cout<<"player 3: "<<id<<endl;	
if(dice_value==6)
active3=true;

if(active3==false)
{
	hit_player3[index3]=1;
	index3++;
	if(index3>=20)
	{
		screen=2;
		sem_post(&Dice_Roll);
		cout<<"thread 2 cancalled"<<endl;
		goto start;
	}
}

cout<<"player2--->"<<endl;

	}	
start:
	if(index3>=20)
	{


	sem_wait(&Board);    //Board
			
	glutDisplayFunc(GameDisplay);
	sem_post(&Board);
	break;

	}
		
		sem_post(&Dice_Roll);
		
		
	}
pthread_exit(NULL);

}

void* player4(void* arg)
{
int id=pthread_self();
cout<<"thread 4: "<<id<<endl;
	while(true)
	{
		 sem_wait(&Dice_Roll);
		if(dicee)
		{
		
		  for(int i=0;i<3;i++)
		{	
			srand(time(0));	
			dice_value=rand()%6+1;

		}
		dicee=false;
		if(dice_value==0)
		dice_value=rand()%6+1;
cout<<"player 4: "<<id<<endl;
		}

		sem_wait(&Board);
		glutDisplayFunc(GameDisplay);
		sem_post(&Board);
		if(flag&&dice_value!=6)
		{
		flag=false;
		}
		sem_post(&Dice_Roll);
	
	}
pthread_exit(NULL);
}

void* MainThread(void* arg)
{
	pthread_t tid[4];
	sem_init(&Dice_Roll,0,1);
        sem_init(&Board,0,1);

for(int i=0;i<20;i++)
{
hit_player1[i]=0;
hit_player2[i]=0;
hit_player3[i]=0;
hit_player4[i]=0;
}



        Turn_Decider(screen);

	cout<<"Main thread"<<endl;
	pthread_create(&tid[0],NULL,&player1,NULL);
	pthread_create(&tid[1],NULL,&player2,NULL);
	pthread_create(&tid[2],NULL,&player3,NULL);
	pthread_create(&tid[3],NULL,&player4,NULL);
	sem_destroy(&Dice_Roll);
        sem_destroy(&Board);
	pthread_exit(NULL);
}
/*
 * our gateway main function
 * */
 
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	pthread_t mid;
	int width = 2000, height = 2000; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(750, 750); // set the initial position of our window
	glutInitWindowSize(1500, 1500); // set the size of our window
	 // tell library which function to call for drawing Canvas.

	
	
	glutCreateWindow("Ludo Master"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
pthread_create(&mid,NULL,&MainThread,NULL);
	//glutDisplayFunc(GameDisplay);
	
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	


	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}




void Red_Tokan_move(int z){
//home
if(Red_Tokan[z][0]>=0&&Red_Tokan[z][0]<=600 && Red_Tokan[z][1] >=0 && Red_Tokan[z][1] <=600 && dice_value==6){

	Red_Tokan[z][0]=rhx;
	Red_Tokan[z][1]=rhy;
	red_score+=6;

}

//Red Left Row
else if(Red_Tokan[z][0]>=600 && Red_Tokan[z][0]<=700 && Red_Tokan[z][1]>=0 && Red_Tokan[z][1]<=600){

	if(dice_value==1){
		if(Red_Tokan[z][1]== 550){
			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=100;
			red_score+=1;
		}
		
		else{
			Red_Tokan[z][1] += 100;
			red_score+=1;
			}
			}
			
	else if(dice_value==2){
		if(Red_Tokan[z][1]== 450){
			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=200;
			red_score+=2;
			
		}
		
		else if(Red_Tokan[z][1]== 550){
			Red_Tokan[z][0] -= 200;
			Red_Tokan[z][1] +=100;
			red_score+=2;
			
		}
		
		else{
			Red_Tokan[z][1] += 200;
			red_score+=2;}
			
			}
		
	else if(dice_value==3){
	
		if(Red_Tokan[z][1]== 350){
			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=300;
			red_score+=3;
		
		
		}
	
		else if(Red_Tokan[z][1]== 450){
			Red_Tokan[z][0] -= 200;
			Red_Tokan[z][1] +=200;
			red_score+=3;
			
		}
		
		else if(Red_Tokan[z][1]== 550){
			Red_Tokan[z][0] -= 300;
			Red_Tokan[z][1] +=100;
			red_score+=3;
			
		}
		
		else{
			Red_Tokan[z][1] += 300;
			red_score+=3;
			}
			
			}
	
	else if(dice_value==4){
	
		if(Red_Tokan[z][1]== 250){
			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=400;
			red_score+=4;
		
		}
		
		else if(Red_Tokan[z][1]== 350){
			Red_Tokan[z][0] -= 200;
			Red_Tokan[z][1] +=300;
			red_score+=4;
		
		
		}
	
		else if(Red_Tokan[z][1]== 450){
			Red_Tokan[z][0] -= 300;
			Red_Tokan[z][1] +=200;
			red_score+=4;
			
		}
		
		else if(Red_Tokan[z][1]== 550){
			Red_Tokan[z][0] -= 400;
			Red_Tokan[z][1] +=100;
			red_score+=4;
			
		}
		
		else{
			Red_Tokan[z][1] += 400;
			red_score+=4;
			}
			
			}
			
			
	else if(dice_value==5){
	
		if(Red_Tokan[z][1]== 150){
			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=500;
			red_score+=5;
		
		
		}
		
		else if(Red_Tokan[z][1]== 250){
			Red_Tokan[z][0] -= 200;
			Red_Tokan[z][1] +=400;
			red_score+=5;
		
		
		}
		
		else if(Red_Tokan[z][1]== 350){
			Red_Tokan[z][0] -= 300;
			Red_Tokan[z][1] +=300;
			red_score+=5;
		
		
		}
	
		else if(Red_Tokan[z][1]== 450){
			Red_Tokan[z][0] -= 400;
			Red_Tokan[z][1] +=200;
			red_score+=5;
			
		}
		
		else if(Red_Tokan[z][1]== 550){
			Red_Tokan[z][0] -= 500;
			Red_Tokan[z][1] +=100;
			red_score+=5;
			
		}
		
		else{
			Red_Tokan[z][1] += 500;
			red_score+=5;
			}
			
			}

	else if(dice_value==6){
	
		if(Red_Tokan[z][1]== 50){
			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=600;
			red_score+=6;
		
		
		}
		
		else if(Red_Tokan[z][1]== 150){
			Red_Tokan[z][0] -= 200;
			Red_Tokan[z][1] +=500;
			red_score+=6;
		
		
		}
		
		else if(Red_Tokan[z][1]== 250){
			Red_Tokan[z][0] -= 300;
			Red_Tokan[z][1] +=400;
			red_score+=6;
		
		
		}
		
		else if(Red_Tokan[z][1]== 350){
			Red_Tokan[z][0] -= 400;
			Red_Tokan[z][1] +=300;
			red_score+=6;
		
		
		}
	
		else if(Red_Tokan[z][1]== 450){
			Red_Tokan[z][0] -= 500;
			Red_Tokan[z][1] +=200;
			red_score+=6;
			
		}
		
		else if(Red_Tokan[z][1]== 550){
			Red_Tokan[z][0] -= 600;
			Red_Tokan[z][1] +=100;
			red_score+=6;
			
		}
		
}


}

//Green Above Row
else if(Red_Tokan[z][0]>=0 && Red_Tokan[z][0]<=600 && Red_Tokan[z][1]>=800 && Red_Tokan[z][1]<=900){

	if(dice_value==1){
		if(Red_Tokan[z][0]== 550){
			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=100;
			red_score+=1;
			
		}
		
		else{
			Red_Tokan[z][0] += 100;
			red_score+=1;
			}
			
			}
			
	else if(dice_value==2){
		if(Red_Tokan[z][0]== 450){
			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=200;
			red_score+=2;
			
		}
		
		else if(Red_Tokan[z][0] == 550){
			Red_Tokan[z][1] += 200;
			Red_Tokan[z][0] +=100;
			red_score+=2;
		}
		
		else{
			Red_Tokan[z][0] += 200;
			red_score+=2;
			}}
		
	else if(dice_value==3){
	
		if(Red_Tokan[z][0]== 350){
			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=300;
			red_score+=3;		
		
		}
	
		else if(Red_Tokan[z][0]== 450){
			Red_Tokan[z][1] += 200;
			Red_Tokan[z][0] +=200;
			red_score+=3;
		}
		
		else if(Red_Tokan[z][0]== 550){
			Red_Tokan[z][1] += 300;
			Red_Tokan[z][0] +=100;
			red_score+=3;
		}
		
		else{
			Red_Tokan[z][0] += 300;
			red_score+=3;
			}}
	
	else if(dice_value==4){
	
		if(Red_Tokan[z][0]== 250){
			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=400;
			red_score+=4;
		
		}
		
		else if(Red_Tokan[z][0]== 350){
			Red_Tokan[z][1] += 200;
			Red_Tokan[z][0] +=300;
			red_score+=4;
		
		}
	
		else if(Red_Tokan[z][0]== 450){
			Red_Tokan[z][1] += 300;
			Red_Tokan[z][0] +=200;
			red_score+=4;
		}
		
		else if(Red_Tokan[z][0]== 550){
			Red_Tokan[z][1] += 400;
			Red_Tokan[z][0] +=100;
			red_score+=4;
		}
		
		else{
			Red_Tokan[z][0] += 400;
			red_score+=4;
			}
			}
			
			
	else if(dice_value==5){
	
		if(Red_Tokan[z][0]== 150){
			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=500;
			red_score+=5;
		
		}
		
		else if(Red_Tokan[z][0]== 250){
			Red_Tokan[z][1] += 200;
			Red_Tokan[z][0] +=400;
			red_score+=5;
		
		}
		
		else if(Red_Tokan[z][0]== 350){
			Red_Tokan[z][1] += 300;
			Red_Tokan[z][0] +=300;
			red_score+=5;
		
		}
	
		else if(Red_Tokan[z][0]== 450){
			Red_Tokan[z][1] += 400;
			Red_Tokan[z][0] +=200;
			red_score+=5;
		}
		
		else if(Red_Tokan[z][0]== 550){
			Red_Tokan[z][1] += 500;
			Red_Tokan[z][0] +=100;
			red_score+=5;
		}
		
		else{
			Red_Tokan[z][0] += 500;
			red_score+=5;
			}}

	else if(dice_value==6){
	
		if(Red_Tokan[z][0]== 50){
			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=600;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][0]== 150){
			Red_Tokan[z][1] += 200;
			Red_Tokan[z][0] +=500;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][0]== 250){
			Red_Tokan[z][1] += 300;
			Red_Tokan[z][0] +=400;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][0]== 350){
			Red_Tokan[z][1] += 400;
			Red_Tokan[z][0] +=300;
			red_score+=6;
		
		}
	
		else if(Red_Tokan[z][0]== 450){
			Red_Tokan[z][1] += 500;
			Red_Tokan[z][0] +=200;
			red_score+=6;
		}
		
		else if(Red_Tokan[z][0]== 550){
			Red_Tokan[z][1] += 600;
			Red_Tokan[z][0] +=100;
			red_score+=6;
		}
		
}


}


//Blue Below Row
else if(Red_Tokan[z][0]>=900 && Red_Tokan[z][0]<=1500 && Red_Tokan[z][1]>=600 && Red_Tokan[z][1]<=700){

	if(dice_value==1){
		if(Red_Tokan[z][0]== 950){
			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=100;
			red_score+=1;
			
		}
		
		else{
			Red_Tokan[z][0] -= 100;
			red_score+=1;}
			
			}
			
	else if(dice_value==2){
		if(Red_Tokan[z][0]== 1050){
			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=200;
			red_score+=2;
		}
		
		else if(Red_Tokan[z][0]== 950){
			Red_Tokan[z][1] -= 200;
			Red_Tokan[z][0] -= 100;
			red_score+=2;
		}
		
		else{
			Red_Tokan[z][0] -= 200;
			red_score+=2;}
			}
		
	else if(dice_value==3){
	
		if(Red_Tokan[z][0]== 1150){
			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=300;
			red_score+=3;
		
		}
	
		else if(Red_Tokan[z][0]== 1050){
			Red_Tokan[z][1] -= 200;
			Red_Tokan[z][0] -=200;
			red_score+=3;
		}
		
		else if(Red_Tokan[z][0]== 950){
			Red_Tokan[z][1] -= 300;
			Red_Tokan[z][0] -=100;
			red_score+=3;
		}
		
		else{
			Red_Tokan[z][0] -= 300;
			red_score+=3;}
			}
	
	else if(dice_value==4){
	
		if(Red_Tokan[z][0]== 1250){
			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=400;
			red_score+=4;
		
		}
		
		else if(Red_Tokan[z][0]== 1150){
			Red_Tokan[z][1] -= 200;
			Red_Tokan[z][0] -=300;
			red_score+=4;
		
		}
	
		else if(Red_Tokan[z][0]== 1050){
			Red_Tokan[z][1] -= 300;
			Red_Tokan[z][0] -=200;
			red_score+=4;
		}
		
		else if(Red_Tokan[z][0]== 950){
			Red_Tokan[z][1] -= 400;
			Red_Tokan[z][0] -=100;
			red_score+=4;
		}
		
		else{
			Red_Tokan[z][0] -= 400;
			red_score+=4;}
			}
			
			
	else if(dice_value==5){
	
		if(Red_Tokan[z][0]== 1350){
			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=500;
			red_score+=5;
		
		}
		
		else if(Red_Tokan[z][0]== 1250){
			Red_Tokan[z][1] -= 200;
			Red_Tokan[z][0] -=400;
			red_score+=5;
		
		}
		
		else if(Red_Tokan[z][0]== 1150){
			Red_Tokan[z][1] -= 300;
			Red_Tokan[z][0] -=300;
			red_score+=5;
		
		}
	
		else if(Red_Tokan[z][0]== 1050){
			Red_Tokan[z][1] -= 400;
			Red_Tokan[z][0] -=200;
			red_score+=5;
		}
		
		else if(Red_Tokan[z][0]== 950){
			Red_Tokan[z][1] -= 500;
			Red_Tokan[z][0] -=100;
			red_score+=5;
		}
		
		else{
			Red_Tokan[z][0] -= 500;
			red_score+=5;}
			}

	else if(dice_value==6){
	
		if(Red_Tokan[z][0]== 1450){
			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=600;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][0]== 1350){
			Red_Tokan[z][1] -= 200;
			Red_Tokan[z][0] -=500;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][0]== 1250){
			Red_Tokan[z][1] -= 300;
			Red_Tokan[z][0] -=400;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][0]== 1150){
			Red_Tokan[z][1] -= 400;
			Red_Tokan[z][0] -=300;
			red_score+=6;
		
		}
	
		else if(Red_Tokan[z][0]== 1050){
			Red_Tokan[z][1] -= 500;
			Red_Tokan[z][0] -=200;
			red_score+=6;
		}
		
		else if(Red_Tokan[z][0]== 950){
			Red_Tokan[z][1] -= 600;
			Red_Tokan[z][0] -=100;
			red_score+=6;	
		}
		
}
}

//Yellow Right Row
else if(Red_Tokan[z][0]>=800 && Red_Tokan[z][0]<=900 && Red_Tokan[z][1]>=900 && Red_Tokan[z][1]<=1500){

	if(dice_value==1){
		if(Red_Tokan[z][1]== 950){
			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=100;
			red_score+=1;
			
		}
		
		else{
			Red_Tokan[z][1] -= 100;
			red_score+=1;}
			}
			
	else if(dice_value==2){
		if(Red_Tokan[z][1]== 1050){
			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=200;
			red_score+=2;
		}
		
		else if(Red_Tokan[z][1]== 950){
			Red_Tokan[z][0] += 200;
			Red_Tokan[z][1] -=100;
			red_score+=2;
		}
		
		else{
			Red_Tokan[z][1] -= 200;
			red_score+=2;}
			}
		
	else if(dice_value==3){
	
		if(Red_Tokan[z][1]== 1150){
			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=300;
			red_score+=3;
		
		}
	
		else if(Red_Tokan[z][1]== 1050){
			Red_Tokan[z][0] += 200;
			Red_Tokan[z][1] -=200;
			red_score+=3;
		}
		
		else if(Red_Tokan[z][1]== 950){
			Red_Tokan[z][0] += 300;
			Red_Tokan[z][1] -=100;
			red_score+=3;	
		}
		
		else{
			Red_Tokan[z][1] -= 300;
			red_score+=3;	}
			}
	
	else if(dice_value==4){
	
		if(Red_Tokan[z][1]== 1250){
			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=400;
			red_score+=4;
		
		}
		
		else if(Red_Tokan[z][1]== 1150){
			Red_Tokan[z][0] += 200;
			Red_Tokan[z][1] -=300;
			red_score+=4;
		
		}
	
		else if(Red_Tokan[z][1]== 1050){
			Red_Tokan[z][0] += 300;
			Red_Tokan[z][1] -=200;
			red_score+=4;	
		}
		
		else if(Red_Tokan[z][1]== 950){
			Red_Tokan[z][0] += 400;
			Red_Tokan[z][1] -=100;
			red_score+=4;	
		}
		
		else
			{Red_Tokan[z][1] -= 400;
			red_score+=4;}	
			}
			
			
	else if(dice_value==5){
	
		if(Red_Tokan[z][1]== 1350){
			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=500;
			red_score+=5;
		
		}
		
		else if(Red_Tokan[z][1]== 1250){
			Red_Tokan[z][0] += 200;
			Red_Tokan[z][1] -=400;
			red_score+=5;
		
		}
		
		else if(Red_Tokan[z][1]== 1150){
			Red_Tokan[z][0] += 300;
			Red_Tokan[z][1] -=300;
			red_score+=5;
		
		}
	
		else if(Red_Tokan[z][1]== 1050){
			Red_Tokan[z][0] += 400;
			Red_Tokan[z][1] -=200;
			red_score+=5;	
		}
		
		else if(Red_Tokan[z][1]== 950){
			Red_Tokan[z][0] += 500;
			Red_Tokan[z][1] -=100;
			red_score+=5;	
		}
		
		else{
			Red_Tokan[z][1] -= 500;
			red_score+=5;	}
			}

	else if(dice_value==6){
	
		if(Red_Tokan[z][1]== 1450){
			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=600;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][1]== 1350){
			Red_Tokan[z][0] += 200;
			Red_Tokan[z][1] -=500;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][1]== 1250){
			Red_Tokan[z][0] += 300;
			Red_Tokan[z][1] -=400;
			red_score+=6;
		
		}
		
		else if(Red_Tokan[z][1]== 1150){
			Red_Tokan[z][0] += 400;
			Red_Tokan[z][1] -=300;
			red_score+=6;
		
		}
	
		else if(Red_Tokan[z][1]== 1050){
			Red_Tokan[z][0] += 500;
			Red_Tokan[z][1] -=200;
			red_score+=6;	
		}
		
		else if(Red_Tokan[z][1]== 950){
			Red_Tokan[z][0] += 600;
			Red_Tokan[z][1] -=100;
			red_score+=6;	
		}
		
}


}



//Red Right Row

else if(Red_Tokan[z][0]>=800 && Red_Tokan[z][0]<=900 && Red_Tokan[z][1]>=0 && Red_Tokan[z][1]<=600){


	if(red_lock==true){
		if(dice_value==1){
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
			}
			
			else
				Red_Tokan[z][1] -= 100;
				
			red_score+=1;
				}
				
		else if(dice_value==2){
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 200;
				
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -=100;
				
			}
			
			else
				Red_Tokan[z][1] -= 200;
				
			red_score+=2;
				}
			
		else if(dice_value==3){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] += 100;
			
			
			}
		
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] -=100;
				
			}
			
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -=100;
				Red_Tokan[z][1] -=200;
				
			}
			
			else
				Red_Tokan[z][1] -= 300;
				
			red_score+=3;
				}
		
		else if(dice_value==4){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] +=200;
			
			
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] -=200;
				
			}
			
			else if(Red_Tokan[z][1]== 350){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -=300;
				
			}
			
			else
				Red_Tokan[z][1] -= 400;
			
			red_score+=4;	
				}
				
				
		else if(dice_value==5){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] += 300;
			
			
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] += 100;
			
			
			}
			
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Red_Tokan[z][1]== 350){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] -= 300;
				
			}
			
			else if(Red_Tokan[z][1]== 450){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -=400;
				
			}
			
			else
				Red_Tokan[z][1] -= 500;
			
			red_score+=5;
				}

		else if(dice_value==6){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] += 400;
			
			
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] += 200;
			
			
			}
			
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -= 200;

			}
			
			else if(Red_Tokan[z][1]== 350){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Red_Tokan[z][1]== 450){
				Red_Tokan[z][0] -= 200;
				Red_Tokan[z][1] -= 400;
				
			}
			
			else if(Red_Tokan[z][1]== 550){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -= 500;
				
			}
			
		red_score+=6;
			
	}
		}
		
		
	else if(red_lock==false){
		if(dice_value==1){
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
			}
			
			else
				Red_Tokan[z][1] -= 100;
				
			red_score+=1;
				}
				
		else if(dice_value==2){
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 100;
				
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -=100;
				
			}
			
			else
				Red_Tokan[z][1] -= 200;
				
			red_score+=2;	}
			
		else if(dice_value==3){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 200;
			
			
			}
		
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 100;
				
			}
			
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -=100;
				Red_Tokan[z][1] -=200;
				
			}
			
			else
				Red_Tokan[z][1] -= 300;
				
			red_score+=3;	}
		
		else if(dice_value==4){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] +=300;
			
			
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 100;
			
			
			}
		
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -= 100;
				
			}
			
			else if(Red_Tokan[z][1]== 350){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -=300;
				
			}
			
			else
				Red_Tokan[z][1] -= 400;
				
			red_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 400;
			
			
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 200;
			
			
			}
			
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -= 100;

			}
		
			else if(Red_Tokan[z][1]== 350){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -= 200;
				
			}
			
			else if(Red_Tokan[z][1]== 450){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -=400;
				
			}
			
			else
				Red_Tokan[z][1] -= 500;
				
			red_score+=5;	}

		else if(dice_value==6){
		
			if(Red_Tokan[z][1]== 50){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 500;
			
			
			}
			
			else if(Red_Tokan[z][1]== 150){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 300;
			
			
			}
			
			else if(Red_Tokan[z][1]== 250){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] += 100;

			}
			
			else if(Red_Tokan[z][1]== 350){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Red_Tokan[z][1]== 450){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -= 300;
				
			}
			
			else if(Red_Tokan[z][1]== 550){
				Red_Tokan[z][0] -= 100;
				Red_Tokan[z][1] -= 500;
				
			}
			red_score+=6;
	}
		}

}


//Green Down Row

else if(Red_Tokan[z][0]>=0 && Red_Tokan[z][0]<=600 && Red_Tokan[z][1]>=600 && Red_Tokan[z][1]<=700){


		if(dice_value==1){
			if(Red_Tokan[z][0]== 50){
				Red_Tokan[z][1] += 100;
			}
			
			else
				Red_Tokan[z][0] -= 100;
				
			red_score+=1;	}
				
		else if(dice_value==2){
			if(Red_Tokan[z][0]== 50){
				Red_Tokan[z][1] += 200;
				
			}
			
			else if(Red_Tokan[z][0]== 150){
				Red_Tokan[z][1] += 100;
				Red_Tokan[z][0] -=100;
				
			}
			
			else
				Red_Tokan[z][0] -= 200;
				
			red_score+=2;	}
			
		else if(dice_value==3){
		
			if(Red_Tokan[z][0]== 50){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] += 100;
			
			
			}
		
			else if(Red_Tokan[z][0]== 150){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] -=100;
				
			}
			
			else if(Red_Tokan[z][0]== 250){
				Red_Tokan[z][1] +=100;
				Red_Tokan[z][0] -=200;
				
			}
			
			else
				Red_Tokan[z][0] -= 300;
				
			red_score+=3;	}
		
		else if(dice_value==4){
		
			if(Red_Tokan[z][0]== 50){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] +=200;
			
			
			}
			
			else if(Red_Tokan[z][0]== 150){
				Red_Tokan[z][1] += 200;
			
			
			}
		
			else if(Red_Tokan[z][0]== 250){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] -=200;
				
			}
			
			else if(Red_Tokan[z][0]== 350){
				Red_Tokan[z][1] += 100;
				Red_Tokan[z][0] -=300;
				
			}
			
			else
				Red_Tokan[z][0] -= 400;
				
			red_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Red_Tokan[z][0]== 50){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] += 300;
			
			
			}
			
			else if(Red_Tokan[z][0]== 150){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] += 100;
			
			
			}
			
			else if(Red_Tokan[z][0]== 250){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] -= 100;
			
			
			}
		
			else if(Red_Tokan[z][0]== 350){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] -= 300;
				
			}
			
			else if(Red_Tokan[z][0]== 450){
				Red_Tokan[z][1] += 100;
				Red_Tokan[z][0] -=400;
				
			}
			
			else
				Red_Tokan[z][0] -= 500;
				
			red_score+=5;	}

		else if(dice_value==6){
		
			if(Red_Tokan[z][0]== 50){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] += 400;
			
			
			}
			
			else if(Red_Tokan[z][0]== 150){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] += 200;
			
			
			}
			
			else if(Red_Tokan[z][0]== 250){
				Red_Tokan[z][1] += 200;

			}
			
			else if(Red_Tokan[z][0]== 350){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Red_Tokan[z][0]== 450){
				Red_Tokan[z][1] += 200;
				Red_Tokan[z][0] -= 400;
				
			}
			
			else if(Red_Tokan[z][0]== 550){
				Red_Tokan[z][1] += 100;
				Red_Tokan[z][0] -= 500;
				
			}
			red_score+=6;
	}


}


//Blue Up Row

else if(Red_Tokan[z][0]>=900 && Red_Tokan[z][0]<=1500 && Red_Tokan[z][1]>=800 && Red_Tokan[z][1]<=900){

		if(dice_value==1){
			if(Red_Tokan[z][0]== 1450){
				Red_Tokan[z][1] -= 100;
			}
			
			else
				Red_Tokan[z][0] += 100;
				
			red_score+=1;	}
				
		else if(dice_value==2){
			if(Red_Tokan[z][0]== 1450){
				Red_Tokan[z][1] -= 200;
				
			}
			
			else if(Red_Tokan[z][0]== 1350){
				Red_Tokan[z][1] -= 100;
				Red_Tokan[z][0] +=100;
				
			}
			
			else
				Red_Tokan[z][0] += 200;
				
			red_score+=2;	}
			
		else if(dice_value==3){
		
			if(Red_Tokan[z][0]== 1450){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Red_Tokan[z][0]== 1350){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] +=100;
				
			}
			
			else if(Red_Tokan[z][0]== 1250){
				Red_Tokan[z][1] -=100;
				Red_Tokan[z][0] +=200;
				
			}
			
			else
				Red_Tokan[z][0] += 300;
				
			red_score+=3;	}
		
		else if(dice_value==4){
		
			if(Red_Tokan[z][0]== 1450){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] -=200;
			
			
			}
			
			else if(Red_Tokan[z][0]== 1350){
				Red_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Red_Tokan[z][0]== 1250){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] +=200;
				
			}
			
			else if(Red_Tokan[z][0] == 1150){
				Red_Tokan[z][1] -= 100;
				Red_Tokan[z][0] +=300;
				
			}
			
			else
				Red_Tokan[z][0] += 400;
				
			red_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Red_Tokan[z][0]== 1450){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] -= 300;
			
			
			}
			
			else if(Red_Tokan[z][0]== 1350){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] -= 100;
		
			
			}
			
			else if(Red_Tokan[z][0]== 1250){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] += 100;
			
			
			}
		
			else if(Red_Tokan[z][0]== 1150){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] += 300;
				
			}
			
			else if(Red_Tokan[z][0]== 1050){
				Red_Tokan[z][1] -= 100;
				Red_Tokan[z][0] +=400;
				
			}
			
			else
				Red_Tokan[z][0] += 500;
				
			red_score+=5;	}

		else if(dice_value==6){
		
			if(Red_Tokan[z][0]== 1450){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] -= 400;
			
			
			}
			
			else if(Red_Tokan[z][0]== 1350){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] -= 200;
			
			
			}
			
			else if(Red_Tokan[z][0]== 1250){
				Red_Tokan[z][1] -= 200;
			}
			
			else if(Red_Tokan[z][0]== 1150){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] += 200;
			
			
			}
		
			else if(Red_Tokan[z][0]== 1050){
				Red_Tokan[z][1] -= 200;
				Red_Tokan[z][0] += 400;
				
			}
			
			else if(Red_Tokan[z][0]== 950){
				Red_Tokan[z][1] -= 100;
				Red_Tokan[z][0] += 500;
				
			}
			red_score+=6;
	}



}



//Yellow Left Row

else if(Red_Tokan[z][0]>=600 && Red_Tokan[z][0]<=700 && Red_Tokan[z][1]>=900 && Red_Tokan[z][1]<=1500){

		if(dice_value==1){
			if(Red_Tokan[z][1]== 1450){
				Red_Tokan[z][0] += 100;
			}
			
			else
				Red_Tokan[z][1] += 100;
				
			red_score+=1;	}
				
		else if(dice_value==2){
			if(Red_Tokan[z][1]== 1450){
				Red_Tokan[z][0] += 200;
				
			}
			
			else if(Red_Tokan[z][1]== 1350){
				Red_Tokan[z][0] += 100;
				Red_Tokan[z][1] +=100;
				
			}
			
			else
				Red_Tokan[z][1] += 200;
				
			red_score+=2;	}
			
		else if(dice_value==3){
		
			if(Red_Tokan[z][1]== 1450){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Red_Tokan[z][1]== 1350){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] +=100;
				
			}
			
			else if(Red_Tokan[z][1]== 1250){
				Red_Tokan[z][0] +=100;
				Red_Tokan[z][1] +=200;
				
			}
			
			else
				Red_Tokan[z][1] += 300;
				
			red_score+=3;	}
		
		else if(dice_value==4){
		
			if(Red_Tokan[z][1]== 1450){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] -=200;
			
			
			}
			
			else if(Red_Tokan[z][1]== 1350){
				Red_Tokan[z][0] += 200;
			
			
			}
		
			else if(Red_Tokan[z][1]== 1250){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] +=200;
				
			}
			
			else if(Red_Tokan[z][1] == 1150){
				Red_Tokan[z][0] += 100;
				Red_Tokan[z][1] +=300;
				
			}
			
			else
				Red_Tokan[z][1] += 400;
				
			red_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Red_Tokan[z][1]== 1450){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] -= 300;
			
			
			}
			
			else if(Red_Tokan[z][1]== 1350){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] -= 100;
		
			
			}
			
			else if(Red_Tokan[z][1]== 1250){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] += 100;
			
			
			}
		
			else if(Red_Tokan[z][1]== 1150){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] += 300;
				
			}
			
			else if(Red_Tokan[z][1]== 1050){
				Red_Tokan[z][0] += 100;
				Red_Tokan[z][1] +=400;
				
			}
			
			else
				Red_Tokan[z][1] += 500;
				
			red_score+=5;	}

		else if(dice_value==6){
		
			if(Red_Tokan[z][1]== 1450){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] -= 400;
			
			
			}
			
			else if(Red_Tokan[z][1]== 1350){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] -= 200;
			
			
			}
			
			else if(Red_Tokan[z][1]== 1250){
				Red_Tokan[z][0] += 200;

			}
			
			else if(Red_Tokan[z][1]== 1150){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] += 200;
			
			
			}
		
			else if(Red_Tokan[z][1]== 1050){
				Red_Tokan[z][0] += 200;
				Red_Tokan[z][1] += 400;
				
			}
			
			else if(Red_Tokan[z][1]== 950){
				Red_Tokan[z][0] += 100;
				Red_Tokan[z][1] += 500;
				
			}
			red_score+=6;
	}

}
//red middle row
else if(Red_Tokan[z][0]>=700 && Red_Tokan[z][0]<=800 && Red_Tokan[z][1]>=0 && Red_Tokan[z][1]<=600){

	if(red_lock==false){
	
		if(dice_value==1){
			
			Red_Tokan[z][1]+=100;
			red_score+=1;
				}
				
		else if(dice_value==2){
			
			if(Red_Tokan[z][1] <= 500){
				Red_Tokan[z][1] += 200;
				red_score+=2;
				
			}
		
				}
			
		else if(dice_value==3){
		
			if(Red_Tokan[z][1]<= 400){
				Red_Tokan[z][1] += 300;
				red_score+=3;

			}
				}
		
		else if(dice_value==4){
		
			if(Red_Tokan[z][1] <=300){

				Red_Tokan[z][1] +=400;
				red_score+=4;
			
			
			}
				}
				
	
		else if(dice_value==5){
		
			if(Red_Tokan[z][1] <= 200){
				Red_Tokan[z][1] += 500;
				red_score+=5;
			}
				}

		else if(dice_value==6){
		
			if(Red_Tokan[z][1]<= 100){
				Red_Tokan[z][1] += 600;
				red_score+=6;
			
			
			}	
				}
				}
		
		
	else if(red_lock==true){
	
	
		if(dice_value==1){
			Red_Tokan[z][0]-=100;
			red_score+=1;}
			
	else if(dice_value==2){

			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=100;

			red_score+=2;}
		
	else if(dice_value==3){

			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=200;

			red_score+=3;}
			
	else if(dice_value==4){

			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=300;

			red_score+=4;}
			
	else if(dice_value==5){

			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=400;

			red_score+=5;}
			
	else if(dice_value==6){

			Red_Tokan[z][0] -= 100;
			Red_Tokan[z][1] +=500;

			red_score+=6;}


	}	
		

}

//yellow middle row

else if(Red_Tokan[z][0]>=700 && Red_Tokan[z][0]<=800 && Red_Tokan[z][1]>=900 && Red_Tokan[z][1]<=1500){

	if(dice_value==1){
			Red_Tokan[z][0]+=100;
			red_score+=1;}
			
	else if(dice_value==2){

			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=100;

			red_score+=2;}
		
	else if(dice_value==3){

			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=200;

			red_score+=3;}
			
	else if(dice_value==4){

			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=300;

			red_score+=4;}
			
	else if(dice_value==5){

			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=400;

			red_score+=5;}
			
	else if(dice_value==6){

			Red_Tokan[z][0] += 100;
			Red_Tokan[z][1] -=500;

			red_score+=6;}

		

}

//blue middle row

else if(Red_Tokan[z][0]>=900 && Red_Tokan[z][0]<=1500 && Red_Tokan[z][1]>=700 && Red_Tokan[z][1]<=800){

	if(dice_value==1){
			Red_Tokan[z][1]-=100;
			red_score+=1;}
			
	else if(dice_value==2){

			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=100;

			red_score+=2;}
		
	else if(dice_value==3){

			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=200;

			red_score+=3;}
			
	else if(dice_value==4){

			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=300;

			red_score+=4;}
			
	else if(dice_value==5){

			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=400;

			red_score+=5;}
			
	else if(dice_value==6){

			Red_Tokan[z][1] -= 100;
			Red_Tokan[z][0] -=500;

			red_score+=6;}

}


//green middle row


else if(Red_Tokan[z][0]>=0 && Red_Tokan[z][0]<=600 && Red_Tokan[z][1]>=700 && Red_Tokan[z][1]<=800){

	if(dice_value==1){
			Red_Tokan[z][1]+=100;
			red_score+=1;}
			
	else if(dice_value==2){

			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=100;

			red_score+=2;}
		
	else if(dice_value==3){

			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=200;

			red_score+=3;}
			
	else if(dice_value==4){

			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=300;

			red_score+=4;}
			
	else if(dice_value==5){

			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=400;

			red_score+=5;}
			
	else if(dice_value==6){

			Red_Tokan[z][1] += 100;
			Red_Tokan[z][0] +=500;

			red_score+=6;}


}


}
void Blue_Tokan_move(int z){
//home
if(Blue_Tokan[z][0]>=900&&Blue_Tokan[z][0]<=1500 && Blue_Tokan[z][1] >=0 && Blue_Tokan[z][1] <=600 && dice_value==6){

	Blue_Tokan[z][0]=bhx;
	Blue_Tokan[z][1]=bhy;
	blue_score+=6;
}

//red Left Row
else if(Blue_Tokan[z][0]>=600 && Blue_Tokan[z][0]<=700 && Blue_Tokan[z][1]>=0 && Blue_Tokan[z][1]<=600){

	if(dice_value==1){
		if(Blue_Tokan[z][1]== 550){
			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=100;
			
		}
		
		else
			Blue_Tokan[z][1] += 100;
			
		blue_score+=1;	}
			
	else if(dice_value==2){
		if(Blue_Tokan[z][1]== 450){
			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 550){
			Blue_Tokan[z][0] -= 200;
			Blue_Tokan[z][1] +=100;
			
		}
		
		else
			Blue_Tokan[z][1] += 200;
			
		blue_score+=2;	}
		
	else if(dice_value==3){
	
		if(Blue_Tokan[z][1]== 350){
			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 450){
			Blue_Tokan[z][0] -= 200;
			Blue_Tokan[z][1] +=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 550){
			Blue_Tokan[z][0] -= 300;
			Blue_Tokan[z][1] +=100;
			
		}
		
		else
			Blue_Tokan[z][1] += 300;
			
		blue_score+=3;	}
	
	else if(dice_value==4){
	
		if(Blue_Tokan[z][1]== 250){
			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=400;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 350){
			Blue_Tokan[z][0] -= 200;
			Blue_Tokan[z][1] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 450){
			Blue_Tokan[z][0] -= 300;
			Blue_Tokan[z][1] +=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 550){
			Blue_Tokan[z][0] -= 400;
			Blue_Tokan[z][1] +=100;
			
		}
		
		else
			Blue_Tokan[z][1] += 400;
			
		blue_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Blue_Tokan[z][1]== 150){
			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=500;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 250){
			Blue_Tokan[z][0] -= 200;
			Blue_Tokan[z][1] +=400;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 350){
			Blue_Tokan[z][0] -= 300;
			Blue_Tokan[z][1] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 450){
			Blue_Tokan[z][0] -= 400;
			Blue_Tokan[z][1] +=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 550){
			Blue_Tokan[z][0] -= 500;
			Blue_Tokan[z][1] +=100;
			
		}
		
		else
			Blue_Tokan[z][1] += 500;
			
		blue_score+=5;	}

	else if(dice_value==6){
	
		if(Blue_Tokan[z][1]== 50){
			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=600;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 150){
			Blue_Tokan[z][0] -= 200;
			Blue_Tokan[z][1] +=500;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 250){
			Blue_Tokan[z][0] -= 300;
			Blue_Tokan[z][1] +=400;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 350){
			Blue_Tokan[z][0] -= 400;
			Blue_Tokan[z][1] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 450){
			Blue_Tokan[z][0] -= 500;
			Blue_Tokan[z][1] +=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 550){
			Blue_Tokan[z][0] -= 600;
			Blue_Tokan[z][1] +=100;
			
		}
		blue_score+=6;
}


}

//green Above Row
else if(Blue_Tokan[z][0]>=0 && Blue_Tokan[z][0]<=600 && Blue_Tokan[z][1]>=800 && Blue_Tokan[z][1]<=900){

	if(dice_value==1){
		if(Blue_Tokan[z][0]== 550){
			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=100;
			
		}
		
		else
			Blue_Tokan[z][0] += 100;
			
		blue_score+=1;	}
			
	else if(dice_value==2){
		if(Blue_Tokan[z][0]== 450){
			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=200;
			
		}
		
		else if(Blue_Tokan[z][0] == 550){
			Blue_Tokan[z][1] += 200;
			Blue_Tokan[z][0] +=100;
			
		}
		
		else
			Blue_Tokan[z][0] += 200;
			
		blue_score+=2;	}
		
	else if(dice_value==3){
	
		if(Blue_Tokan[z][0]== 350){
			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 450){
			Blue_Tokan[z][1] += 200;
			Blue_Tokan[z][0] +=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 550){
			Blue_Tokan[z][1] += 300;
			Blue_Tokan[z][0] +=100;
			
		}
		
		else
			Blue_Tokan[z][0] += 300;
			
		blue_score+=3;	}
	
	else if(dice_value==4){
	
		if(Blue_Tokan[z][0]== 250){
			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=400;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 350){
			Blue_Tokan[z][1] += 200;
			Blue_Tokan[z][0] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 450){
			Blue_Tokan[z][1] += 300;
			Blue_Tokan[z][0] +=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 550){
			Blue_Tokan[z][1] += 400;
			Blue_Tokan[z][0] +=100;
			
		}
		
		else
			Blue_Tokan[z][0] += 400;
			
		blue_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Blue_Tokan[z][0]== 150){
			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=500;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 250){
			Blue_Tokan[z][1] += 200;
			Blue_Tokan[z][0] +=400;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 350){
			Blue_Tokan[z][1] += 300;
			Blue_Tokan[z][0] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 450){
			Blue_Tokan[z][1] += 400;
			Blue_Tokan[z][0] +=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 550){
			Blue_Tokan[z][1] += 500;
			Blue_Tokan[z][0] +=100;
			
		}
		
		else
			Blue_Tokan[z][0] += 500;
			
		blue_score+=5;	}

	else if(dice_value==6){
	
		if(Blue_Tokan[z][0]== 50){
			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=600;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 150){
			Blue_Tokan[z][1] += 200;
			Blue_Tokan[z][0] +=500;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 250){
			Blue_Tokan[z][1] += 300;
			Blue_Tokan[z][0] +=400;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 350){
			Blue_Tokan[z][1] += 400;
			Blue_Tokan[z][0] +=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 450){
			Blue_Tokan[z][1] += 500;
			Blue_Tokan[z][0] +=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 550){
			Blue_Tokan[z][1] += 600;
			Blue_Tokan[z][0] +=100;
			
		}
		blue_score+=6;
}


}


//Bluee Below Row
else if(Blue_Tokan[z][0]>=900 && Blue_Tokan[z][0]<=1500 && Blue_Tokan[z][1]>=600 && Blue_Tokan[z][1]<=700){

	if(dice_value==1){
		if(Blue_Tokan[z][0]== 950){
			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=100;
			
		}
		
		else
			Blue_Tokan[z][0] -= 100;
			
		blue_score+=1;	}
			
	else if(dice_value==2){
		if(Blue_Tokan[z][0]== 1050){
			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 950){
			Blue_Tokan[z][1] -= 200;
			Blue_Tokan[z][0] -= 100;
			
		}
		
		else
			Blue_Tokan[z][0] -= 200;
			
		blue_score+=2;	}
		
	else if(dice_value==3){
	
		if(Blue_Tokan[z][0]== 1150){
			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 1050){
			Blue_Tokan[z][1] -= 200;
			Blue_Tokan[z][0] -=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 950){
			Blue_Tokan[z][1] -= 300;
			Blue_Tokan[z][0] -=100;
			
		}
		
		else
			Blue_Tokan[z][0] -= 300;
			
		blue_score+=3;	}
	
	else if(dice_value==4){
	
		if(Blue_Tokan[z][0]== 1250){
			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=400;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 1150){
			Blue_Tokan[z][1] -= 200;
			Blue_Tokan[z][0] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 1050){
			Blue_Tokan[z][1] -= 300;
			Blue_Tokan[z][0] -=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 950){
			Blue_Tokan[z][1] -= 400;
			Blue_Tokan[z][0] -=100;
			
		}
		
		else
			Blue_Tokan[z][0] -= 400;
			
		blue_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Blue_Tokan[z][0]== 1350){
			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=500;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 1250){
			Blue_Tokan[z][1] -= 200;
			Blue_Tokan[z][0] -=400;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 1150){
			Blue_Tokan[z][1] -= 300;
			Blue_Tokan[z][0] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 1050){
			Blue_Tokan[z][1] -= 400;
			Blue_Tokan[z][0] -=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 950){
			Blue_Tokan[z][1] -= 500;
			Blue_Tokan[z][0] -=100;
			
		}
		
		else
			Blue_Tokan[z][0] -= 500;
			
		blue_score+=5;	}

	else if(dice_value==6){
	
		if(Blue_Tokan[z][0]== 1450){
			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=600;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 1350){
			Blue_Tokan[z][1] -= 200;
			Blue_Tokan[z][0] -=500;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 1250){
			Blue_Tokan[z][1] -= 300;
			Blue_Tokan[z][0] -=400;
		
		
		}
		
		else if(Blue_Tokan[z][0]== 1150){
			Blue_Tokan[z][1] -= 400;
			Blue_Tokan[z][0] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][0]== 1050){
			Blue_Tokan[z][1] -= 500;
			Blue_Tokan[z][0] -=200;
			
		}
		
		else if(Blue_Tokan[z][0]== 950){
			Blue_Tokan[z][1] -= 600;
			Blue_Tokan[z][0] -=100;
			
		}
		blue_score+=6;
}
}

//yellow Right Row
else if(Blue_Tokan[z][0]>=800 && Blue_Tokan[z][0]<=900 && Blue_Tokan[z][1]>=900 && Blue_Tokan[z][1]<=1500){

	if(dice_value==1){
		if(Blue_Tokan[z][1]== 950){
			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=100;
			
		}
		
		else
			Blue_Tokan[z][1] -= 100;
			
		blue_score+=1;	}
			
	else if(dice_value==2){
		if(Blue_Tokan[z][1]== 1050){
			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 950){
			Blue_Tokan[z][0] += 200;
			Blue_Tokan[z][1] -=100;
			
		}
		
		else
			Blue_Tokan[z][1] -= 200;
			
		blue_score+=2;	}
		
	else if(dice_value==3){
	
		if(Blue_Tokan[z][1]== 1150){
			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 1050){
			Blue_Tokan[z][0] += 200;
			Blue_Tokan[z][1] -=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 950){
			Blue_Tokan[z][0] += 300;
			Blue_Tokan[z][1] -=100;
			
		}
		
		else
			Blue_Tokan[z][1] -= 300;
			
		blue_score+=3;	}
	
	else if(dice_value==4){
	
		if(Blue_Tokan[z][1]== 1250){
			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=400;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 1150){
			Blue_Tokan[z][0] += 200;
			Blue_Tokan[z][1] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 1050){
			Blue_Tokan[z][0] += 300;
			Blue_Tokan[z][1] -=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 950){
			Blue_Tokan[z][0] += 400;
			Blue_Tokan[z][1] -=100;
			
		}
		
		else
			Blue_Tokan[z][1] -= 400;
			
		blue_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Blue_Tokan[z][1]== 1350){
			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=500;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 1250){
			Blue_Tokan[z][0] += 200;
			Blue_Tokan[z][1] -=400;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 1150){
			Blue_Tokan[z][0] += 300;
			Blue_Tokan[z][1] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 1050){
			Blue_Tokan[z][0] += 400;
			Blue_Tokan[z][1] -=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 950){
			Blue_Tokan[z][0] += 500;
			Blue_Tokan[z][1] -=100;
			
		}
		
		else
			Blue_Tokan[z][1] -= 500;
			
		blue_score+=5;	}

	else if(dice_value==6){
	
		if(Blue_Tokan[z][1]== 1450){
			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=600;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 1350){
			Blue_Tokan[z][0] += 200;
			Blue_Tokan[z][1] -=500;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 1250){
			Blue_Tokan[z][0] += 300;
			Blue_Tokan[z][1] -=400;
		
		
		}
		
		else if(Blue_Tokan[z][1]== 1150){
			Blue_Tokan[z][0] += 400;
			Blue_Tokan[z][1] -=300;
		
		
		}
	
		else if(Blue_Tokan[z][1]== 1050){
			Blue_Tokan[z][0] += 500;
			Blue_Tokan[z][1] -=200;
			
		}
		
		else if(Blue_Tokan[z][1]== 950){
			Blue_Tokan[z][0] += 600;
			Blue_Tokan[z][1] -=100;
			
		}
		blue_score+=6;
}


}



//red Right Row

else if(Blue_Tokan[z][0]>=800 && Blue_Tokan[z][0]<=900 && Blue_Tokan[z][1]>=0 && Blue_Tokan[z][1]<=600){

		if(dice_value==1){
			if(Blue_Tokan[z][1]== 50){
				Blue_Tokan[z][0] -= 100;
			}
			
			else
				Blue_Tokan[z][1] -= 100;
				
			blue_score+=1;	}
				
		else if(dice_value==2){
			if(Blue_Tokan[z][1]== 50){
				Blue_Tokan[z][0] -= 200;
				
			}
			
			else if(Blue_Tokan[z][1]== 150){
				Blue_Tokan[z][0] -= 100;
				Blue_Tokan[z][1] -=100;
				
			}
			
			else
				Blue_Tokan[z][1] -= 200;
				
			blue_score+=2;	}
			
		else if(dice_value==3){
		
			if(Blue_Tokan[z][1]== 50){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] += 100;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 150){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] -=100;
				
			}
			
			else if(Blue_Tokan[z][1]== 250){
				Blue_Tokan[z][0] -=100;
				Blue_Tokan[z][1] -=200;
				
			}
			
			else
				Blue_Tokan[z][1] -= 300;
				
			blue_score+=3;	}
		
		else if(dice_value==4){
		
			if(Blue_Tokan[z][1]== 50){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] +=200;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 150){
				Blue_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 250){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] -=200;
				
			}
			
			else if(Blue_Tokan[z][1]== 350){
				Blue_Tokan[z][0] -= 100;
				Blue_Tokan[z][1] -=300;
				
			}
			
			else
				Blue_Tokan[z][1] -= 400;
				
			blue_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Blue_Tokan[z][1]== 50){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] += 300;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 150){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] += 100;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 250){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 350){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] -= 300;
				
			}
			
			else if(Blue_Tokan[z][1]== 450){
				Blue_Tokan[z][0] -= 100;
				Blue_Tokan[z][1] -=400;
				
			}
			
			else
				Blue_Tokan[z][1] -= 500;
				
			blue_score+=5;	}

		else if(dice_value==6){
		
			if(Blue_Tokan[z][1]== 50){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] += 400;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 150){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] += 200;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 250){
				Blue_Tokan[z][0] -= 200;

			}
			
			else if(Blue_Tokan[z][1]== 350){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 450){
				Blue_Tokan[z][0] -= 200;
				Blue_Tokan[z][1] -= 400;
				
			}
			
			else if(Blue_Tokan[z][1]== 550){
				Blue_Tokan[z][0] -= 100;
				Blue_Tokan[z][1] -= 500;
				
			}
			blue_score+=6;
	}

}


//green Down Row

else if(Blue_Tokan[z][0]>=0 && Blue_Tokan[z][0]<=600 && Blue_Tokan[z][1]>=600 && Blue_Tokan[z][1]<=700){

		if(dice_value==1){
			if(Blue_Tokan[z][0]== 50){
				Blue_Tokan[z][1] += 100;
			}
			
			else
				Blue_Tokan[z][0] -= 100;
				
			blue_score+=1;	}
				
		else if(dice_value==2){
			if(Blue_Tokan[z][0]== 50){
				Blue_Tokan[z][1] += 200;
				
			}
			
			else if(Blue_Tokan[z][0]== 150){
				Blue_Tokan[z][1] += 100;
				Blue_Tokan[z][0] -=100;
				
			}
			
			else
				Blue_Tokan[z][0] -= 200;
				
			blue_score+=2;	}
			
		else if(dice_value==3){
		
			if(Blue_Tokan[z][0]== 50){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] += 100;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 150){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] -=100;
				
			}
			
			else if(Blue_Tokan[z][0]== 250){
				Blue_Tokan[z][1] +=100;
				Blue_Tokan[z][0] -=200;
				
			}
			
			else
				Blue_Tokan[z][0] -= 300;
				
			blue_score+=3;	}
		
		else if(dice_value==4){
		
			if(Blue_Tokan[z][0]== 50){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] +=200;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 150){
				Blue_Tokan[z][1] += 200;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 250){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] -=200;
				
			}
			
			else if(Blue_Tokan[z][0]== 350){
				Blue_Tokan[z][1] += 100;
				Blue_Tokan[z][0] -=300;
				
			}
			
			else
				Blue_Tokan[z][0] -= 400;
				
			blue_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Blue_Tokan[z][0]== 50){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] += 300;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 150){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] += 100;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 250){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] -= 100;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 350){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] -= 300;
				
			}
			
			else if(Blue_Tokan[z][0]== 450){
				Blue_Tokan[z][1] += 100;
				Blue_Tokan[z][0] -=400;
				
			}
			
			else
				Blue_Tokan[z][0] -= 500;
				
			blue_score+=5;	}

		else if(dice_value==6){
		
			if(Blue_Tokan[z][0]== 50){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] += 400;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 150){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] += 200;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 250){
				Blue_Tokan[z][1] += 200;

			}
			
			else if(Blue_Tokan[z][0]== 350){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 450){
				Blue_Tokan[z][1] += 200;
				Blue_Tokan[z][0] -= 400;
				
			}
			
			else if(Blue_Tokan[z][0]== 550){
				Blue_Tokan[z][1] += 100;
				Blue_Tokan[z][0] -= 500;
				
			}
			blue_score+=6;
	}

}


//Bluee Up Row

else if(Blue_Tokan[z][0]>=900 && Blue_Tokan[z][0]<=1500 && Blue_Tokan[z][1]>=800 && Blue_Tokan[z][1]<=900){

	if(blue_lock==true){
		if(dice_value==1){
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
			}
			
			else
				Blue_Tokan[z][0] += 100;
				
			blue_score+=1;	}
				
		else if(dice_value==2){
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 200;
				
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] +=100;
				
			}
			
			else
				Blue_Tokan[z][0] += 200;
				
			blue_score+=2;	}
			
		else if(dice_value==3){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] +=100;
				
			}
			
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -=100;
				Blue_Tokan[z][0] +=200;
				
			}
			
			else
				Blue_Tokan[z][0] += 300;
				
			blue_score+=3;	}
		
		else if(dice_value==4){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] -=200;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] +=200;
				
			}
			
			else if(Blue_Tokan[z][0] == 1150){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] +=300;
				
			}
			
			else
				Blue_Tokan[z][0] += 400;
				
			blue_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] -= 300;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] -= 100;
		
			
			}
			
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] += 100;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1150){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] += 300;
				
			}
			
			else if(Blue_Tokan[z][0]== 1050){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] +=400;
				
			}
			
			else
				Blue_Tokan[z][0] += 500;
				
			blue_score+=5;	}

		else if(dice_value==6){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] -= 400;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] -= 200;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -= 200;
			}
			
			else if(Blue_Tokan[z][0]== 1150){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] += 200;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1050){
				Blue_Tokan[z][1] -= 200;
				Blue_Tokan[z][0] += 400;
				
			}
			
			else if(Blue_Tokan[z][0]== 950){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] += 500;
				
			}
			blue_score+=6;
	}
		}
		
	else if(blue_lock==false){
		if(dice_value==1){
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
			}
			
			else
				Blue_Tokan[z][0] += 100;
				
				}
				
		else if(dice_value==2){
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 100;
				
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] +=100;
				
			}
			
			else
				Blue_Tokan[z][0] += 200;
				
				}
			
		else if(dice_value==3){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 100;
				
			}
			
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -=100;
				Blue_Tokan[z][0] +=200;
				
			}
			
			else
				Blue_Tokan[z][0] += 300;
				
				}
		
		else if(dice_value==4){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -=300;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 100;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] += 100;
				
			}
			
			else if(Blue_Tokan[z][0]== 1150){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] +=300;
				
			}
			
			else
				Blue_Tokan[z][0] += 400;
				
				}
				
				
		else if(dice_value==5){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 400;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 200;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -= 100;

			}
		
			else if(Blue_Tokan[z][0]== 1150){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] += 200;
				
			}
			
			else if(Blue_Tokan[z][0]== 1050){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] +=400;
				
			}
			
			else
				Blue_Tokan[z][0] += 500;
				
				}

		else if(dice_value==6){
		
			if(Blue_Tokan[z][0]== 1450){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 500;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1350){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 300;
			
			
			}
			
			else if(Blue_Tokan[z][0]== 1250){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] -= 100;

			}
			
			else if(Blue_Tokan[z][0]== 1150){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] += 100;
			
			
			}
		
			else if(Blue_Tokan[z][0]== 1050){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] += 300;
				
			}
			
			else if(Blue_Tokan[z][0]== 950){
				Blue_Tokan[z][1] -= 100;
				Blue_Tokan[z][0] += 500;
				
			}
			
	}
		}


}



//yellow Left Row

else if(Blue_Tokan[z][0]>=600 && Blue_Tokan[z][0]<=700 && Blue_Tokan[z][1]>=900 && Blue_Tokan[z][1]<=1500){

		if(dice_value==1){
			if(Blue_Tokan[z][1]== 1450){
				Blue_Tokan[z][0] += 100;
			}
			
			else
				Blue_Tokan[z][1] += 100;
				
			blue_score+=1;	}
				
		else if(dice_value==2){
			if(Blue_Tokan[z][1]== 1450){
				Blue_Tokan[z][0] += 200;
				
			}
			
			else if(Blue_Tokan[z][1]== 1350){
				Blue_Tokan[z][0] += 100;
				Blue_Tokan[z][1] +=100;
				
			}
			
			else
				Blue_Tokan[z][1] += 200;
				
			blue_score+=2;	}
			
		else if(dice_value==3){
		
			if(Blue_Tokan[z][1]== 1450){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 1350){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] +=100;
				
			}
			
			else if(Blue_Tokan[z][1]== 1250){
				Blue_Tokan[z][0] +=100;
				Blue_Tokan[z][1] +=200;
				
			}
			
			else
				Blue_Tokan[z][1] += 300;
				
			blue_score+=3;	}
		
		else if(dice_value==4){
		
			if(Blue_Tokan[z][1]== 1450){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] -=200;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 1350){
				Blue_Tokan[z][0] += 200;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 1250){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] +=200;
				
			}
			
			else if(Blue_Tokan[z][1] == 1150){
				Blue_Tokan[z][0] += 100;
				Blue_Tokan[z][1] +=300;
				
			}
			
			else
				Blue_Tokan[z][1] += 400;
				
			blue_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Blue_Tokan[z][1]== 1450){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] -= 300;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 1350){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] -= 100;
		
			
			}
			
			else if(Blue_Tokan[z][1]== 1250){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] += 100;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 1150){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] += 300;
				
			}
			
			else if(Blue_Tokan[z][1]== 1050){
				Blue_Tokan[z][0] += 100;
				Blue_Tokan[z][1] +=400;
				
			}
			
			else
				Blue_Tokan[z][1] += 500;
				
			blue_score+=5;	}

		else if(dice_value==6){
		
			if(Blue_Tokan[z][1]== 1450){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] -= 400;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 1350){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] -= 200;
			
			
			}
			
			else if(Blue_Tokan[z][1]== 1250){
				Blue_Tokan[z][0] += 200;

			}
			
			else if(Blue_Tokan[z][1]== 1150){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] += 200;
			
			
			}
		
			else if(Blue_Tokan[z][1]== 1050){
				Blue_Tokan[z][0] += 200;
				Blue_Tokan[z][1] += 400;
				
			}
			
			else if(Blue_Tokan[z][1]== 950){
				Blue_Tokan[z][0] += 100;
				Blue_Tokan[z][1] += 500;
				
			}
			blue_score+=6;
	}

}
//red middle row
else if(Blue_Tokan[z][0]>=700 && Blue_Tokan[z][0]<=800 && Blue_Tokan[z][1]>=0 && Blue_Tokan[z][1]<=600){

	if(dice_value==1){
			Blue_Tokan[z][0]-=100;
			blue_score+=1;}
			
	else if(dice_value==2){

			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=100;

			blue_score+=2;}
		
	else if(dice_value==3){

			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=200;

			blue_score+=3;}
			
	else if(dice_value==4){

			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=300;

			blue_score+=4;}
			
	else if(dice_value==5){

			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=400;

			blue_score+=5;}
			
	else if(dice_value==6){

			Blue_Tokan[z][0] -= 100;
			Blue_Tokan[z][1] +=500;

			blue_score+=6;}


}

//yellow middle row

else if(Blue_Tokan[z][0]>=700 && Blue_Tokan[z][0]<=800 && Blue_Tokan[z][1]>=900 && Blue_Tokan[z][1]<=1500){

	if(dice_value==1){
			Blue_Tokan[z][0]+=100;
			blue_score+=1;}
			
	else if(dice_value==2){

			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=100;

			blue_score+=2;}
		
	else if(dice_value==3){

			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=200;

			blue_score+=3;}
			
	else if(dice_value==4){

			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=300;

			blue_score+=4;}
			
	else if(dice_value==5){

			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=400;

			blue_score+=5;}
			
	else if(dice_value==6){

			Blue_Tokan[z][0] += 100;
			Blue_Tokan[z][1] -=500;

			blue_score+=6;}



}

//bluee middle row

else if(Blue_Tokan[z][0]>=900 && Blue_Tokan[z][0]<=1500 && Blue_Tokan[z][1]>=700 && Blue_Tokan[z][1]<=800){

	if(blue_lock==false){
	
		if(dice_value==1){
			
			Blue_Tokan[z][0]-=100;
			blue_score+=1;	}
				
		else if(dice_value==2){
			
			if(Blue_Tokan[z][0] >= 1000){
				Blue_Tokan[z][0] -= 200;
				blue_score+=2;
			}
		
				}
			
		else if(dice_value==3){
		
			if(Blue_Tokan[z][0] >= 1100){
				Blue_Tokan[z][0] -= 300;
				blue_score+=3;
			}
				}
		
		else if(dice_value==4){
		
			if(Blue_Tokan[z][0] >= 1200){
				Blue_Tokan[z][0] -=400;
			blue_score+=4;
			
			}
				}
				
	
		else if(dice_value==5){
		
			if(Blue_Tokan[z][0] >= 1300){
				Blue_Tokan[z][0] -= 500;
				blue_score+=5;
			}
				}

		else if(dice_value==6){
		
			if(Blue_Tokan[z][0] >= 1400){
				Blue_Tokan[z][0] -= 600;
				blue_score+=6;
			
			}	
				}
				}
		
		
	else if(blue_lock==true){
	
	
		if(dice_value==1){
			Blue_Tokan[z][1]-=100;
			blue_score+=1;}
			
	else if(dice_value==2){

			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=100;

			blue_score+=2;}
		
	else if(dice_value==3){

			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=200;

			blue_score+=3;}
			
	else if(dice_value==4){

			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=300;

			blue_score+=4;}
			
	else if(dice_value==5){

			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=400;

			blue_score+=5;}
			
	else if(dice_value==6){

			Blue_Tokan[z][1] -= 100;
			Blue_Tokan[z][0] -=500;

			blue_score+=6;}


	}	
		

}


//green middle row


else if(Blue_Tokan[z][0]>=0 && Blue_Tokan[z][0]<=600 && Blue_Tokan[z][1]>=700 && Blue_Tokan[z][1]<=800){

	if(dice_value==1){
			Blue_Tokan[z][1]+=100;
			blue_score+=1;}
			
	else if(dice_value==2){

			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=100;

			blue_score+=2;}
		
	else if(dice_value==3){

			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=200;

			blue_score+=3;}
			
	else if(dice_value==4){

			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=300;

			blue_score+=4;}
			
	else if(dice_value==5){

			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=400;

			blue_score+=5;}
			
	else if(dice_value==6){

			Blue_Tokan[z][1] += 100;
			Blue_Tokan[z][0] +=500;

			blue_score+=6;}


	}	
		


}



void Yellow_Tokan_move(int z){
//home
if(Yellow_Tokan[z][0]>=900&&Yellow_Tokan[z][0]<=1500 && Yellow_Tokan[z][1] >=900 && Yellow_Tokan[z][1] <=1500 && dice_value==6){

	Yellow_Tokan[z][0]=yhx;
	Yellow_Tokan[z][1]=yhy;
	yellow_score+=6;
}

//red Left Row
else if(Yellow_Tokan[z][0]>=600 && Yellow_Tokan[z][0]<=700 && Yellow_Tokan[z][1]>=0 && Yellow_Tokan[z][1]<=600){

	if(dice_value==1){
		if(Yellow_Tokan[z][1]== 550){
			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=100;
			
		}
		
		else
			Yellow_Tokan[z][1] += 100;
			
		yellow_score+=1;	}
			
	else if(dice_value==2){
		if(Yellow_Tokan[z][1]== 450){
			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 550){
			Yellow_Tokan[z][0] -= 200;
			Yellow_Tokan[z][1] +=100;
			
		}
		
		else
			Yellow_Tokan[z][1] += 200;
			
		yellow_score+=2;	}
		
	else if(dice_value==3){
	
		if(Yellow_Tokan[z][1]== 350){
			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 450){
			Yellow_Tokan[z][0] -= 200;
			Yellow_Tokan[z][1] +=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 550){
			Yellow_Tokan[z][0] -= 300;
			Yellow_Tokan[z][1] +=100;
			
		}
		
		else
			Yellow_Tokan[z][1] += 300;
			
		yellow_score+=3;	}
	
	else if(dice_value==4){
	
		if(Yellow_Tokan[z][1]== 250){
			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=400;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 350){
			Yellow_Tokan[z][0] -= 200;
			Yellow_Tokan[z][1] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 450){
			Yellow_Tokan[z][0] -= 300;
			Yellow_Tokan[z][1] +=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 550){
			Yellow_Tokan[z][0] -= 400;
			Yellow_Tokan[z][1] +=100;
			
		}
		
		else
			Yellow_Tokan[z][1] += 400;
			
		yellow_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Yellow_Tokan[z][1]== 150){
			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=500;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 250){
			Yellow_Tokan[z][0] -= 200;
			Yellow_Tokan[z][1] +=400;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 350){
			Yellow_Tokan[z][0] -= 300;
			Yellow_Tokan[z][1] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 450){
			Yellow_Tokan[z][0] -= 400;
			Yellow_Tokan[z][1] +=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 550){
			Yellow_Tokan[z][0] -= 500;
			Yellow_Tokan[z][1] +=100;
			
		}
		
		else
			Yellow_Tokan[z][1] += 500;
			
		yellow_score+=5;	}

	else if(dice_value==6){
	
		if(Yellow_Tokan[z][1]== 50){
			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=600;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 150){
			Yellow_Tokan[z][0] -= 200;
			Yellow_Tokan[z][1] +=500;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 250){
			Yellow_Tokan[z][0] -= 300;
			Yellow_Tokan[z][1] +=400;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 350){
			Yellow_Tokan[z][0] -= 400;
			Yellow_Tokan[z][1] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 450){
			Yellow_Tokan[z][0] -= 500;
			Yellow_Tokan[z][1] +=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 550){
			Yellow_Tokan[z][0] -= 600;
			Yellow_Tokan[z][1] +=100;
			
		}
		yellow_score+=6;
}


}

//green Above Row
else if(Yellow_Tokan[z][0]>=0 && Yellow_Tokan[z][0]<=600 && Yellow_Tokan[z][1]>=800 && Yellow_Tokan[z][1]<=900){

	if(dice_value==1){
		if(Yellow_Tokan[z][0]== 550){
			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=100;
			
		}
		
		else
			Yellow_Tokan[z][0] += 100;
			
		yellow_score+=1;	}
			
	else if(dice_value==2){
		if(Yellow_Tokan[z][0]== 450){
			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=200;
			
		}
		
		else if(Yellow_Tokan[z][0] == 550){
			Yellow_Tokan[z][1] += 200;
			Yellow_Tokan[z][0] +=100;
			
		}
		
		else
			Yellow_Tokan[z][0] += 200;
			
		yellow_score+=2;	}
		
	else if(dice_value==3){
	
		if(Yellow_Tokan[z][0]== 350){
			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 450){
			Yellow_Tokan[z][1] += 200;
			Yellow_Tokan[z][0] +=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 550){
			Yellow_Tokan[z][1] += 300;
			Yellow_Tokan[z][0] +=100;
			
		}
		
		else
			Yellow_Tokan[z][0] += 300;
			
		yellow_score+=3;	}
	
	else if(dice_value==4){
	
		if(Yellow_Tokan[z][0]== 250){
			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=400;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 350){
			Yellow_Tokan[z][1] += 200;
			Yellow_Tokan[z][0] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 450){
			Yellow_Tokan[z][1] += 300;
			Yellow_Tokan[z][0] +=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 550){
			Yellow_Tokan[z][1] += 400;
			Yellow_Tokan[z][0] +=100;
			
		}
		
		else
			Yellow_Tokan[z][0] += 400;
			
		yellow_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Yellow_Tokan[z][0]== 150){
			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=500;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 250){
			Yellow_Tokan[z][1] += 200;
			Yellow_Tokan[z][0] +=400;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 350){
			Yellow_Tokan[z][1] += 300;
			Yellow_Tokan[z][0] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 450){
			Yellow_Tokan[z][1] += 400;
			Yellow_Tokan[z][0] +=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 550){
			Yellow_Tokan[z][1] += 500;
			Yellow_Tokan[z][0] +=100;
			
		}
		
		else
			Yellow_Tokan[z][0] += 500;
			
		yellow_score+=5;	}

	else if(dice_value==6){
	
		if(Yellow_Tokan[z][0]== 50){
			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=600;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 150){
			Yellow_Tokan[z][1] += 200;
			Yellow_Tokan[z][0] +=500;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 250){
			Yellow_Tokan[z][1] += 300;
			Yellow_Tokan[z][0] +=400;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 350){
			Yellow_Tokan[z][1] += 400;
			Yellow_Tokan[z][0] +=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 450){
			Yellow_Tokan[z][1] += 500;
			Yellow_Tokan[z][0] +=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 550){
			Yellow_Tokan[z][1] += 600;
			Yellow_Tokan[z][0] +=100;
			
		}
		yellow_score+=6;
}


}


//blue Below Row
else if(Yellow_Tokan[z][0]>=900 && Yellow_Tokan[z][0]<=1500 && Yellow_Tokan[z][1]>=600 && Yellow_Tokan[z][1]<=700){

	if(dice_value==1){
		if(Yellow_Tokan[z][0]== 950){
			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=100;
			
		}
		
		else
			Yellow_Tokan[z][0] -= 100;
			
		yellow_score+=1;	}
			
	else if(dice_value==2){
		if(Yellow_Tokan[z][0]== 1050){
			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 950){
			Yellow_Tokan[z][1] -= 200;
			Yellow_Tokan[z][0] -= 100;
			
		}
		
		else
			Yellow_Tokan[z][0] -= 200;
			
		yellow_score+=2;	}
		
	else if(dice_value==3){
	
		if(Yellow_Tokan[z][0]== 1150){
			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 1050){
			Yellow_Tokan[z][1] -= 200;
			Yellow_Tokan[z][0] -=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 950){
			Yellow_Tokan[z][1] -= 300;
			Yellow_Tokan[z][0] -=100;
			
		}
		
		else
			Yellow_Tokan[z][0] -= 300;
			
		yellow_score+=3;	}
	
	else if(dice_value==4){
	
		if(Yellow_Tokan[z][0]== 1250){
			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=400;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 1150){
			Yellow_Tokan[z][1] -= 200;
			Yellow_Tokan[z][0] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 1050){
			Yellow_Tokan[z][1] -= 300;
			Yellow_Tokan[z][0] -=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 950){
			Yellow_Tokan[z][1] -= 400;
			Yellow_Tokan[z][0] -=100;
			
		}
		
		else
			Yellow_Tokan[z][0] -= 400;
			
		yellow_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Yellow_Tokan[z][0]== 1350){
			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=500;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 1250){
			Yellow_Tokan[z][1] -= 200;
			Yellow_Tokan[z][0] -=400;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 1150){
			Yellow_Tokan[z][1] -= 300;
			Yellow_Tokan[z][0] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 1050){
			Yellow_Tokan[z][1] -= 400;
			Yellow_Tokan[z][0] -=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 950){
			Yellow_Tokan[z][1] -= 500;
			Yellow_Tokan[z][0] -=100;
			
		}
		
		else
			Yellow_Tokan[z][0] -= 500;
			
		yellow_score+=5;	}

	else if(dice_value==6){
	
		if(Yellow_Tokan[z][0]== 1450){
			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=600;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 1350){
			Yellow_Tokan[z][1] -= 200;
			Yellow_Tokan[z][0] -=500;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 1250){
			Yellow_Tokan[z][1] -= 300;
			Yellow_Tokan[z][0] -=400;
		
		
		}
		
		else if(Yellow_Tokan[z][0]== 1150){
			Yellow_Tokan[z][1] -= 400;
			Yellow_Tokan[z][0] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][0]== 1050){
			Yellow_Tokan[z][1] -= 500;
			Yellow_Tokan[z][0] -=200;
			
		}
		
		else if(Yellow_Tokan[z][0]== 950){
			Yellow_Tokan[z][1] -= 600;
			Yellow_Tokan[z][0] -=100;
			
		}
		yellow_score+=6;
}
}

//yellow Right Row
else if(Yellow_Tokan[z][0]>=800 && Yellow_Tokan[z][0]<=900 && Yellow_Tokan[z][1]>=900 && Yellow_Tokan[z][1]<=1500){

	if(dice_value==1){
		if(Yellow_Tokan[z][1]== 950){
			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=100;
			
		}
		
		else
			Yellow_Tokan[z][1] -= 100;
			
		yellow_score+=1;	}
			
	else if(dice_value==2){
		if(Yellow_Tokan[z][1]== 1050){
			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 950){
			Yellow_Tokan[z][0] += 200;
			Yellow_Tokan[z][1] -=100;
			
		}
		
		else
			Yellow_Tokan[z][1] -= 200;
			
		yellow_score+=2;	}
		
	else if(dice_value==3){
	
		if(Yellow_Tokan[z][1]== 1150){
			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 1050){
			Yellow_Tokan[z][0] += 200;
			Yellow_Tokan[z][1] -=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 950){
			Yellow_Tokan[z][0] += 300;
			Yellow_Tokan[z][1] -=100;
			
		}
		
		else
			Yellow_Tokan[z][1] -= 300;
			
		yellow_score+=3;	}
	
	else if(dice_value==4){
	
		if(Yellow_Tokan[z][1]== 1250){
			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=400;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 1150){
			Yellow_Tokan[z][0] += 200;
			Yellow_Tokan[z][1] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 1050){
			Yellow_Tokan[z][0] += 300;
			Yellow_Tokan[z][1] -=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 950){
			Yellow_Tokan[z][0] += 400;
			Yellow_Tokan[z][1] -=100;
			
		}
		
		else
			Yellow_Tokan[z][1] -= 400;
			
		yellow_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Yellow_Tokan[z][1]== 1350){
			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=500;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 1250){
			Yellow_Tokan[z][0] += 200;
			Yellow_Tokan[z][1] -=400;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 1150){
			Yellow_Tokan[z][0] += 300;
			Yellow_Tokan[z][1] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 1050){
			Yellow_Tokan[z][0] += 400;
			Yellow_Tokan[z][1] -=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 950){
			Yellow_Tokan[z][0] += 500;
			Yellow_Tokan[z][1] -=100;
			
		}
		
		else
			Yellow_Tokan[z][1] -= 500;
			
		yellow_score+=5;	}

	else if(dice_value==6){
	
		if(Yellow_Tokan[z][1]== 1450){
			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=600;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 1350){
			Yellow_Tokan[z][0] += 200;
			Yellow_Tokan[z][1] -=500;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 1250){
			Yellow_Tokan[z][0] += 300;
			Yellow_Tokan[z][1] -=400;
		
		
		}
		
		else if(Yellow_Tokan[z][1]== 1150){
			Yellow_Tokan[z][0] += 400;
			Yellow_Tokan[z][1] -=300;
		
		
		}
	
		else if(Yellow_Tokan[z][1]== 1050){
			Yellow_Tokan[z][0] += 500;
			Yellow_Tokan[z][1] -=200;
			
		}
		
		else if(Yellow_Tokan[z][1]== 950){
			Yellow_Tokan[z][0] += 600;
			Yellow_Tokan[z][1] -=100;
			
		}
		yellow_score+=6;
}


}



//red Right Row

else if(Yellow_Tokan[z][0]>=800 && Yellow_Tokan[z][0]<=900 && Yellow_Tokan[z][1]>=0 && Yellow_Tokan[z][1]<=600){


		if(dice_value==1){
			if(Yellow_Tokan[z][1]== 50){
				Yellow_Tokan[z][0] -= 100;
			}
			
			else
				Yellow_Tokan[z][1] -= 100;
				
			yellow_score+=1;	}
				
		else if(dice_value==2){
			if(Yellow_Tokan[z][1]== 50){
				Yellow_Tokan[z][0] -= 200;
				
			}
			
			else if(Yellow_Tokan[z][1]== 150){
				Yellow_Tokan[z][0] -= 100;
				Yellow_Tokan[z][1] -=100;
				
			}
			
			else
				Yellow_Tokan[z][1] -= 200;
				
			yellow_score+=2;	}
			
		else if(dice_value==3){
		
			if(Yellow_Tokan[z][1]== 50){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] += 100;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 150){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] -=100;
				
			}
			
			else if(Yellow_Tokan[z][1]== 250){
				Yellow_Tokan[z][0] -=100;
				Yellow_Tokan[z][1] -=200;
				
			}
			
			else
				Yellow_Tokan[z][1] -= 300;
				
			yellow_score+=3;	}
		
		else if(dice_value==4){
		
			if(Yellow_Tokan[z][1]== 50){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] +=200;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 150){
				Yellow_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 250){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] -=200;
				
			}
			
			else if(Yellow_Tokan[z][1]== 350){
				Yellow_Tokan[z][0] -= 100;
				Yellow_Tokan[z][1] -=300;
				
			}
			
			else
				Yellow_Tokan[z][1] -= 400;
				
			yellow_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Yellow_Tokan[z][1]== 50){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] += 300;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 150){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] += 100;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 250){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 350){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] -= 300;
				
			}
			
			else if(Yellow_Tokan[z][1]== 450){
				Yellow_Tokan[z][0] -= 100;
				Yellow_Tokan[z][1] -=400;
				
			}
			
			else
				Yellow_Tokan[z][1] -= 500;
				
			yellow_score+=5;	}

		else if(dice_value==6){
		
			if(Yellow_Tokan[z][1]== 50){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] += 400;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 150){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] += 200;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 250){
				Yellow_Tokan[z][0] -= 200;

			}
			
			else if(Yellow_Tokan[z][1]== 350){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 450){
				Yellow_Tokan[z][0] -= 200;
				Yellow_Tokan[z][1] -= 400;
				
			}
			
			else if(Yellow_Tokan[z][1]== 550){
				Yellow_Tokan[z][0] -= 100;
				Yellow_Tokan[z][1] -= 500;
				
			}
			yellow_score+=6;
	}

}


//green Down Row

else if(Yellow_Tokan[z][0]>=0 && Yellow_Tokan[z][0]<=600 && Yellow_Tokan[z][1]>=600 && Yellow_Tokan[z][1]<=700){

		if(dice_value==1){
			if(Yellow_Tokan[z][0]== 50){
				Yellow_Tokan[z][1] += 100;
			}
			
			else
				Yellow_Tokan[z][0] -= 100;
				
			yellow_score+=1;	}
				
		else if(dice_value==2){
			if(Yellow_Tokan[z][0]== 50){
				Yellow_Tokan[z][1] += 200;
				
			}
			
			else if(Yellow_Tokan[z][0]== 150){
				Yellow_Tokan[z][1] += 100;
				Yellow_Tokan[z][0] -=100;
				
			}
			
			else
				Yellow_Tokan[z][0] -= 200;
				
			yellow_score+=2;	}
			
		else if(dice_value==3){
		
			if(Yellow_Tokan[z][0]== 50){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] += 100;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 150){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] -=100;
				
			}
			
			else if(Yellow_Tokan[z][0]== 250){
				Yellow_Tokan[z][1] +=100;
				Yellow_Tokan[z][0] -=200;
				
			}
			
			else
				Yellow_Tokan[z][0] -= 300;
				
			yellow_score+=3;	}
		
		else if(dice_value==4){
		
			if(Yellow_Tokan[z][0]== 50){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] +=200;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 150){
				Yellow_Tokan[z][1] += 200;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 250){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] -=200;
				
			}
			
			else if(Yellow_Tokan[z][0]== 350){
				Yellow_Tokan[z][1] += 100;
				Yellow_Tokan[z][0] -=300;
				
			}
			
			else
				Yellow_Tokan[z][0] -= 400;
				
			yellow_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Yellow_Tokan[z][0]== 50){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] += 300;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 150){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] += 100;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 250){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] -= 100;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 350){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] -= 300;
				
			}
			
			else if(Yellow_Tokan[z][0]== 450){
				Yellow_Tokan[z][1] += 100;
				Yellow_Tokan[z][0] -=400;
				
			}
			
			else
				Yellow_Tokan[z][0] -= 500;
				
			yellow_score+=5;	}

		else if(dice_value==6){
		
			if(Yellow_Tokan[z][0]== 50){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] += 400;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 150){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] += 200;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 250){
				Yellow_Tokan[z][1] += 200;

			}
			
			else if(Yellow_Tokan[z][0]== 350){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 450){
				Yellow_Tokan[z][1] += 200;
				Yellow_Tokan[z][0] -= 400;
				
			}
			
			else if(Yellow_Tokan[z][0]== 550){
				Yellow_Tokan[z][1] += 100;
				Yellow_Tokan[z][0] -= 500;
				
			}
			yellow_score+=6;
	}

}


//blue Up Row

else if(Yellow_Tokan[z][0]>=900 && Yellow_Tokan[z][0]<=1500 && Yellow_Tokan[z][1]>=800 && Yellow_Tokan[z][1]<=900){


		if(dice_value==1){
			if(Yellow_Tokan[z][0]== 1450){
				Yellow_Tokan[z][1] -= 100;
			}
			
			else
				Yellow_Tokan[z][0] += 100;
				
			yellow_score+=1;	}
				
		else if(dice_value==2){
			if(Yellow_Tokan[z][0]== 1450){
				Yellow_Tokan[z][1] -= 200;
				
			}
			
			else if(Yellow_Tokan[z][0]== 1350){
				Yellow_Tokan[z][1] -= 100;
				Yellow_Tokan[z][0] +=100;
				
			}
			
			else
				Yellow_Tokan[z][0] += 200;
				
			yellow_score+=2;	}
			
		else if(dice_value==3){
		
			if(Yellow_Tokan[z][0]== 1450){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 1350){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] +=100;
				
			}
			
			else if(Yellow_Tokan[z][0]== 1250){
				Yellow_Tokan[z][1] -=100;
				Yellow_Tokan[z][0] +=200;
				
			}
			
			else
				Yellow_Tokan[z][0] += 300;
				
			yellow_score+=3;	}
		
		else if(dice_value==4){
		
			if(Yellow_Tokan[z][0]== 1450){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] -=200;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 1350){
				Yellow_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 1250){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] +=200;
				
			}
			
			else if(Yellow_Tokan[z][0] == 1150){
				Yellow_Tokan[z][1] -= 100;
				Yellow_Tokan[z][0] +=300;
				
			}
			
			else
				Yellow_Tokan[z][0] += 400;
				
			yellow_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Yellow_Tokan[z][0]== 1450){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] -= 300;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 1350){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] -= 100;
		
			
			}
			
			else if(Yellow_Tokan[z][0]== 1250){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] += 100;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 1150){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] += 300;
				
			}
			
			else if(Yellow_Tokan[z][0]== 1050){
				Yellow_Tokan[z][1] -= 100;
				Yellow_Tokan[z][0] +=400;
				
			}
			
			else
				Yellow_Tokan[z][0] += 500;
				
			yellow_score+=5;	}

		else if(dice_value==6){
		
			if(Yellow_Tokan[z][0]== 1450){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] -= 400;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 1350){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] -= 200;
			
			
			}
			
			else if(Yellow_Tokan[z][0]== 1250){
				Yellow_Tokan[z][1] -= 200;
			}
			
			else if(Yellow_Tokan[z][0]== 1150){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] += 200;
			
			
			}
		
			else if(Yellow_Tokan[z][0]== 1050){
				Yellow_Tokan[z][1] -= 200;
				Yellow_Tokan[z][0] += 400;
				
			}
			
			else if(Yellow_Tokan[z][0]== 950){
				Yellow_Tokan[z][1] -= 100;
				Yellow_Tokan[z][0] += 500;
				
			}
			yellow_score+=6;
	}

}



//yellow Left Row

else if(Yellow_Tokan[z][0]>=600 && Yellow_Tokan[z][0]<=700 && Yellow_Tokan[z][1]>=900 && Yellow_Tokan[z][1]<=1500){

	if(yellow_lock==true){
		if(dice_value==1){
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
			}
			
			else
				Yellow_Tokan[z][1] += 100;
				
			yellow_score+=1;	}
				
		else if(dice_value==2){
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 200;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] +=100;
				
			}
			
			else
				Yellow_Tokan[z][1] += 200;
				
			yellow_score+=2;	}
			
		else if(dice_value==3){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] +=100;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] +=100;
				Yellow_Tokan[z][1] +=200;
				
			}
			
			else
				Yellow_Tokan[z][1] += 300;
				
			yellow_score+=3;	}
		
		else if(dice_value==4){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] -=200;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 200;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] +=200;
				
			}
			
			else if(Yellow_Tokan[z][1] == 1150){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] +=300;
				
			}
			
			else
				Yellow_Tokan[z][1] += 400;
				
			yellow_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] -= 300;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] -= 100;
		
			
			}
			
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] += 100;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1150){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] += 300;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1050){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] +=400;
				
			}
			
			else
				Yellow_Tokan[z][1] += 500;
				
			yellow_score+=5;	}

		else if(dice_value==6){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] -= 400;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] -= 200;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] += 200;

			}
			
			else if(Yellow_Tokan[z][1]== 1150){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] += 200;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1050){
				Yellow_Tokan[z][0] += 200;
				Yellow_Tokan[z][1] += 400;
				
			}
			
			else if(Yellow_Tokan[z][1]== 950){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] += 500;
				
			}
			yellow_score+=6;
	}
	}
	else if(yellow_lock==false){
		if(dice_value==1){
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
			}
			
			else
				Yellow_Tokan[z][1] += 100;
				
				}
				
		else if(dice_value==2){
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 100;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] +=100;
				
			}
			
			else
				Yellow_Tokan[z][1] += 200;
				
				}
			
		else if(dice_value==3){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 100;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] +=100;
				Yellow_Tokan[z][1] +=200;
				
			}
			
			else
				Yellow_Tokan[z][1] += 300;
				
				}
		
		else if(dice_value==4){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -=300;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] += 100;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1150){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] +=300;
				
			}
			
			else
				Yellow_Tokan[z][1] += 400;
				
				}
				
				
		else if(dice_value==5){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 400;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 200;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] += 100;

			}
		
			else if(Yellow_Tokan[z][1]== 1150){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] += 200;
				
			}
			
			else if(Yellow_Tokan[z][1]== 1050){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] +=400;
				
			}
			
			else
				Yellow_Tokan[z][1] += 500;
				
				}

		else if(dice_value==6){
		
			if(Yellow_Tokan[z][1]== 1450){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 500;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1350){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 300;
			
			
			}
			
			else if(Yellow_Tokan[z][1]== 1250){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] -= 100;

			}
			
			else if(Yellow_Tokan[z][1]== 1150){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] += 100;
			
			
			}
		
			else if(Yellow_Tokan[z][1]== 1050){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] += 300;
				
			}
			
			else if(Yellow_Tokan[z][1]== 950){
				Yellow_Tokan[z][0] += 100;
				Yellow_Tokan[z][1] += 500;
				
			}
			
	}
		}




}
//red middle row
else if(Yellow_Tokan[z][0]>=700 && Yellow_Tokan[z][0]<=800 && Yellow_Tokan[z][1]>=0 && Yellow_Tokan[z][1]<=600){

	if(dice_value==1){
			Yellow_Tokan[z][0]-=100;
			yellow_score+=1;}
			
	else if(dice_value==2){

			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=100;

			yellow_score+=2;}
		
	else if(dice_value==3){

			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=200;

			yellow_score+=3;}
			
	else if(dice_value==4){

			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=300;

			yellow_score+=4;}
			
	else if(dice_value==5){

			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=400;

			yellow_score+=5;}
			
	else if(dice_value==6){

			Yellow_Tokan[z][0] -= 100;
			Yellow_Tokan[z][1] +=500;

			yellow_score+=5;}


}

//yellow middle row

else if(Yellow_Tokan[z][0]>=700 && Yellow_Tokan[z][0]<=800 && Yellow_Tokan[z][1]>=900 && Yellow_Tokan[z][1]<=1500){

	if(yellow_lock==false){
	
		if(dice_value==1){
			
			Yellow_Tokan[z][1]-=100;
			yellow_score+=1;	}
				
		else if(dice_value==2){
			
			if(Yellow_Tokan[z][1] >= 1000){
				Yellow_Tokan[z][1] -= 200;
				yellow_score+=2;
			}
		
				}
			
		else if(dice_value==3){
		
			if(Yellow_Tokan[z][1] >= 1100){
				Yellow_Tokan[z][1] -= 300;
				yellow_score+=3;
			}
				}
		
		else if(dice_value==4){
		
			if(Yellow_Tokan[z][1] >= 1200){

				Yellow_Tokan[z][1] -=400;
				yellow_score+=4;
			
			}
				}
				
	
		else if(dice_value==5){
		
			if(Yellow_Tokan[z][1] >= 1300){
				Yellow_Tokan[z][1] -= 500;
				yellow_score+=5;
			}
				}

		else if(dice_value==6){
		
			if(Yellow_Tokan[z][1]>= 1400){
				Yellow_Tokan[z][1] -= 600;
				yellow_score+=6;
			
			}	
				}
				}
		
		
	else if(yellow_lock==true){
	
	
		if(dice_value==1){
			Yellow_Tokan[z][0]+=100;
			yellow_score+=1;}
			
	else if(dice_value==2){

			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=100;

			yellow_score+=2;}
		
	else if(dice_value==3){

			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=200;

			yellow_score+=3;}
			
	else if(dice_value==4){

			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=300;

			yellow_score+=4;}
			
	else if(dice_value==5){

			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=400;

			yellow_score+=5;}
			
	else if(dice_value==6){

			Yellow_Tokan[z][0] += 100;
			Yellow_Tokan[z][1] -=500;

			yellow_score+=6;}


	}	
		

}

//blue middle row

else if(Yellow_Tokan[z][0]>=900 && Yellow_Tokan[z][0]<=1500 && Yellow_Tokan[z][1]>=700 && Yellow_Tokan[z][1]<=800){

	if(dice_value==1){
			Yellow_Tokan[z][1]-=100;
			yellow_score+=1;}
			
	else if(dice_value==2){

			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=100;

			yellow_score+=2;}
		
	else if(dice_value==3){

			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=200;

			yellow_score+=3;}
			
	else if(dice_value==4){

			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=300;

			yellow_score+=4;}
			
	else if(dice_value==5){

			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=400;

			yellow_score+=5;}
			
	else if(dice_value==6){

			Yellow_Tokan[z][1] -= 100;
			Yellow_Tokan[z][0] -=500;

			yellow_score+=6;}

}


//green middle row


else if(Yellow_Tokan[z][0]>=0 && Yellow_Tokan[z][0]<=600 && Yellow_Tokan[z][1]>=700 && Yellow_Tokan[z][1]<=800){

	if(dice_value==1){
			Yellow_Tokan[z][1]+=100;
			yellow_score+=1;}
			
	else if(dice_value==2){

			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=100;

			yellow_score+=2;}
		
	else if(dice_value==3){

			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=200;

			yellow_score+=3;}
			
	else if(dice_value==4){

			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=300;

			yellow_score+=4;}
			
	else if(dice_value==5){

			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=400;

			yellow_score+=5;}
			
	else if(dice_value==6){

			Yellow_Tokan[z][1] += 100;
			Yellow_Tokan[z][0] +=500;

			yellow_score+=6;}


	}	

}

void Green_Tokan_move(int z){
//home
if(Green_Tokan[z][0]>=0&&Green_Tokan[z][0]<=600 && Green_Tokan[z][1] >=900 && Green_Tokan[z][1] <=1500 && dice_value==6){

	Green_Tokan[z][0]=ghx;
	Green_Tokan[z][1]=ghy;
	green_score+=6;
}

//red Left Row
else if(Green_Tokan[z][0]>=600 && Green_Tokan[z][0]<=700 && Green_Tokan[z][1]>=0 && Green_Tokan[z][1]<=600){

	if(dice_value==1){
		if(Green_Tokan[z][1]== 550){
			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=100;
			
		}
		
		else
			Green_Tokan[z][1] += 100;
			
		green_score+=1; }
			
	else if(dice_value==2){
		if(Green_Tokan[z][1]== 450){
			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=200;
			
		}
		
		else if(Green_Tokan[z][1]== 550){
			Green_Tokan[z][0] -= 200;
			Green_Tokan[z][1] +=100;
			
		}
		
		else
			Green_Tokan[z][1] += 200;
			
		green_score+=2;	}
		
	else if(dice_value==3){
	
		if(Green_Tokan[z][1]== 350){
			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 450){
			Green_Tokan[z][0] -= 200;
			Green_Tokan[z][1] +=200;
			
		}
		
		else if(Green_Tokan[z][1]== 550){
			Green_Tokan[z][0] -= 300;
			Green_Tokan[z][1] +=100;
			
		}
		
		else
			Green_Tokan[z][1] += 300;
			
		green_score+=3;	}
	
	else if(dice_value==4){
	
		if(Green_Tokan[z][1]== 250){
			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=400;
		
		
		}
		
		else if(Green_Tokan[z][1]== 350){
			Green_Tokan[z][0] -= 200;
			Green_Tokan[z][1] +=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 450){
			Green_Tokan[z][0] -= 300;
			Green_Tokan[z][1] +=200;
			
		}
		
		else if(Green_Tokan[z][1]== 550){
			Green_Tokan[z][0] -= 400;
			Green_Tokan[z][1] +=100;
			
		}
		
		else
			Green_Tokan[z][1] += 400;
			
		green_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Green_Tokan[z][1]== 150){
			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=500;
		
		
		}
		
		else if(Green_Tokan[z][1]== 250){
			Green_Tokan[z][0] -= 200;
			Green_Tokan[z][1] +=400;
		
		
		}
		
		else if(Green_Tokan[z][1]== 350){
			Green_Tokan[z][0] -= 300;
			Green_Tokan[z][1] +=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 450){
			Green_Tokan[z][0] -= 400;
			Green_Tokan[z][1] +=200;
			
		}
		
		else if(Green_Tokan[z][1]== 550){
			Green_Tokan[z][0] -= 500;
			Green_Tokan[z][1] +=100;
			
		}
		
		else
			Green_Tokan[z][1] += 500;
			
		green_score+=5;	}

	else if(dice_value==6){
	
		if(Green_Tokan[z][1]== 50){
			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=600;
		
		
		}
		
		else if(Green_Tokan[z][1]== 150){
			Green_Tokan[z][0] -= 200;
			Green_Tokan[z][1] +=500;
		
		
		}
		
		else if(Green_Tokan[z][1]== 250){
			Green_Tokan[z][0] -= 300;
			Green_Tokan[z][1] +=400;
		
		
		}
		
		else if(Green_Tokan[z][1]== 350){
			Green_Tokan[z][0] -= 400;
			Green_Tokan[z][1] +=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 450){
			Green_Tokan[z][0] -= 500;
			Green_Tokan[z][1] +=200;
			
		}
		
		else if(Green_Tokan[z][1]== 550){
			Green_Tokan[z][0] -= 600;
			Green_Tokan[z][1] +=100;
			
		}
		green_score+=6;
}


}

//green Above Row
else if(Green_Tokan[z][0]>=0 && Green_Tokan[z][0]<=600 && Green_Tokan[z][1]>=800 && Green_Tokan[z][1]<=900){

	if(dice_value==1){
		if(Green_Tokan[z][0]== 550){
			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=100;
			
		}
		
		else
			Green_Tokan[z][0] += 100;
			
		green_score+=1;	}
			
	else if(dice_value==2){
		if(Green_Tokan[z][0]== 450){
			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=200;
			
		}
		
		else if(Green_Tokan[z][0] == 550){
			Green_Tokan[z][1] += 200;
			Green_Tokan[z][0] +=100;
			
		}
		
		else
			Green_Tokan[z][0] += 200;
			
		green_score+=2;	}
		
	else if(dice_value==3){
	
		if(Green_Tokan[z][0]== 350){
			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 450){
			Green_Tokan[z][1] += 200;
			Green_Tokan[z][0] +=200;
			
		}
		
		else if(Green_Tokan[z][0]== 550){
			Green_Tokan[z][1] += 300;
			Green_Tokan[z][0] +=100;
			
		}
		
		else
			Green_Tokan[z][0] += 300;
			
		green_score+=3;	}
	
	else if(dice_value==4){
	
		if(Green_Tokan[z][0]== 250){
			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=400;
		
		
		}
		
		else if(Green_Tokan[z][0]== 350){
			Green_Tokan[z][1] += 200;
			Green_Tokan[z][0] +=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 450){
			Green_Tokan[z][1] += 300;
			Green_Tokan[z][0] +=200;
			
		}
		
		else if(Green_Tokan[z][0]== 550){
			Green_Tokan[z][1] += 400;
			Green_Tokan[z][0] +=100;
			
		}
		
		else
			Green_Tokan[z][0] += 400;
			
		green_score+=4;}
			
			
	else if(dice_value==5){
	
		if(Green_Tokan[z][0]== 150){
			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=500;
		
		
		}
		
		else if(Green_Tokan[z][0]== 250){
			Green_Tokan[z][1] += 200;
			Green_Tokan[z][0] +=400;
		
		
		}
		
		else if(Green_Tokan[z][0]== 350){
			Green_Tokan[z][1] += 300;
			Green_Tokan[z][0] +=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 450){
			Green_Tokan[z][1] += 400;
			Green_Tokan[z][0] +=200;
			
		}
		
		else if(Green_Tokan[z][0]== 550){
			Green_Tokan[z][1] += 500;
			Green_Tokan[z][0] +=100;
			
		}
		
		else
			Green_Tokan[z][0] += 500;
			
		green_score+=5;	}

	else if(dice_value==6){
	
		if(Green_Tokan[z][0]== 50){
			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=600;
		
		
		}
		
		else if(Green_Tokan[z][0]== 150){
			Green_Tokan[z][1] += 200;
			Green_Tokan[z][0] +=500;
		
		
		}
		
		else if(Green_Tokan[z][0]== 250){
			Green_Tokan[z][1] += 300;
			Green_Tokan[z][0] +=400;
		
		
		}
		
		else if(Green_Tokan[z][0]== 350){
			Green_Tokan[z][1] += 400;
			Green_Tokan[z][0] +=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 450){
			Green_Tokan[z][1] += 500;
			Green_Tokan[z][0] +=200;
			
		}
		
		else if(Green_Tokan[z][0]== 550){
			Green_Tokan[z][1] += 600;
			Green_Tokan[z][0] +=100;
			
		}
		green_score+=6;
}


}


//blue Below Row
else if(Green_Tokan[z][0]>=900 && Green_Tokan[z][0]<=1500 && Green_Tokan[z][1]>=600 && Green_Tokan[z][1]<=700){

	if(dice_value==1){
		if(Green_Tokan[z][0]== 950){
			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=100;
			
		}
		
		else
			Green_Tokan[z][0] -= 100;
			
		green_score+=1;	}
			
	else if(dice_value==2){
		if(Green_Tokan[z][0]== 1050){
			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=200;
			
		}
		
		else if(Green_Tokan[z][0]== 950){
			Green_Tokan[z][1] -= 200;
			Green_Tokan[z][0] -= 100;
			
		}
		
		else
			Green_Tokan[z][0] -= 200;
			
		green_score+=2;	}
		
	else if(dice_value==3){
	
		if(Green_Tokan[z][0]== 1150){
			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 1050){
			Green_Tokan[z][1] -= 200;
			Green_Tokan[z][0] -=200;
			
		}
		
		else if(Green_Tokan[z][0]== 950){
			Green_Tokan[z][1] -= 300;
			Green_Tokan[z][0] -=100;
			
		}
		
		else
			Green_Tokan[z][0] -= 300;
			
		green_score+=3;	}
	
	else if(dice_value==4){
	
		if(Green_Tokan[z][0]== 1250){
			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=400;
		
		
		}
		
		else if(Green_Tokan[z][0]== 1150){
			Green_Tokan[z][1] -= 200;
			Green_Tokan[z][0] -=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 1050){
			Green_Tokan[z][1] -= 300;
			Green_Tokan[z][0] -=200;
			
		}
		
		else if(Green_Tokan[z][0]== 950){
			Green_Tokan[z][1] -= 400;
			Green_Tokan[z][0] -=100;
			
		}
		
		else
			Green_Tokan[z][0] -= 400;
			
		green_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Green_Tokan[z][0]== 1350){
			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=500;
		
		
		}
		
		else if(Green_Tokan[z][0]== 1250){
			Green_Tokan[z][1] -= 200;
			Green_Tokan[z][0] -=400;
		
		
		}
		
		else if(Green_Tokan[z][0]== 1150){
			Green_Tokan[z][1] -= 300;
			Green_Tokan[z][0] -=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 1050){
			Green_Tokan[z][1] -= 400;
			Green_Tokan[z][0] -=200;
			
		}
		
		else if(Green_Tokan[z][0]== 950){
			Green_Tokan[z][1] -= 500;
			Green_Tokan[z][0] -=100;
			
		}
		
		else
			Green_Tokan[z][0] -= 500;
			
		green_score+=5;	}

	else if(dice_value==6){
	
		if(Green_Tokan[z][0]== 1450){
			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=600;
		
		
		}
		
		else if(Green_Tokan[z][0]== 1350){
			Green_Tokan[z][1] -= 200;
			Green_Tokan[z][0] -=500;
		
		
		}
		
		else if(Green_Tokan[z][0]== 1250){
			Green_Tokan[z][1] -= 300;
			Green_Tokan[z][0] -=400;
		
		
		}
		
		else if(Green_Tokan[z][0]== 1150){
			Green_Tokan[z][1] -= 400;
			Green_Tokan[z][0] -=300;
		
		
		}
	
		else if(Green_Tokan[z][0]== 1050){
			Green_Tokan[z][1] -= 500;
			Green_Tokan[z][0] -=200;
			
		}
		
		else if(Green_Tokan[z][0]== 950){
			Green_Tokan[z][1] -= 600;
			Green_Tokan[z][0] -=100;
			
		}
		green_score+=6;
}
}

//yellow Right Row
else if(Green_Tokan[z][0]>=800 && Green_Tokan[z][0]<=900 && Green_Tokan[z][1]>=900 && Green_Tokan[z][1]<=1500){

	if(dice_value==1){
		if(Green_Tokan[z][1]== 950){
			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=100;
			
		}
		
		else
			Green_Tokan[z][1] -= 100;
			
		green_score+=1;	}
			
	else if(dice_value==2){
		if(Green_Tokan[z][1]== 1050){
			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=200;
			
		}
		
		else if(Green_Tokan[z][1]== 950){
			Green_Tokan[z][0] += 200;
			Green_Tokan[z][1] -=100;
			
		}
		
		else
			Green_Tokan[z][1] -= 200;
			
		green_score+=2;	}
		
	else if(dice_value==3){
	
		if(Green_Tokan[z][1]== 1150){
			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 1050){
			Green_Tokan[z][0] += 200;
			Green_Tokan[z][1] -=200;
			
		}
		
		else if(Green_Tokan[z][1]== 950){
			Green_Tokan[z][0] += 300;
			Green_Tokan[z][1] -=100;
			
		}
		
		else
			Green_Tokan[z][1] -= 300;
			
		green_score+=3;	}
	
	else if(dice_value==4){
	
		if(Green_Tokan[z][1]== 1250){
			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=400;
		
		
		}
		
		else if(Green_Tokan[z][1]== 1150){
			Green_Tokan[z][0] += 200;
			Green_Tokan[z][1] -=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 1050){
			Green_Tokan[z][0] += 300;
			Green_Tokan[z][1] -=200;
			
		}
		
		else if(Green_Tokan[z][1]== 950){
			Green_Tokan[z][0] += 400;
			Green_Tokan[z][1] -=100;
			
		}
		
		else
			Green_Tokan[z][1] -= 400;
			
		green_score+=4;	}
			
			
	else if(dice_value==5){
	
		if(Green_Tokan[z][1]== 1350){
			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=500;
		
		
		}
		
		else if(Green_Tokan[z][1]== 1250){
			Green_Tokan[z][0] += 200;
			Green_Tokan[z][1] -=400;
		
		
		}
		
		else if(Green_Tokan[z][1]== 1150){
			Green_Tokan[z][0] += 300;
			Green_Tokan[z][1] -=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 1050){
			Green_Tokan[z][0] += 400;
			Green_Tokan[z][1] -=200;
			
		}
		
		else if(Green_Tokan[z][1]== 950){
			Green_Tokan[z][0] += 500;
			Green_Tokan[z][1] -=100;
			
		}
		
		else
			Green_Tokan[z][1] -= 500;
			
		green_score+=5;}

	else if(dice_value==6){
	
		if(Green_Tokan[z][1]== 1450){
			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=600;
		
		
		}
		
		else if(Green_Tokan[z][1]== 1350){
			Green_Tokan[z][0] += 200;
			Green_Tokan[z][1] -=500;
		
		
		}
		
		else if(Green_Tokan[z][1]== 1250){
			Green_Tokan[z][0] += 300;
			Green_Tokan[z][1] -=400;
		
		
		}
		
		else if(Green_Tokan[z][1]== 1150){
			Green_Tokan[z][0] += 400;
			Green_Tokan[z][1] -=300;
		
		
		}
	
		else if(Green_Tokan[z][1]== 1050){
			Green_Tokan[z][0] += 500;
			Green_Tokan[z][1] -=200;
			
		}
		
		else if(Green_Tokan[z][1]== 950){
			Green_Tokan[z][0] += 600;
			Green_Tokan[z][1] -=100;
			
		}
		green_score+=6;
}


}



//red Right Row

else if(Green_Tokan[z][0]>=800 && Green_Tokan[z][0]<=900 && Green_Tokan[z][1]>=0 && Green_Tokan[z][1]<=600){


		if(dice_value==1){
			if(Green_Tokan[z][1]== 50){
				Green_Tokan[z][0] -= 100;
			}
			
			else
				Green_Tokan[z][1] -= 100;
				
			green_score+=1;	}
				
		else if(dice_value==2){
			if(Green_Tokan[z][1]== 50){
				Green_Tokan[z][0] -= 200;
				
			}
			
			else if(Green_Tokan[z][1]== 150){
				Green_Tokan[z][0] -= 100;
				Green_Tokan[z][1] -=100;
				
			}
			
			else
				Green_Tokan[z][1] -= 200;
				
			green_score+=2;	}
			
		else if(dice_value==3){
		
			if(Green_Tokan[z][1]== 50){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] += 100;
			
			
			}
		
			else if(Green_Tokan[z][1]== 150){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] -=100;
				
			}
			
			else if(Green_Tokan[z][1]== 250){
				Green_Tokan[z][0] -=100;
				Green_Tokan[z][1] -=200;
				
			}
			
			else
				Green_Tokan[z][1] -= 300;
				
			green_score+=3;	}
		
		else if(dice_value==4){
		
			if(Green_Tokan[z][1]== 50){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] +=200;
			
			
			}
			
			else if(Green_Tokan[z][1]== 150){
				Green_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Green_Tokan[z][1]== 250){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] -=200;
				
			}
			
			else if(Green_Tokan[z][1]== 350){
				Green_Tokan[z][0] -= 100;
				Green_Tokan[z][1] -=300;
				
			}
			
			else
				Green_Tokan[z][1] -= 400;
				
			green_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Green_Tokan[z][1]== 50){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] += 300;
			
			
			}
			
			else if(Green_Tokan[z][1]== 150){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] += 100;
			
			
			}
			
			else if(Green_Tokan[z][1]== 250){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Green_Tokan[z][1]== 350){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] -= 300;
				
			}
			
			else if(Green_Tokan[z][1]== 450){
				Green_Tokan[z][0] -= 100;
				Green_Tokan[z][1] -=400;
				
			}
			
			else
				Green_Tokan[z][1] -= 500;
				
			green_score+=5;	}

		else if(dice_value==6){
		
			if(Green_Tokan[z][1]== 50){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] += 400;
			
			
			}
			
			else if(Green_Tokan[z][1]== 150){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] += 200;
			
			
			}
			
			else if(Green_Tokan[z][1]== 250){
				Green_Tokan[z][0] -= 200;

			}
			
			else if(Green_Tokan[z][1]== 350){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Green_Tokan[z][1]== 450){
				Green_Tokan[z][0] -= 200;
				Green_Tokan[z][1] -= 400;
				
			}
			
			else if(Green_Tokan[z][1]== 550){
				Green_Tokan[z][0] -= 100;
				Green_Tokan[z][1] -= 500;
				
			}
			green_score+=6;
	}

}


//green Down Row

else if(Green_Tokan[z][0]>=0 && Green_Tokan[z][0]<=600 && Green_Tokan[z][1]>=600 && Green_Tokan[z][1]<=700){

	if(green_lock==true){
		if(dice_value==1){
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
			}
			
			else
				Green_Tokan[z][0] -= 100;
				
			green_score+=1;	}
				
		else if(dice_value==2){
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 200;
				
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -=100;
				
			}
			
			else
				Green_Tokan[z][0] -= 200;
				
			green_score+=2;	}
			
		else if(dice_value==3){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] += 100;
			
			
			}
		
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] -=100;
				
			}
			
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] +=100;
				Green_Tokan[z][0] -=200;
				
			}
			
			else
				Green_Tokan[z][0] -= 300;
				
			green_score+=3;	}
		
		else if(dice_value==4){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] +=200;
			
			
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 200;
			
			
			}
		
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] -=200;
				
			}
			
			else if(Green_Tokan[z][0]== 350){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -=300;
				
			}
			
			else
				Green_Tokan[z][0] -= 400;
				
			green_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] += 300;
			
			
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] += 100;
			
			
			}
			
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] -= 100;
			
			
			}
		
			else if(Green_Tokan[z][0]== 350){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] -= 300;
				
			}
			
			else if(Green_Tokan[z][0]== 450){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -=400;
				
			}
			
			else
				Green_Tokan[z][0] -= 500;
				
			green_score+=5;	}

		else if(dice_value==6){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] += 400;
			
			
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] += 200;
			
			
			}
			
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] += 200;

			}
			
			else if(Green_Tokan[z][0]== 350){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Green_Tokan[z][0]== 450){
				Green_Tokan[z][1] += 200;
				Green_Tokan[z][0] -= 400;
				
			}
			
			else if(Green_Tokan[z][0]== 550){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -= 500;
				
			}
			green_score+=6;
	}
	}
	
	else if(green_lock==false){
		if(dice_value==1){
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
			}
			
			else
				Green_Tokan[z][0] -= 100;
				
				}
				
		else if(dice_value==2){
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 100;
				
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -=100;
				
			}
			
			else
				Green_Tokan[z][0] -= 200;
				
				}
			
		else if(dice_value==3){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 200;
			
			
			}
		
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 100;
				
			}
			
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] +=100;
				Green_Tokan[z][0] -=200;
				
			}
			
			else
				Green_Tokan[z][0] -= 300;
				
				}
		
		else if(dice_value==4){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] +=300;
			
			
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 100;
			
			
			}
		
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -= 100;
				
			}
			
			else if(Green_Tokan[z][0]== 350){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -=300;
				
			}
			
			else
				Green_Tokan[z][0] -= 400;
				
				}
				
				
		else if(dice_value==5){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 400;
			
			
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 200;
			
			
			}
			
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] += 100;

			}
		
			else if(Green_Tokan[z][0]== 350){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -= 200;
				
			}
			
			else if(Green_Tokan[z][0]== 450){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -=400;
				
			}
			
			else
				Green_Tokan[z][0] -= 500;
				
				}

		else if(dice_value==6){
		
			if(Green_Tokan[z][0]== 50){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 500;
			
			
			}
			
			else if(Green_Tokan[z][0]== 150){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 300;
			
			
			}
			
			else if(Green_Tokan[z][0]== 250){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] += 100;

			}
			
			else if(Green_Tokan[z][0]== 350){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -= 100;
			
			
			}
		
			else if(Green_Tokan[z][0]== 450){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -= 300;
				
			}
			
			else if(Green_Tokan[z][0]== 550){
				Green_Tokan[z][1] += 100;
				Green_Tokan[z][0] -= 500;
				
			}
			
	}
		}


}


//blue Up Row

else if(Green_Tokan[z][0]>=900 && Green_Tokan[z][0]<=1500 && Green_Tokan[z][1]>=800 && Green_Tokan[z][1]<=900){


		if(dice_value==1){
			if(Green_Tokan[z][0]== 1450){
				Green_Tokan[z][1] -= 100;
			}
			
			else
				Green_Tokan[z][0] += 100;
				
			green_score+=1;	}
				
		else if(dice_value==2){
			if(Green_Tokan[z][0]== 1450){
				Green_Tokan[z][1] -= 200;
				
			}
			
			else if(Green_Tokan[z][0]== 1350){
				Green_Tokan[z][1] -= 100;
				Green_Tokan[z][0] +=100;
				
			}
			
			else
				Green_Tokan[z][0] += 200;
				
			green_score+=2;	}
			
		else if(dice_value==3){
		
			if(Green_Tokan[z][0]== 1450){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] -= 200;
			
			
			}
		
			else if(Green_Tokan[z][0]== 1350){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] +=100;
				
			}
			
			else if(Green_Tokan[z][0]== 1250){
				Green_Tokan[z][1] -=100;
				Green_Tokan[z][0] +=200;
				
			}
			
			else
				Green_Tokan[z][0] += 300;
				
			green_score+=3;	}
		
		else if(dice_value==4){
		
			if(Green_Tokan[z][0]== 1450){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] -=200;
			
			
			}
			
			else if(Green_Tokan[z][0]== 1350){
				Green_Tokan[z][1] -= 200;
			
			
			}
		
			else if(Green_Tokan[z][0]== 1250){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] +=200;
				
			}
			
			else if(Green_Tokan[z][0] == 1150){
				Green_Tokan[z][1] -= 100;
				Green_Tokan[z][0] +=300;
				
			}
			
			else
				Green_Tokan[z][0] += 400;
				
			green_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Green_Tokan[z][0]== 1450){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] -= 300;
			
			
			}
			
			else if(Green_Tokan[z][0]== 1350){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] -= 100;
		
			
			}
			
			else if(Green_Tokan[z][0]== 1250){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] += 100;
			
			
			}
		
			else if(Green_Tokan[z][0]== 1150){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] += 300;
				
			}
			
			else if(Green_Tokan[z][0]== 1050){
				Green_Tokan[z][1] -= 100;
				Green_Tokan[z][0] +=400;
				
			}
			
			else
				Green_Tokan[z][0] += 500;
				
			green_score+=5;	}

		else if(dice_value==6){
		
			if(Green_Tokan[z][0]== 1450){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] -= 400;
			
			
			}
			
			else if(Green_Tokan[z][0]== 1350){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] -= 200;
			
			
			}
			
			else if(Green_Tokan[z][0]== 1250){
				Green_Tokan[z][1] -= 200;
			}
			
			else if(Green_Tokan[z][0]== 1150){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] += 200;
			
			
			}
		
			else if(Green_Tokan[z][0]== 1050){
				Green_Tokan[z][1] -= 200;
				Green_Tokan[z][0] += 400;
				
			}
			
			else if(Green_Tokan[z][0]== 950){
				Green_Tokan[z][1] -= 100;
				Green_Tokan[z][0] += 500;
				
			}
			green_score+=6;
	}

}



//yellow Left Row

else if(Green_Tokan[z][0]>=600 && Green_Tokan[z][0]<=700 && Green_Tokan[z][1]>=900 && Green_Tokan[z][1]<=1500){


		if(dice_value==1){
			if(Green_Tokan[z][1]== 1450){
				Green_Tokan[z][0] += 100;
			}
			
			else
				Green_Tokan[z][1] += 100;
				
			green_score+=1;	}
				
		else if(dice_value==2){
			if(Green_Tokan[z][1]== 1450){
				Green_Tokan[z][0] += 200;
				
			}
			
			else if(Green_Tokan[z][1]== 1350){
				Green_Tokan[z][0] += 100;
				Green_Tokan[z][1] +=100;
				
			}
			
			else
				Green_Tokan[z][1] += 200;
				
			green_score+=2;	}
			
		else if(dice_value==3){
		
			if(Green_Tokan[z][1]== 1450){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] -= 100;
			
			
			}
		
			else if(Green_Tokan[z][1]== 1350){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] +=100;
				
			}
			
			else if(Green_Tokan[z][1]== 1250){
				Green_Tokan[z][0] +=100;
				Green_Tokan[z][1] +=200;
				
			}
			
			else
				Green_Tokan[z][1] += 300;
				
			green_score+=3;	}
		
		else if(dice_value==4){
		
			if(Green_Tokan[z][1]== 1450){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] -=200;
			
			
			}
			
			else if(Green_Tokan[z][1]== 1350){
				Green_Tokan[z][0] += 200;
			
			
			}
		
			else if(Green_Tokan[z][1]== 1250){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] +=200;
				
			}
			
			else if(Green_Tokan[z][1] == 1150){
				Green_Tokan[z][0] += 100;
				Green_Tokan[z][1] +=300;
				
			}
			
			else
				Green_Tokan[z][1] += 400;
				
			green_score+=4;	}
				
				
		else if(dice_value==5){
		
			if(Green_Tokan[z][1]== 1450){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] -= 300;
			
			
			}
			
			else if(Green_Tokan[z][1]== 1350){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] -= 100;
		
			
			}
			
			else if(Green_Tokan[z][1]== 1250){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] += 100;
			
			
			}
		
			else if(Green_Tokan[z][1]== 1150){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] += 300;
				
			}
			
			else if(Green_Tokan[z][1]== 1050){
				Green_Tokan[z][0] += 100;
				Green_Tokan[z][1] +=400;
				
			}
			
			else
				Green_Tokan[z][1] += 500;
				
			green_score+=5;	}

		else if(dice_value==6){
		
			if(Green_Tokan[z][1]== 1450){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] -= 400;
			
			
			}
			
			else if(Green_Tokan[z][1]== 1350){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] -= 200;
			
			
			}
			
			else if(Green_Tokan[z][1]== 1250){
				Green_Tokan[z][0] += 200;

			}
			
			else if(Green_Tokan[z][1]== 1150){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] += 200;
			
			
			}
		
			else if(Green_Tokan[z][1]== 1050){
				Green_Tokan[z][0] += 200;
				Green_Tokan[z][1] += 400;
				
			}
			
			else if(Green_Tokan[z][1]== 950){
				Green_Tokan[z][0] += 100;
				Green_Tokan[z][1] += 500;
				
			}
			green_score+=6;
	}

}
//red middle row
else if(Green_Tokan[z][0]>=700 && Green_Tokan[z][0]<=800 && Green_Tokan[z][1]>=0 && Green_Tokan[z][1]<=600){

	if(dice_value==1){
			Green_Tokan[z][0]-=100;
			green_score+=1;}
			
	else if(dice_value==2){

			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=100;

			green_score+=2;}
		
	else if(dice_value==3){

			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=200;

			green_score+=3;}
			
	else if(dice_value==4){

			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=300;

			green_score+=4;}
			
	else if(dice_value==5){

			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=400;

			green_score+=5;}
			
	else if(dice_value==6){

			Green_Tokan[z][0] -= 100;
			Green_Tokan[z][1] +=500;

			green_score+=6;}

}

//yellow middle row

else if(Green_Tokan[z][0]>=700 && Green_Tokan[z][0]<=800 && Green_Tokan[z][1]>=900 && Green_Tokan[z][1]<=1500){

	if(dice_value==1){
			Green_Tokan[z][0]+=100;
			green_score+=1;}
			
	else if(dice_value==2){

			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=100;

			green_score+=2;}
		
	else if(dice_value==3){

			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=200;

			green_score+=3;}
			
	else if(dice_value==4){

			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=300;

			green_score+=4;}
			
	else if(dice_value==5){

			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=400;

			green_score+=5;}
			
	else if(dice_value==6){

			Green_Tokan[z][0] += 100;
			Green_Tokan[z][1] -=500;

			green_score+=6;}

}

//blue middle row

else if(Green_Tokan[z][0]>=900 && Green_Tokan[z][0]<=1500 && Green_Tokan[z][1]>=700 && Green_Tokan[z][1]<=800){

	if(dice_value==1){
			Green_Tokan[z][1]-=100;
			green_score+=1;}
			
	else if(dice_value==2){

			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=100;

			green_score+=2;}
		
	else if(dice_value==3){

			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=200;

			green_score+=3;}
			
	else if(dice_value==4){

			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=300;

			green_score+=4;}
			
	else if(dice_value==5){

			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=400;

			green_score+=5;}
			
	else if(dice_value==6){

			Green_Tokan[z][1] -= 100;
			Green_Tokan[z][0] -=500;

			green_score+=6;}


}


//green middle row


else if(Green_Tokan[z][0]>=0 && Green_Tokan[z][0]<=600 && Green_Tokan[z][1]>=700 && Green_Tokan[z][1]<=800){

	if(green_lock==false){
	
		if(dice_value==1){
			
			Green_Tokan[z][0]+=100;
			green_score+=1; }
				
		else if(dice_value==2){
			
			if(Green_Tokan[z][0] <= 500){
				Green_Tokan[z][0] += 200;
				green_score+=2;
			}
		
				}
			
		else if(dice_value==3){
		
			if(Green_Tokan[z][0]<= 400){
				Green_Tokan[z][0] += 300;
				green_score+=3;
			}
				}
		
		else if(dice_value==4){
		
			if(Green_Tokan[z][0] <=300){

				Green_Tokan[z][0] +=400;
				green_score+=4;
			
			}
				}
				
	
		else if(dice_value==5){
		
			if(Green_Tokan[z][0] <= 200){
				Green_Tokan[z][0] += 500;
				green_score+=5;
			}
				}

		else if(dice_value==6){
		
			if(Green_Tokan[z][0]<= 100){
				Green_Tokan[z][0] += 600;
				green_score+=6;
			
			}	
				}
				}
		
		
	else if(green_lock==true){
	
	
		if(dice_value==1){
			Green_Tokan[z][1]+=100;
			green_score+=1;}
			
	else if(dice_value==2){

			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=100;

			green_score+=2;}
		
	else if(dice_value==3){

			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=200;

			green_score+=3;}
			
	else if(dice_value==4){

			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=300;

			green_score+=4;}
			
	else if(dice_value==5){

			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=400;

			green_score+=5;}
			
	else if(dice_value==6){

			Green_Tokan[z][1] += 100;
			Green_Tokan[z][0] +=500;

			green_score+=6;}


	}	
		

}

}



void Kill_Fun(int u){

	if(t==4){
	
		for(int i=0; i<4; i++){
			if(Red_Tokan[u][0] == Blue_Tokan[i][0] && Red_Tokan[u][1] == Blue_Tokan[i][1]){			
				if(((Blue_Tokan[i][0]!=bhx || Blue_Tokan[i][0]!=bhy) && (Blue_Tokan[i][0]!=rhx || Blue_Tokan[i][0]!=rhy )&& (Blue_Tokan[i][0]!=yhx || Blue_Tokan[i][0]!=yhy) && (Blue_Tokan[i][0]!=ghx || Blue_Tokan[i][0]!=ghy)) || ((Blue_Tokan[i][0]!=bsx || Blue_Tokan[i][0]!=bsy) && (Blue_Tokan[i][0]!=rsx || Blue_Tokan[i][0]!=rsy )&& (Blue_Tokan[i][0]!=ysx || Blue_Tokan[i][0]!=ysy) && (Blue_Tokan[i][0]!=gsx || Blue_Tokan[i][0]!=gsy))){
					Blue_Tokan[i][0] = blue_init[i][0];
					Blue_Tokan[i][1] = blue_init[i][1];
					red_lock = false;
					red_score += 10;
				}
				}
				
			if(Red_Tokan[u][0] == Yellow_Tokan[i][0] && Red_Tokan[u][1] == Yellow_Tokan[i][1]){
				if(((Yellow_Tokan[i][0]!=bhx || Yellow_Tokan[i][0]!=bhy) && (Yellow_Tokan[i][0]!=rhx || Yellow_Tokan[i][0]!=rhy )&& (Yellow_Tokan[i][0]!=yhx || Yellow_Tokan[i][0]!=yhy) && (Yellow_Tokan[i][0]!=ghx || Yellow_Tokan[i][0]!=ghy)) || ((Yellow_Tokan[i][0]!=bsx || Yellow_Tokan[i][0]!=bsy) && (Yellow_Tokan[i][0]!=rsx || Yellow_Tokan[i][0]!=rsy )&& (Yellow_Tokan[i][0]!=ysx || Yellow_Tokan[i][0]!=ysy) && (Yellow_Tokan[i][0]!=gsx || Yellow_Tokan[i][0]!=gsy))){
					Yellow_Tokan[i][0] = yellow_init[i][0];
					Yellow_Tokan[i][1] = yellow_init[i][1];
					red_lock = false;
					red_score += 10;
				
				}
				
				}
				
			if(Red_Tokan[u][0] == Green_Tokan[i][0] && Red_Tokan[u][1] == Green_Tokan[i][1]){
				if(((Green_Tokan[i][0]!=bhx || Green_Tokan[i][0]!=bhy) && (Green_Tokan[i][0]!=rhx || Green_Tokan[i][0]!=rhy )&& (Green_Tokan[i][0]!=yhx || Green_Tokan[i][0]!=yhy) && (Green_Tokan[i][0]!=ghx || Green_Tokan[i][0]!=ghy)) || ((Green_Tokan[i][0]!=bsx || Green_Tokan[i][0]!=bsy) && (Green_Tokan[i][0]!=rsx || Green_Tokan[i][0]!=rsy )&& (Green_Tokan[i][0]!=ysx || Green_Tokan[i][0]!=ysy) && (Green_Tokan[i][0]!=gsx || Green_Tokan[i][0]!=gsy))){
					Green_Tokan[i][0] = green_init[i][0];
					Green_Tokan[i][1] = green_init[i][1];
					red_lock = false;
					red_score += 10;
				
				}
				}
				
				
			}
	
	}
		
	else if(t==1){
	
		for(int i=0; i<4; i++){
			if(Blue_Tokan[u][0] == Red_Tokan[i][0] && Blue_Tokan[u][1] == Red_Tokan[i][1]){
				if(((Red_Tokan[i][0]!=bhx || Red_Tokan[i][0]!=bhy) && (Red_Tokan[i][0]!=rhx || Red_Tokan[i][0]!=rhy )&& (Red_Tokan[i][0]!=yhx || Red_Tokan[i][0]!=yhy) && (Red_Tokan[i][0]!=ghx || Red_Tokan[i][0]!=ghy)) || ((Red_Tokan[i][0]!=bsx || Red_Tokan[i][0]!=bsy) && (Red_Tokan[i][0]!=rsx || Red_Tokan[i][0]!=rsy )&& (Red_Tokan[i][0]!=ysx || Red_Tokan[i][0]!=ysy) && (Red_Tokan[i][0]!=gsx || Red_Tokan[i][0]!=gsy))){
					Red_Tokan[i][0] = red_init[i][0];
					Red_Tokan[i][1] = red_init[i][1];
					blue_lock = false;
					blue_score += 10;
				
				}
				}
				
			if(Blue_Tokan[u][0] == Yellow_Tokan[i][0] && Blue_Tokan[u][1] == Yellow_Tokan[i][1]){
				if(((Yellow_Tokan[i][0]!=bhx || Yellow_Tokan[i][0]!=bhy) && (Yellow_Tokan[i][0]!=rhx || Yellow_Tokan[i][0]!=rhy )&& (Yellow_Tokan[i][0]!=yhx || Yellow_Tokan[i][0]!=yhy) && (Yellow_Tokan[i][0]!=ghx || Yellow_Tokan[i][0]!=ghy)) || ((Yellow_Tokan[i][0]!=bsx || Yellow_Tokan[i][0]!=bsy) && (Yellow_Tokan[i][0]!=rsx || Yellow_Tokan[i][0]!=rsy )&& (Yellow_Tokan[i][0]!=ysx || Yellow_Tokan[i][0]!=ysy) && (Yellow_Tokan[i][0]!=gsx || Yellow_Tokan[i][0]!=gsy))){
					Yellow_Tokan[i][0] = yellow_init[i][0];
					Yellow_Tokan[i][1] = yellow_init[i][1];
					blue_lock = false;
					blue_score += 10;
				
				}
				}
				
			if(Blue_Tokan[u][0] == Green_Tokan[i][0] && Blue_Tokan[u][1] == Green_Tokan[i][1]){
				if(((Green_Tokan[i][0]!=bhx || Green_Tokan[i][0]!=bhy) && (Green_Tokan[i][0]!=rhx || Green_Tokan[i][0]!=rhy )&& (Green_Tokan[i][0]!=yhx || Green_Tokan[i][0]!=yhy) && (Green_Tokan[i][0]!=ghx || Green_Tokan[i][0]!=ghy)) || ((Green_Tokan[i][0]!=bsx || Green_Tokan[i][0]!=bsy) && (Green_Tokan[i][0]!=rsx || Green_Tokan[i][0]!=rsy )&& (Green_Tokan[i][0]!=ysx || Green_Tokan[i][0]!=ysy) && (Green_Tokan[i][0]!=gsx || Green_Tokan[i][0]!=gsy))){
					Green_Tokan[i][0] = green_init[i][0];
					Green_Tokan[i][1] = green_init[i][1];
					blue_lock = false;
					blue_score += 10;
				
				}
				}
				
				
			}
	
	}		


	else if(t==2){
	
		for(int i=0; i<4; i++){
			if(Yellow_Tokan[u][0] == Red_Tokan[i][0] && Yellow_Tokan[u][1] == Red_Tokan[i][1]){
				if(((Red_Tokan[i][0]!=bhx || Red_Tokan[i][0]!=bhy) && (Red_Tokan[i][0]!=rhx || Red_Tokan[i][0]!=rhy )&& (Red_Tokan[i][0]!=yhx || Red_Tokan[i][0]!=yhy) && (Red_Tokan[i][0]!=ghx || Red_Tokan[i][0]!=ghy)) || ((Red_Tokan[i][0]!=bsx || Red_Tokan[i][0]!=bsy) && (Red_Tokan[i][0]!=rsx || Red_Tokan[i][0]!=rsy )&& (Red_Tokan[i][0]!=ysx || Red_Tokan[i][0]!=ysy) && (Red_Tokan[i][0]!=gsx || Red_Tokan[i][0]!=gsy))){
					Red_Tokan[i][0] = red_init[i][0];
					Red_Tokan[i][1] = red_init[i][1];
					yellow_lock = false;
					yellow_score+=10;
				
				}
				}
				
			if(Yellow_Tokan[u][0] == Blue_Tokan[i][0] && Yellow_Tokan[u][1] == Blue_Tokan[i][1]){

				if(((Blue_Tokan[i][0]!=bhx || Blue_Tokan[i][0]!=bhy) && (Blue_Tokan[i][0]!=rhx || Blue_Tokan[i][0]!=rhy )&& (Blue_Tokan[i][0]!=yhx || Blue_Tokan[i][0]!=yhy) && (Blue_Tokan[i][0]!=ghx || Blue_Tokan[i][0]!=ghy)) || ((Blue_Tokan[i][0]!=bsx || Blue_Tokan[i][0]!=bsy) && (Blue_Tokan[i][0]!=rsx || Blue_Tokan[i][0]!=rsy )&& (Blue_Tokan[i][0]!=ysx || Blue_Tokan[i][0]!=ysy) && (Blue_Tokan[i][0]!=gsx || Blue_Tokan[i][0]!=gsy))){
					Blue_Tokan[i][0] = blue_init[i][0];
					Blue_Tokan[i][1] = blue_init[i][1];
					yellow_lock = false;
					yellow_score+=10;
				}
				}
				
			if(Yellow_Tokan[u][0] == Green_Tokan[i][0] && Yellow_Tokan[u][1] == Green_Tokan[i][1]){
				if(((Green_Tokan[i][0]!=bhx || Green_Tokan[i][0]!=bhy) && (Green_Tokan[i][0]!=rhx || Green_Tokan[i][0]!=rhy )&& (Green_Tokan[i][0]!=yhx || Green_Tokan[i][0]!=yhy) && (Green_Tokan[i][0]!=ghx || Green_Tokan[i][0]!=ghy)) || ((Green_Tokan[i][0]!=bsx || Green_Tokan[i][0]!=bsy) && (Green_Tokan[i][0]!=rsx || Green_Tokan[i][0]!=rsy )&& (Green_Tokan[i][0]!=ysx || Green_Tokan[i][0]!=ysy) && (Green_Tokan[i][0]!=gsx || Green_Tokan[i][0]!=gsy))){
					Green_Tokan[i][0] = green_init[i][0];
					Green_Tokan[i][1] = green_init[i][1];
					yellow_lock = false;
					yellow_score+=10;
				
				}
				}
				
				
			}
	
	}
	

	else if(t==3){
	
		for(int i=0; i<4; i++){
			if(Green_Tokan[u][0] == Red_Tokan[i][0] && Green_Tokan[u][1] == Red_Tokan[i][1]){
				if(((Red_Tokan[i][0]!=bhx || Red_Tokan[i][0]!=bhy) && (Red_Tokan[i][0]!=rhx || Red_Tokan[i][0]!=rhy )&& (Red_Tokan[i][0]!=yhx || Red_Tokan[i][0]!=yhy) && (Red_Tokan[i][0]!=ghx || Red_Tokan[i][0]!=ghy)) || ((Red_Tokan[i][0]!=bsx || Red_Tokan[i][0]!=bsy) && (Red_Tokan[i][0]!=rsx || Red_Tokan[i][0]!=rsy )&& (Red_Tokan[i][0]!=ysx || Red_Tokan[i][0]!=ysy) && (Red_Tokan[i][0]!=gsx || Red_Tokan[i][0]!=gsy))){
					Red_Tokan[i][0] = red_init[i][0];
					Red_Tokan[i][1] = red_init[i][1];
					green_lock = false;
					green_score+=10;
				
				}			
				}
				
			if(Green_Tokan[u][0] == Blue_Tokan[i][0] && Green_Tokan[u][1] == Blue_Tokan[i][1]){
				if(((Blue_Tokan[i][0]!=bhx || Blue_Tokan[i][0]!=bhy) && (Blue_Tokan[i][0]!=rhx || Blue_Tokan[i][0]!=rhy )&& (Blue_Tokan[i][0]!=yhx || Blue_Tokan[i][0]!=yhy) && (Blue_Tokan[i][0]!=ghx || Blue_Tokan[i][0]!=ghy)) || ((Blue_Tokan[i][0]!=bsx || Blue_Tokan[i][0]!=bsy) && (Blue_Tokan[i][0]!=rsx || Blue_Tokan[i][0]!=rsy )&& (Blue_Tokan[i][0]!=ysx || Blue_Tokan[i][0]!=ysy) && (Blue_Tokan[i][0]!=gsx || Blue_Tokan[i][0]!=gsy))){
					Blue_Tokan[i][0] = blue_init[i][0];
					Blue_Tokan[i][1] = blue_init[i][1];
					green_lock = false;
					green_score+=10;
				
				}
				}
				
			if(Green_Tokan[u][0] == Yellow_Tokan[i][0] && Green_Tokan[u][1] == Yellow_Tokan[i][1]){	
				if(((Yellow_Tokan[i][0]!=bhx || Yellow_Tokan[i][0]!=bhy) && (Yellow_Tokan[i][0]!=rhx || Yellow_Tokan[i][0]!=rhy )&& (Yellow_Tokan[i][0]!=yhx || Yellow_Tokan[i][0]!=yhy) && (Yellow_Tokan[i][0]!=ghx || Yellow_Tokan[i][0]!=ghy)) || ((Yellow_Tokan[i][0]!=bsx || Yellow_Tokan[i][0]!=bsy) && (Yellow_Tokan[i][0]!=rsx || Yellow_Tokan[i][0]!=rsy )&& (Yellow_Tokan[i][0]!=ysx || Yellow_Tokan[i][0]!=ysy) && (Yellow_Tokan[i][0]!=gsx || Yellow_Tokan[i][0]!=gsy))){
					Yellow_Tokan[i][0] = yellow_init[i][0];
					Yellow_Tokan[i][1] = yellow_init[i][1];
					green_lock = false;
					green_score+=10;
				
				}
				
				}
				
				
			}
		}


}

void won(){



	if(Red_Tokan[0][0]==rwx && Red_Tokan[0][1]==rwy && Red1_Wins == false){
			red_score+=15;
			red_wins+=1;
			Red1_Wins = true;
	}

	else if(Red_Tokan[1][0]==rwx && Red_Tokan[1][1]==rwy && Red2_Wins == false){
			red_score+=15;
			red_wins+=1;
			Red2_Wins = true;
	}


	else if(Red_Tokan[2][0]==rwx && Red_Tokan[2][1]==rwy&& Red3_Wins == false){
			red_score+=15;
			red_wins+=1;
			Red3_Wins = true;
	}


	else if(Red_Tokan[3][0]==rwx && Red_Tokan[3][1]==rwy && Red4_Wins == false){
			red_score+=15;
			red_wins+=1;
			Red4_Wins = true;
	}


	else if(Blue_Tokan[0][0]==bwx && Blue_Tokan[0][1]==bwy && Blue1_Wins == false){
			blue_score+=15;
			blue_wins+=1;
			Blue1_Wins = true;
	}

	else if(Blue_Tokan[1][0]==bwx && Blue_Tokan[1][1]==bwy && Blue2_Wins == false){
			blue_score+=15;
			blue_wins+=1;
			Blue2_Wins = true;
	}


	else if(Blue_Tokan[2][0]==bwx && Blue_Tokan[2][1] ==bwy&& Blue3_Wins == false){
			blue_score+=15;
			blue_wins+=1;
			Blue3_Wins = true;
	}


	else if(Blue_Tokan[3][0]==bwx && Blue_Tokan[3][1] ==bwy&& Blue4_Wins == false){
			blue_score+=15;
			blue_wins+=1;
			Blue4_Wins = true;
	}


	else if(Yellow_Tokan[0][0]==ywx && Yellow_Tokan[0][1]==ywy && Yellow1_Wins == false){
			yellow_score+=15;
			yellow_wins+=1;
			Yellow1_Wins = true;
	
	}

	else if(Yellow_Tokan[1][0]==ywx && Yellow_Tokan[1][1]==ywy && Yellow2_Wins == false){
			yellow_score+=15;
			yellow_wins+=1;
			Yellow2_Wins = true;
	
	}


	else if(Yellow_Tokan[2][0]==ywx && Yellow_Tokan[2][1]==ywy && Yellow3_Wins == false){
			yellow_score+=15;
			yellow_wins+=1;
			Yellow3_Wins = true;
	
	}


	else if(Yellow_Tokan[3][0]==ywx && Yellow_Tokan[3][1]==ywy && Yellow4_Wins == false){
			yellow_score+=15;
			yellow_wins+=1;
			Yellow4_Wins = true;
	
	}

	
	else if(Green_Tokan[0][0]==gwx && Green_Tokan[0][1]==gwy && Green1_Wins == false){
			green_score+=15;
			green_wins+=1;
		        Green1_Wins = true;
	}

	else if(Green_Tokan[1][0]==gwx && Green_Tokan[1][1]==gwy && Green2_Wins == false){
			green_score+=15;
			green_wins+=1;
			 Green2_Wins = true;
	}


	else if(Green_Tokan[2][0]==gwx && Green_Tokan[2][1] ==gwy && Green3_Wins == false){
			green_score+=15;
			green_wins+=1;
			 Green3_Wins = true;
	}


	else if(Green_Tokan[3][0]==gwx && Green_Tokan[3][1] ==gwy && Green4_Wins == false){
			green_score+=15;
			green_wins+=1;
			 Green4_Wins = true;
	}


}


//File Handling For Leaderboards
void update_score(){
	
	//reads the highscore.txt to get top 10 highscores and fit ur score in the right position in the .txt file
	int high_scores[11]={0};
	ifstream file;
	file.open("highscores.txt");
	int index=0; //index of highscores being accessed
	while (file)
	{
		int temp;
		file>>temp;
		high_scores[index]=temp;
		index++;
	}
	file.close();
	
	if(screen==3){
		
		//Red Scores
		if(rh_lock==false){
			int I=0;
			for (; I<11 && red_score<high_scores[I]; I++){}
			if (I<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>I; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[I]=red_score;

			}
			
			rh_lock=true;
			}
			
		//Blue Scores
		if(bh_lock==false){
			int J=0;
			for (; J<11 && blue_score<high_scores[J]; J++){}
			if (J<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>J; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[J]=blue_score;
			}
			
			bh_lock=true;
			}
			
		//Yellow Scores
		if(yh_lock==false){
			int K=0;
			for (; K<11 && yellow_score<high_scores[K]; K++){}
			if (K<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>K; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[K]=yellow_score;
			}
			
			yh_lock=true;
			}
			
			
		//Green Scores
		if(gh_lock==false){
			int L=0;
			for (; L<11 && green_score<high_scores[L]; L++){}
			if (L<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>L; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[L]=green_score;
				

			}	
			
			gh_lock=true;
		}
	}
	
	
	if(screen==2){
		
		//Red Scores
		if(rh_lock==false){
			int I=0;
			for (; I<11 && red_score<high_scores[I]; I++){}
			if (I<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>I; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[I]=red_score;

			}
			
			rh_lock=true;
			}
			
		//Blue Scores
		if(bh_lock==false){
			int J=0;
			for (; J<11 && blue_score<high_scores[J]; J++){}
			if (J<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>J; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[J]=blue_score;
			}
			
			bh_lock=true;
			}
			
		//Yellow Scores
		if(yh_lock==false){
			int K=0;
			for (; K<11 && yellow_score<high_scores[K]; K++){}
			if (K<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>K; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[K]=yellow_score;
			}
			
			yh_lock=true;
			}
			
			
	}
	
	
	if(screen==1){
			
		//Red Scores
		if(rh_lock==false){
			int I=0;
			for (; I<11 && red_score<high_scores[I]; I++){}
			if (I<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>I; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[I]=red_score;

			}
			
			rh_lock=true;
			}
			
		//Blue Scores
		if(bh_lock==false){
			int J=0;
			for (; J<11 && blue_score<high_scores[J]; J++){}
			if (J<11)
			{//you are one of the top 10 scores 
				for (int j=10; j>J; j--)
				{
					high_scores[j]=high_scores[j-1];
				}
				high_scores[J]=blue_score;
			}
			
			bh_lock=true;
			}
			

	}
	
	
	
	ofstream file2;
	file2.open("highscores.txt");
	for(int i=0; i<11; i++)
	{
		file2<<high_scores[i]<<endl;
	}
	file2.close();
}


#endif /* Ludo_Masters_By_Asad */
  
  
