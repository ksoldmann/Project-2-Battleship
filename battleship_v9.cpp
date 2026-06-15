/*
    Author: Katya M. Soldmann
    Date: June 10th, 2026
    Purpose: Battleship game project 2
*/

//System Libraries 
#include <iostream>//Input/Output Library
#include <cstdlib>//Random Number Library
#include <iomanip> //Input Output Manipulator 
#include <cmath> //Math Library
#include <fstream> //File Input/Output Library
#include <string> //String Library
#include <ctime> //Time Library
#include <vector> //Vector Library
using namespace std;

//User Libraries

//Global Constants - Physics/Chemistry/Conversions/Array Dimension
const int BRDSZ=10; //size of board never changes, always ten rows

//Function Prototypes
void prntBd(bool, char [][BRDSZ],bool shwShp=false);


//Execution Begins Here
int main(int argv,char **argc) {
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0))); 
  
int choice;
string crtr; //creator name
fstream in,out; //used to display creator name from file in into

in.open("in.dat",ios::in); //Input Output Files
out.open("out.dat",ios::out);
in>>crtr;   

do{ //do while loop around everything, so game is capable of restarting when player prompts it to do so at end of game
    //Declare Variables
    int plNum, //player's chosen numeric coordinate to attack
        rNum, //random number generated for player's numeric coordinates for ship placements
        coNum[5]; //opponent (computer's) randomly generated numeric coordinates 
       
    char plLet, //player's chosen alphabetic coordinate to attack
        coLet[5]; //opponent (computer's) randomly generated alphabetic coordinates
       
    float atkAc; //attack accuracy
    bool coHit1=false, //initilializing boolean statement that determines if opponent ships have been hit
         coHit2=false, 
         coHit3=false, 
         coHit4=false, 
         coHit5=false;
    const int SHIPS=5; 
    int remShip = SHIPS;
    float totHit=0.0f; //total number of successful hits player makes against opponent's ships
    float totShot=0.0f; //total shots player takes in an attempt to sink opponent's ships
    char board[BRDSZ][BRDSZ];
    for(int r=0;r<BRDSZ;r++)
        for(int c=0;c<BRDSZ;c++)board[r][c]=' ';
    //Initialize Variables
    in.open("in.dat",ios::in); //file input and output; outputs creator's name in introduction from a file
    out.open("out.dat",ios::out);
    in>>crtr;

    //Mapping Process -> Input to Outputs
    for(int i=0;i<SHIPS;i++){
        coLet[i]='K'+rand()%10;
        coNum[i]=rand()%10+11;
    } 


    //Display Input/Outputs
    cout<<"Welcome to battleship."<<endl<<endl;
    cout<<"This game was created by "<<crtr<<"."<<endl<<endl;
    cout<<"This game utilizes a ten by ten board for you, as well as a separate one for your opponent."<<endl<<endl;
    cout<<"You will begin with five ships."<<endl<<endl; //one with a length of five spaces, one with a length of four spaces, two with a length of three spaces, and one with a length of two spaces 
    cout<<"The placement of each of your ships will be chosen randomly."<<endl<<endl;
    cout<<"Here is your board; the coordinates of your ships will be printed below your board."<<endl<<endl;
    prntBd(false,board);
  

    
    cout<<"Your ship placements are as follows: "<<endl<<endl;
    for (int i = 1; i < 6; i++) { //player's randomly generated ship placements
        char lttr='A'+rand()%10; //randomly generated letter, A-J
        int rNum=rand()%10+1; //randomly generated number, 1-10
        cout<<" "<<lttr<<rNum<<" "<<endl<<endl; //print five randomly generated ship placements for player
       
    }
    cout<<"Here is your opponent's board: "<<endl;
    prntBd(true, board);


     cout<<"To launch an attack on your opponent, type the letter coordinate, then the number coordinate you would like to target."<<endl<<endl;
     cout<<"Remember that your opponent's coordinates run on a 11-20, K-T system."<<endl<<endl;
     cout<<"For example: typing P, pressing return, then entering 11 will attack the coordinate P11. If the opponent has a ship on that coordinate, it will sink."<<endl<<endl;
    
     while (remShip>0){
     cin>>plLet;
     cout<<"The row you chose was "<<plLet<<endl<<endl;
     cout<<"Input the column you would like as a single number between 11 and 20. "<<endl;
     cin>>plNum;
     totShot++;
     atkAc = static_cast<float>(totHit)/static_cast<float>(totShot)*100;
     atkAc=round(atkAc);

    if (!coHit1&&plLet==coLet[0]&&plNum==coNum[0]) { //if else if statements to keep track of player's attacks, both hits and misses
            cout<<"You have hit one of your opponent's ships - and it sank!"<<endl<<endl;
            cout<<"Accuracy: "<<setw(6)<<fixed<<setprecision(4)<<atkAc<<"%"<<endl<<endl;//outputs hit accuracy
            cout<<"Enter a letter coordinate between K and T to launch a new attack."<<endl;
            coHit1=true;
            remShip--;//decrement to decrease remaining ships by one each time the player hits a ship
            totHit++;//increment to increase total hits by one each time player hits an opponent's ship
          if (remShip==4){
            cout<<"You hit your first ship! Way to go!"<<endl; //encouragement for player; can take awhile to get first hit since board is so large 
            //after first hit, accuracy calc does not work properly, but it works for other cases. This bug will be fixed in project 2
        }

     }   
     else if (!coHit2&&plLet==coLet[1]&&plNum==coNum[1]) {
            cout<<"You have hit one of your opponent's ships - and it sank!"<<endl<<endl;
            cout<<"Accuracy: "<<setw(6)<<fixed<<setprecision(1)<<atkAc<<"%"<<endl<<endl;
            cout<<"Enter a letter coordinate between K and T to launch a new attack."<<endl;
            coHit2=true;
            remShip--;
            totHit++;
            if(remShip==3){
                cout<<"Three opponent ships left!"<<endl;
            
            }
                else
                cout<<"Great job!"<<endl;
    }
     else if (!coHit3&&plLet==coLet[2]&&plNum==coNum[2])  {
            cout<<"You have hit one of your opponent's ships - and it sank!"<<endl<<endl;
            cout<<"Accuracy: "<<setw(6)<<fixed<<setprecision(1)<<atkAc<<"%"<<endl<<endl;
            cout<<"Enter a letter coordinate between K and T to launch a new attack."<<endl;
            coHit3=true;
            remShip--;
            totHit++;
           
     }
     else if (!coHit4&&plLet==coLet[3]&&plNum==coNum[3])  {
            cout<<"You have hit one of your opponent's ships - and it sank!"<<endl<<endl;
            cout<<"Accuracy: "<<setw(6)<<fixed<<setprecision(1)<<atkAc<<"%"<<endl<<endl;
            cout<<"Enter a letter coordinate between K and T to launch a new attack."<<endl;
            coHit4=true;
            remShip--;
            totHit++;
            cout<<(remShip==1? "One ship left!" //player encouragement
                             :"Keep firing!")<<endl;
           
    }

     else if (!coHit5&&plLet==coLet[4]&&plNum==coNum[4])  {
            cout<<"You have hit one of your opponent's ships - and it sank!"<<endl<<endl;
            cout<<"Accuracy: "<<setw(6)<<fixed<<setprecision(1)<<atkAc<<"%"<<endl<<endl;
            coHit5=true;
            remShip--;
            totHit++;
            
     }
       
    else {
    cout<<"You did not hit any of your opponent's ships."<<endl<<endl;
    cout<<"To launch another attack, repeat the same process."<<endl;

    
      
     }
    }  


cout<<"You sank all your opponent's ships! Would you like to play again?"<<endl; //
cout<<"Type 1 for yes or 2 for no."<<endl;
cin>>choice;

switch(choice) { //switch case presents player with option to play again, using two possible options, and exits program if entry is invalid
    case 1: cout<<"The game will now restart."<<endl<<endl;break;
    case 2: cout<<"Hopefully you enjoyed battelship! Thanks for playing!"<<endl<<endl;break;
    default:cout<<"INVALID ENTRY"<<endl;choice=2;
}



} while (choice==1);
    //closing files
    in.close();    
    out.close(); 

   



    //Exit the Program
    return 0;   
}

