/*
	author:Salman Sayeed
	last modified: August 8, 2008
*/
# include "iGraphics.h"
#include<math.h>
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<cstdlib>
using namespace std;
//==========================================
//      controls
//==========================================
void saveHighScores();
// a for amp decrease
// A for amp increase
// f for f increase
// F for freq decrease
// q for backscreen
int screen=1;
int lives=3;
int score=0;
int start=0;
bool sound=true;
char score_string[100];
int extreme=1;
int musicon=1;
char *music;
int level=1;
int screen_index=0;
char screen_input[20];

int a=0;
int b=400;
/*
	function iDraw() is called again and again by the system.
*/
char high_names[20][11];
char high_scores_string[20][11];
int high_scores[11];
void getSaveData();
void saveData();
void getBlockData();
void saveBlockData();
int xunit=5;
int yunit=5;

int screen_width=1280;
int screen_height=yunit*144;

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
    int R,G,B;
}Ball;
int ball_radius=10;
Ball ball={575,85,5,5,255,255,255};

typedef struct{
    int width;
    int height;
    int x;
    int y;
    int speed;
}Paddle;

Paddle paddle={30*xunit,5*yunit,500,50,30};

typedef struct{
    int x;
    int y;
    int exist;
    int r;
    int g;
    int b;

}Block;
Block blocks[10][10];
int block_width=100;
int block_height=25;
int block_change=1;


//=======================================

//  POWERUPS

//=======================================
int power_speed=5;
//int powerups_exist[10]={0,0,0,0,0,0,0,0,0,0};
//int powerups_x[10]={100,900,500,800,200,300,400,1100,600,1200};
//int powerups_y[10]={720,720,720,720,720,720,720,720,720,720};

int powerups_exist=0;
int powerups_x=0;
int powerups_y=0;
int powerup_active=0;
int powerup_width=75;
//FUNCTIONS FOR POWERUPS
void paddlePlus(){
    if(paddle.width<150) paddle.width=150;
    else paddle.width=250;
}
void paddleMinus(){
    if(paddle.width>150) paddle.width=150;
    else paddle.width=100;
}
void ballPlus(){
    if(ball.dx>0)ball.dx=10;
    if(ball.dx<0)ball.dx=-10;
    if(ball.dy<0)ball.dy=-10;
    if(ball.dy>0)ball.dy=10;


}
void ballMinus(){
    if(ball.dx>0)ball.dx=3;
    if(ball.dx<0)ball.dx=-3;
    if(ball.dy>0)ball.dy=3;
    if(ball.dy<0)ball.dy=-3;
}
void lifePlus(){
    if(lives<3) lives++;
}
void lifeMinus(){
    lives--;
}
void ballBig(){
    ball_radius=30;
}
void ballSmall(){
    ball_radius=5;
}
void paddleFast(){
    paddle.speed=50;
}
void paddleSlow(){
    paddle.speed=15;
}

