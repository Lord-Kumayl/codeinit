#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 70            //All definations
#define HEIGHT 30
#define SQUARE_SIZE 4
#define DELAY 45000
#define GRAVITY 10.0
//#define RESTITUTION 0.8
#define TIME_STEP 0.1
#define CIRCLE_RADIUS 2

typedef struct {
    int x, y;       // Top-left corner position
    int dx, dy;     // Movement direction
} Square;

typedef struct {
    int x, y;
    int dx, dy;
} Circle;

Square squares[100];
int square_count = 0;
Circle circles[100];
int circle_count = 0;

// Function to clear the terminal screen
void clearScreen() {
    printf("\033[2J");
    fflush(stdout);
}

// Function to move the cursor in the terminal
void moveCursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

// Function to draw a square on the terminal screen
void drawSquare(Square square) {
    for (int i = 0; i < SQUARE_SIZE; i++) {
        moveCursor(square.x, square.y + i);
        for (int j = 0; j < SQUARE_SIZE; j++) {
            printf("X");  // Draw square using 'X'
        }
    }
    fflush(stdout);
}

// Function to check for a collision between two squares
int checkCollision(Square a, Square b) {
    return !(a.x + SQUARE_SIZE <= b.x || b.x + SQUARE_SIZE <= a.x ||
             a.y + SQUARE_SIZE <= b.y || b.y + SQUARE_SIZE <= a.y);
}

// Function to update the position of a square
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

// Function to handle collision between two squares
void handleCollision(Square *a, Square *b) {
    if (checkCollision(*a, *b)) {
        // Reverse directions upon collision
        a->dx = -a->dx;
        a->dy = -a->dy;
        b->dx = -b->dx;
        b->dy = -b->dy;
    }
}

// Function to draw a circle on the terminal screen
void drawCircle(Circle circle) {
    moveCursor(circle.x, circle.y);
    printf("  oo  ");
    moveCursor(circle.x, circle.y + 1);
    printf("ooooooo");
    moveCursor(circle.x, circle.y + 2);
    printf("ooooooo");
    moveCursor(circle.x, circle.y + 3);
    printf("  oo  ");
}

// Function to check for a collision between two circles
int checkCollisionForCircle(Circle a, Circle b) {
    return !(a.x + 2 * CIRCLE_RADIUS <= b.x || b.x + 2 * CIRCLE_RADIUS <= a.x ||
             a.y + 2 * CIRCLE_RADIUS <= b.y || b.y + 2 * CIRCLE_RADIUS <= a.y);
}

// Function to update the position of a circle
void updatePositionForCircle(Circle *circle) {
    circle->x += circle->dx;
    circle->y += circle->dy;

    // Bounce off walls
    if (circle->x <= 0 || circle->x + 2 * CIRCLE_RADIUS >= WIDTH) {
        circle->dx = -circle->dx;
    }
    if (circle->y <= 0 || circle->y + 2 * CIRCLE_RADIUS >= HEIGHT) {
        circle->dy = -circle->dy;
    }
}

// Function to handle collision between two circles
void handleCollisionForCircle(Circle *a, Circle *b) {
    if (checkCollisionForCircle(*a, *b)) {
        // Reverse directions upon collision
        a->dx = -a->dx;
        a->dy = -a->dy;
        b->dx = -b->dx;
        b->dy = -b->dy;
    }
}

// Command input thread function
void* commandThread(void* arg) {
    char buffer[1024];

    while (1) {
      clearScreen();
        printf("Enter command (ADD_SQUARE, ADD_CIRCLE): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character

        if (strcmp(buffer, "s") == 0) {
            if (square_count < 100) {
                Square new_square = {rand() % WIDTH-SQUARE_SIZE, rand() % HEIGHT-SQUARE_SIZE, 10, 10};
                squares[square_count++] = new_square;
                printf("Square added!\n");
            } else {
                printf("Maximum number of squares reached.\n");
            }
        } else if (strcmp(buffer, "c") == 0) {
            if (circle_count < 100) {
                Circle new_circle = {rand() % WIDTH-2*CIRCLE_RADIUS+2, rand() % HEIGHT-2*CIRCLE_RADIUS+2, 10, 10};
                circles[circle_count++] = new_circle;
                printf("Circle added!\n");
            } else {
                printf("Maximum number of circles reached.\n");
            }
        }


        else {
            printf("Invalid command.\n");
        }
    }
    return NULL;
}


int main() {
    pthread_t command_thread;

    //  new thread for handling commands
    if (pthread_create(&command_thread, NULL, commandThread, NULL) != 0) {
        perror("Failed to create command thread");
        return 1;
    }

    // Main loop for simulation
    while (1) {
        clearScreen();

        // Draw and update squares
        for (int i = 0; i < square_count; i++) {
            drawSquare(squares[i]);
            updatePosition(&squares[i]);
            handleCollision(&squares[0],&squares[1]);
        }

        

        // Draw and update circles
        for (int i = 0; i < circle_count; i++) {
            drawCircle(circles[i]);
             

            updatePositionForCircle(&circles[i]);
            handleCollisionForCircle(&circles[0],&circles[1]);
        }
       
        usleep(DELAY);  // Pause for a short time before the next frame
    }

    // Wait for the command thread to finish 
    pthread_join(command_thread, NULL);

    return 0;
}
