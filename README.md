# Juego-Snake-Arduino-ATMega2560
Juego Snake para Arduino Mega 2560 con pantalla LCD 16x2 y buzzer. Controlado con pulsadores.
#include <LiquidCrystal.h>

// Configuración del LCD (Keypad Shield típico)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Botones
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int adc_key_in  = 0;
int lcd_key     = 0;

// Tamaño del “campo de juego”
const int WIDTH = 16;
const int HEIGHT = 2;

// Serpiente
int snakeX[32];
int snakeY[32];
int snakeLength;
int dir;

// Comida
int foodX, foodY;

// Estado del juego
bool gameOver;
int score;

// Buzzer
int buzzerPin = 3;

// ==================== FUNCIONES ====================

int read_LCD_buttons() {
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;
}

void spawnFood() {
  bool valid = false;
  while (!valid) {
    foodX = random(0, WIDTH);
    foodY = random(0, HEIGHT);
    valid = true;
    // Evitar que aparezca encima de la serpiente
    for (int i = 0; i < snakeLength; i++) {
      if (snakeX[i] == foodX && snakeY[i] == foodY) {
        valid = false;
      }
    }
  }
}

void drawGame() {
  lcd.clear();
  
  // Mostrar puntaje en la esquina
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.print(score);

  // Dibujar comida
  lcd.setCursor(foodX, foodY);
  lcd.write('*');

  // Dibujar serpiente
  for (int i = 0; i < snakeLength; i++) {
    lcd.setCursor(snakeX[i], snakeY[i]);
    if (i == 0) lcd.write((byte)1); // cabeza
    else lcd.write('o'); // cuerpo
  }
}

void updateSnake() {
  // mover cuerpo
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // mover cabeza
  if (dir == btnUP)    snakeY[0]--;
  if (dir == btnDOWN)  snakeY[0]++;
  if (dir == btnLEFT)  snakeX[0]--;
  if (dir == btnRIGHT) snakeX[0]++;

  // verificar bordes
  if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
    gameOver = true;
    tone(buzzerPin, 300, 500); // sonido perder
    return;
  }

  // verificar choque con cuerpo
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
      tone(buzzerPin, 200, 500);
      return;
    }
  }

  // comer comida
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    score++;
    tone(buzzerPin, 1000, 200); // sonido comer
    spawnFood();
  }
}

void resetGame() {
  snakeLength = 3;
  score = 0;
  dir = btnRIGHT;
  gameOver = false;

  // Inicializar serpiente en medio
  snakeX[0] = 5; snakeY[0] = 0;
  snakeX[1] = 4; snakeY[1] = 0;
  snakeX[2] = 3; snakeY[2] = 0;

  spawnFood();
  lcd.clear();
  lcd.print("SNAKE listo!");
  delay(1000);
}

// ==================== SETUP ====================
void setup() {
  lcd.begin(16, 2);
  randomSeed(analogRead(5));
  pinMode(buzzerPin, OUTPUT);

  resetGame();
}

// ==================== LOOP ====================
void loop() {
  if (gameOver) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.print(score);
    delay(3000);
    resetGame();
  }

  // leer dirección
  lcd_key = read_LCD_buttons();
  if (lcd_key == btnUP && dir != btnDOWN) dir = btnUP;
  if (lcd_key == btnDOWN && dir != btnUP) dir = btnDOWN;
  if (lcd_key == btnLEFT && dir != btnRIGHT) dir = btnLEFT;
  if (lcd_key == btnRIGHT && dir != btnLEFT) dir = btnRIGHT;

  updateSnake();
  drawGame();

  // velocidad aumenta según puntaje
  int speed = 500 - (score * 20);
  if (speed < 150) speed = 150;
  delay(speed);
}