int random_number;
void changeBall(){
    //======================================================


    //  BASIC MODE


    //======================================================
    if(screen==1) music="m1.wav";
    if(screen==2) music="m2.wav";
    if(screen==5) music="m4.wav";
    if(screen==6) music="m3.wav";

    //if(screen==1) music="m1.wav";
    if(screen==2 && start==0){
        ball.dy=5;


    }
    if(screen==2 && start==1){
        itoa(score*100,score_string,10);
        //BALL MOVEMENT
        ball.x+=ball.dx;
        ball.y+=ball.dy;
        if(ball.x+ball_radius>=screen_width) ball.dx=-1*ball.dx;
        if(ball.y+ball_radius>=screen_height) ball.dy=-1*ball.dy;
        if(ball.x-ball_radius<=0) ball.dx=-1*ball.dx;
        if(ball.y-ball_radius<=0){
            lives--;
            //powerup_active=0;
            PlaySound("fall.wav",NULL,SND_FILENAME | SND_ASYNC);
            Sleep(1500);
            start=0;
            paddle.x=500;
            ball.x=paddle.x+paddle.width/2;
            ball.y=paddle.y+paddle.height+ball_radius;


        }
        //PADDLE COLLISION
        if((ball.x+ball_radius>=paddle.x && ball.x-ball_radius<paddle.x+paddle.width)&&(ball.y-ball_radius==paddle.y+paddle.height)){
            ball.dy=-1*ball.dy;
            PlaySound("music\\boop.wav",NULL,SND_FILENAME | SND_ASYNC);

        }







        //BLOCK COLLISION
        for(int i=1;i<=10;i++){
                for(int j=1;j<=10;j++){
                    //Removing faulty balls

                    if(blocks[i][j].exist==1 && (blocks[i][j].x<100 || blocks[i][j].x>1050)|| blocks[i][j].y<400){
                        blocks[i][j].exist=0;
                        //printf("%d %d\n",i,j);
                    }


                    if(blocks[i][j].exist==1 && (ball.x+ball_radius>=blocks[i][j].x && ball.x-ball_radius<=blocks[i][j].x+block_width) && (ball.y+ball_radius>=blocks[i][j].y && ball.y-ball_radius<=blocks[i][j].y+block_height)) {
                    blocks[i][j].exist=0;
                    ball.dy=-1*ball.dy;



                    //printf("%d\n",++score);
                    score++;
                    if(sound) PlaySound("music\\boop.wav",NULL,SND_FILENAME | SND_ASYNC);

                }

            }
        }
        //blocks[10][1].x=100;
        //blocks[10][1].y=700;

        //Repositioning screen when score is hundred
        if(score%100==0) {

            for(int i=1;i<=10;i++){
                for(int j=1;j<=10;j++){
                    blocks[i][j].exist=1;
                }
            }
        }
        //Going to screen 3 when life is 0
        if(lives==0){
            screen=3;
        }

    }

    //=============================================

    //  Extreme Mode

    //=============================================


    if(screen==6 && start==1){
        itoa(score*100,score_string,10);
        //BALL MOVEMENT
        ball.x+=ball.dx;
        ball.y+=ball.dy;
        if(ball.x+ball_radius>=screen_width) ball.dx=-1*ball.dx;
        if(ball.y+ball_radius>=screen_height) ball.dy=-1*ball.dy;
        if(ball.x-ball_radius<=0) ball.dx=-1*ball.dx;
        if(ball.y-ball_radius<=0){
            lives--;
            powerup_active=0;
            puts("inactive life done");
            PlaySound("fall.wav",NULL,SND_FILENAME | SND_ASYNC);
            Sleep(1500);
            start=0;
            paddle.x=500;
            ball.x=paddle.x+paddle.width/2;
            ball.y=paddle.y+paddle.height+ball_radius;


        }
        //PADDLE COLLISION
        if((ball.x+ball_radius>=paddle.x && ball.x-ball_radius<paddle.x+paddle.width)&&(ball.y-ball_radius==paddle.y+paddle.height)){
            ball.dy=-1*ball.dy;
            PlaySound("music\\boop.wav",NULL,SND_FILENAME | SND_ASYNC);

        }



        //Collision with powerup
        //for(int p=0;p<9;p++){



        //}


       // for(int i=0;i<10;i++){
            //printf("Exist %d %d\n",i ,powerups_exist);
            if(powerup_active==1 && powerups_y>=0){
                powerups_y-=power_speed;
            }
            if(powerup_active==1 && powerups_y<0){
                //powerups_exist=0;
                powerup_active=0;
                powerups_y=720;
                puts("inactive crossed\n");
            }
        //}
        //BLOCK COLLISION
        for(int i=1;i<=10;i++){
                for(int j=1;j<=10;j++){
                    //Removing faulty ball
                    //if(blocks[i][j].exist==1 && (blocks[i][j].x<100 || blocks[i][j].x>1050)|| blocks[i][j].y<400){
                        //blocks[i][j].exist=0;
                        //printf("%d %d\n",i,j);
                    //}


                    if(blocks[i][j].exist==1 && (ball.x+ball_radius>=blocks[i][j].x && ball.x-ball_radius<=blocks[i][j].x+block_width) && (ball.y+ball_radius>=blocks[i][j].y && ball.y-ball_radius<=blocks[i][j].y+block_height)) {

                    ball.dy=-1*ball.dy;
                    score++;
                    printf("%d\n",powerup_active);
                    if(powerup_active==0 ){
                        puts("ok");
                        random_number=rand()%10;
                        powerups_exist=1;
                        powerup_active=1;

                        printf("%d is active",random_number);
                        powerups_x=blocks[i][j].x;
                        //powerups_y=blocks[i][j].y;
                        powerups_y=600;

                    }
                    blocks[i][j].exist=0;
                    //printf("%d\n",++score);

                    if(sound) PlaySound("music\\boop.wav",NULL,SND_FILENAME | SND_ASYNC);

                }
            //cOLLISION WITH POWERUP
            if(powerup_active==1&&(powerups_x+powerup_width>=paddle.x && powerups_x-powerup_width<=paddle.x+paddle.width)&&(powerups_y==paddle.y+paddle.height)){
                //printf("paddle collides with %d\n",p);
                //powerups_exist=0;
                puts("paddle hit");
                powerup_active=0;

                powerups_y=720;
                PlaySound("eat.wav",NULL,SND_FILENAME | SND_ASYNC);

                if(random_number==0) lifePlus();
                if(random_number==1) paddlePlus();
                if(random_number==2) ballMinus();
                if(random_number==3) lifeMinus();
                if(random_number==4) paddleMinus();
                if(random_number==5) ballPlus();
                if(random_number==6) paddleFast();
                if(random_number==7) ballBig();
                if(random_number==8) paddleSlow();
                if(random_number==9) ballSmall();


            }

            }
        }
        //blocks[10][1].x=100;
        //blocks[10][1].y=700;
        //cOLLISION WITH POWERUP
/*
            if(powerup_active==1&&(powerups_x+powerup_width>=paddle.x && powerups_x-powerup_width<=paddle.x+paddle.width)&&(powerups_y==paddle.y+paddle.height)){
                //printf("paddle collides with %d\n",p);
                //powerups_exist=0;
                puts("paddle hit");
                powerup_active=0;

                powerups_y=720;
                PlaySound("eat.wav",NULL,SND_FILENAME | SND_ASYNC);

                if(random_number==0) lifePlus();
                if(random_number==1) paddlePlus();
                if(random_number==2) ballMinus();
                if(random_number==3) lifeMinus();
                if(random_number==4) paddleMinus();
                if(random_number==5) ballPlus();
                if(random_number==6) paddleFast();
                if(random_number==7) ballBig();
                if(random_number==8) paddleSlow();
                if(random_number==9) ballSmall();


            }*/














        //Repositioning screen when score is hundred
        if(score%99==0) {

            for(int i=1;i<=10;i++){
                for(int j=1;j<=10;j++){
                    blocks[i][j].exist=1;
                }
            }
        }
        //Going to screen 3 when life is 0
        if(lives==0){
            screen=3;
        }

    }

}



