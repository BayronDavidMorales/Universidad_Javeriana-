#include <Servo.h>

Servo servo;
byte pinServo=9;
byte posServo=0;

byte pinLedUno = 13;
byte pinChicharra= 8;

int pinAnalogoPiezoElectro = A0;

int pinPulzador=7;

byte pinFotoSensor= A1;

int e = 0;
int state = LOW;
int stateFotoSensor=LOW;

void setup()
{
    Serial.begin(115200);
    servo.attach(pinServo); // servo

    pinMode(LED_BUILTIN, OUTPUT); // led del pin 13---se usa como bandera

    pinMode(pinChicharra, OUTPUT); // chicharra
    pinMode(pinLedUno, OUTPUT); // chicharra

    pinMode(pinFotoSensor, INPUT); // analogo
}

void loop(){
    Serial.println(analogRead(pinFotoSensor));
    chicharraHorno(pinChicharra, 0);

    // delay(500);
    if (e == 0){
        girarServo(servo, 0);
    }
    if (piezoElectrico(pinAnalogoPiezoElectro) == HIGH & e==0)
    {
        leds(pinLedUno, 1);
        girarServo(servo, 1);
        e++;
        delay(3000);
    }
    if (fotorresistor(pinFotoSensor) == HIGH & e == 1)
    {
        leds(pinLedUno, 0);
        chicharraHorno(pinChicharra, HIGH);
        girarServo(servo, 0);
        chicharraHorno(pinChicharra, HIGH);
        e++;
        // delay(3000);
    }
}

//---------FUNCIONES----------------
// FOTO RESISTOR
byte fotorresistor(byte pinFotoSensor)
{
    // Serial.println(analogRead(pinFotoSensor));
    if (analogRead(pinFotoSensor)>900){
        stateFotoSensor=!stateFotoSensor;
        return stateFotoSensor;
    }
    return stateFotoSensor;
}
//PIEZO ELECTRICO
byte piezoElectrico(int pinAnalogoPiezoElectro)
{
    if(analogRead(pinAnalogoPiezoElectro)>100){
        state = !state;
        delay(300);
        return state;
    }
    // Serial.println(state);
    return state;
}
//PULZADOR
byte pulzador(int pinPulzador)
{
    if (digitalRead(pinPulzador) == HIGH)
    {
        // Serial.println(state);
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

int girarServo(Servo servo, int orden)
{
    switch(orden){
        case 0:
            for (int pos = servo.read(); pos >= 2; pos -= 1)
            {
                servo.write(pos);
                delay(20);
            }
            break;
        case 1:
            for (int pos = servo.read(); pos <= 120; pos += 1)
            {
                servo.write(pos);
                delay(30);
            }
            break;
        default:
            for (int pos = servo.read(); pos >= 2; pos -= 1)
            {
                servo.write(pos);
                delay(10);
            }
            break;
    }
    
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
        noTone(pinChicharra);
    }
}
byte chicharraHorno(int pinChicharra, byte onOff)
{
    if (onOff == 1)
    {
        float sinVal;
        int toneVal;
        for (int x = 0; x < 2; x++)
        {
            sinVal = (sin(8 * (3.14 / 180)));
            toneVal = 2000 + (int(sinVal * 1000));
            tone(pinChicharra, toneVal);
            delay(200);
            noTone(pinChicharra);
            delay(100);
        }
    }
    else
    {
        noTone(pinChicharra);
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
