#pragma once
#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include "ofxImGui.h"
#include "ofxImGuizmo.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void drawDebug();
	void keyPressed(int key);

private:
	ofEasyCam cam_;
	ImGuizmo::OPERATION op_;
	ImGuizmo::MODE mode_;
	ofNode node_;
	ofxImGui::Gui gui_;
};