//=====================
//  Screen 1
//=====================


void screen1(){
        iClear();
        iShowBMP(0,0,"home.bmp");
        iShowBMP(100,150,"b4.bmp");
        iShowBMP(100,265,"b3.bmp");
        iShowBMP(100,380,"b2.bmp");
        iShowBMP(100,495,"b1.bmp");

        iShowBMP(900,150,"b5.bmp");
        iShowBMP(900,265,"b6.bmp");

        iShowBMP(100,30,"mon.bmp");
        iShowBMP(175,30,"moff.bmp");
        //iText(400,525,"Boring version");


}



//=====================
//  Screen 2
//=====================
void screen2(){
    iClear();
    iShowBMP(0,0,"bg5.bmp");
    //showing the score
    iSetColor(74,74,74);
    //
    iText(165,22,score_string,GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
    //show lives

    if(lives==3) {
        iShowBMP(1220,15,"life.bmp");
        iShowBMP(1170,15,"life.bmp");
        iShowBMP(1120,15,"life.bmp");
    }
     if(lives==2) {
        iShowBMP(1170,15,"life.bmp");
        iShowBMP(1120,15,"life.bmp");
    }
     if(lives==1) {
        iShowBMP(1120,15,"life.bmp");
    }

    iFilledCircle(ball.x,ball.y,ball_radius);
    iFilledRectangle(paddle.x,paddle.y,paddle.width,paddle.height);

    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){

            if(blocks[i][j].exist==1) {

                iSetColor(blocks[i][j].r,blocks[i][j].g,blocks[i][j].b);
                iFilledRectangle(blocks[i][j].x,blocks[i][j].y,block_width,block_height);
                iSetColor(255,255,255);
            }
        }
    }




}
//=====================
//  Screen 3
//=====================
void screen3(){
    iClear();
    iShowBMP(0,0,"over.bmp");
    iSetColor(0,0,0);
    iText(450,475,score_string,GLUT_BITMAP_TIMES_ROMAN_24);
    iText(545,390,screen_input,GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
}

//=====================
//  Screen 4
//=====================
char* temp_score1[10];
char* temp_score2[10];

int line_dist=0;
//Highscores
void screen4(){
    iClear();
    iShowBMP(0,0,"score.bmp");
    iSetColor(0,0,0);
    //Rank
        //iText(235,485-line_dist,temp_score1[1],GLUT_BITMAP_TIMES_ROMAN_24);
        //Name
       // iText(325,485-line_dist,high_names[1],GLUT_BITMAP_TIMES_ROMAN_24);
        //Score
        //iText(450,485-line_dist,temp_score2[1],GLUT_BITMAP_TIMES_ROMAN_24);



    for(int i=0;i<10;i++){

        //Rank
        //iText(235,485-line_dist,temp_score1[i],GLUT_BITMAP_TIMES_ROMAN_24);
        //Name
        iText(300,450-line_dist,high_names[i],GLUT_BITMAP_TIMES_ROMAN_24);
        //Score
        iText(1040,450-line_dist,high_scores_string[i],GLUT_BITMAP_TIMES_ROMAN_24);
        //iText(450,485-line_dist,temp_score2[i],GLUT_BITMAP_TIMES_ROMAN_24);

        line_dist+=40;
    }

    line_dist=0;
    iSetColor(255,255,255);
}
//=====================
//  Screen 5
//=====================
//instrunctions page
void screen5(){
    iClear();
    iShowBMP(0,0,"inst.bmp");
}

//=====================
//  Screen 6
//=====================
//extreme page
void screen6(){
    iClear();
    iShowBMP(0,0,"bg5.bmp");
    //showing the score
    iSetColor(74,74,74);
    //
    iText(165,22,score_string,GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(255,255,255);
    //show lives

    if(lives==3) {
        iShowBMP(1220,15,"life.bmp");
        iShowBMP(1170,15,"life.bmp");
        iShowBMP(1120,15,"life.bmp");
    }
     if(lives==2) {
        iShowBMP(1170,15,"life.bmp");
        iShowBMP(1120,15,"life.bmp");
    }
     if(lives==1) {
        iShowBMP(1120,15,"life.bmp");
    }

    iFilledCircle(ball.x,ball.y,ball_radius);
    iFilledRectangle(paddle.x,paddle.y,paddle.width,paddle.height);

    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){

            if(blocks[i][j].exist==1) {

                iSetColor(blocks[i][j].r,blocks[i][j].g,blocks[i][j].b);
                iFilledRectangle(blocks[i][j].x,blocks[i][j].y,block_width,block_height);
                iSetColor(255,255,255);
            }
        }
    }



        if(powerup_active==1){
            if(random_number==0) iShowBMP(powerups_x,powerups_y,"p1.bmp");
            if(random_number==1) iShowBMP(powerups_x,powerups_y,"p2.bmp");
            if(random_number==2) iShowBMP(powerups_x,powerups_y,"p3.bmp");
            if(random_number==3) iShowBMP(powerups_x,powerups_y,"p4.bmp");
            if(random_number==4) iShowBMP(powerups_x,powerups_y,"p5.bmp");
            if(random_number==5) iShowBMP(powerups_x,powerups_y,"p6.bmp");
            if(random_number==6) iShowBMP(powerups_x,powerups_y,"p7.bmp");
            if(random_number==7) iShowBMP(powerups_x,powerups_y,"p8.bmp");
            if(random_number==8) iShowBMP(powerups_x,powerups_y,"p9.bmp");
            if(random_number==9) iShowBMP(powerups_x,powerups_y,"p10.bmp");

        }
}

