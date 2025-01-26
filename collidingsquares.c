#include <stdio.h>
#include <math.h>
#include <unistd.h> // For usleep function

#define WIDTH 40
#define HEIGHT 20
#define SQUARE_SIZE 4
#define DELAY 100000 // Delay in microseconds (100 ms)

// Structure to represent a square
typedef struct {
    int x, y;       // Top-left corner position
    int dx, dy;     // Movement direction
} Square;

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

int main() {
    Square square1 = {5, 5, 1, 1};   // Initial position and direction for square 1
    Square square2 = {20, 10, -1, 1}; // Initial position and direction for square 2

    while (1) {
        // Clear the screen
        clearScreen();

        // Draw the squares
        drawSquare(square1);
        drawSquare(square2);

        // Update positions
        updatePosition(&square1);
        updatePosition(&square2);

        // Handle collision between the squares
        handleCollision(&square1, &square2);

        // Wait for the next frame
        usleep(DELAY);
    }

    return 0;
}