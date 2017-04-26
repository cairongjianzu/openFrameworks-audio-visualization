#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableSmoothing();
	ofSetVerticalSync(true);
	screenw = ofGetWidth();
	screenh = ofGetHeight();
 

	_bChange.set("ChangeCharecter", false);	
	_DisplayCharacter.setName("CharacterWave");	
	_DisplayCharacter.add(_bChange);
	//�Ƿ�ı���ĸ
	_bChange.addListener(this, &ofApp::bChangeCharacter);
	
    _GUI.setup("GUI");
	_GUI.add(_DisplayCharacter);
    _GUI.setPosition(ofGetWidth()-_GUI.getWidth(),0);

	boneFont.loadFont("GOUDYSTO.ttf", 200);
	ofBackground(0, 0, 0);
	showC = "A";
	showLine = false;
	//������������
	sound.loadSound("song.mp3");
	sound.setLoop(true);
	sound.play();
	time0 = 0;

	//��ʼ��Ƶ����
	for (int i = 0; i<N; i++) {
		spectrum[i] = 0.0f;
	}
	//��ʼ������
	for (int i = 0; i < 700; i++) {
		par myParticle;
		myParticle.setInitialCondition(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0, 0);
		particles.push_back(myParticle);
	}
	//��ʼ������
	initCanvas();
}

//--------------------------------------------------------------
void ofApp::update(){
	_GUI.setPosition(ofGetWidth() - _GUI.getWidth(), 0);
	ofSoundUpdate();
	beatSound();
	updateParticles();
}

//--------------------------------------------------------------
void ofApp::draw(){
	float time = ofGetElapsedTimef();
	float u = 0.025 + time;
	ofSoundUpdate();
	beatSound();

	_Canvas.draw(0, 0, ofGetWidth(), ofGetHeight());
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].pos.x >(ofGetWidth() / 2 - boneFont.stringWidth(showC) / 2 - 20)
			&& particles[i].pos.x < (ofGetWidth() / 2 + boneFont.stringWidth(showC) / 2 + 90)
			&& particles[i].pos.y >(ofGetHeight() / 2 - boneFont.stringHeight(showC) / 2 - 50)
			&& particles[i].pos.y < (ofGetHeight() / 2 + boneFont.stringHeight(showC) / 2) + 40)
		{
			//�����Ʒ�Χ�ڸ��ݻ�����ɫ��ʾ����
			if (_VFPx.getColor(floor(particles[i].pos.x), floor(particles[i].pos.y)) == ofColor(0, 0, 1, 255)) {
				int red = ofMap(sin(u), -1, 1, 0, 255);
				int green = ofMap(sin(u * 2), -1, 1, 0, 255);
				int blue = 255 - green;
				color = ofColor(red, green, blue);
				particles[i].draw(color);
			}
			else if(_VFPx.getColor(floor(particles[i].pos.x), floor(particles[i].pos.y)) == ofColor(255, 228, 225, 255)){
				color = ofColor(255, 228, 225);
				particles[i].draw(color);
			}
			else {
				color = ofColor(0, 0, 0);
				particles[i].draw(color);
			}
		}
	}	
    _GUI.draw();
}
//��Ƶ�����еĵ�����������ʾ����
void ofApp::beatSound() {
	float *val = ofSoundGetSpectrum(N);
	if (val[2] > 0.5) {
		showLine = true;
	}
	else {
		showLine = false;
	}
	initCanvas();
}
//�任��д��ĸ
void ofApp::bChangeCharacter(bool &val) {

	if (val) {
		if (showC[0] > 'Y') {
			showC[0] = 'A';
		}
		else {
			showC[0] += 1;
		}
		initCanvas();
	}
}
//��ʼ������
void ofApp::initCanvas() {
	_Canvas.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	_Canvas.begin();
	ofClear(0, 0, 0, 0);
	ofPushStyle();
	ofSetColor(0, 0, 1);
	boneFont.drawString(showC, ofGetWidth() / 2 - boneFont.stringWidth(showC) / 2, ofGetHeight() / 2 + boneFont.stringHeight(showC) / 2);
	ofPopStyle();
	if (showLine) {
		ofPushStyle();
		ofSetColor(255, 228, 225);
		ofNoFill();
		ofSetLineWidth(3);
		float angle = 0;
		float angleVel = ofRandom(0.0,0.1);
		//��ʾ����
		ofBeginShape();
		for (int x = 0; x <= ofGetWidth(); x += 5) {
			float y = ofMap(sin(angle), -1, 1, ofGetHeight() / 2.5, ofGetHeight() / 1.5);
		    ofVertex(x, y);
			angle += angleVel;
		}
		ofEndShape();
		ofPopStyle();
	}
	_Canvas.end();
	_Canvas.readToPixels(_VFPx);
}
//�����������ӡ������е�������֮����ų���������������������
void ofApp::updateParticles() {
	//��ʼ����
	for (int i = 0; i < particles.size(); i++) {
		particles[i].resetForce();
	}
	for (int i = 0; i < particles.size(); i++) {
		//���߳���ʱ���е�����Ӳ����ų��������Ч�������������˶�������
		if ( showLine ) {
			particles[i].addRepulsionForce(ofGetWidth()/2, ofGetHeight()/2, 700, 2.5);
		}
		else {
			particles[i].addAttractionForce(ofGetWidth() / 2, ofGetHeight() / 2, 700, 2.5);
		}
		for (int j = 0; j < i; j++) {
			//����������֮�����������������󣬲�����������������Χ�������󣬲����ۼ�Ч��
			particles[i].addRepulsionForce(particles[j], 60, 0.95);
			particles[i].addAttractionForce(particles[j], 600, 0.005);
		}
	}

	for (int i = 0; i < particles.size(); i++) {
		particles[i].addDampingForce();
		particles[i].update();
	}
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofSetWindowShape(screenw, screenh);//������Ļ��С

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
