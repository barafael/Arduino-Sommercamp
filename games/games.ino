/*
 * SNAKE FOR THE ARDUINO
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

/*
 * TFT pins
 */

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     53
#define TFT_RST    9  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 52   // set these to be whatever pins you like!
#define TFT_MOSI 51   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

const byte FIELD_SIZE = 4;
const byte BOARD_SIZE = 31;

const uint16_t BACKGROUND_COLOR = ST7735_BLACK;
const uint16_t SNAKE_COLOR      = ST7735_GREEN;
const uint16_t FOOD_COLOR       = ST7735_RED;
const uint16_t TEXT_COLOR       = ST7735_WHITE; 
const uint16_t CIRCLE_COLOR     = ST7735_GREEN;
const uint16_t CROSS_COLOR      = ST7735_RED;
const uint16_t WINNER_COLOR     = ST7735_CYAN;

const byte PIN_LEFT  = 5;
const byte PIN_DOWN  = 4;
const byte PIN_UP    = 3;
const byte PIN_RIGHT = 2;
const byte PIN_ENTER = 6;

bool playingSnake = true;

/*
 * Snake variables
 */

const byte SNAKE_MAX_LENGTH = 50;
const int FREEZE_DURATION = 1000;

struct Position2d {
    signed char x;
    signed char y;
};

Position2d snake[SNAKE_MAX_LENGTH];
byte snakeLength = 1;
bool didEat = false;
Position2d oldPosition;

Position2d food;

// specifies the direction of the snake
enum {
    DIR_LEFT  = 0,
    DIR_DOWN  = 1,
    DIR_UP    = 2,
    DIR_RIGHT = 3
};

byte direction = DIR_LEFT;
byte selectedDirection = DIR_LEFT;

/*
 * TicTacToe variables
 */

byte states[9];

byte selectedX = 1;
byte selectedY = 1;

byte activePlayer = 1;

byte countingMoves = 0;

void drawCircle (byte x, byte y) {
    tft.drawCircle(21 + 42 * x,21 + 42 * y, 15, CIRCLE_COLOR);  
}

void drawCross (byte x, byte y) {
    tft.drawLine(42 * x, 42 * y, 42 * (x + 1), 42 * (y + 1), CROSS_COLOR);
    tft.drawLine(42 * x, 42 * y + 42, 42 * (x + 1), 42 * y,  CROSS_COLOR);     
}

void initButtons() {
    pinMode(PIN_LEFT,  INPUT);
    pinMode(PIN_DOWN,  INPUT);
    pinMode(PIN_UP,    INPUT);
    pinMode(PIN_RIGHT, INPUT);
    pinMode(PIN_ENTER, INPUT);

    // activate pullup-resistors
    digitalWrite(PIN_LEFT,  HIGH);
    digitalWrite(PIN_DOWN,  HIGH);
    digitalWrite(PIN_UP,    HIGH);
    digitalWrite(PIN_RIGHT, HIGH);
    digitalWrite(PIN_ENTER, HIGH);
}

void setup(void) {
    // Use this initializer if you're using a 1.8" TFT
    tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
    tft.setRotation(2);

    initButtons();

    resetSnake();
    resetTicTacToe();
}

// lets the user change a game
void chooseGame() {
    bool didChoose = false;

    while (!didChoose) {
        tft.fillRect(0, 0, tft.width(), tft.height(), BACKGROUND_COLOR);

        tft.setCursor(10, 10);
        tft.setTextColor(FOOD_COLOR);
        tft.print("Choose a game");

        if (playingSnake) {
            tft.setCursor(10, 25);
            tft.setTextColor(SNAKE_COLOR);
            tft.print("> Snake");

            tft.setCursor(23, 40);
            tft.setTextColor(TEXT_COLOR);
            tft.print("Tic-Tac-Toe");
        } else {
            tft.setCursor(23, 25);
            tft.setTextColor(TEXT_COLOR);
            tft.print("Snake");

            tft.setCursor(10, 40);
            tft.setTextColor(SNAKE_COLOR);
            tft.print("> Tic-Tac-Toe");
        }

        tft.setCursor(10, 100);
        tft.setTextColor(FOOD_COLOR);
        tft.print("Up/Down/Enter");

        bool pressedUp    = false;
        bool pressedDown  = false;
        bool pressedEnter = false;

        do { 
            pressedUp    = digitalRead(PIN_UP)  == LOW;
            pressedDown  = digitalRead(PIN_DOWN) == LOW;
            pressedEnter = digitalRead(PIN_ENTER) == LOW;
            delay(50);
        } while (!pressedUp && !pressedDown && !pressedEnter);

        if (pressedUp) {
            playingSnake = true;
        } else if (pressedDown) {
            playingSnake = false;
        } else if (pressedEnter){
            didChoose = true;
        }
    }

    tft.fillRect(0, 0, tft.width(), tft.height(), BACKGROUND_COLOR);
}

