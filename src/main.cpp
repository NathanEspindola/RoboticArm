/*
 * PUCRS - Pontifícia Universidade Católica do Rio Grande do Sul
 * Escola Politécnica
 * Engenharia da Computação
 * Trabalho de Conclusão de Curso
 * Aluno Nathan Espindola
 * Orientador Professor Mestre Julio Cesar Marques de Lima
 * This sketch uses the Arduino ESP32 Servo Library to sweep 4 servos in sequence.
 * 
 * Different servos require different pulse widths to vary servo angle, but the range is 
 * an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
 * sweep 180 degrees, so the lowest number in the published range for a particular servo
 * represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
 * of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
 * 1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
 * degrees.
 * 
 * Circuit:
 * Servo motors have three wires: power, ground, and signal. The power wire is typically red,
 * the ground wire is typically black or brown, and the signal wire is typically yellow,
 * orange or white. Since the ESP32 can supply limited current at only 3.3V, and servos draw
 * considerable power, we will connect servo power to the VBat pin of the ESP32 (located
 * near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS. 
 * 
 * We could also connect servo power to a separate external
 * power source (as long as we connect all of the grounds (ESP32, servo, and external power).
 * In this example, we just connect ESP32 ground to servo ground. The servo signal pins
 * connect to any available GPIO pins on the ESP32 (in this example, we use pins
 * 22, 19, 23, & 18).
 * 
 * In this example, we assume four Tower Pro SG90 small servos.
 * The published min and max for this servo are 500 and 2400, respectively.
 * These values actually drive the servos a little past 0 and 180, so
 * if you are particular, adjust the min and max values to match your needs.
 * Experimentally, 550 and 2350 are pretty close to 0 and 180.
 */

// PIN MANAGER
// 12 - Servo1
// 13 - Servo2
// 15 - Servo3
// 2
// 17
// 22 - Ultrasonic Trig
// 21 - Ultrasonic Echo
// 27 - Servo4
// 26 - Servo5
// 25 - Servo6
// 33
// 32
// SVN
// 38
// 37
// SVP

//#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Ultrasonic.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// WiFI & MQTT ================================================================
/*
const char* ssid = "PUG";
const char* password = "lovemy2pugs";

const char* mqtt_server = "192.168.2.15";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

void wifiSetup(void)
{

}*/

// DISPLAY ================================================================

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

uint32_t targetTime = 0;       // for next 1 second timeout

byte omm = 99;
boolean initial = 1;
byte xcolon = 0;
unsigned int colour = 0;

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

uint8_t hh=conv2d(__TIME__), mm=conv2d(__TIME__+3), ss=conv2d(__TIME__+6);  // Get H, M, S from compile time

//void displaysetup(void);

void displaySetup(void){

	tft.init();
	tft.setRotation(1);
	tft.fillScreen(TFT_BLACK);

	tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour

	targetTime = millis() + 1000; 
}

// SERVO ================================================================

Servo servo1;
Servo servo2;
//Servo servo3;
//Servo servo4;
//Servo servo5;
//Servo servo6;

int minUs = 500;
int maxUs = 2500;

int servo1Pin = 12;
int servo2Pin = 13;
//int servo3Pin = 15;
//int servo4Pin = 27;
//int servo5Pin = 26;
//int servo6Pin = 25;

ESP32PWM pwm;

void vInitHW(void);

void vInitHW(void)
{
	Serial.begin(115200);

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	servo1.setPeriodHertz(250);   
	servo2.setPeriodHertz(250);    
 	//servo3.setPeriodHertz(250);    
	//servo4.setPeriodHertz(250);    
	//servo5.setPeriodHertz(250);    
	//servo6.setPeriodHertz(250);    

}

// ULTRASONIC ================================================================

const int echoPin = 21;
const int trigPin = 22;

#define SOUND_SPEED 0.034

long duration;
float distance;

void ultrasonicSetup(void)
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

// RTOS TASKS ================================================================

TaskHandle_t xTask1Handle,xTask2Handle, xTask3Handle, xTask4Handle;
TaskHandle_t xTask5Handle,xTask6Handle, xTask7Handle, xTask8Handle;
TaskHandle_t xTask9Handle; //,xTask6Handle, xTask7Handle, xTask8Handle;


void vTask1(void *arg);
void vTask2(void *arg);
//void vTask3(void *arg);
//void vTask4(void *arg);
//void vTask5(void *arg);
//void vTask6(void *arg);
void vTask7(void *arg);
void vTask8(void *arg);
//void vTask9(void *arg);


void loop() { 
    vTaskDelay(pdMS_TO_TICKS(3000));    /* Delay de 3 segundos */
}

