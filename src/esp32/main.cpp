#include "core/HexapodBody.h"
#include "core/TripodGait.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <cstdint>


#define ZERO_ANGLE 0
#define SERVO_MIN 150
#define SERVO_MAX 500

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
HexapodBody body;
TripodGait gait;


void setAngle(uint8_t channel, float deg){
    deg = constrain(deg, 0, 180);
    uint16_t pulse = (uint16_t)(SERVO_MIN + (deg / 180.0f) * (SERVO_MAX - SERVO_MIN));
    pwm.setPWM(channel, 0, pulse);
}

/*void setAngle(uint8_t channel, float deg){
    //deg = constrain(deg, 0, 180);
    uint16_t pulse = map(deg, 0, 180, SERVO_MIN, SERVO_MAX);
    //uint8_t pulse = (uint16_t)(SERVO_MIN + (degrees / 180.0f) * (SERVO_MAX - SERVO_MIN));
    pwm.setPWM(channel, 0, pulse);
}*/


void writeLeg(int leg, vec3 anglesDeg){
    pwm.setPWM(leg * 3 + 0, 0, (uint16_t)(SERVO_MIN + ((anglesDeg.x) / 180.0f) * (SERVO_MAX - SERVO_MIN)));
    pwm.setPWM(leg * 3 + 1, 0, (uint16_t)(SERVO_MIN + ((anglesDeg.y ) / 180.0f) * (SERVO_MAX - SERVO_MIN)));
    pwm.setPWM(leg * 3 + 2, 0, (uint16_t)(SERVO_MIN + ((anglesDeg.z) / 180.0f) * (SERVO_MAX - SERVO_MIN)));
}


unsigned long lastTime = 0;


#if ZERO_ANGLE
void setup(){
    Serial.begin(115200);


    pwm.begin();
    pwm.setPWMFreq(50);
    delay(10);


    setAngle(0, 90);
    setAngle(1, 0);
    setAngle(2, 0);

    delay(2000);

    Serial.println("Done");
}

void loop(){}

#else
void setup(){
    Serial.begin(115200);

    body = HexapodBody(vec3(0, 0.69, 0));
    body.update();
    vec3 angles = body.getLegs()[0].getAngles();


    pwm.begin();
    pwm.setPWMFreq(50);
    delay(10);

    writeLeg(0, angles);


    gait.setMoveDir(vec3(1, 0, 0));
    delay(2000);


    Serial.println("Done");
}

void loop(){

    unsigned long now = millis();
    float dt          = (now - lastTime) / 1000.0f;
    lastTime          = now;

    auto targets = gait.getGaitTarget(dt);
    body.setLegTarget(targets);
    body.update();

    vec3 angles = body.getLegs()[0].getAngles();
    writeLeg(0, angles);

}

#endif