//=====================
//  Screen 7
//=====================
//POWERUPS page

void screen7(){
    iClear();
    iShowBMP(0,0,"powerups.bmp");
}




void instructions(){
    iClear();
    iText(100,880,"=========================================INSTRUCTIONS=========================================");
    iText(100,800,"Press 'q' to go to the previous screen");
    iText(100,780,"Press 'x' to quit app");
    iText(100,760,"");
    iText(100,740,"Press '+' to increase the velocity");
    iText(100,720,"Press '-' to decrease the velocity");
    iText(100,700,"Press 'pageUp' to add new waves");
    iText(100,680,"Press 'pageDown' to remove a wave");
    iText(100,660,"Press 'rightArrow' to increase phase by 30deg");
    iText(100,640,"Press 'leftArray' to decrease phase by 30deg");
    iText(100,620,"");
    iText(100,600,"Press 'a' to decrease amplitude");
    iText(100,580,"Press 'A' to increase amplitude");
    iText(100,560,"Press 'f' to increase frequency");
    iText(100,540,"Press 'F' to increase frequency");
    iText(100,520,"Press '1' '2' '3' '4' '5' '6' to show/hide corresponding ball");
    iText(100,500,"Press '0' to show/hide sum curve ball");
    iText(100,480,"");
    iText(100,460,"Press 'S' to show the curve lines");
    iText(100,440,"Press 's' to hide the curve lines");
    iText(100,420,"Press 'p' to pause the ball movement");
    iText(100,400,"Press 'r' to resume the ball movement");

}






