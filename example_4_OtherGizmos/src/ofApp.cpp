#include "ofApp.h"
#include <glm/gtx/matrix_decompose.hpp>

//--------------------------------------------------------------
void ofApp::setup() {
	gui_.setup();

	cam_.setPosition({ 0,0,100 });
	cam_.lookAt({ 0,0,0 });
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam_.begin();
	node_.draw();
	cam_.end();

	gui_.begin();

	//ImGuizmo::BeginFrame();
	//ImGuizmo::Manipulate(cam_, node_, op_, mode_);


	float* const viewMatrix = cameraView;
	const float* const projectionMatrix = cameraProjection;

	const ImVec2 pos{ 0.0f, 0.0f };
	const float size = 120.0f;
	const float pivotDistance = 0.0f;
	const bool background = false;

	ImGui::Begin("ofApp");
	
	ImGuiIO& io = ImGui::GetIO();

	Perspective(fov, io.DisplaySize.x / io.DisplaySize.y, 0.1f, 100.f, cameraProjection);

	rect.setWidth(io.DisplaySize.x);
	rect.setHeight(io.DisplaySize.y);


	//// specify position and size of guizmo window
	//// optional: set distance to pivot (-> activates interaction)
	//// optional: show background
	//if (ImOGuizmo::drawGizmo(viewMatrix, projectionMatrix, pos, size, pivotDistance, false))
	//{
	//	// in case of user interaction viewMatrix gets updated
	//}
	
	static const float identityMatrix[16] =
	{ 1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f };

	//TODO
	//ImGuizmo::DrawCubes(cameraView, cameraProjection, &objectMatrix[0], 1);
	//ImGuizmo::DrawGrid(cameraView, cameraProjection, identityMatrix, 100.f);
	//ImGuizmo::DrawGrid(viewMatrix, projectionMatrix, identityMatrix, 100.f);

	ImGui::End();

	gui_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'w': op_ = ImGuizmo::TRANSLATE; break;
	case 'e': op_ = ImGuizmo::SCALE; break;
	case 'r': op_ = ImGuizmo::ROTATE; break;
	case ' ': mode_ = mode_ == ImGuizmo::LOCAL ? ImGuizmo::WORLD : ImGuizmo::LOCAL; break;
	}
}
