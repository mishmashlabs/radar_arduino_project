#include<Servo.h>

// set ouptut pins
const int TriggerPin = 11;
const int EchoPin = 12;
const int motorSignalPin = 9;

// starting loaction
const int startAngle = 90;

// rotation limits
const int minimumAngle = 6;
const int maximumAngle = 175;

// speed
const int degreesPerCycle = 1;

// Library class instance
Servo motor;

void setup(void) 
{
    pinMode(TriggerPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    motor.attach(motorSignalPin);
    Serial.begin(9600);
}

void loop(void)
{
    static int currentAngle = startAngle;
    static int motorRotateAmount = degreesPerCycle;

    // move motor
    motor.write(currentAngle);
    delay(10);
    // calculate the distance from the sensor, and write the valu with locqtion to serial
    SerialOutput(currentAngle, CalculateDistance());

    // update motor location
    currentAngle += motorRotateAmount;

    // if the motor has reached the limits, change direction
    if(currentAngle <= minimumAngle || currentAngle >= maximumAngle) 
    {
        motorRotateAmount = -motorRotateAmount;
    }
}

int CalculateDistance(void)
{
    // trigger the ultrasonc senosr and record the time taken reflect
    digitalWrite(TriggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin, LOW);
    long duration = pulseIn(EchoPin, HIGH);
    // convert this duration to a distance
    float distance = duration * 0.017F;
    return int(distance);
}

void SerialOutput(const int angle, const int distance)
{
    // convert the angle and distance to a string and serial print
    Serial.println(String(angle) + "," + String(distance));
}
