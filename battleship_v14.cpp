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
bool isHit(char,int,char[],int[],bool[],int&,int&);
float accCal(float,float);
void prntMsg(int);
void prntMsg(string);
void usBrd(char [][BRDSZ],char,int,bool);
void rShot(vector<string> &,string);


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
    bool coHit[5]; //initilializing boolean statement that determines if opponent ships have been hit
         
    const int SHIPS=5; 
    int remShip = SHIPS;
    int totHit=0; //total number of successful hits player makes against opponent's ships
    float totShot=0.0f; //total shots player takes in an attempt to sink opponent's ships
    char board[BRDSZ][BRDSZ];
    for(int r=0;r<BRDSZ;r++)
        for(int c=0;c<BRDSZ;c++)board[r][c]=' ';
    
    vector<string> shotHis; //shot history storage
    string shotAr[200]; //sort/search array for shots
    int numSht=0; //number of shots taken

    
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
    for(int i=0;i<SHIPS;i++)coHit[i]=false;

    
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
     string coord="";
     coord+=plLet;
     coord+=to_string(plNum);
     rShot(shotHis,coord);
     shotAr[numSht++]=coord;
     totShot++;
     atkAc = accCal(static_cast<float>(totHit),totShot);
    

        bool hit=isHit(plLet,plNum,coLet,coNum,coHit,totHit,remShip);
        if(hit){
            cout<<"You have hit one of your opponent's ships - and it sank!"<<endl<<endl;
            cout<<"Accuracy: "<<setw(6)<<fixed<<setprecision(1)<<atkAc<<"%"<<endl<<endl;
            cout<<"Enter a letter coordinate between K and T to launch a new attack."<<endl<<endl;
            usBrd(board,plLet,plNum,true);
            prntMsg(remShip);
        }else{
            cout<<"You did not hit any of your opponent's ships."<<endl<<endl;
            usBrd(board,plLet,plNum,false);
            prntMsg(string("You did not hit a ship. Keep trying!"));
        }
    }  

bblSort(shotAr,numSht);
selSort(shotAr,numSht);
cout<<"Here are your sorted shots from this game: "<<endl;
    for(int i=0;i<numSht;i++)cout<<" "<<shotAr[i]<<endl;
    cout<<endl;

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

bool isHit(char plLet,int plNum,char coLet[],int coNum[],
           bool coHit[],int &totHit,int &remShip){
    for(int i=0;i<BRDSZ;i++){
        if(!coHit[i]&&plLet==coLet[i]&&plNum==coNum[i]){
            coHit[i]=true;
            totHit++;
            remShip--;
            return true;
        }
    }
    return false;
}
float accCal(float totHit,float totShot){
    if(totShot==0)return 0.0f;
    return round(totHit/totShot*100);
}
void prntMsg(int remShip){
    static int callCnt=0;
    callCnt++;
    if     (remShip==4)cout<<"You hit your first ship, great job!"<<endl<<endl;
    else if(remShip==3)cout<<"Three opponent ships remaining!"<<endl<<endl;
    else if(remShip==2)cout<<"Two opponent ships remaining!"<<endl<<endl;
    else if(remShip==1)cout<<"One ship left, you got this!"<<endl<<endl;
    else               cout<<"You sunk all your opponent's ships!"<<endl<<endl;
}
void prntMsg(string msg){
    static int callCnt=0;
    callCnt++;
    cout<<msg<<endl<<endl;

}

void usBrd(char board[][BRDSZ],char plLet,int plNum,bool hit){
    int row=plLet-'K';
    int col=plNum-11;
    if(row>=0&&row<BRDSZ&&col>=0&&col<BRDSZ)
        board[row][col]=hit?'H':'M';
}

void rShot(vector<string> &shots,string coord){
    shots.push_back(coord);
}

void bblSort(string shots[],int size){
    bool swapped;
    int redList=size-1;
    do{
        swapped=false;
        for(int i=0;i<redList;i++){
            if(shots[i]>shots[i+1]){
                string tmp=shots[i];
                shots[i]=shots[i+1];
                shots[i+1]=tmp;
                swapped=true;
            }
        }
        redList--;
    }while(swapped);
}
void selSort(string shots[],int size){
    for(int i=0;i<size-1;i++){
        int minIdx=i;
        for(int j=i+1;j<size;j++)
            if(shots[j]<shots[minIdx])minIdx=j;
        if(minIdx!=i){
            string tmp=shots[i];
            shots[i]=shots[minIdx];
            shots[minIdx]=tmp;
        }
    }
}
