#pragma once
#include <array>
#include "Leg.h"



#ifndef NUM_LEGS
#define NUM_LEGS 6
#endif


using namespace std;

class TripodGait{

public:

std::array<vec3, NUM_LEGS> getGaitTarget(float dt);
void setMoveDir(vec3 moveDir);
vec3 getMoveDir();

void setTurnRate(float tr);
float getTurnRate();

void setRestTargets(const std::array<vec3, NUM_LEGS>& t);
std::array<vec3, NUM_LEGS>& getRestTargets();

private:
int groupA[3] = {0, 2, 4};
int groupB[3] = {1, 3, 5};

float mGaitPhase    = 0.0f;
float mStepDuration = 2.0f; // og 0.5
float mStepHeight   = 0.2f; // og 0.3, make constructor for these
float mStrideRadius = 0.2f;
vec3  mMoveDir = vec3(0);
float mTurnRate = 0.0f;

//std::array<vec3, NUM_LEGS>  mRestTargets = {vec3(0, -0.69, 1.33), vec3(0.42, -0.69, 1.22), vec3(0.42, -0.69, -1.22), vec3(0, -0.69, -1.33), vec3(-0.42, -0.69, -1.22), vec3(-0.42, -0.69, 1.22)};
//std::array<vec3, NUM_LEGS>  mRestTargets = {vec3(0, -0.80, 0.90), vec3(0.46, -0.80, 0.65), vec3(0.46, -0.80, -0.65), vec3(0, -0.80, -0.90), vec3(-0.46, -0.80, -0.65), vec3(-0.46, -0.80, 0.65)};
std::array<vec3, NUM_LEGS>  mRestTargets;
std::array<vec3, NUM_LEGS>  mCurrentTargets;


void updateGroup(bool group, float phase);

};
