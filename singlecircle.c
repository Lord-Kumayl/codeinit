#include <stdio.h>
#include <unistd.h> // For usleep function
#include <math.h>   // For fabs function

#define WIDTH 80
#define HEIGHT 40
#define GRAVITY 4
#define RESTITUTION 0
#define TIME_STEP 0.000005 // Time step in seconds

void clearScreen() {
    // ANSI escape code to clear the screen
    printf("\033[2J");
    fflush(stdout);
}

void moveCursor(int x, int y) {
    // ANSI escape code to move the cursor
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

void drawBall(int x, int y) {
    moveCursor(x, y);
    printf("O");
    fflush(stdout);
}

int main() {
    double x = WIDTH / 2.0, y = HEIGHT / 2.0; // Ball's initial position
    double vx = 5.0, vy = 0.0;                // Ball's initial velocity

    clearScreen();

    while (1) {
        // Clear previous ball position
        moveCursor(0, 0);
        printf("\033[2J");

        

    for(int i=0;i<HEIGHT;i++){
        for (int j=0;j<WIDTH;j++){

            if (j==0 ||i==0 ||i==(HEIGHT-1) || j==(WIDTH-1)){
                
            printf("#");
            }

            else if ((int)round(x)==i && (int)round(y)==j){
                printf("\033[0;0H");
            drawBall((int)round(x), (int)round(y));
            usleep((int)(TIME_STEP * 1000000));

            }
            else{

            printf ( " ");
            usleep((int)(TIME_STEP * 1000000));
            }



        }
        printf("\n");
    }




        // Draw ball at new position
        

        // Update velocity with gravity
        vy += GRAVITY * TIME_STEP;

        // Update position
        x += vx * TIME_STEP;
        y += vy * TIME_STEP;

        // Check for collision with walls and apply restitution
        if (x <= 0) {
            x = 0;
            vx = -vx; // Reverse horizontal velocity
        } else if (x >= WIDTH) {
            x = WIDTH;
            vx = -vx; // Reverse horizontal velocity
        }

        if (y >= HEIGHT) {
            y = HEIGHT;
            vy = -vy * RESTITUTION; // Reverse vertical velocity with restitution
            // If the vertical velocity is very small after collision, stop the ball
            if (fabs(vy) < 0.1) {
                vy = 0;
            }
        }

        // Wait before the next frame
        usleep((int)(TIME_STEP * 1000000));
    }

    return 0;
}