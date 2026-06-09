#pragma once
#include "Leg.h"
#include <array>

#ifndef NUM_LEGS
#define NUM_LEGS 6
#endif


class HexapodBody{

public:

HexapodBody();
HexapodBody(vec3 startingPos);

void reset();
void update();

vec3 getPosition();
void setPosition(vec3 p);
void setStartingPos(vec3 p);

vec3 getVelocity();
void setVelocity(vec3 v);

float getYaw();
void  setYaw(float yaw);

float getBodySize();


std::array<Leg, NUM_LEGS>& getLegs();
void setLegLength(vec3 l);
void setStartingLegLength(vec3 l);
vec3 getLegLength();


const std::array<vec3, NUM_LEGS>& getRestTargets();
std::array<vec3, NUM_LEGS> getLegTargets();
vec3 getLegTarget(int i);
void setLegTarget(int i, vec3 target);
void setLegTarget(std::array<vec3, NUM_LEGS> targets);

private:

void buildLegs();

float rx = 0.3f, rz = 0.5f; // used to generate leg positions in buildLegs()
//float legAngles[6] = {0, 30, 150, 180, 210, 330};
//float legAngles[6] = {0, 50, 130, 180, 230, 310};
float legAngles[6] = {0, 45, 135, 180, 235, 315};

vec3 startingLegLength = vec3(0.10f, 0.30f, 0.80f);
vec3 legLength = startingLegLength; // coxa, femur, tibia

vec3 mStartingLegAngles = vec3(90.0f, 90.0f, 90.0f);
vec3 mStartingPos = vec3(0);
float mBodySize        = 0.5;
vec3  mBodyPos;
vec3  mBodyVelocity   = vec3(0);
std::array<Leg, NUM_LEGS> mLegs;
std::array<vec3, NUM_LEGS> mRestTargets;

float mYaw = 0.0f;

};
