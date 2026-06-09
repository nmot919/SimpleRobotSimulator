#include "LegRenderer.h"


LegRenderer::LegRenderer(Leg& leg){
  rebuildBatches(leg);
}

void LegRenderer::draw(Leg& leg, vec3 bodyPos){

    vec3 localOffset = leg.getLocalOffset();
    vec3 angles = leg.getAnglesRad();
    vec3 lengths = leg.getLengths();
    vec3 outDir = leg.getOutDir();


      // don't forget that changing this may mean that getFootWorldPos has to be changed as

      gl::ScopedModelMatrix root;
      gl::translate(bodyPos + localOffset);
      //gl::rotate(-atan2(outDir.z, outDir.x) + angles.x - (M_PI / 2.0), vec3(0, 1, 0));
      //gl::rotate(atan2(outDir.x, outDir.z) - (M_PI / 2.0) + angles.x, vec3(0, 1, 0));
      gl::rotate(atan2(outDir.x, outDir.z) + angles.x - (M_PI), vec3(0, 1, 0));

      {
        // move to coxa draw point and draw coxa
        gl::ScopedModelMatrix m;
        gl::translate(vec3(lengths.x * 0.5f, 0, 0));
        mCoxa->draw();
      }

      // move to tip of coxa
      gl::translate(vec3(lengths.x, 0, 0));
      gl::rotate(angles.y, vec3(0, 0, 1));

      {
        // move to femur draw point and draw femur
        // length being negative shouldnt affect the rest of the system, just makes the drawing correct
          gl::ScopedModelMatrix m;
          gl::translate(vec3(0, -lengths.y * 0.5f, 0));
          mFemur->draw();
      }

      // move to tip of femur
      gl::translate(vec3(0, -lengths.y, 0));
      gl::rotate(-angles.z + (M_PI / 2.0), vec3(0, 0, 1));
      gl::rotate(angles.z + (M_PI), vec3(0, 0, 1));


      {
        // move to tibia draw point and draw tibia
          gl::ScopedModelMatrix m;
          gl::translate(vec3(0, -lengths.z * 0.5, 0));
          mTibia->draw();
      }

      // move to tip of tibia to draw foot
      gl::translate(vec3(0, -lengths.z, 0));
      mFoot->draw();
}

    void LegRenderer::rebuildBatches(Leg& leg){
      vec3 lengths = leg.getLengths();

      auto shader = gl::getStockShader(gl::ShaderDef().lambert().color());
      auto blue   = geom::Constant(geom::COLOR, Color(0.3f, 0.6f, 1.0f));
      auto yellow = geom::Constant(geom::COLOR, Color(1, 1, 0));

      mCoxa  = gl::Batch::create(geom::Cube().size(vec3(lengths.x, 0.03, 0.03)) >> blue, shader);
      mFemur = gl::Batch::create(geom::Cube().size(vec3(0.03, lengths.y, 0.03)) >> blue, shader);
      mTibia = gl::Batch::create(geom::Cube().size(vec3(0.03, lengths.z, 0.03)) >> blue, shader);
      mFoot  = gl::Batch::create(geom::Sphere().radius(0.03).subdivisions(8) >> yellow, shader);
}