/*
 * TicTacToe functions
 */

// resets the board and the game data
void resetTicTacToe() {
    for (byte i = 0; i < 9; i++) {
      states[i] = 0;
    }
    countingMoves = 0;

    chooseGame();
}

// conditionally sets the direction to a new one
void setSelectedField() {
    bool pressedLeft = false;
    bool pressedDown  = false;
    bool pressedUp    = false;
    bool pressedRight = false;
    bool pressedEnter = false;
  
    do { 
      delay(50);
      pressedLeft  = digitalRead(PIN_LEFT)  == LOW;
      pressedDown  = digitalRead(PIN_DOWN)  == LOW;
      pressedUp    = digitalRead(PIN_UP)    == LOW;
      pressedRight = digitalRead(PIN_RIGHT) == LOW;
      pressedEnter = digitalRead(PIN_ENTER) == LOW;
    } while (!pressedLeft && !pressedDown && !pressedUp && !pressedRight && !pressedEnter);

    if (pressedUp && selectedY != 0) {
      selectedY --;
    }
    if(pressedLeft && selectedX != 0) {
      selectedX --;
    }
    if(pressedDown && selectedY != 2) {
      selectedY ++;
    }
    if(pressedRight && selectedX != 2) {
      selectedX ++;
    }
    if(pressedEnter && !states[selectedX * 3 + selectedY]) {
      states[selectedX * 3 + selectedY] = activePlayer;
      drawTicTacToe();

      countingMoves ++;

      if (activePlayer == 1) {
        activePlayer = 2;
      } 
      else {
        activePlayer = 1;
      }
    }
    delay(200);
}

void drawField( byte x, byte y, byte state) {
  if (state == 1) {
    drawCircle(x, y);
  }
  if (state == 2) {
    drawCross(x, y);
  }
}

// redraws the whole board
void drawTicTacToe() {
    tft.fillRect(0, 0, tft.width(), tft.height(), BACKGROUND_COLOR);
  
    //draw the vertical lines
    tft.drawFastVLine(42, 0, 128, TEXT_COLOR);
    tft.drawFastVLine(84, 0, 128, TEXT_COLOR);
  
    // draw the horizontal lines
    tft.drawFastHLine(0, 42, 128, TEXT_COLOR);
    tft.drawFastHLine(0, 84, 128, TEXT_COLOR);

    tft.drawCircle(21 + 42 * selectedX, 21 + 42 * selectedY, 2, CIRCLE_COLOR); 

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            drawField(x, y, states[x * 3 + y]);
        }
    }
}

void winner() {
    const char* text = "Winner!";
    int16_t  x1, y1;
    uint16_t w, h;

    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    
    tft.setCursor(
        (tft.width() - w) / 2,
        (tft.height()-h) / 2
    );

    tft.setTextColor(WINNER_COLOR);
    tft.print(text);
    delay(1000);
}

/*
 * Snake functions
 */

// checks if the field is occupied
bool isOccupied(byte x, byte y) {
    for (byte i = 0; i < snakeLength; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return true;
        }
    }

    return false;
}

// sets the food location to a new random location
void placeFood() {
    byte randX = 0;
    byte randY = 0;

    // find a free location
    do {
        randX = random(BOARD_SIZE);
        randY = random(BOARD_SIZE);
    } while (isOccupied(randX, randY));

    // set the food location to the newly found location
    food.x = randX;
    food.y = randY;
}

// resets the board and the game data
void resetSnake() {
    direction = selectedDirection = DIR_LEFT;
    snakeLength = 1;
    didEat = false;

    snake[0].x = oldPosition.x = tft.width()  / 8;
    snake[0].y = oldPosition.y = tft.height() / 8;

    placeFood();
    
    tft.fillRect(0, 0, tft.width(), tft.height(), BACKGROUND_COLOR);

    chooseGame();
}

// displays the "game over" screen
void gameOver() {
    const char* text = "Game over!";
    int16_t  x1, y1;
    uint16_t w, h;

    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    
    tft.setCursor(
        (tft.width() - w) / 2,
        (tft.height()-h) / 2
    );

    tft.setTextColor(TEXT_COLOR);
    tft.print(text);
    delay(FREEZE_DURATION); 
}

