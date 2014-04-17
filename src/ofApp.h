#pragma once

#include "ofMain.h"

#define BUFFER_SIZE 512
#define SAMPLE_RATE 44100
#define NUM_SAMPLES 3072

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
    void audioOut(float *input, int bufferSize, int nChannels);
private:
    ofSoundStream soundStream;
    vector<int> notes;
    vector<float> period;
    vector<float> lAudio;
    vector<float> rAudio;
    int periodN;
    int periodIndex;
    float current;
    bool feedNoise;
};
