#pragma once
#ifdef ARDUINO
#include "../math/Vec3.h"
using vec3 = Vec3;
#else
#include <cinder/Vector.h>
using namespace ci;
#endif





class Leg {
  public:
    Leg(vec3 outDir);
    void IK_Solver();

    void setTargetFootPos(vec3 targetFootPos);
    vec3 getTargetFootPos();
    void setLocalOffset(vec3 localOffset);
    vec3 getLocalOffset();
    void setAngles(vec3 angleDeg);
    vec3 getAngles();
    vec3 getAnglesRad();
    void setLengths(vec3 lengths);
    vec3 getLengths();
    vec3 getFootWorldPos(vec3 bodyPos);

    vec3 getOutDir();

  private:
    // coxa, femur, tibia
    vec3 angles;
    vec3 lengths;
    vec3 outDir;
    vec3 targetFootPos; // target foot position in local space
    vec3 localOffset; // offset from center of body to leg in local position
};
