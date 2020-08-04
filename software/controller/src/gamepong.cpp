#include "gamepong.h"
extern TFT display;
extern char cmdBuffer[BUFFERMAX];


/**________ [160:128] ________**\
 *                             *
 * A_PADDLE           B_PADDLE *
 * ___________________________ */

#define XSCORE              52
#define YSCORE              10
#define XSCORE_BIG          24
#define YSCORE_BIG          50
#define PADDLE_MOVE         10
#define PADDLE_HEIGHT       25
#define PADDLE_WIDTH        5
#define APADDLE_X           0
#define BPADDLE_X           155
#define BALL_SIZE           4
#define WIN_POINTS          5

int
    ballSpeed,
    ballX, ballY, ballXold, ballYold, ballXdirection, ballYdirection,
    aPaddle, aPaddleOld, bPaddle, bPaddleOld;
byte
    aScore, bScore;


// Internal functions
void scoreWinner();
void scoreShow();
void scoreShowBlink(char *score);
void moveUp(int *paddle);
void moveDown(int *paddle);
void ballMove();
void ballDraw();
void ballReset();
byte ballPaddle(int paddleX, int paddleY, int direction);
void paddleReset();

// Show game screen
void gamepongPage() {
    ballXold = ballYold =
    aScore   = bScore   = 0;
    ballXdirection = millis()%2==0? 1: -1;      // Pseudo random direction of the ball (without rand() like functions)
    ballYdirection = millis()%3==0? 1: -1;
    scoreShow();
    ballReset();
    ballDraw();
    paddleReset();    
} /**/


void scoreShowBlink(char *score) {
    display.stroke(255, 255, 255);
    display.setCursor(XSCORE_BIG, YSCORE_BIG);
    display.print(score);
    delay(500);
    display.stroke(0, 0, 0);
    display.setCursor(XSCORE_BIG, YSCORE_BIG);
    display.print(score);
    delay(200);
} /**/

void scoreShow() {
    display.background(0, 0, 0);
    sprintf(cmdBuffer, "%2d:%d", aScore, bScore);
    // Score big
    display.setTextSize(4);
    scoreShowBlink(cmdBuffer);
    scoreShowBlink(cmdBuffer);
    scoreShowBlink(cmdBuffer);
    // Score small
    display.stroke(0, 255, 0);
} /**/

void scoreWinner() {
    if (aScore >= WIN_POINTS || bScore >= WIN_POINTS) {
        if (ballXdirection != 0) {
            if (aScore >= WIN_POINTS) {
                ballXdirection = 0x07E0;
                ballYdirection = 0x001F;
                ballX = 25;
                ballY = 105;
            } else {
                ballXdirection = 0x001F;
                ballYdirection = 0x07E0;
                ballX = 105;
                ballY = 25;
            }
            display.stroke(0, 0, 0);
            display.setTextSize(4);
            display.fillRect(APADDLE_X+PADDLE_WIDTH+1,   30, (LCD_WIDTH-PADDLE_WIDTH*3)/2+2, LCD_HEIGHT/3, ballXdirection);
            display.setCursor(32, 35);
            display.print(aScore);
            display.fillRect(LCD_WIDTH/2+PADDLE_WIDTH-1, 30, (LCD_WIDTH-PADDLE_WIDTH*3)/2-3, LCD_HEIGHT/3, ballYdirection);
            display.setCursor(110, 35);
            display.print(bScore);
            display.setTextSize(1);
            display.setCursor(ballX, 63);
            display.print(F("Winner"));
            display.setCursor(ballY, 63);
            display.print(F("Loser"));
            ballX = ballXold;
            ballY = ballYold;
            ballYdirection = ballXdirection = 0;
            display.stroke(255, 255, 255);
            display.setCursor(LCD_WIDTH/2-28, LCD_HEIGHT-40);
            display.print(F("Continue ?"));
            display.setCursor(LCD_WIDTH/2-70, LCD_HEIGHT-10);
            display.print(F("Left Button  Right Button"));
            display.setTextSize(2);
            display.setCursor(LCD_WIDTH/2-55, LCD_HEIGHT-30);
            display.print(F("YES    NO"));
        }
    }
} /**/

