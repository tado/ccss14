//
//  ofxVboParticles.cpp
//
//  Created by Atsushi Tadokoro on 8/14/14.
//
//

#include "ofxVboParticles.h"

ofxVboParticles::ofxVboParticles(int _maxParticles, float _pointSize){
    maxParticles = _maxParticles;
    pointSize = _pointSize;
    numParticles = 0;
    friction = 0.01;
    
    /*
    static GLfloat distance[] = { 0.0, 0.0, 1.0 };
    glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
    glPointSize(pointSize);
     */
    
    // billboards.setUsage(GL_DYNAMIC_DRAW);
    billboards.setMode(OF_PRIMITIVE_POINTS);
    billboards.disableTextures();
    
    billboards.getVertices().resize(maxParticles);
    billboards.getColors().resize(maxParticles);
    billboards.getNormals().resize(maxParticles, ofVec3f(0));
}

void ofxVboParticles::resetForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec3f(0, 0, 0);
    }
}

void ofxVboParticles::addForce(int count, ofVec3f force){
    forces[count] += force;
}

void ofxVboParticles::addDampingForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] -= velocitys[i] * friction;
    }
}

void ofxVboParticles::resetOffWalls(){
    float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
    for(int i = 0; i < positions.size(); i++){
        /*
        if (positions[i].x > maxx || positions[i].y > maxy || positions[i].x < minx || positions[i].y < miny) {
            positions[i].x = ofRandom(minx, maxx);
            positions[i].y = ofRandom(miny, maxy);
        }
         */
        if (positions[i].x > maxx){
            positions[i].x = minx;
        }
        if (positions[i].y > maxy){
            positions[i].y = miny;
        }
        if (positions[i].x < minx){
            positions[i].x = maxx;
        }
        if (positions[i].y < miny){
            positions[i].y = maxy;
        }
    }
}

void ofxVboParticles::updatePos(){
    for(int i = 0; i < positions.size(); i++){
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
        billboards.getVertices()[i].set(positions[i].x, positions[i].y, positions[i].z);
    }
}

void ofxVboParticles::update(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec3f(0, 0, 0);
        forces[i] -= velocitys[i] * friction;
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
        billboards.getVertices()[i].set(positions[i].x, positions[i].y, positions[i].z);
    }
}

void ofxVboParticles::draw(){
    ofPushStyle();
    //ofEnableDepthTest();
    ofEnablePointSprites();
    billboards.draw();
    //ofDisablePointSprites();
    ofPopStyle();
}

void ofxVboParticles::addParticle(ofVec3f _position, ofVec3f _velocity, ofColor _color){
    positions.push_back(_position);
    velocitys.push_back(_velocity);
    colors.push_back(_color);
    forces.push_back(ofVec3f(0, 0, 0));
    
    billboards.getVertices()[numParticles].set(positions[numParticles].x, positions[numParticles].y, positions[numParticles].z);
    billboards.getColors()[numParticles].set(colors[numParticles]);
    
    numParticles++;
    
    if (positions.size() > maxParticles) {
        positions.pop_front();
        colors.pop_front();
        velocitys.pop_front();
        forces.pop_front();

        for (int i = 0; i < numParticles-1; i++) {
            //billboards.getVertices()[i] = billboards.getVertices()[i + 1];
            billboards.getColors()[i] = billboards.getColors()[i + 1];
        }
        
        numParticles--;
    }
}