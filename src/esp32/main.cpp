#include "core/HexapodBody.h"
#include "core/TripodGait.h"
#include "esp32-hal.h"
#include <Arduino.h>
#include <cstdint>
#include "ServoController.h"







HexapodBody body;
TripodGait gait;
ServoController* servoController;



unsigned long lastTime = 0;


void setup(){
    Serial.begin(115200);

    body = HexapodBody(vec3(0, 0.69, 0));
    body.update();
    //vec3 angles = body.getLegs()[0].getAngles();
    std::array<Leg, NUM_LEGS> legs = body.getLegs();

    servoController = ServoController::getInstance();

    for(int i = 0; i < 6; i++){
        servoController->writeLeg(i, legs[i].getAngles());
    }


    gait.setMoveDir(vec3(1, 0, 0));
    delay(2000);


    Serial.println("Done");
}

void loop(){

    // unsigned long now = millis();
    // float dt          = (now - lastTime) / 1000.0f;
    // lastTime          = now;

    // auto targets = gait.getGaitTarget(dt);
    // body.setLegTarget(targets);
    // body.update();

    // vec3 angles = body.getLegs()[0].getAngles();
    // writeLeg(0, angles);

}
