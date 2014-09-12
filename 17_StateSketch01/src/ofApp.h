#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // sphere
    ofLight light;
    
    // stats
    int top;
    int left;
    int width;
    int height;
    float maxValue;
    int lapTime;
    int mode; //(0:fps, 1:ms)
    deque<float> fpsList;
    deque<float> msList;
    int lastLap;
    float currentMs;
    float curretFps;
    float lastMs;
    float padding;
};
