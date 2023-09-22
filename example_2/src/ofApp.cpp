#include "ofApp.h"
#include <glm/gtx/matrix_decompose.hpp>

//--------------------------------------------------------------
void ofApp::setup() {
	gui_.setup();

	cam_.disableMouseInput();
	cam_.setPosition({ 0,0,100 });
	cam_.lookAt({ 0,0,0 });

	op_ = ImGuizmo::TRANSLATE;
	mode_ = ImGuizmo::LOCAL;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::drawDebug() {
	string s = "";
	s += "\n";
	s += "KEYS\n\n";
	s += "BACKSPACE: Reset\n";
	s += "\n";
	s += "E, R, T:\n";
	switch (op_)
	{
	case ImGuizmo::TRANSLATE: s += "TRANSLATE"; break;
	case ImGuizmo::ROTATE: s += "ROTATE"; break;
	case ImGuizmo::SCALE: s += "SCALE"; break;
	}
	s += "\n\n";
	s += "Transformation:\n" + ofToString(node_.getGlobalTransformMatrix());
	s += "\n\n";
	s += "Scale:\n" + ofToString(node_.getGlobalScale());
	s += "\n\n";
	s += "Rotation:\n" + ofToString(node_.getGlobalOrientation());
	s += "\n\n";
	s += "SPACE:\nMODE ";
	if (mode_ == ImGuizmo::LOCAL) s += "LOCAL\n";
	else if (mode_ == ImGuizmo::WORLD) s += "WORLD\n";
	ofDrawBitmapStringHighlight(s, 10, 20);
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawDebug();

	//--

	cam_.begin();
	{
		//node_.draw();

		// Applies the node's transformation matrix
		ImGuizmo::beginGuizmoTransform(node_);
		{
			ofPushStyle();
			ofNoFill();
			ofDrawBox(25);
			ofPopStyle();
		}
		ImGuizmo::endGuizmoTransform();
	}
	cam_.end();

	ImGuizmo::drawImGuizmo(&gui_, cam_, node_, op_, mode_);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key)
	{
	case 'w': op_ = ImGuizmo::TRANSLATE; break;
	case 'e': op_ = ImGuizmo::SCALE; break;
	case 'r': op_ = ImGuizmo::ROTATE; break;

	case ' ': mode_ = mode_ == ImGuizmo::LOCAL ? ImGuizmo::WORLD : ImGuizmo::LOCAL; break;

	case OF_KEY_BACKSPACE: {//reset ofNode
		node_.setPosition(glm::vec3{ 0,0,0 });
		node_.setScale(glm::vec3{ 1,1,1 });
		node_.setOrientation(glm::quat{ 0,0,0,0 });
	}break;
	}
}
