#pragma once

#include "ofMain.h"

#include "ofxBTrack.h"

#include "ofxSoundDevicesManager.h"


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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxBTrack btrack;

		ofxSoundDevicesManager audioDevices;

		int sampleRate = 44100;
		int bufferSize = 256;

        void audioIn(float *input, int bufferSize, int nChannels);
		//void audioIn(ofSoundBuffer& input) override; 
		void audioOut(ofSoundBuffer& output) override;

		void drawWaveform();
		float waveformInput[4096]; //make this bigger, just in case
		int waveInputIndex;
		float waveformOutput[4096]; //make this bigger, just in case
		int waveOutputIndex;

		void setupLogDebug();
};
