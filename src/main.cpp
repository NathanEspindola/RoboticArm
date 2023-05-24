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
#include <ESP32Servo.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Ultrasonic.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// DISPLAY ================================================================

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

boolean initial = 1;
byte xcolon = 0;
unsigned int colour = 0;

void displaySetup(void){

	tft.init();
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);

	tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
}

// SERVO ================================================================

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int minUs1 = 500;
int maxUs1 = 2500;
int minUs2 = 500;
int maxUs2 = 2500;

int servo1Pin = 12;
int servo2Pin = 13;
int servo3Pin = 15;
int servo4Pin = 27;
int servo5Pin = 26;
int servo6Pin = 25;

ESP32PWM pwm;

//void vInitHW(void);

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
 	servo3.setPeriodHertz(250);    
	servo4.setPeriodHertz(250);    
	servo5.setPeriodHertz(250);    
	servo6.setPeriodHertz(250);    

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
//TaskHandle_t xTask9Handle; //,xTask6Handle, xTask7Handle, xTask8Handle;


void vTask1(void *arg);
void vTask2(void *arg);
void vTask3(void *arg);
void vTask4(void *arg);
void vTask5(void *arg);
void vTask6(void *arg);
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
		servo1.attach(servo1Pin, minUs1, maxUs1);
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

		servo2.attach(servo2Pin, minUs1, maxUs1);
		pwm.attachPin(27, 10000);//10khz

/*		for (int pos2 = 0; pos2 <= 180; pos2 += 1) { // sweep from 0 degrees to 180 degrees
			servo2.write(pos2);
			delay(20);             // waits 20ms for the servo to reach the position
		}

		for (int pos2 = 180; pos2 >= 0; pos2 -= 1) { // sweep from 180 degrees to 0 degrees
			servo2.write(pos2);
			delay(20);
		}		
*/
		servo2.write(0);
			delay(20);             // waits 20ms for the servo to reach the position

		servo2.detach();
		pwm.detachPin(27);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask3(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{

		servo3.attach(servo3Pin, minUs1, maxUs1);
		pwm.attachPin(27, 10000);//10khz

/*		for (int pos2 = 0; pos2 <= 180; pos2 += 1) { // sweep from 0 degrees to 180 degrees
			servo2.write(pos2);
			delay(20);             // waits 20ms for the servo to reach the position
		}

		for (int pos2 = 180; pos2 >= 0; pos2 -= 1) { // sweep from 180 degrees to 0 degrees
			servo2.write(pos2);
			delay(20);
		}		
*/
		servo3.write(0);
			delay(20);             // waits 20ms for the servo to reach the position

		servo3.detach();
		pwm.detachPin(27);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask4(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{

		servo4.attach(servo4Pin, minUs2, maxUs2);
		pwm.attachPin(27, 10000);//10khz

/*		for (int pos2 = 0; pos2 <= 180; pos2 += 1) { // sweep from 0 degrees to 180 degrees
			servo2.write(pos2);
			delay(20);             // waits 20ms for the servo to reach the position
		}

		for (int pos2 = 180; pos2 >= 0; pos2 -= 1) { // sweep from 180 degrees to 0 degrees
			servo2.write(pos2);
			delay(20);
		}		
*/
		servo4.write(0);
			delay(20);             // waits 20ms for the servo to reach the position

		servo4.detach();
		pwm.detachPin(27);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask5(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{

		servo5.attach(servo5Pin, minUs2, maxUs2);
		pwm.attachPin(27, 10000);//10khz

/*		for (int pos2 = 0; pos2 <= 180; pos2 += 1) { // sweep from 0 degrees to 180 degrees
			servo2.write(pos2);
			delay(20);             // waits 20ms for the servo to reach the position
		}

		for (int pos2 = 180; pos2 >= 0; pos2 -= 1) { // sweep from 180 degrees to 0 degrees
			servo2.write(pos2);
			delay(20);
		}		
*/
		servo5.write(0);
			delay(20);             // waits 20ms for the servo to reach the position

		servo5.detach();
		pwm.detachPin(27);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask6(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{

		servo6.attach(servo6Pin, minUs2, maxUs2);
		pwm.attachPin(27, 10000);//10khz

/*		for (int pos2 = 0; pos2 <= 180; pos2 += 1) { // sweep from 0 degrees to 180 degrees
			servo2.write(pos2);
			delay(20);             // waits 20ms for the servo to reach the position
		}

		for (int pos2 = 180; pos2 >= 0; pos2 -= 1) { // sweep from 180 degrees to 0 degrees
			servo2.write(pos2);
			delay(20);
		}		
*/
		servo6.write(0);
			delay(20);             // waits 20ms for the servo to reach the position

		servo6.detach();
		pwm.detachPin(27);

   	vTaskDelay(pdMS_TO_TICKS(100));     /* Delay de 1 segundos */

	}
}

void vTask7(void *arg) // Display
{
	(void) arg;

	while(1)
	{
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
	xTaskCreate(vTask1, "servo1", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask1Handle);
	xTaskCreate(vTask2, "servo2", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask2Handle);
    xTaskCreate(vTask3, "servo3", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask3Handle);
	xTaskCreate(vTask4, "servo4", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask4Handle);
	xTaskCreate(vTask5, "servo5", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask5Handle);
	xTaskCreate(vTask6, "servo6", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask6Handle);
	xTaskCreate(vTask7, "Display", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask7Handle);
  	xTaskCreate(vTask8, "Ultrasonic", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask8Handle);
  //xTaskCreate(vTask9, "MQTT", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask9Handle);
}

// MQTT
// Tela TFT Interativa
// Camera com Reconhecimento
// Rodas?
// 