// conditionally sets the direction to a new one
void setDirection() {
    // read user input
    bool pressedLeft  = digitalRead(PIN_LEFT)  == LOW;
    bool pressedDown  = digitalRead(PIN_DOWN)  == LOW;
    bool pressedUp    = digitalRead(PIN_UP)    == LOW;
    bool pressedRight = digitalRead(PIN_RIGHT) == LOW;

    // if user input is valid, modify the snake direction
    if (pressedLeft && (direction == DIR_UP || direction == DIR_DOWN)) {
        selectedDirection = DIR_LEFT;
    } else if (pressedDown && (direction == DIR_LEFT || direction == DIR_RIGHT)) {
        selectedDirection = DIR_DOWN;
    } else if (pressedUp && (direction == DIR_LEFT || direction == DIR_RIGHT)) {
        selectedDirection = DIR_UP;
    } else if (pressedRight && (direction == DIR_UP || direction == DIR_DOWN)) {
        selectedDirection = DIR_RIGHT;
    }
}

// moves the snake according to the direction variable
void moveSnake() {
    direction = selectedDirection;

    oldPosition.x = snake[0].x;
    oldPosition.y = snake[0].y;

    // move the snake's head
    if (direction == DIR_LEFT) {
        snake[0].x = oldPosition.x - 1;
    } else if (direction == DIR_DOWN) {
        snake[0].y = oldPosition.y + 1;
    } else if (direction == DIR_UP) {
        snake[0].y = oldPosition.y - 1;
    } else if (direction == DIR_RIGHT) {
        snake[0].x = oldPosition.x + 1;
    }

    // move the tail
    for (byte i = 1; i < snakeLength; i++) {
        byte x = snake[i].x;
        byte y = snake[i].y;
        snake[i].x = oldPosition.x;
        snake[i].y = oldPosition.y;
        oldPosition.x = x;
        oldPosition.y = y;
    }
}

// fills a field
void fillField(int x, int y, uint16_t color) {
    tft.fillRect(
        x * FIELD_SIZE + 2,  // position of the rectangle in x direction
        y * FIELD_SIZE + 2,  // position of the rectangle in y direction
        FIELD_SIZE,          // width
        FIELD_SIZE,          // height
        color                // color
    );
}

// redraws the whole board
void drawSnake() {
    // draw the head
    fillField(snake[0].x, snake[0].y, SNAKE_COLOR);

    for (byte i = 0; i < snakeLength; i++) {
        fillField(snake[i].x, snake[i].y, SNAKE_COLOR);
    }

    fillField(food.x, food.y, FOOD_COLOR);

    if (didEat) {
        // draw the food
        fillField(food.x, food.y, FOOD_COLOR);
        didEat = false;
    } else {
        // clear the old tail
        fillField(oldPosition.x, oldPosition.y, BACKGROUND_COLOR);
    }
}

// validates the last move and
// conditionally resets the game
void validateAction() {
    if (snake[0].x < 0 || snake[0].y < 0 || snake[0].x > BOARD_SIZE || snake[0].y > BOARD_SIZE) {
        gameOver();
        resetSnake();
    }

    // check if the snake is trying to eat itself
    for (byte i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            resetSnake();
            return;
        }
    }

    // check if the snake should eat
    if (snake[0].x == food.x && snake[0].y == food.y) {
        if (snakeLength < SNAKE_MAX_LENGTH) {
            didEat = true;
            snake[snakeLength].x = oldPosition.x;
            snake[snakeLength].y = oldPosition.y;
            snakeLength++;
            placeFood();
        } else {
            // snake too long
            gameOver();
            resetSnake();
        }
    }
}

void loop() {
    if (playingSnake) {
        for (byte i = 0; i < 6; i++) {
            setDirection();
            delay(50);
        }

        moveSnake();
        validateAction();
        drawSnake();
    } else {
        drawTicTacToe();
        setSelectedField();

        if (countingMoves == 9) {
            delay(1000);
            resetTicTacToe();
        }

        if (states[0] && states[0] == states[1] && states[1] == states[2] ||
                states[3] && states[3] == states[4] && states[4] == states[5] || 
                states[6] && states[6] == states[7] && states[7] == states[8] || 
                states[0] && states[0] == states[3] && states[3] == states[6] || 
                states[1] && states[1] == states[4] && states[4] == states[7] || 
                states[2] && states[2] == states[5] && states[5] == states[8] || 
                states[0] && states[0] == states[4] && states[4] == states[8] || 
                states[6] && states[6] == states[4] && states[4] == states[2]) {
            winner();
            delay (2000);
            resetTicTacToe();    
        }   
    }
}
