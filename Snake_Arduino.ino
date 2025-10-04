#include <LiquidCrystal.h>

// Configuración del LCD (ejemplo típico con Keypad Shield)
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Definición de botones (Keypad Shield o entradas digitales)
#define btnRIGHT   0
#define btnUP      1
#define btnDOWN    2
#define btnLEFT    3
#define btnSELECT  4
#define btnNONE    5

int adc_key_in = 0;
int key = btnNONE;

// Campo de juego (16x2)
const int WIDTH = 16;
const int HEIGHT = 2;

// Estado de la serpiente
int snakeX[32], snakeY[32]; // posiciones de la serpiente
int snakeLength = 3;
int dir = btnRIGHT;

// Comida
int foodX, foodY;

// Puntaje
int score = 0;

// Leer botones del Keypad Shield (A0)
int read_LCD_buttons() {
  adc_key_in = analogRead(0); // leer valor de A0
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;
}

// Generar comida aleatoria
void spawnFood() {
  foodX = random(0, WIDTH);
  foodY = random(0, HEIGHT);
}

// Inicialización
void setup() {
  lcd.begin(16, 2);
  randomSeed(analogRead(5));

  // posición inicial de la serpiente
  snakeX[0] = 5; snakeY[0] = 0;
  snakeX[1] = 4; snakeY[1] = 0;
  snakeX[2] = 3; snakeY[2] = 0;

  spawnFood();
}

// Dibujar en pantalla
void drawGame() {
  lcd.clear();

  // Dibujar comida
  lcd.setCursor(foodX, foodY);
  lcd.print("*");

  // Dibujar serpiente
  for (int i = 0; i < snakeLength; i++) {
    lcd.setCursor(snakeX[i], snakeY[i]);
    lcd.print((i == 0) ? "O" : "o");
  }

  // Mostrar puntaje
  lcd.setCursor(0, 1);
  lcd.print("P:" + String(score));
}

// Mover serpiente
void moveSnake() {
  // mover cuerpo
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // mover cabeza
  if (dir == btnRIGHT) snakeX[0]++;
  if (dir == btnLEFT)  snakeX[0]--;
  if (dir == btnUP)    snakeY[0]--;
  if (dir == btnDOWN)  snakeY[0]++;

  // detectar colisiones con bordes
  if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(2, 1);
    lcd.print("Puntaje:" + String(score));
    while (1); // detener juego
  }

  // detectar colisión con comida
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    score++;
    spawnFood();
  }
}

void loop() {
  key = read_LCD_buttons();
  if (key != btnNONE) {
    if (key == btnUP && dir != btnDOWN) dir = btnUP;
    if (key == btnDOWN && dir != btnUP) dir = btnDOWN;
    if (key == btnLEFT && dir != btnRIGHT) dir = btnLEFT;
    if (key == btnRIGHT && dir != btnLEFT) dir = btnRIGHT;
  }

  moveSnake();
  drawGame();
  delay(400 - (score * 20)); // más rápido con más puntaje
}
