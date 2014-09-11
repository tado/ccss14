#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(0);
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    myImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    pixels = myImage.getPixels();
    
    particleNum = 30000;
    particles = new ofxVboParticles(particleNum);
    particles->friction = 0.015;
    
    for (int i = 0; i < particleNum; i++) {
        ofVec3f position = ofVec3f(ofRandom(width), ofRandom(height));
        particles->addParticle(position);
    }
    
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            float scaleX = 5;
            float scaleY = 6;
            float noiseX = ofMap(i, 0, width, 0, scaleX);
            float noiseY = ofMap(j, 0, width, 0, scaleY);
            int noiseVal = ofNoise(noiseX, noiseY) * 255;
            pixels[j * width + i] = noiseVal;
        }
    }
    myImage.update();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float speed = 0.1;
    particles->resetForce();
    for (int i = 0; i < particleNum; i++) {
        int val = pixels[int(particles->positions[i].y) * width + int(particles->positions[i].x)];
		int angle = ofMap(val, 0, 255, 0, PI*2.0);
		ofVec3f force;
		force.x = cos(angle) * speed;
		force.y = sin(angle) * speed;
        particles->addForce(i, force);
    }
    particles->addDampingForce();
    particles->resetOffWalls();
    particles->updatePos();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0, 7);
    ofRect(0, 0, width, height);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255);
    particles->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}