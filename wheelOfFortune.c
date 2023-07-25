#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>


// Constants
#define PUZZLE "HELLO WORLD"
#define PUZZLE_LENGTH strlen(PUZZLE)
#define MAX_GUESSES 6
#define WHEEL_SIZE 5
#define ANIMATION_DELAY 150000 // Microseconds

// Function prototypes
void displayBoard(const char* guessedLetters, int score, char wheelSegment, int *WHEEL);
char spinWheel();
void handleGuess(char *letter, const char* puzzle, char* guessedLetters, int* score);

int main() {
    srand(time(0));

    int score = 0;
    char guessedLetters[PUZZLE_LENGTH];
    //memset(guessedLetters, '_', PUZZLE_LENGTH);
    for (int i = 0; i< PUZZLE_LENGTH; i++) {
            guessedLetters[i] = '_';
    }
    guessedLetters[PUZZLE_LENGTH-1] = '\0';

    int wheel[WHEEL_SIZE] = {100, 200, 300, 400, 500};

    printf("Welcome to Wheel of Fortune!\n");
    printf("Guess the puzzle: ");

    while (1) {
        char wheelSegment = spinWheel(); // Spin the wheel and get the current segment

        for (int i = 0; i < WHEEL_SIZE; i++) {
            // Clear the screen (UNIX-based systems)
            system("clear");
            // For Windows: Use "cls" instead of "clear"

            displayBoard(guessedLetters, score, wheelSegment, wheel);
            printf("Spinning...\n");
            usleep(ANIMATION_DELAY);
            wheelSegment = (wheelSegment + 1) % WHEEL_SIZE; // Simulate spinning
        }

        // Wheel stops spinning, ask for letter guess
        displayBoard(guessedLetters, score, wheelSegment, wheel);

        char guess[2];
        printf("Guess a letter: ");
        //scanf("%c", &guess);
        guess[0] = getc(stdin);
        guess[1] = '\0';
        guess[0] = toupper(guess[0]);
    
        handleGuess(guess, PUZZLE, guessedLetters, &score);

        if (strcmp(guessedLetters, PUZZLE) == 0) {
            printf("\nCongratulations! You solved the puzzle!\n");
            displayBoard(guessedLetters, score, wheelSegment, wheel);
            break;
        }
    }

    return 0;
}

void displayBoard(const char* guessedLetters, int score, char wheelSegment, int *WHEEL) {
    printf("\n+-----------------+\n");
    printf("|  WHEEL OF FORTUNE  |\n");
    printf("+-----------------+\n");
    printf("|   PUZZLE: %s    |\n", guessedLetters);
    printf("|   SCORE: %d    |\n", score);
    printf("+-----------------+\n");

    // Display the wheel
    //int wheel[WHEEL_SIZE] = {100, 200, 300, 400, 500};
    printf("\n");
    for (int i = 0; i < WHEEL_SIZE; i++) {
        if (i == wheelSegment) {
            printf("  %c%d%c   ", '|', WHEEL[i], '|'); // Pointer at the current segment
        } else {
            printf(" %c%d%c  ", '/', WHEEL[i], '\\');
        }
    }
    printf("\n\n");
}

char spinWheel() {
    char wheel[WHEEL_SIZE] = {100, 200, 300, 400, 500};
    int index = rand() % WHEEL_SIZE;
    return index;
}

void handleGuess(char *letter, const char* puzzle, char* guessedLetters, int* score) {
    int correctGuess = 0;

    for (int i = 0; i < PUZZLE_LENGTH; i++) {
        if (puzzle[i]  == letter[0]) {
            guessedLetters[i] = letter[0];
            correctGuess++;
            // printf("%d!!!\n", i);
            // sleep(10);
        }
        // printf("%d!!!%c!%c\n", i, puzzle[i], letter[0]);
        // sleep(1);

    }

    if (correctGuess == 0) {
        printf("\nIncorrect guess!\n");
        *score -= (spinWheel() + 1) * 100; // Subtract points if incorrect guess
    } else {
        printf("\nCorrect guess!\n");
        *score += (spinWheel() + 1) * 100; // Add points if correct guess
    }
}
