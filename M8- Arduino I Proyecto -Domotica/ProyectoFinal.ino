#include <Servo.h>

Servo servo; 
int pinLedUno = 7;

int pinServo = 9;
int pos = 0;    

void setup() {
  servo.attach(9);  
}

void loop() {
  girarServo(servo, 90);
  girarServo(servo, -90);
}
//---------FUNCIONES----------------

//GIRAR SERVO MOTOR

//la funcion girar servo recibe como primer parametro un objeto tipo servo Servo, despues en angulo, un numero positivo gira en contra de las manecillas de relog
//y un angulo negativo en sentido de las manecillas.
//ejemplo;
//girarServo(servo, 90) => gira 90 grados en contra de las manecillas
//girarServo(servo, -90) => gira 90 grados en sentido de las manecillas

int girarServo(Servo servo, int angulo){ 
  if(angulo>0){
    for (pos = angulo; pos >= 0; pos -= 1) {
      servo.write(pos);             
      delay(15);                      
    }
  }
  
  else{
    for (pos = angulo; pos <= 0; pos += 1) { 
      servo.write(pos);              
      delay(15);                       
        }
    }

    return servo.read();
}

//PRENDER Y APAGAR LEDS
//la funcion leds recibe como parametros el pin previamente definido como OUTPUT en setup y como segundo parametro
//un 0 o 1 en donde 0 apaga el led y 1 lo enciende
//ejemplo:

//const int ledPIN = 7;
 
//void setup() {
//  pinMode(ledPIN , OUTPUT);  //definir pin como salida
//}
 
//void loop(){
//    leds(7, 1)   => prende el led del pin 7
//    delay(1000)  => espera 1 segundo
//    leds(7, 0)   => apaga el led del pin 7
       
//}

int leds(int pinLed, int onOff){
  if(onOff==0){
    digitalWrite( pinLed , LOW);
  }else
    digitalWrite( pinLed , HIGH);
}
  