void vTask1(void *arg) // Controle Servo 1
{
	(void) arg;
	
	while(1)
	{
		servo1.attach(servo1Pin, minUs, maxUs);
		pwm.attachPin(27, 10000);//10khz

    

      if (distance <= 10)
      {
        servo1.write(0);
        delay(20);             // waits 20ms for the servo to reach the position
      }

      if (distance > 10) 
      {
        servo1.write(90);
        delay(20);
      }		

    

		servo1.detach();
		pwm.detachPin(27);

    vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask2(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{

		servo2.attach(servo2Pin, minUs, maxUs);
		pwm.attachPin(27, 10000);//10khz

		for (int pos2 = 0; pos2 <= 180; pos2 += 1) { // sweep from 0 degrees to 180 degrees
			servo2.write(pos2);
			delay(20);             // waits 20ms for the servo to reach the position
		}

		for (int pos2 = 180; pos2 >= 0; pos2 -= 1) { // sweep from 180 degrees to 0 degrees
			servo2.write(pos2);
			delay(20);
		}		

		servo2.detach();
		pwm.detachPin(27);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask7(void *arg) // Display
{
	(void) arg;

	while(1)
	{

    if (targetTime < millis()) 
    {
      targetTime = millis() + 1000;
      ss++; // Advance second

      if (ss == 60) 
      {
        ss = 0;
        omm = mm;
        mm++; // Advance minute

        if(mm > 59) 
        {
          mm = 0;
          hh++; // Advance hour

          if (hh > 23) 
          {
            hh = 0;
          }
        }
      }      

      if (ss == 0 || initial) 
      {
        initial = 0;
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.setCursor (50, 0);
        tft.print(__DATE__); // This uses the standard ADAFruit small font

        //tft.setTextColor(TFT_BLUE, TFT_BLACK);
        //tft.drawCentreString("It is windy", 120, 48, 2); // Next size up font 2

        //tft.setTextColor(0xF81F, TFT_BLACK); // Pink
        //tft.drawCentreString("12.34",80,100,6); // Large font 6 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 . : a p m
      }
      // Update digital time
      byte xpos = 0;
      byte ypos = 0;

      if (omm != mm) 
      { // Only redraw every minute to minimise flicker
        // Uncomment ONE of the next 2 lines, using the ghost image demonstrates text overlay as time is drawn over it
        tft.setTextColor(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
        //tft.setTextColor(TFT_BLACK, TFT_BLACK); // Set font colour to black to wipe image
        // Font 7 is to show a pseudo 7 segment display.
        // Font 7 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .
        tft.drawString("88:88", xpos, ypos, 2); // Overwrite the text to clear it
        tft.setTextColor(0xFBE0, TFT_BLACK); // Orange
        omm = mm;

        if (hh < 10) xpos+= tft.drawChar('0', xpos, ypos, 2);
        xpos+= tft.drawNumber(hh, xpos, ypos, 2);
        xcolon = xpos;
        xpos+= tft.drawChar(':', xpos, ypos, 2);
        if (mm < 10) xpos+= tft.drawChar('0', xpos, ypos, 2);
        tft.drawNumber(mm, xpos, ypos, 2);
      }

      else if (ss%2) 
      { // Flash the colon
        tft.setTextColor(0x39C4, TFT_BLACK);
        xpos+= tft.drawChar(':', xcolon, ypos, 2);
        tft.setTextColor(0xFBE0, TFT_BLACK);
      }
    }
    
    // IMPRIME DISTANCIA EM cm NO DISPLAY TFT ==================================
    float updatecm;

    if(distance != updatecm)
    {
      tft.setTextColor(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
      tft.drawString("8888", 0, 75, 7); // Overwrite the text to clear it
    }

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawNumber(distance, 0, 75, 7);
    updatecm = distance;

    vTaskDelay(pdMS_TO_TICKS(10));     /* Delay de 1 segundos */
  }
}

void vTask8(void *arg) // Ultrasonic
{
	(void) arg;

	while(1)
	{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance
    float distanceCm = duration * SOUND_SPEED/2;

    distance = distanceCm;

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */
	}
}

// INICIALIZA ================================================================

void setup()
{
	vInitHW();
	displaySetup();
	ultrasonicSetup();

	// Endereço da Task1, Identificação da Task, Bytes Disponibilizados para Task1, Permite Enviar um Parametro para Task, Prioridade (pode ser de 1 a 5), Handler
	xTaskCreate(vTask1, "servo1", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask1Handle);
	xTaskCreate(vTask2, "servo2", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask2Handle);
  //xTaskCreate(vTask3, "servo3", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask3Handle);
	//xTaskCreate(vTask4, "servo4", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask4Handle);
	//xTaskCreate(vTask5, "servo5", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask5Handle);
	//xTaskCreate(vTask6, "servo6", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask6Handle);
	xTaskCreate(vTask7, "Display", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask7Handle);
  xTaskCreate(vTask8, "Ultrasonic", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask8Handle);
  //xTaskCreate(vTask9, "MQTT", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask9Handle);

}

// MQTT
// Tela TFT Interativa
// Camera com Reconhecimento
// Rodas?
// 
