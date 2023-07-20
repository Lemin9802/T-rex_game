#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

const int WIDTH = 50;
const int HEIGHT = 5;
const int JUMP_HEIGHT = 3;
const int T_REX_ROW = HEIGHT - 1;

struct Player {
    int x;
    int y;
};

class TRexGame {
public:
    TRexGame() {
        // initialize the player at the left side of the screen
        player.x = 2;
        player.y = HEIGHT - 1;
        score = 0;
        isOver = false;
        srand(time(NULL));
    }

    void DisplayGame() {
        system("cls"); // clear the console before displaying the game

        // display the game board
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (y == player.y && x == player.x) {
                    cout << "O";
                }
                else if (y == HEIGHT - 1 && x == WIDTH - 10) {
                    cout << "Score: " << score;
                }
                else if (obstacleX == x && obstacleY == y) {
                    cout << "X";
                }
                else {
                    cout << ".";
                }
            }
            cout << endl;
        }
    }

    void MovePlayerUp() {
        if (player.y == HEIGHT - 1) {
            // start the jump
            jumpHeight = JUMP_HEIGHT;
        }
    }

    void UpdateGame() {
        // update the player position based on the jump height
        if (jumpHeight > 0) {
            player.y--;
            jumpHeight--;
        }
        else if (player.y < HEIGHT - 1) {
            player.y++;
        }

       // update the obstacle position
		obstacleX--;
		if (obstacleX < 0) {
		    obstacleX = WIDTH - 1;
		    obstacleY = T_REX_ROW;
		    score++;
		}


        // check for collision
        if (obstacleX == player.x && obstacleY == player.y) {
            isOver = true;
        }
    }

    bool IsGameOver() {
        return isOver;
    }

private:
    Player player;
    int score;
    int obstacleX = WIDTH - 1;
    int obstacleY = HEIGHT - 1;
    int jumpHeight = 0;
    bool isOver;
};

int main() {
    TRexGame game;

    while (!game.IsGameOver()) {
        game.DisplayGame();

        // get the user's input and update the player position
        if (_kbhit()) {
            char input = _getch();
            if (input == ' ') {
                game.MovePlayerUp();
            }
        }

        // update the game state
        game.UpdateGame();

        // wait for 100 milliseconds before the next iteration
        Sleep(100);
    }

    // print the game over message
    cout << "Game Over!" << endl;
    cout << "Your score: " << game.IsGameOver() << endl;

    return 0;
}
