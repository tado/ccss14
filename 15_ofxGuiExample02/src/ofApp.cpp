#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetBackgroundAuto(false);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetCircleResolution(3);
    
    // イベントリスナー設定
    friction.addListener(this, &ofApp::frictionChanged);
    radius.addListener(this, &ofApp::radiusChanged);
    clearButton.addListener(this, &ofApp::clearButtonPressed);
    resetButton.addListener(this, &ofApp::resetButtonPressed);
    randomVF.addListener(this, &ofApp::randomButtonPressed);
    
    // GUI設定
    gui.setup();
    gui.add(friction.setup("friction", 0.0015, 0.0, 0.003));
    gui.add(radius.setup("radius", 1.5, 0.0, 3.0));
    gui.add(color.setup("color", ofColor(15,31,63), ofColor(0,0), ofColor(255,255)));
    gui.add(resetButton.setup("reset particles"));
    gui.add(clearButton.setup("clear VecotorField"));
    gui.add(randomVF.setup("randomize VectorFirld"));


	// 画面の中心付近にパーティクルを配置
	for (int i = 0; i < 50000; i++){
		Particle p;
        float angle, length;
        length = ofRandom(3);
        angle = ofRandom(PI * 2.0);
        ofVec2f pos;
        pos.x = cos(angle) * length + ofGetWidth()/2;
        pos.y = sin(angle) * length + ofGetHeight()/2;
        p.setup(pos, ofVec2f(0, 0));
        p.radius = 1.2;
        p.friction = friction;
		particles.push_back(p);
	}
	
	VF.setupField(400,200,ofGetWidth(), ofGetHeight());
    VF.randomizeField(0.1);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	for (int i = 0; i < particles.size(); i++){
		
		//particleの力をリセット
		particles[i].resetForce();
		
		//ベクトル場から、それぞれのparticleにかかる力を算出
		ofVec2f force;
		force = VF.getForceFromPos(particles[i].position.x, particles[i].position.y);
		
		//Particleの状態を更新
		particles[i].addForce(ofVec2f(force.x, force.y));
		particles[i].updateForce();
        particles[i].bounceOffWalls();
		particles[i].update();
	}
	
	//ベクトル場の力の減衰
	VF.fadeField(1.0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(0,15);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofEnableBlendMode(OF_BLENDMODE_ADD);

	//ベクトル場に配置されたparticleを描画
    ofSetColor(color);

	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}
    
    // GUI
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    gui.draw();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}

// イベントリスナー
void ofApp::frictionChanged(float & friction){
    for (int i = 0; i < particles.size(); i++){
        particles[i].friction = friction;
    }
}

void ofApp::radiusChanged(float & radius){
    for (int i = 0; i < particles.size(); i++){
        particles[i].radius = radius;
    }
}

void ofApp::resetButtonPressed(){
    for (int i = 0; i < particles.size(); i++){
        float angle, length;
        length = ofRandom(3);
        angle = ofRandom(PI * 2.0);
        ofVec2f pos;
        pos.x = cos(angle) * length + ofGetWidth()/2;
        pos.y = sin(angle) * length + ofGetHeight()/2;
        particles[i].setup(pos, ofVec2f(0, 0));
        particles[i].friction = friction;
    }
}

void ofApp::clearButtonPressed(){
    VF.clear();
}


void ofApp::randomButtonPressed(){
    VF.randomizeField(0.1);
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	
	switch (key) {
		case 'c':
			VF.clear();
			break;
			
		case ' ':
			//パーティクルの場所を初期化
            for (int i = 0; i < particles.size(); i++){
                float angle, length;
                length = ofRandom(3);
                angle = ofRandom(PI * 2.0);
                ofVec2f pos;
                pos.x = cos(angle) * length + ofGetWidth()/2;
                pos.y = sin(angle) * length + ofGetHeight()/2;
                particles[i].setup(pos, ofVec2f(0, 0));
                particles[i].friction = friction;
			}
            VF.randomizeField(0.1);
			break;
            
        case 'r':
            VF.randomizeField(0.1);
            break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
	float diffx = x - prevMouseX;
	float diffy = y - prevMouseY;
	
	//VF.addVectorCircle((float)x, (float)y, diffx*0.3, diffy*0.3, 10, 0.3);
    VF.addClockwiseCircle(x, y, 100, 0.01);
    //VF.addInwardCircle(x,y, 100, 0.01);
	
	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(){
}
