#pragma once
#include "LegRenderer.h"
#include "../core/HexapodBody.h"
#include <cinder/gl/Batch.h>


class BodyRenderer {

    public:
        BodyRenderer() = default;
        BodyRenderer(HexapodBody& body);
        void draw(HexapodBody& body);
        void rebuildLegRenderers(HexapodBody& body);


    private:
        gl::BatchRef mBodyBatch;
        std::vector<LegRenderer> mLegRenderers;

};
