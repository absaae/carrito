#include <AFMotor.h>
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MAX_SPEED 150
#define ENCODER_PIN 2
#define ENCODER_TYPE 3

// Configuración del motor
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(3, MOTOR12_1KHZ);

// Configuración del sensor ultrasónico
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Variables para el codificador
long encoderCount = 0;
long lastEncoderCount = 0;
int encoderDirection = 0; // 1 para adelante, -1 para atrás

// Función para leer el valor del codificador
long readEncoder() {
  long newCount = encoderRead(ENCODER_PIN);
  encoderDirection = (newCount > lastEncoderCount) ? 1 : -1;
  lastEncoderCount = newCount;
  return newCount;
}

// Función para actualizar la pantalla OLED
void updateOLED() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Distancia: ");
  display.print(sonar.ping_cm());
  display.print(" cm");
  display.setCursor(0, 16);
  display.print("Rotaciones: ");
  display.print(readEncoder());
  display.display();
}

// Función para mover el robot
void move(int speed, int direction) {
  motor1.setSpeed(speed * direction);
  motor2.setSpeed(speed * direction);
}

void setup() {
  // Inicializar comunicación serial
  Serial.begin(9600);

  // Inicializar codificador
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), readEncoder, CHANGE);

  // Inicializar sensor ultrasónico
  sonar.begin();

  // Inicializar pantalla OLED
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  // Leer distancia con el sensor ultrasónico
  int distance = sonar.ping_cm();

  // Leer valor del codificador
  long encoderValue = readEncoder();

  // Actualizar pantalla OLED
  updateOLED();

  // Control de movimiento
  if (distance <= 20) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);

    // Implementar lógica para mirar a izquierda y derecha (con servo motor)
    // y girar hacia el lado con más espacio.

  } else {
    moveForward();
  }
}

void moveStop() {
  move(0, 0);
}

void moveForward() {
  move(MAX_SPEED, 1);
}

void moveBackward() {
  move(MAX_SPEED, -1);
}
