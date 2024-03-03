#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->noise_param += 0.03;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	
	ofColor color;
	for (int deg_start = 0; deg_start < 360; deg_start += 30) {

		auto noise_seed = ofRandom(1000);
		for (int deg = deg_start; deg < deg_start + 8; deg += 1) {

			color.setHsb(ofMap(deg, deg_start, deg_start + 8, 0, 255), 230, 255);
			ofSetColor(color);

			ofPushMatrix();
			ofRotate(deg_start);

			auto base_location = glm::vec2(0, -15);
			auto target_location = glm::vec2(0, -320);
			auto distance = target_location - base_location;
			auto len = glm::length(distance);

			for (int d = 0; d <= len; d++) {

				auto location = base_location + glm::normalize(distance) * d;

				auto gap = abs(len * 0.5 - d);
				auto power = gap < len * 0.15 ? 1 : ofMap(gap, len * 0.15, len * 0.5, 1, 0);

				auto noise_x = ofMap(ofNoise(noise_seed + deg * 0.03, location.x * 0.0085, location.y * 0.0085 + this->noise_param), 0, 1, -40, 40);
				location += glm::vec2(noise_x * power, 0);

				ofDrawCircle(location, 1);
			}

			ofPopMatrix();
		}
	}

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}