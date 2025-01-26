#include <iostream>
#include <conio.h>
//#include <winuser.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include<vector>
#include <unistd.h>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;
using namespace std;
#define HEIGHT 30
#define WIDTH 100


 int fps = 5;


vector<vector<char>> world(HEIGHT, vector<char>(WIDTH));



void boundary();
void display(const vector<vector<char>>& world);
//void World();
 void clearScreen();
void setup();
void Draw(volatile int x_coor,volatile int y_coor);
 int y_coor(volatile float dt,volatile int y_in,float vel);
 int x_coor(volatile float dt,volatile int x_in,float vel);
void drawball(int x,int y);
void sprite(int x,int y,int side);
void cursor_pos(int x,int y);

int x_m=0,y_m=0;



int main()
{   

   
  //  Draw((HEIGHT/2),(WIDTH/2));
 
 // int y_in = HEIGHT/2;
  //int x_in = WIDTH/2;
  //volatile float dt =0;
 // World();
 boundary();

while(true){
   //  milliseconds frame_duration(1000 / fps);
     std::ios::sync_with_stdio(false);
     cout.tie(0);
   // auto start_time = high_resolution_clock::now();

    system("cls");
     sleep_for(milliseconds(0));
    //sprite(x_m,y_m,0);
    x_m++;
    display(world);
     sleep_for(milliseconds(100));
   
    
 //       auto end_time = high_resolution_clock::now();
 //      milliseconds frame_time = duration_cast<milliseconds>(end_time - start_time  );
 //      // Sleep for the remaining time to maintain the FPS
 //      if (frame_time < frame_duration) {
 //           sleep_for(frame_duration - frame_time);
 //     }
        

}

return 0;
}








void display(const vector<vector<char>>& buffer){





    for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
       
                
            cout<<buffer[i][j]<<flush;
            //fflush(stdout);
            

    }
    cout<<'\n';
  //  cout.flush();
    //fflush(stdout); 
}
cout.flush();

}

void sprite(int x,int y,int side){
    for(int i=y-1;i<(side+y);i++){
        world[i][x-1]  = ' ';
    }

    for(int i=y;i<(side+y);i++){
    for(int j=x;j<(side+x);j++){
       
                
            world[i][j] = '*';

    }
    
}
}





 
void boundary(){
for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
        if (j==0 ||i==0 ||i==(HEIGHT-1) || j==(WIDTH-1)){
                
            world[i][j] ='#';
            }
        else
        world[i][j]=' ';
    }
}

    for(int i=0;i<HEIGHT;i++){
    for(int j=0;j<WIDTH;j++){
       
                
            cout<<world[i][j]<<flush;
            //fflush(stdout);
            

    }
    cout<<'\n';
    cout.flush();
    //fflush(stdout); 
}
}