void iDraw(){

	//place your drawing codes here

	if(screen==1) screen1();
	if(screen==2) screen2();
    if(screen==3) screen3();
    if(screen==4) screen4();
    if(screen==5) screen5();
    if(screen==6) screen6();
    if(screen==7) screen7();

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    //new game
    if(screen==1&&(mx>=100&&mx<=400)&&(my>=495&&my<=560)){
        //Start music
        musicon=0;
        PlaySound(0,0,0);


        //Reset all the data
        score=0;
        paddle.x=500;
        ball.x=paddle.x+paddle.width/2;
        ball.y=paddle.y+paddle.height+ball_radius;

        lives=3;
        start=0;
        ball.dy=5;
        for(int i=1;i<=10;i++){
            for(int j=1;j<=10;j++){
                blocks[i][j].exist=1;
            }
        }
        //goto screen
        screen=2;
    }
    //continue
    if(screen==1&&(mx>=100&&mx<=400)&&(my>=380&&my<=445))  {

        getBlockData();
        getSaveData();
        screen=2;
    }
    //highscores
    if(screen==1&&(mx>=100&&mx<=400)&&(my>=265&&my<=330))  screen=4;

    //instructions
    if(screen==1&&(mx>=100&&mx<=400)&&(my>=150&&my<=215))  screen=5;
    //powerups screen
    if(screen==1&&(mx>=900&&mx<=1200)&&(my>=265&&my<=330)) {
        screen=7;
    }

    //extreme screen
    if(screen==1&&(mx>=900&&mx<=1200)&&(my>=150&&my<=215))  {
            musicon=0;
            PlaySound(0,0,0);
            //Reset all the data
            score=0;
            paddle.x=500;
            ball.x=paddle.x+paddle.width/2;
            ball.y=paddle.y+paddle.height+ball_radius;

            lives=3;
            start=0;
            ball.dy=5;
            for(int i=1;i<=10;i++){
                for(int j=1;j<=10;j++){
                    blocks[i][j].exist=1;
                }
            }
            screen=6;
    }
    if(screen==1&&(mx>=175&&mx<=225)&&(my>=30&&my<=80)&&musicon){
        musicon=0;
        PlaySound(0,0,0);
        printf("%d\n",musicon);

    }
     if(screen==1&&(mx>=100&&mx<=150)&&(my>=30&&my<=80)&&musicon==0){
        musicon=1;
        music="m1.wav";
        PlaySound(music,NULL,SND_LOOP | SND_ASYNC);
        printf("%d\n",musicon);
     }
    //==================================
    //  For screen 3
    //==================================
    if(screen==3 &&(mx>=1013&&mx<=1120)&&(my>=352&&my<=427)){
        puts("CLICKED");
        saveHighScores();
    }

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key)
{
	if(key == 'x')
	{
		//do something with 'x'
		exit(0);
	}
	//======================================
	//  Code for screen 2
	//======================================
    if(screen ==2 && key=='p'){
        iPauseTimer(0);
    }
    if(screen ==2 && key=='P'){
        iResumeTimer(0);
    }
    if(screen ==2 && key=='q'){
        saveData();
        saveBlockData();
        music="m1.wav";
        PlaySound(music,NULL,SND_LOOP | SND_ASYNC);
        screen=1;
    }

    if(screen ==2 && key=='s'){
        saveData();
        saveBlockData();
    }
    ///test




    //======================================
	//  Code for screen 3
	//======================================
    //if(screen ==3 && key=='q'){
        //screen=1;
    //}

    if(screen == 3 && key!='\b'){
        screen_input[screen_index]=key;
        screen_input[screen_index+1]='\0';
        screen_index++;
    }else{
        if(screen_index>0){
            screen_input[screen_index-1]='\0';
            screen_index--;
        }else{
            screen_index=0;
        }
    }
    if(screen==3 && key=='\n'){
        screen=1;
    }


	//======================================
	//  Code for screen 4
	//======================================
    if(screen ==4 && key=='q'){
        screen=1;
    }


    //======================================
	//  Code for screen 5
	//======================================
    if(screen ==5 && key=='q'){
        music="m1.wav";
        PlaySound(music,NULL,SND_LOOP | SND_ASYNC);
        screen=1;
    }
      //======================================
	//  Code for screen 6
	//======================================
    if(screen ==6 && key=='q'){
        screen=1;
    }
    if(screen ==6 && key=='p'){
        iPauseTimer(0);
    }
    if(screen ==6 && key=='P'){
        iResumeTimer(0);
    }
    //======================================
	//  Code for screen 6
	//======================================
    if(screen ==7 && key=='q'){
        screen=1;
    }
	//======================================
	//  Code for screen change
	//======================================
	if(screen==2 && key=='q') screen=1;
	if(screen==3 && key=='q') screen=1;
	if(screen==6 && key=='q') screen=1;
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	if(screen==2 && key==GLUT_KEY_RIGHT && paddle.x+paddle.width<=screen_width){
        paddle.x+=paddle.speed;
        if(!start) ball.x+=paddle.speed;
	}
	if(screen==2 && key==GLUT_KEY_LEFT && paddle.x>=0){
        paddle.x-=paddle.speed;
        if(!start) ball.x-=paddle.speed;
	}
	if(screen==2 &key==GLUT_KEY_UP){
        start=1;
	}

	//screen 6
    if(screen==6 && key==GLUT_KEY_RIGHT && paddle.x+paddle.width<=screen_width){
        paddle.x+=paddle.speed;
        if(!start) ball.x+=paddle.speed;
	}
	if(screen==6 && key==GLUT_KEY_LEFT && paddle.x>=0){
        paddle.x-=paddle.speed;
        if(!start) ball.x-=paddle.speed;
	}
	if(screen==6 &key==GLUT_KEY_UP){
        start=1;
	}
}
void getSaveData(){
    FILE *save_game;
    save_game=fopen("save.txt","r");
    if(save_game==NULL){
        printf("Error No file");
    }
    int data[50], index=0,a;
    while(fscanf(save_game,"%d",&a)!=EOF){
        data[index]=a;
        index++;
    }
    score=data[0];
    ball.x=data[1];
    ball.y=data[2];
    paddle.x=data[3];
    lives=data[4];
}
void saveData(){
    FILE *save_game;
    save_game=fopen("save.txt","w");
    if(save_game==NULL){
        printf("Error No file");
    }
    int data[10];
    data[0]=score;
    data[1]=ball.x;
    data[2]=ball.y;
    data[3]=paddle.x;
    data[4]=lives;
    for(int i=0;i<5;i++){
        fprintf(save_game,"%d\n",data[i]);
    }
    fflush(save_game);
}
void getBlockData(){
    FILE *block_save;
    block_save=fopen("block_save.txt","r");
    if(block_save==NULL){
        printf("blocksavefile not found");
    }
    int a, index=1,block_data[150];
    while(fscanf(block_save,"%d",&a)!=EOF){
        block_data[index]=a;
        index++;
    }
    index=1;
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            blocks[i][j].exist=block_data[index];
            index++;
        }
    }
}
void saveBlockData(){
    FILE *block_save;
    block_save=fopen("block_save.txt","w");
    if(block_save==NULL){
        printf("blocksavefile not found");
    }
    int block_data[150]={0},index=1;
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            block_data[index]=blocks[i][j].exist;
            //printf("%d\n",blocks[i][j].exist);
            //printf("%d\n",block_data[index]);
            index++;
        }
    }
    //
    for(int i=1;i<=100;i++){
        //printf("%d\n",block_data[i]);
        fprintf(block_save,"%d\n",block_data[i]);
    }

    //printf("%d",block_data[50]);
    fflush(block_save);

}




