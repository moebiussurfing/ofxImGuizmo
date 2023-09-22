#pragma once
#include "ofMain.h"

/*

TODO
not working yet

*/

#define IMGUI_DEFINE_MATH_OPERATORS

#include "ofxImGui.h"
#include "ofxImGuizmo.h"

//// Required C++17 / OF 0.12
//#include "imoguizmo.hpp"
//// it is recommended to use a separate projection matrix since the values that work best
//// can be very different from what works well with normal renderings
//// aspect ratio should be 1 otherwise axes would scale differently
//// e.g. with glm -> glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);

#include "ImGuizmoExample.cpp"

class ofApp : public ofBaseApp {

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

	// raw cpp camera
	float cameraView[16] =
	{ 1.f, 0.f, 0.f, 0.f,
	  0.f, 1.f, 0.f, 0.f,
	  0.f, 0.f, 1.f, 0.f,
	  0.f, 0.f, 0.f, 1.f };
	float cameraProjection[16];


	float objectMatrix[16] =
	{ 1.f, 0.f, 0.f, 0.f,
	  0.f, 1.f, 0.f, 0.f,
	  0.f, 0.f, 1.f, 0.f,
	  0.f, 0.f, 0.f, 1.f };



	// Camera projection
	bool isPerspective = true;
	float fov = 27.f;
	float viewWidth = 10.f; // for orthographic
	float camYAngle = 165.f / 180.f * 3.14159f;
	float camXAngle = 32.f / 180.f * 3.14159f;


	float w = 320;
	ofRectangle rect{ 0, 0, w, w / (16 / 9.f) };

};
