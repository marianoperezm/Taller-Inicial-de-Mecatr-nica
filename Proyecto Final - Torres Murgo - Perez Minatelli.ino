#include <Servo.h>  // Incluye la librería para controlar el servo

// Pines del L298N
int enA = 6;       	// PWM para Motor 1 (ENA)
int in1 = 7;        // IN1 para Motor 1
int in2 = 8;        // IN2 para Motor 1
int in3 = 5;        // IN3 para Motor 2
int in4 = 4;        // IN4 para Motor 2
int enB = 3;        // PWM para Motor 2 (ENB)

// Pines de los LEDs
int ledBlanco = 9;  // LED blanco para adelante
int ledRojo = 10;    // LED rojo para atrás

// Configuración del servo
Servo miServo; // Crear objeto para controlar el servo
int anguloServoRep = 90; // Ángulo del servo en reposo
int anguloServoDer = 60; // Ángulo del servo cuando gira hacia la derecha
int anguloServoIzq = 120; // Ángulo del servo cuando gira hacia la izquierda

char comando; // Variable para almacenar el comando recibido desde el teléfono

// Setup inicial
void setup() {

  Serial.begin(9600);
  Serial.println("Esperando comandos...");

  // Configura los pines del L298N
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Configura los pines de los LEDs
  pinMode(ledBlanco, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  // Asignamos el pin 11 para el servo
  miServo.attach(11);
  miServo.write(anguloServoRep); // Inicializamos el servo en 90°

  // Inicializa los motores apagados
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  // Apaga ambos LEDs al inicio
  digitalWrite(ledBlanco, LOW);
  digitalWrite(ledRojo, LOW);
  
}

void loop() {
  // Verificar si hay datos disponibles desde el módulo Bluetooth
  if (Serial.available()) {
    comando = Serial.read(); // Leer el comando del hc-05
  switch(comando){
      // Mostrar el comando recibido en el monitor serial

    case 'F': // Avanzar (Forward)
    // Avanza el motor y enciende el LED blanco
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 225);  // Velocidad Motor 1
      analogWrite(enB, 255);  // Velocidad Motor 2

    // Enciende el LED blanco y apaga el rojo
      digitalWrite(ledBlanco, HIGH);
      digitalWrite(ledRojo, LOW);    
      Serial.println("Comando recibido: Avanzar (F)");
      break;

    case 'B': // Retroceder (Backwards)
        // Reversa los motores y enciende el LED rojo
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, 225);  // Velocidad Motor 1
      analogWrite(enB, 255);  // Velocidad Motor 2

    // Enciende el LED rojo y apaga el Blanco
      digitalWrite(ledBlanco, LOW);
      digitalWrite(ledRojo, HIGH);
      Serial.println("Comando recibido: Retroceder (B)");
      break;

    case 'L': // Girar a la izquierda (Left)
      miServo.write(anguloServoIzq);
      Serial.println("Comando recibido: Izquierda (L)");
       break;

    case 'R': // Girar a la derecha (Right)
      miServo.write(anguloServoDer);
      Serial.println("Comando recibido: Derecha (R)");
        break;

    case 'G': // Adelante Izquierda
    // Avanza el motor, enciende el LED verde y gira el servo a 150°
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 225);  // Velocidad Motor 1
      analogWrite(enB, 255);  // Velocidad Motor 2

    // Enciende el LED blanco y apaga el rojo
      digitalWrite(ledBlanco, HIGH);
      digitalWrite(ledRojo, LOW);    
      Serial.println("Comando recibido: Adelante Izquierda (F)");

    // Gira el servo
      miServo.write(anguloServoIzq);
      break;

      case 'I': // Adelante Derecha
    // Avanza el motor, enciende el LED verde y gira el servo a 60°
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enA, 225);  // Velocidad Motor 1
      analogWrite(enB, 255);  // Velocidad Motor 2

    // Enciende el LED blanco y apaga el rojo
      digitalWrite(ledBlanco, HIGH);
      digitalWrite(ledRojo, LOW);    
      Serial.println("Comando recibido: Adelante Derecha");

    // Gira el servo
      miServo.write(anguloServoDer);
      break;

    case 'H': // Atrás Izquierda
    // Avanza el motor, enciende el LED verde y gira el servo a 150°
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, 225);  // Velocidad Motor 1
      analogWrite(enB, 255);  // Velocidad Motor 2

    // Enciende el LED rojo y apaga el blanco
      digitalWrite(ledBlanco, LOW);
      digitalWrite(ledRojo, HIGH);    
      Serial.println("Comando recibido: Atrás Izquierda (F)");

    // Gira el servo
      miServo.write(anguloServoIzq);
      break;

      case 'J': // Atrás Derecha
    // Avanza el motor, enciende el LED verde y gira el servo a 30°
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enA, 225);  // Velocidad Motor 1
      analogWrite(enB, 255);  // Velocidad Motor 2

    // Enciende el LED rojo y apaga el blanco
      digitalWrite(ledBlanco, LOW);
      digitalWrite(ledRojo, HIGH);   
      Serial.println("Comando recibido: Atrás Derecha");

    // Gira el servo
      miServo.write(anguloServoDer);
      break;

      case 'X': // Activar balizas
        Serial.println("Balizas activadas");
        while (true) { // Bucle infinito hasta recibir el comando 'x'
          digitalWrite(ledBlanco, HIGH);
          digitalWrite(ledRojo, LOW);
          delay(500); // Esperar 500ms
          digitalWrite(ledBlanco, LOW);
          digitalWrite(ledRojo, HIGH);
          delay(500); // Esperar 500ms

          // Salir del bucle si se recibe el comando 'x'
          if (Serial.available()) {
            char stopCommand = Serial.read();
            if (stopCommand == 'x') {
              Serial.println("Balizas desactivadas");
              digitalWrite(ledBlanco, LOW);
              digitalWrite(ledRojo, LOW);
              break;
            }
          }
        }
        break;
        
    default: //  Si no se aprieta ningún botón

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enA, 0);
      analogWrite(enB, 0);

    // Apaga ambos LEDs
      digitalWrite(ledBlanco, LOW);
      digitalWrite(ledRojo, LOW);
      Serial.print("Comando desconocido: ");
      Serial.println(comando);

      miServo.write(anguloServoRep); // Vuelve a la posición inicial (90°)
      break;
  
  delay(20); // Pequeña espera para evitar rebotar los pulsadores
  }
  }
}