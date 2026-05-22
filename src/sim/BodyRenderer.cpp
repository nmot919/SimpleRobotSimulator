#include "BodyRenderer.h"


BodyRenderer::BodyRenderer(HexapodBody& body){

    auto shader = gl::getStockShader(gl::ShaderDef().lambert().color());
    auto blue   = geom::Constant(geom::COLOR, Color(0.3f, 0.6f, 1.0f));
    mBodyBatch  = gl::Batch::create(geom::Cube().size(vec3(body.getBodySize())) >> blue, shader);

    for(int i = 0; i < NUM_LEGS; i++){
        mLegRenderers.push_back(LegRenderer(body.getLegs()[i]));
    }
}

void BodyRenderer::rebuildLegRenderers(HexapodBody& body){
    mLegRenderers.clear();
    for(int i = 0; i < NUM_LEGS; i++){
        mLegRenderers.push_back(LegRenderer(body.getLegs()[i]));
    }
}

void BodyRenderer::draw(HexapodBody& body){
    gl::ScopedModelMatrix root;
    gl::translate(body.getPosition());
    gl::rotate(body.getYaw(), vec3(0, 1, 0));

    {
        gl::ScopedModelMatrix m;
        gl::scale(vec3(0.75f, 0.10f, 1.0f));
        mBodyBatch->draw();
    }

    // draw legs
    for(int i = 0; i < NUM_LEGS; i++)
        mLegRenderers[i].draw(body.getLegs()[i], vec3(0));
}
