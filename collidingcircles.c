
       #include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 70
#define HEIGHT 30
#define SQUARE_SIZE 4
#define DELAY 45000 
#define GRAVITY 10.0
#define RESTITUTION 0.8
#define TIME_STEP 0.1
#define CIRCLE_RADIUS 3

int main(){

typedef struct {
    int x, y;       // Top-left corner position
    int dx, dy;     // Movement direction
} Square;

typedef struct{
    int x,y;
    int dx ,dy;
}Circle;

void clearScreen() {
    printf("\033[2J"); // Clear the screen
    fflush(stdout);
}

void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y, x); // Move the cursor
    fflush(stdout);
}

void drawSquare(Square square) {
    for (int i = 0; i < SQUARE_SIZE; i++) {
        moveCursor(square.x, square.y + i);
        for (int j = 0; j < SQUARE_SIZE; j++) {
            printf("X"); // Draw square using 'X'
        }
    }
    fflush(stdout);
}

int checkCollision(Square a, Square b) {
    return !(a.x + SQUARE_SIZE <= b.x || b.x + SQUARE_SIZE <= a.x ||
             a.y + SQUARE_SIZE <= b.y || b.y + SQUARE_SIZE <= a.y);
}

void updatePosition(Square *square) {
    square->x += square->dx;
    square->y += square->dy;

    // Bounce off walls
    if (square->x <= 0 || square->x + SQUARE_SIZE >= WIDTH) {
        square->dx = -square->dx;
    }
    if (square->y <= 0 || square->y + SQUARE_SIZE >= HEIGHT) {
        square->dy = -square->dy;
    }
}

void handleCollision(Square *a, Square *b) {
    if (checkCollision(*a, *b)) {
        // Reverse directions upon collision
        a->dx = -a->dx;
        a->dy = -a->dy;
        b->dx = -b->dx;
        b->dy = -b->dy;
    }
}

void drawCircle(Circle circle)
{
    moveCursor(circle.x ,circle.y);
    printf("  oo  ");
    moveCursor(circle.x ,circle.y+1);
    printf("ooooooo");
    moveCursor(circle.x ,circle.y+2);
    printf("ooooooo");
    moveCursor(circle.x,circle.y+3);
    printf("  oo  ");

    
}

int checkCollisionforcircle(Circle a, Circle b) {
    return !(a.x + 2*CIRCLE_RADIUS <= b.x || b.x + 2*CIRCLE_RADIUS <= a.x ||
             a.y + 2*CIRCLE_RADIUS <= b.y || b.y + 2*CIRCLE_RADIUS <= a.y);
}

void updatePositionforcircle(Circle *circle) {
    circle->x += circle->dx;
    circle->y += circle->dy;

    // Bounce off walls
    if (circle->x <= 0 || circle->x + 2*CIRCLE_RADIUS >= WIDTH) {
        circle->dx = -circle->dx;
    }
    if (circle->y <= 0 || circle->y + 2*CIRCLE_RADIUS >= HEIGHT) {
        circle->dy = -circle->dy;
    }
}

void handleCollisionforcircle(Circle *a, Circle *b) {
    if (checkCollisionforcircle(*a, *b)) {
        // Reverse directions upon collision
        a->dx = -a->dx;
        a->dy = -a->dy;
        b->dx = -b->dx;
        b->dy = -b->dy;
    }
}
       Circle circle1 ={10,10,1,1};
       Circle circle2 ={20,20,-1,1};


       while(1){

            clearScreen();

            drawCircle(circle1);
            drawCircle(circle2);

            updatePositionforcircle(&circle1);
            updatePositionforcircle(&circle2);

            handleCollisionforcircle(&circle1,&circle2);

            usleep(DELAY);

       }
       return 0;
       }
    
