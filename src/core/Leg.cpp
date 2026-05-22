#include "Leg.h"



    Leg::Leg(vec3 outDir) : outDir(outDir){
      // starting angles should be calculated from outDir to stand straight up
      angles = vec3(toRadians(90.0f), toRadians(120.0f), toRadians(180.0f));
    }

    // targetFootPos is in local coordinates, maybe make private in the future.
    void Leg::setTargetFootPos(vec3 targetFootPos){
      this->targetFootPos = targetFootPos;
    }

    vec3 Leg::getOutDir(){return outDir;}

    vec3 Leg::getTargetFootPos(){return targetFootPos;}

    void Leg::setLocalOffset(vec3 localOffset){
      this->localOffset = localOffset;
    }

    vec3 Leg::getLocalOffset(){return localOffset;}

    // takes inputs as degrees since those are easier to visualize but uses radians for internal math because it's easier to do
    void Leg::setAngles(vec3 angleDeg){angles = vec3(toRadians(angleDeg.x), toRadians(angleDeg.y), toRadians(angleDeg.z));}

    vec3 Leg::getAngles(){return vec3(toDegrees(angles.x), toDegrees(angles.y), toDegrees(angles.z));}

    vec3 Leg::getAnglesRad(){return vec3(angles.x, angles.y, angles.z);}


    void Leg::setLengths(vec3 lengths){
      if(this->lengths != lengths){
        this->lengths = lengths;
      }
    }

    vec3 Leg::getLengths(){return lengths;}

    vec3 Leg::getFootWorldPos(vec3 bodyPos){
      #ifdef ARDUINO
          // manual matrix math
          vec3 pos = localOffset + bodyPos;

          float yaw = atan2(outDir.x, outDir.z) + angles.x - (float(M_PI)/2.0f);
          float cosYaw = cos(yaw), sinYaw = sin(yaw);

          // coxa tip
          float coxaX = cosYaw * lengths.x;
          float coxaZ = sinYaw * lengths.x;
          pos.x += coxaX;
          pos.z += coxaZ;

          // femur tip
          float femurX = -sin(angles.y) * lengths.y;
          float femurY = -cos(angles.y) * lengths.y;
          pos.x += cosYaw * femurX;
          pos.y += femurY;
          pos.z += sinYaw * femurX;

          // tibia tip
          float tibiaAngle = angles.y + angles.z + float(M_PI);
          float tibiaX = -sin(tibiaAngle) * lengths.z;
          float tibiaY = -cos(tibiaAngle) * lengths.z;
          pos.x += cosYaw * tibiaX;
          pos.y += tibiaY;
          pos.z += sinYaw * tibiaX;

          return pos;
      #else
          // glm version for sim — keep this working and verified
          glm::mat4 m = glm::mat4(1.0f);
          m = glm::translate(m, localOffset + bodyPos);
          m = glm::rotate(m, float(atan2(outDir.x, outDir.z) + angles.x - (M_PI/2.0f)), glm::vec3(0, 1, 0));
          m = glm::translate(m, glm::vec3(lengths.x, 0, 0));
          m = glm::rotate(m, float(angles.y), glm::vec3(0, 0, 1));
          m = glm::translate(m, glm::vec3(0, -lengths.y, 0));
          m = glm::rotate(m, float(angles.z + M_PI), glm::vec3(0, 0, 1));
          m = glm::translate(m, glm::vec3(0, -lengths.z, 0));
          return vec3(m[3]);
      #endif
    }



    // takes target foot position which is in local coordinates and computes the required angle coxa, femur, and tibia angles required
    // to reach that foot position
  void Leg::IK_Solver(){

  vec3 t = targetFootPos - localOffset;
  float targetAngle = atan2(t.x, t.z);
  float baseAngle = atan2(outDir.x, outDir.z);
  angles.x = targetAngle - baseAngle;

  float horizontal = sqrt(t.x*t.x + t.z*t.z) - lengths.x;
  float L = sqrt(t.y*t.y + horizontal*horizontal);
  float maxReach = lengths.y + lengths.z;
  float minReach = abs(lengths.y - lengths.z);
  if(L > maxReach) L = maxReach - 0.005f;

  if(L < minReach) L = minReach + 0.005f;

  float alpha1 = acos(-t.y/L);
  float alpha2 = acos((lengths.z*lengths.z - lengths.y*lengths.y - L*L)/(-2*lengths.y*L));
  float alpha  = alpha1 + alpha2;

  float beta = acos((L*L - lengths.z*lengths.z - lengths.y*lengths.y)/(-2*lengths.z*lengths.y));

  angles.y = alpha;
  angles.z = beta;
}
