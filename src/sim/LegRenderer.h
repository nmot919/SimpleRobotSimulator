#pragma once
#include "../core/Leg.h"
#include "cinder/gl/gl.h"
#include <cinder/gl/Batch.h>


class LegRenderer {
    public:
        LegRenderer(Leg& leg);

        void draw(Leg& leg, vec3 bodyPos);
        void rebuildBatches(Leg& leg);
    private:
        gl::BatchRef mCoxa, mFemur, mTibia, mFoot;
};