void getHighScores(){
    FILE *high_names_r;
    FILE *high_scores_r;

    high_names_r=fopen("high_names.txt","r+");
    high_scores_r=fopen("high_scores.txt","r+");

    puts("ok1");
    char *rough[20];
    int p=0;
    while(!feof(high_names_r)){
        fscanf(high_names_r,"%s",high_names[p]);
        p++;
    }
    for(int i=0;i<11;i++){
        puts(high_names[i]);
    }
    p=0;
    while(!feof(high_scores_r)){
        //fscanf(high_scores_r,"%s",&high_scores_string[p]);

        fscanf(high_scores_r,"%d",&high_scores[p]);
        sprintf(high_scores_string[p],"%d",high_scores[p]);
        puts(high_scores_string[p]);

        //fscanf(high_scores_r,"%s",&high_scores_string[p]);
        p++;
    }
    for(int i=0;i<10;i++){
        //printf("%d\n",high_scores[i]);
    }



    //CREATING STRINGS
    for(int i=0;i<10;i++){
        //sprintf(temp_score1[i],"%d",i+1);
        //sprintf(temp_score2[i],"%d",high_scores[i]);
        //itoa(i+1,temp_score1[i],10);

    }
    for(int i=0;i<10;i++){
        //printf("%s\n",temp_score1[i]);
    }

}
int temp_score;
char temp_name[20];
void changeArray(){
    for(int i=0;i<10;i++){
        if(score*100>=high_scores[i]){
            temp_score=high_scores[i];
            high_scores[i]=score*100;
            high_scores[i+1]=temp_score;
            strcpy(temp_name,high_names[i]);
            //temp_name=high_names[i];
            //high_names[i]=screen_input;
            strcpy(high_names[i],screen_input);
            strcpy(high_names[i+1],temp_name);
            //high_names[i+1]=temp_name;
           for(int j=9;j>i;j--){
                //high_names[j]=high_names[j-1];
                strcpy(high_names[j],high_names[j-1]);
                high_scores[j]=high_scores[j-1];
            }
        }
    }
}





