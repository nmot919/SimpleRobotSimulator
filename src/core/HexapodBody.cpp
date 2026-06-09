#include "HexapodBody.h"
#include <array>

HexapodBody::HexapodBody(vec3 startingPos) : mStartingPos(startingPos) {
    mBodyPos    = mStartingPos;
    buildLegs();
}


HexapodBody::HexapodBody() : HexapodBody(vec3(0)) {}


vec3 HexapodBody::getLegLength(){
    return this->legLength;
}

void HexapodBody::setLegLength(vec3 l){
    this->legLength = l;
    buildLegs();
}

void HexapodBody::setStartingLegLength(vec3 l){
    this->startingLegLength = l;
}

std::array<Leg, NUM_LEGS>& HexapodBody::getLegs(){
    return mLegs;
}
std::array<vec3, NUM_LEGS> HexapodBody::getLegTargets(){
    std::array<vec3, NUM_LEGS> t;
    for(int i = 0; i < NUM_LEGS; i++){
        t[i] = mLegs[i].getFootWorldPos(vec3(0));
    }
    return t;
}


vec3 HexapodBody::getLegTarget(int i){
    return mLegs[i].getTargetFootPos();
}

const std::array<vec3, NUM_LEGS>& HexapodBody::getRestTargets() {
    return mRestTargets;
}

void HexapodBody::setLegTarget(int i, vec3 target){
    mLegs[i].setTargetFootPos(target);
}

void HexapodBody::setLegTarget(std::array<vec3, NUM_LEGS> targets){
    for(int i = 0; i < NUM_LEGS; i++){
        mLegs[i].setTargetFootPos(targets[i]);
    }
}

void HexapodBody::buildLegs(){
    for(int i = 0; i < NUM_LEGS; i++){
        float a = toRadians(legAngles[i]);

        vec3 attach = vec3(rx * sin(a), 0, rz * cos(a));

        // outDir should point away from body-center along the actual attach direction
        vec3 out = normalize(vec3(attach.x, 0, attach.z));

        Leg leg(out);
        leg.setLocalOffset(attach);
        leg.setLengths(legLength);
        // this one changes rest targets
        leg.setAngles(mStartingLegAngles);

        vec3 restTarget = leg.getFootWorldPos(vec3(0));
        leg.setTargetFootPos(restTarget);
        mRestTargets[i] = restTarget;
        mLegs[i] = leg;


    }
}


void HexapodBody::reset(){
    this->mBodyPos = this->mStartingPos;
    this->mYaw = 0.0f;
    this->mBodyVelocity = vec3(0);
    this->legLength = this->startingLegLength;
    buildLegs();
}

void HexapodBody::update(){
    for(int i = 0; i < NUM_LEGS; i++){
        mLegs[i].IK_Solver();
    }
}

vec3 HexapodBody::getPosition(){
    return this->mBodyPos;
}

void HexapodBody::setPosition(vec3 p){
    this->mBodyPos = p;
}

void HexapodBody::setStartingPos(vec3 p){
    this->mStartingPos = p;
}

vec3 HexapodBody::getVelocity(){
    return this->mBodyVelocity;
}

void HexapodBody::setVelocity(vec3 v){
    this->mBodyVelocity = v;
}

float HexapodBody::getBodySize(){
    return this->mBodySize;
}

void HexapodBody::setYaw(float yaw){
    this->mYaw = yaw;
}

float HexapodBody::getYaw(){
    return this->mYaw;
}
