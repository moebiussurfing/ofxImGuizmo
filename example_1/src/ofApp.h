#pragma once
#include "ofMain.h"

#define IMGUI_DEFINE_MATH_OPERATORS

#include "ofxImGui.h"
#include "ofxImGuizmo.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void draw();
	void keyPressed(int key);

private:
	ofCamera cam_;
	ImGuizmo::OPERATION op_;
	ImGuizmo::MODE mode_;
	ofNode node_;
	ofxImGui::Gui gui_;
};