void saveHighScores(){
    //changeArray();
    FILE *high_names_w;

    FILE *high_scores_w;
    //high_names_r=fopen("high_names.txt","r+");
    high_names_w=fopen("high_names.txt","w+");
    //high_scores_r=fopen("high_scores.txt","r+");
    high_scores_w=fopen("high_scores.txt","w+");
    puts("ok1");
    char *rough[20];
    for(int i=0;i<10;i++){
        //fscanf(high_names_r,"%s",rough);

        //strcpy(names[i],rough);
        //puts(names[i]);
    }
    for(int i=0;i<10;i++){
        //puts("ok");
        //puts(names[i]);
        fprintf(high_names_w,"%s\n",high_names[i]);
        fprintf(high_scores_w,"%d\n",high_scores[i]);
    }
    fflush(high_names_w);
    fclose(high_names_w);

    fclose(high_scores_w);

}














int main()
{
	//place your own initialization codes here.

	getHighScores();
	//musicon=1;
	music="m1.wav";
    if(musicon){
        PlaySound(music,NULL,SND_LOOP | SND_ASYNC);
        puts(music);
    }

	//timer needs to be before initialize
	iSetTimer(5,changeBall);
	//iSetTimer(5,powerUpChange);
    //int a=0;
    //int b=400;
    int red=230;
    int green=134;
    int blue=255;

    //Inputting the score
    itoa(score*100,score_string,10);
    //POWERUPS
    //int random_x=(rand()%670)+50;


    for(int i=0;i<10;i++){
        //powerups_exist[i]=0;
        //powerups_y[i]=rand()%900+720;
    }

    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            blocks[i][j].x=100+a*(block_width+3);
            blocks[i][j].y=b;
            blocks[i][j].exist=1;
            a++;
            blocks[i][j].r=red;
            blocks[i][j].g=green;
            blocks[i][j].b=blue;


            //defining different colors

            if(j+i==2){
                red=140;
                green=252;
                blue=85;
            }
            if(j+i==4){
                red=85;
                green=252;
                blue=249;
            }
            if(j+i==6){
                red=252;
                green=85;
                blue=107;
            }
            if(j+i==8){
                red=172;
                green=245;
                blue=130;
            }
            if(j+i==10){
                red=255;
                green=0;
                blue=0;
            }
            if(j+i==12){
                red=252;
                green=85;
                blue=107;
            }
            if(j+i==14){
                red=236;
                green=255;
                blue=0;
            }
            if(j+i==16){
                red=14;
                green=225;
                blue=27;
            }
            if(j+i==18){
                red=44;
                green=51;
                blue=132;
            }
            if(j+i==20){
                red=245;
                green=244;
                blue=130;
            }

        }
        a=0;
        b+=(block_height+3);



    }


   /*  for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            blocks[i][j].x=100+a*(block_width+3);
            blocks[i][j].y=b;
            a++;
      }
        a=0;
        b+=(block_height+3);
    }
*/

    powerup_active=0;


    //iSetTimer(5,allTimers);

    iShowBMP(0,0,"bg.bmp");
	iInitialize(screen_width, screen_height, "DX BALL");

	//iSetTimer(500,changeBall);
	return 0;
}
