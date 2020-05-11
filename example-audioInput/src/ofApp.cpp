#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	
	//-

	sampleRate = 44100;
	bufferSize = 256;

	//setup frame size
	btrack.setup(bufferSize);

	//FIX: this is experimental inplementation.
	btrack.setConfidentThreshold(0.75);

	//beat circle
	float _radius = 200;
	ofSetCircleResolution(80);
	circleBeat.setColor(ofColor(255, 225));
	circleBeat.setSize(_radius);
	circleBeat.setSpeed(0.2f);
	glm::vec2 _pos = glm::vec2(ofGetWindowWidth()*0.5f, ofGetWindowHeight()*0.5f);
	circleBeat.setPosition(_pos);

	//-

	//setup Audio Input
	audioDevices.setup(sampleRate, bufferSize);
	//or use your own sound manager
	//ofSoundStreamSetup(0, 1, sampleRate, bufferSize, 4);

#ifdef INCLUDE_ofxTextFlow//LOG
	setupLogDebug();
#endif
}

//--------------------------------------------------------------
void ofApp::update() {
	audioDevices.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	//BPM
	float bpm = btrack.getEstimatedBPM();
	ofDrawBitmapStringHighlight("ESTIMATED BPM: " + ofToString(bpm, 1), 30, 300);
	ofDrawBitmapStringHighlight("CONFIDENCE: " + ofToString(btrack.getConfidence(), 2), 30, 325);
	//confidence is an experimental feature at this moment

	//Beat callback
	circleBeat.draw();
	if (btrack.hasBeat())
	{
		circleBeat.bang();
#ifdef INCLUDE_ofxTextFlow//LOG
		logLine("BEAT! \t BPM: " + ofToString(bpm,1));
#endif
	}

	//without circleBeat
	//ofDrawBitmapString("BEAT", 85, 195);
	//if (btrack.hasBeat()) {    //FIXME: calling this method resets hasBeat flag in ofxBTrack object
	//	ofSetColor(ofColor::magenta);
	//}
	//else ofSetColor(ofColor::lightGray);
	//ofDrawCircle(100, 150, 30);

	//--

	audioDevices.draw();

	drawWaveform();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}


//--------------------------------------------------------------
void ofApp::drawWaveform() {

	ofPushStyle();
	ofPushMatrix();

	ofFill();
	ofSetColor(0, 225);
	ofSetLineWidth(3.0f);
	//float _max = ofGetHeight() / 5.f;
	float _max = 200;

	ofTranslate(0, ofGetHeight() / 2.f);
	ofDrawLine(0, 0, 1, waveformInput[1] * _max); //first line
	for (int i = 1; i < (ofGetWidth() - 1); ++i) {
		ofDrawLine(i, waveformInput[i] * _max, i + 1, waveformInput[i + 1] * _max);
	}

	ofPopMatrix();
	ofPopStyle();
}

//audio callbacks
//--------------------------------------------------------------
void ofApp::audioIn(float *input, int _bufferSize, int _nChannels) {

	//feed audio frame into ofxBTrack object
	btrack.audioIn(input, _bufferSize, _nChannels);

	std::size_t nChannels = _nChannels;
	for (size_t i = 0; i < _bufferSize; i++)
	{
		//handle input here
		//Hold the values so the draw method can draw them
		waveformInput[waveInputIndex] = input[i * _nChannels];
		if (waveInputIndex < (ofGetWidth() - 1)) {
			++waveInputIndex;
		}
		else {
			waveInputIndex = 0;
		}
	}
}

////--------------------------------------------------------------
//void ofApp::audioIn(ofSoundBuffer& input) {
//	//feed audio frame into ofxBTrack object
//	btrack.audioIn(input.get, bufferSize, input.getNumChannels());//?
//
//	//std::size_t nChannels = input.getNumChannels();
//	//for (size_t i = 0; i < input.getNumFrames(); i++)
//	//{
//	//	//handle input here
//	//	//Hold the values so the draw method can draw them
//	//	waveformInput[waveInputIndex] = input[i * nChannels];
//	//	if (waveInputIndex < (ofGetWidth() - 1)) {
//	//		++waveInputIndex;
//	//	}
//	//	else {
//	//		waveInputIndex = 0;
//	//	}
//	//}
//}


#ifdef INCLUDE_ofxTextFlow//LOG
//--------------------------------------------------------------
void ofApp::setupLogDebug() {
	string pathFont = "fonts/telegrama_render.otf";
	float fontSize = 8;
	ofFile file(pathFont);
	if (file.exists())//must check this font file is found there
	{
		ofxGuiSetFont(pathFont, fontSize);
	}
	else
	{
		ofLogError(__FUNCTION__) << "Font file not found: " << pathFont;
	}

	float w = 500;
	ofxTextFlow::loadFont(pathFont, 6);
	ofxTextFlow::setBackgroundColor(ofColor(0, 0, 0, 200));
	ofxTextFlow::setBBoxWidth(w);
	ofxTextFlow::setMaxLineNum(40);
	ofxTextFlow::setPosition(10, 400);//left
	ofxTextFlow::setShowing(true);
	ofxTextFlow::setShowingBBox(true);
	ofxTextFlow::setMarginBorders(10);
	ofxTextFlow::setRounded(true, 5);
	ofxTextFlow::setTitle("ofxSoundDevicesManager");
}

//--------------------------------------------------------------
void ofApp::logLine(string s)
{
	ofxTextFlow::addText(s);
	ofLogNotice(__FUNCTION__) << s;
}

#endif


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}