// Main Loop
void gamepongLoop() {
    // Clear previous and draw new
    if (aPaddleOld != aPaddle) {
        display.fillRect(APADDLE_X, aPaddleOld, PADDLE_WIDTH, PADDLE_HEIGHT, 0x0000);
        display.fillRect(APADDLE_X, aPaddle,    PADDLE_WIDTH, PADDLE_HEIGHT, 0xFFFF);
        aPaddleOld = aPaddle;
    }
    if (bPaddleOld != bPaddle) {
        display.fillRect(BPADDLE_X, bPaddleOld, PADDLE_WIDTH, PADDLE_HEIGHT, 0x0000);
        display.fillRect(BPADDLE_X, bPaddle,    PADDLE_WIDTH, PADDLE_HEIGHT, 0xFFFF);
        bPaddleOld = bPaddle;
    }
    // update ball's position and draw it on screen
    if (millis() % ballSpeed < 2) {
        ballMove();
    }
} /**/


void gamepongAction(byte Action) {
    switch (Action) {
    case ACTION_CONTROL_LEFT:
        moveUp(&bPaddle);
        break;
    case ACTION_CONTROL_RIGHT:
        moveDown(&bPaddle);
        break;
    case ACTION_MACRO_LEFT:
        moveUp(&aPaddle);
        break;
    case ACTION_MACRO_RIGHT:
        moveDown(&aPaddle);
        break;
    case ACTION_MACRO_BUTTON:
        if (ballXdirection==0) {        // Game Over
            gamepongPage();
        } else {                        // During Game
            stateSet(STATUS_NONE);
        }
        break;
    case ACTION_CONTROL_BUTTON:
        if (ballXdirection==0) {        // Game Over
            stateSet(STATUS_NONE);
        } else {                        // During Game
            gamepongPage();
        }
        break;
    }
} /**/


void moveUp(int *paddle) {
    *paddle = *paddle-PADDLE_MOVE>0 ? *paddle-PADDLE_MOVE: 0;
} /**/

void moveDown(int *paddle) {
    *paddle = *paddle+PADDLE_MOVE+PADDLE_HEIGHT<LCD_HEIGHT ? *paddle+PADDLE_MOVE: LCD_HEIGHT-PADDLE_HEIGHT;
} /**/


void ballMove() {
    // Ball vertically going off screen, reversing direction
    if (ballY+BALL_SIZE >= LCD_HEIGHT || ballY <= 0) {
        ballYdirection = -ballYdirection;
    }
    // Ball passing by [aPaddle] (X:0)
    if (ballX <= 0) {
        bScore++;
        scoreShow();
        ballReset();
        paddleReset();
        ballXdirection = -1;
    }
    // Ball passing by [bPaddle] (X:MAX)
    if (ballX >= LCD_WIDTH) {
        aScore++;
        scoreShow();
        ballReset();
        paddleReset();
        ballXdirection = 1;
    }
    // Detect if ball hits the paddles
    if (ballPaddle(APADDLE_X, aPaddle, -1) == 1 || ballPaddle(BPADDLE_X, bPaddle, 1) == 1) {
        ballXdirection = -ballXdirection;
    }
    // Elect winner, if any
    scoreWinner();
    // Move ball
    ballDraw();
} /**/


void ballReset() {
    ballX = LCD_WIDTH  / 2;
    ballY = LCD_HEIGHT / 2;
    ballSpeed = 100;
} /**/

void ballDraw() {
    ballXold = ballX;
    ballYold = ballY;
    ballX += ballXdirection;
    ballY += ballYdirection;
    display.fillRect(ballXold, ballYold, BALL_SIZE, BALL_SIZE, 0x0000);
    display.fillRect(ballX,    ballY,    BALL_SIZE, BALL_SIZE, 0xFFFF);
} /**/

byte ballPaddle(int paddleX, int paddleY, int direction) {
    if (ballX+BALL_SIZE >= paddleX  &&  ballX <= paddleX+PADDLE_WIDTH  &&
        ballY+BALL_SIZE >= paddleY  &&  ballY <= paddleY+PADDLE_HEIGHT &&
        direction == ballXdirection) {
            ballSpeed -= 5;
            return 1;
    }
    return 0;
} /**/

void paddleReset() {
    aPaddleOld = bPaddleOld = 0;
    aPaddle    = bPaddle    = (LCD_HEIGHT-PADDLE_HEIGHT) / 2;
} /**/
