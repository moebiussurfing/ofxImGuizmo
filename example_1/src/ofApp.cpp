#include "ofApp.h"
#include <glm/gtx/matrix_decompose.hpp>

//--------------------------------------------------------------
void ofApp::setup(){
	gui_.setup();

	cam_.setPosition({0,0,100});
	cam_.lookAt({0,0,0});

	op_ = ImGuizmo::TRANSLATE;
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam_.begin();
	node_.draw();
	cam_.end();

	gui_.begin();
	ImGuizmo::BeginFrame();
	ImGuizmo::Manipulate(cam_, node_, op_, mode_);
	gui_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'w': op_ = ImGuizmo::TRANSLATE; break;
		case 'e': op_ = ImGuizmo::SCALE; break;
		case 'r': op_ = ImGuizmo::ROTATE; break;
		case ' ': mode_ = mode_==ImGuizmo::LOCAL?ImGuizmo::WORLD:ImGuizmo::LOCAL; break;
	}
}
