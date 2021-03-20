#include <Servo.h>

Servo servo;
byte pinServo=9;
byte posServo=0;

byte pinLedUno = 13;
byte pinChicharra= 8;

int pinAnalogoPiezoElectro = A0;

int pinPulzador=7;

int e = 0;
int state = LOW;

void setup()
{
    Serial.begin(115200);
    servo.attach(pinServo); // servo

    pinMode(LED_BUILTIN, OUTPUT); // led del pin 13---se usa como bandera

    pinMode(pinChicharra, OUTPUT); // chicharra
    pinMode(pinLedUno, OUTPUT); // chicharra
}

void loop(){
    // leds(pinLedUno, HIGH);
    //chicharra(8, 1);
    //blinkFunction(5);
    // chicharra(pinChicharra, 1);

    chicharra(pinChicharra, pulzador(pinPulzador));

        // leds(pinLedUno, pulzador(pinPulzador));
    // chicharra(pinChicharra, piezoElectrico(pinAnalogoPiezoElectro));
    // delay(100);
    // if (piezoElectrico(pinAnalogoPiezoElectro) == 1)
    //     girarServo(servo, 90);
    //     else{
    //         girarServo(servo, -90);
    //     }
}
//---------FUNCIONES----------------
//PIEZO ELECTRICO
byte piezoElectrico(int pinAnalogoPiezoElectro)
{
    if(analogRead(pinAnalogoPiezoElectro)>50){
        state = !state;
        delay(500);
        return state;
    }
    // delay(100);
    return state;
}
//PIEZO ELECTRICO
byte pulzador(int pinPulzador)
{
    if (digitalRead(pinPulzador) == HIGH)
    {
        Serial.println(state);
        state = !state;
        delay(200);
        return state;
    }
    // delay(100);
    return state;
}
//GIRAR SERVO MOTOR

//la funcion girar servo recibe como primer parametro un objeto tipo servo Servo, despues en angulo, un numero positivo gira en contra de las manecillas de relog
//y un angulo negativo en sentido de las manecillas.
//ejemplo;
//girarServo(servo, 90) => gira 90 grados en contra de las manecillas
//girarServo(servo, -90) => gira 90 grados en sentido de las manecillas

int girarServo(Servo servo, int angulo)
{
    if (angulo > 0)
    {
        for (int pos = posServo; pos <= angulo; pos += 1)
        {
            servo.write(pos);
            delay(15);
        }
    }

    else
    {
        for (int pos = angulo; pos <= posServo; pos += 1)
        {
            servo.write(pos);
            delay(15);
        }
    }
    posServo = servo.read();
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

int leds(int pinLed, byte onOff)
{
    if (onOff == 0)
    {
        digitalWrite(pinLed, LOW);
    }
    else
        digitalWrite(pinLed, HIGH);

    return digitalRead(pinLed);
}
//CHICHARRA
//la funcion chicharra recibe como parametros el pin previamente definido como OUTPUT en setup y como segundo parametro
//un 1 para hacer sonar la chicharra o un 0 para apagarla

byte chicharra(int pinChicharra, byte onOff)
{

    if (onOff == 1)
    {
        float sinVal;
        int toneVal;
        for (int x = 0; x < 180; x++)
        {
            sinVal = (sin(x * (3.14 / 180)));
            toneVal = 2000 + (int(sinVal * 1000));
            tone(pinChicharra, toneVal);
            delay(2);
        }
    }
    else
    {
        tone(pinChicharra, 0);
    }
}
//BLINK
void blinkFunction(int n)
{
    for (int i = n; i >= 0; i--)
    {
        digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
        delay(100);                      // wait for a second
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
        delay(1000);
    }
}