void prntBd(bool isOpp,char board[][BRDSZ],bool shwShp){
    if(!isOpp){
        cout<<"  1   2   3   4   5   6   7   8   9   10"<<endl;
    string rows="ABCDEFGHIJ";
        for(int r=0;r<BRDSZ;r++){
            cout<<"  ___  ___  ___  ___  ___  ___  ___  ___  ___  ___"<<endl;
            cout<<rows[r]<<" |";
            for(int c=0;c<BRDSZ;c++)cout<<" "<<board[r][c]<<" |";
            cout<<endl;
        }
        cout<<"   ___  ___  ___  ___  ___  ___  ___  ___  ___  ___"<<endl<<endl;
    }else{
        cout<<"The opponent's board appears as follows: "<<endl<<endl;
        cout<<"   11   12   13   14   15   16   17   18   19   20"<<endl;  
        string rows="KLMNOPQRST";
        for(int r=0;r<BRDSZ;r++){
            cout<<" ___  ___  ___  ___  ___  ___  ___  ___ ___  ___"<<endl;
            cout<<rows[r]<<" |";
            for(int c=0;c<BRDSZ;c++)cout<<" "<<board[r][c]<<" |";
            cout<<endl;
        }
        cout<<" ___  ___  ___  ___  ___  ___  ___  ___  ___  ___"<<endl<<endl;
    
    }
    }
