#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 44100;
    bufferSize = 256;
    
    // Setup frame size
    btrack.setup(bufferSize);
    
    // FIX: this is experimental inplementation.
    btrack.setConfidentThreshold(0.75);
    
    
	// Setup Audio Input
	audioDevices.setup();//setup with default settings
	//ofSoundStreamSetup(0, 1, sampleRate, bufferSize, 4);

	setupLogDebug();
}

//--------------------------------------------------------------
void ofApp::update(){
	audioDevices.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // BPM
    ofSetColor(ofColor::black);
    float bpm = btrack.getEstimatedBPM();
    ofDrawBitmapString("Estimated BPM: " + ofToString(bpm, 1), 30, 50);
    ofDrawBitmapString("Confidence: " + ofToString(btrack.getConfidence(), 2), 30, 75); // confidence is an experimental feature at this moment
    

    // Beat
    ofDrawBitmapString("BEAT", 85, 195);
    if (btrack.hasBeat()) {    //FIXME: calling this method resets hasBeat flag in ofxBTrack object
        ofSetColor(ofColor::magenta);
    } else ofSetColor(ofColor::lightGray);
    ofDrawCircle(100, 150, 30);

	//--

	audioDevices.draw();

	drawWaveform();
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//log
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

	float w = 600;
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
void ofApp::drawWaveform() {
	//ofSetColor(255, 225);
	ofSetColor(0, 225);

	ofFill();
	ofSetLineWidth(1.0f);

	ofPushMatrix();

	ofTranslate(0, ofGetHeight() / 4);
	ofDrawLine(0, 0, 1, waveformInput[1] * ofGetHeight() / 2.); //first line
	for (int i = 1; i < (ofGetWidth() - 1); ++i) {
		ofDrawLine(i, waveformInput[i] * ofGetHeight() / 2., i + 1, waveformInput[i + 1] * ofGetHeight() / 4.);
	}

	ofTranslate(0, 2 * ofGetHeight() / 4);
	ofDrawLine(0, 0, 1, waveformOutput[1] * ofGetHeight() / 2.); //first line
	for (int i = 1; i < (ofGetWidth() - 1); ++i) {
		ofDrawLine(i, waveformOutput[i] * ofGetHeight() / 2., i + 1, waveformOutput[i + 1] * ofGetHeight() / 4.);
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::audioIn(float *input, int _bufferSize, int _nChannels) {

	// feed audio frame into ofxBTrack object
	btrack.audioIn(input, _bufferSize, _nChannels);

	//std::size_t nChannels = nChannels;
	//for (size_t i = 0; i < _bufferSize; i++)
	//{
	//	// handle input here
	//	//Hold the values so the draw method can draw them
	//	waveformInput[waveInputIndex] = input[i * _nChannels];
	//	if (waveInputIndex < (ofGetWidth() - 1)) {
	//		++waveInputIndex;
	//	}
	//	else {
	//		waveInputIndex = 0;
	//	}
	//}
}

////--------------------------------------------------------------
//void ofApp::audioIn(ofSoundBuffer& input) {
//	// feed audio frame into ofxBTrack object
//	btrack.audioIn(input.get, bufferSize, input.getNumChannels());//?
//
//	//std::size_t nChannels = input.getNumChannels();
//	//for (size_t i = 0; i < input.getNumFrames(); i++)
//	//{
//	//	// handle input here
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

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output) {
	float volume = 0.1f;
	std::size_t outChannels = output.getNumChannels();
	for (int i = 0; i < output.getNumFrames(); ++i) {

		//output[i * outChannels] = oscillator1.square(532) * 0.5;
		//output[i * outChannels + 1] = output[i * outChannels];

		output[i * outChannels] = volume * ofRandom(-1, 1);
		output[i * outChannels + 1] = output[i * outChannels];

		//Hold the values so the draw method can draw them
		waveformOutput[waveOutputIndex] = output[i * outChannels];
		if (waveOutputIndex < (ofGetWidth() - 1)) {
			++waveOutputIndex;
		}
		else {
			waveOutputIndex = 0;
		}
	}
}