#include "RandomWalker.h"

RandomWalker::RandomWalker(){

    //初期位置を、画面内にランダムに設定
    position.x = ofGetWidth()/2.0;
    position.y = ofGetHeight()/2.0;
    left = ofRandom(0.9, 1.0);
    right = ofRandom(0.9, 1.0);
    top = ofRandom(0.9, 1.0);
    bottom = ofRandom(0.9, 1.0);
}

void RandomWalker::draw(){
    // 10回くりかえし
    for (int i = 0; i < 10; i++) {
        
        //上下左右同じ確率でランダムに移動
        position.x += ofRandom(-left, right);
        position.y += ofRandom(-top, bottom);
        
        // 画面からはみ出たら、反対側から出現
        if (position.x < 0) {
            position.x = ofGetWidth();
        }
        if (position.x > ofGetWidth()) {
            position.x = 0;
        }
        if (position.y < 0) {
            position.y = ofGetHeight();
        }
        if (position.y > ofGetHeight()) {
            position.y = 0;
        }
        
        //円を描く
        ofCircle(position.x, position.y, 1);
    }
}