#pragma once

#include "ofMain.h"

#include "ofxBTrack.h"

#include "ofxSoundDevicesManager.h"
#include "circleBeat.h"

//LOG
//#define INCLUDE_ofxTextFlow
#ifdef INCLUDE_ofxTextFlow
#include "ofxTextFlow.h"
#endif

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

		int sampleRate = 44100;
		int bufferSize = 256;
    
        ofxBTrack btrack;
		CircleBeat circleBeat;

		ofxSoundDevicesManager audioDevices;

        void audioIn(float *input, int bufferSize, int nChannels);
		//void audioIn(ofSoundBuffer& input) override; 

		void drawWaveform();
		float waveformInput[4096]; //make this bigger, just in case
		int waveInputIndex;

#ifdef INCLUDE_ofxTextFlow//LOG
		void setupLogDebug();
		void logLine(string s);
#endif
};
