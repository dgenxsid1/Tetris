#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <windows.h>                                                    //  header file for gotoxy
#include <stdio.h>                                                      //header file for standard input output
#include <dos.h>
#include <time.h>
using namespace std;



int gameOver();                                                     // displays game over
void title();                                                       // displays title tetris
void gameLoop();                                                    // runs game
void display();                                                     // display game board
bool makepieces();                                                  // make pieces
void initGame();                                                    // initializes game
void movepiece(int, int);                                           // move pieces
void collidable();                                                  // fix the piece
bool isCollide(int, int);                                           // check collisions
void userInput();                                                   // takes input from user
bool rotatepiece();                                                 // rotates the piece
void spawnpiece();                                                  // moves piece down
void speed();







COORD coord={0,0};                               //center of axis is set to the top left cornor of the screen
void gotoxy(int x,int y)                                                // gotoxy function
{
 coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

 int piece[4][4]= 
 {
 	{0, 0, 0, 0},
 	{0, 0, 0, 0},
 	{0, 0, 0, 0},
 	{0, 0, 0, 0}
 };

 int stage[31][20]={};                  
int field[31][20]={};
int x = 8, y = 0;                                               // coordinate
bool gameover = false;                                          // check whether game is over or not
long long int GAMESPEED ;                               // determines game speed
int score = 0,old_score=0;                                      // calculate score
int high_score = 0;                                      // to maintain high score



int getRandom()
{
     mt19937 mt(time(NULL)); 
     int random=mt()%7;
     return random;
}

void title()                                                        // title function
{
   system("cls");  
                                                   // clears screen
    cout << "================================================================================\n\n\n\n\n\n"
            "\t\t####### ####### ####### ######    ###    #####\n"    // C++ merges separate constant strings automatically
            "\t\t   #    #          #    #     #    #    #     #\n"
            "\t\t   #    #          #    #     #    #    #\n"
            "\t\t   #    #####      #    ######     #     #####\n"
            "\t\t   #    #          #    #   #      #          #\n"
            "\t\t   #    #          #    #    #     #    #     #\n"
      "########\t   #    #######    #    #     #   ###    #####\t\t########\n\n\n"
            "\nEASY: PRESS 1\nMEDIUM: PRESS 2\nHARD: PRESS 3\n"
            "PRESS ENTER TWICE AFTER SETTING THE LEVEL"
           "================================================================================\n";

           char ch;

           cin>>ch;

           // getch();

           if(ch=='1')
           {
           	GAMESPEED=25000;
           }

           else if(ch=='2')
           {
           	GAMESPEED=10000;
           }

           else if(ch=='3')
           {
           	GAMESPEED=5000;
           }

  

           // getch();                 
}


void gameLoop()                                                         // gameLoop function
{
	
    int time = 0;
    initGame();                                                    // initializes game
    while(!gameover)                                // check whether game is over or not
    {
        if (kbhit())   
        {                             // function to determine if key is pressed or not
            userInput(); 
        }  
                                 // calls function to take user input
        if (time < GAMESPEED) 
        {                      // for by default down
            time++;
        }

        else
        {
            spawnpiece();                                               // move the piece down
            time = 0;
        }
    }
}


	int piece_list[7][4][4]=    // pieces
{
    {{ 0, 0, 0, 0 },
     { 0, 0, 0, 0 },
     { 1, 1, 1, 1 },
     { 0, 0, 0, 0 }},    //  [----] 

    {{ 0, 0, 0, 0 },
     { 0, 1, 0, 0 },
     { 1, 1, 1, 0 },
     { 0, 0, 0, 0 }},   //   inverted T

    {{ 0, 0, 0, 0 },
     { 1, 1, 0, 0 },
     { 0, 1, 1, 0 },
     { 0, 0, 0, 0 }},   // Z

    {{ 0, 0, 0, 0 },
     { 0, 0, 1, 1 },
     { 0, 1, 1, 0 },
     { 0, 0, 0, 0 }},   //  S

    {{ 0, 0, 0, 0 },
     { 0, 1, 1, 0 },
     { 0, 1, 1, 0 },
     { 0, 0, 0, 0 }},   // box

    {{ 0, 0, 0, 0 },
     { 0, 1, 0, 0 },
     { 0, 1, 1, 1 },
     { 0, 0, 0, 0 }},   // rOTATed l

    {{ 0, 0, 0, 0 },
     { 0, 0, 1, 0 },
     { 1, 1, 1, 0 },
     { 0, 0, 0, 0 }}    // rotated L
};



void initGame()
{
	                                       
    for(int i=0;i<=30;i++)                                              
    {
        for(int j=0;j<=19;j++)                                         
        {

            field[i][j]=(j==0||j==19||i==30)?9:0;       //marks border with 9 and non border with 0

            stage[i][j]=field[i][j];

        }
    }

    makepieces();                                                       // calls makespieces function
    display();                                                          // calls display function
}


void spawnpiece()                                                       
{
    if (!isCollide(x, y + 1))                                          
        movepiece(x, y + 1);                                       
    else                                                                
     {
        collidable();

        makepieces(); 

        display();                                                      
    }
}

int gameOver()                                                          
{
    system("cls");                                                      
    cout << "\n\n\n\n"
            "\t #####     #    #     # ####### ####### #     # ####### ######\n"
            "\t#     #   # #   ##   ## #       #     # #     # #       #     #\n"
            "\t#        #   #  # # # # #       #     # #     # #       #     #\n"
            "\t#  #### #     # #  #  # #####   #     # #     # #####   ######\n"
            "\t#     # ####### #     # #       #     #  #   #  #       #   #\n"
            "\t#     # #     # #     # #       #     #   # #   #       #    #\n"
            "\t #####  #     # #     # ####### #######    #    ####### #     #\n"
            "\n\n\n\n";
            cout<<"\t\t\t\tYour score is : "<<score; 

            if(score>high_score)
            {
            	cout<<"!!!CONGRATULATIONS, YOU MADE A HIGH SCORE!!!!";
            }                   
            cout<<"\n\n\n";
            char ch;
            cout<<"\t\t\tWant to start a new game {y/n}: ";



            cin>>ch;
            if(ch=='y'){                                                
                gameover = false;

                score = 0;

                old_score=0;

                title();

                gameLoop();
            }
            cout<<endl;

            cout<<"Alt+f4 to exit the terminal and game";

            // cout<<"Press Alt+F4 to exit the terminal and game";
            // cout<<'\n';
            
}


bool rotatepiece()                                                      // rotate piece function
{
    int tmp[4][4];
    for (int i = 0; i < 4; i++)                                         // Save temporarily piece
        for (int j = 0; j < 4; j++)
            tmp[i][j] = piece[i][j];
    for (int i = 0; i < 4; i++)                                         // rotate
        for (int j = 0; j < 4; j++)
            piece[i][j] = tmp[3 - j][i];                            // rotates clockwise
    if (isCollide(x, y))
    {                                                               // And stop if it overlaps not to be rotated
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                piece[i][j] = tmp[i][j];
        return true;                                                    // rotation occurs
    }

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            field[y + i][x + j] -= tmp[i][j];                           // remove original piece
            field[y + i][x + j] += piece[i][j];                         // adds rotated piece
        }
    display();                                                          // calls display function
    return false;
}




