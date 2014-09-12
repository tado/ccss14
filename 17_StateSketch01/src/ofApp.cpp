#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(63);
    
    light.setup();
    light.setPosition(ofGetWidth()/2 - 100, ofGetHeight()/2 - 100, 400);
    
    top = 0;
    left = 0;
    width = 80;
    height = 48;
    maxValue = 120;
    lapTime = 100;
    mode = 0;
    lastLap = 0;
    lastMs = 0;
    padding = 3;
}

//--------------------------------------------------------------
void ofApp::update(){
    curretFps = ofGetFrameRate();
    currentMs = (ofGetElapsedTimef() - lastMs) * 1000;
    lastMs = ofGetElapsedTimef();
    
    if (int(ofGetElapsedTimef() * 1000) / lapTime > lastLap) {
        fpsList.push_front(curretFps);
        if (fpsList.size() > width - padding * 2 + 1) {
            fpsList.pop_back();
        }
        msList.push_front(currentMs);
        if (msList.size() > width - padding * 2 + 1) {
            msList.pop_back();
        }
        lastLap++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // sphere animation
    ofPushStyle();
    ofEnableDepthTest();
    ofEnableLighting();
    light.enable();
    ofSetHexColor(0xcccccc);
    ofSpherePrimitive sphere;
    sphere.setRadius(sin(ofGetElapsedTimef() * 4.0) * 100 + 200);
    sphere.setResolution(mouseX / 2.0);
    sphere.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    sphere.drawWireframe();
    ofDisableLighting();
    ofDisableDepthTest();
    ofPopStyle();
    
    // stats
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(left, top);
    ofEnableAlphaBlending();
    
    ofSetColor(0, 0, 0, 204);
    ofRect(0, 0, width, height);
    float scale = float(height - 14 - padding*2) / maxValue;
    
    if (mode == 0) { // FPS
        ofSetHexColor(0x00ffff);
        
        ofBeginShape();
        ofVertex(width-padding, height-padding);
        for (int i = 0; i < fpsList.size(); i++) {
            float length = fpsList[i] * scale;
            if (length > height) {
                length = height;
            }
            ofVertex(width - padding - i, height - padding - length);
        }
        ofVertex(width - padding - fpsList.size() + 1, height - padding);
        ofEndShape();
        
        ofSetColor(0, 0, 0, 204);
        ofRect(0, 0, width, 14);
        ofSetHexColor(0x00ffff);
        ofDrawBitmapString(ofToString(curretFps, 0) + " fps", 2, 11);
    }
    if (mode == 1) { // MS
        ofSetHexColor(0x00ff00);
        
        ofBeginShape();
        ofVertex(width-padding, height-padding);
        for (int i = 0; i < msList.size(); i++) {
            float length = msList[i] * scale;
            if (length > height) {
                length = height;
            }
            ofVertex(width - padding - i, height - padding - length);
        }
        ofVertex(width - padding - msList.size() + 1, height - padding);
        ofEndShape();
        
        ofSetColor(0, 0, 0, 204);
        ofRect(0, 0, width, 14);
        ofSetHexColor(0x00ff00);
        ofDrawBitmapString(ofToString(currentMs, 0) + " ms", 2, 11);
    }
    
    ofPopMatrix();
    ofPopStyle();
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
    if (x > left && x < left+width && y > top && y < top+height) {
        (mode == 0)? mode = 1: mode = 0;
    }
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
