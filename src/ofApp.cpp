#include "ofApp.h"

void ofApp::setup() {
    lAudio.assign(BUFFER_SIZE, 0.0);
    rAudio.assign(BUFFER_SIZE, 0.0);
    soundStream.setup(this, 2, 0, SAMPLE_RATE, BUFFER_SIZE, 4);
    
    notes.push_back(82);
    notes.push_back(110);
    notes.push_back(147);
    notes.push_back(196);
    notes.push_back(247);
    notes.push_back(330);
    
    periodN = SAMPLE_RATE / 220; // length = sampleRate / targetFrequency
    period.clear();
    for (int i = 0; i < periodN; i++) {
        period.push_back(0);
    }
    periodIndex = 0;
    feedNoise = true;
    current = 0.0;
}

void ofApp::update() {
    for (int i = 0; i < NUM_SAMPLES; ++i) {
        if (periodIndex == periodN) {
            periodIndex = 0;
            feedNoise = false;
        }
        
        if (feedNoise) {
            period[periodIndex] += ofRandom(1) - ofRandom(1);
        }
        
        current += (period[periodIndex] - current) * 0.5; // 1 pole lowpass
        period[periodIndex] = current; // write feedback
        cout << current << endl;
        ++periodIndex;
    }
}

void ofApp::draw() {

}

void ofApp::keyReleased(int key) {
    int result = -1;
    switch (key) {
        case '1': result = notes[0]; break;
        case '2': result = notes[1]; break;
        case '3': result = notes[2]; break;
        case '4': result = notes[3]; break;
        case '5': result = notes[4]; break;
        case '6': result = notes[5]; break;
    }
    cout << "KEY: " << result << endl;
    current = result;
    feedNoise = false;
}

void ofApp::audioOut(float *input, int bufferSize, int nChannels) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        lAudio[i] = input[i * nChannels] = current;
        rAudio[i] = input[i * nChannels + 1] = current;
    }
}