void display()                                                          // display function
{
    system("cls");                                                      // clears the screen
    cout<<"\n\n\n\n\t\t Your Score : "<<score<<"\t\t Highest Score : "<<high_score;// displays score & high_score
    int a=10;
    for (int i = 0; i < 31; i++)                                        // loop for rows
    {
            gotoxy(32,a);                                               // for starting position of row
            a++;                                                        // updates row
        for (int j = 0; j < 20; j++)                                    // loop for column
        {
            switch (field[i][j])
            {
            case 0: cout<<" "<<flush;                                   // for empty space
                    break;
            case 9: cout<<"X"<<flush;                                   // for border and base
                    break;
            default: cout<<"#"<<flush;                                  // for filled part
                     break;
            }
        }
        cout<<endl;
    }
    cout << "\n\n\n\t\tA: left\tS: down\tD: right \t Space bar: rotate\t G: gameover \t E: Exit the game \t Alt+F4:Exit the terminal";      // for instructions
    if (gameover)                                                           // check for game over
        gameOver();                                                         // calls gameOver function
}

bool makepieces()                                                           // makepieces function
{
	// initialaize_pieces();

    x = 8;                                                                  // for middle of game
    y = 0;                                                                  // for random piece
    int pieceType = getRandom();
    for (int i = 0; i < 4; i++)                                             // loop for piece
    {
        for (int j = 0; j < 4; j++)
        {
            piece[i][j] = 0;
            piece[i][j] = piece_list[pieceType][i][j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            field[i][j + x] = stage[i][j + x] + piece[i][j];                 // copying piece to field

            if (field[i][j + x] > 1)                                        // collision occurs
            {
                gameover = true;                                            // denotes game over
                return true;
            }
        }
    }
    return false;
}


void movepiece(int x2, int y2)                                              // movepiece function
{
    for (int i = 0; i < 4; i++)                                             // remove piece
        for (int j = 0; j < 4; j++)
            field[y + i][x + j] -= piece[i][j];
    x = x2;                                                                 // update coordinates
    y = y2;
    for (int i = 0; i < 4; i++)                                      // assign a piece with the updated value
        for (int j = 0; j < 4; j++)
            field[y + i][x + j] += piece[i][j];
    display();                                                              // calls display function
}


void userInput()                                                        // user input function
{
    char key;
    key = getch();
    switch (key)
    {
    case 'd':   if (!isCollide(x + 1, y))                               // move right if(no collision
                    movepiece(x + 1, y);                                // move it
                break;
    case 'a':   if (!isCollide(x - 1, y))                               // move left if no collision
                    movepiece(x - 1, y);                                // move it
                break;
    case 's':   if (!isCollide(x, y + 1))                               // move down if no collision
                    movepiece(x, y + 1);                                // move it
                break;
    case ' ':   rotatepiece(); 
    			 break; 										//rotate piece

    case 'g': if(!gameover) { gameOver(); break;}

    case 'e': if(!gameover) {system("cls");gameover=1; break;}
    


    }
}


void collidable()                                                           // collidable function
{
    int c=1,k=29;
    for(int i=29;i>=0;i--)                                                  // for each row
    {
        c=1;
        for(int j=0;j<20;j++)                                               // for each column
        {
            if(field[i][j]==0)                                          // check for the empty space in a line
            {
                c=0;
                break;
            }
        }
        if(c==0)                                   // empty space found then copy as it is else don't do anything
        {
            for(int j=0;j<20;j++)
                stage[k][j] = field[i][j];          // copying after eliminating filled lines
            k--;
        }
    }
    for (int i = 0; i<31; i++)
        for (int j = 0; j<20; j++)
            field[i][j] = stage[i][j];                                  // copying final field then
    score += 10;                                                         // increase of 5 for fixing each piece
    score += (k+1)*20;                                                  // increase of 10 for removal of each line
    if(k>=1)                                                            // if lines removed are more than one
        score += 20;                                                    // then increase the score by 20
    if(score> high_score)                                               // updates high score if possible
        high_score = score;
    speed();                                                            // calls speed function
 }


bool isCollide(int x2, int y2)                                          // check for collisions
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (piece[i][j] && stage[y2 + i][x2 + j] != 0)
                return true;                                            // if collision then return true
    return false;                                                       // else remove false
}



void speed()                                                            // speed function
{
    if(score - old_score >=200 )
    {
        old_score += 200;
        GAMESPEED -= 5000;                                              // increases speed
    }
}


int main()
{
	title();  
	                                                      // calls title function
    gameLoop();                                                     // calls gameLoop function
    
    return 0;
	
}
