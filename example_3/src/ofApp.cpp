#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	SurfingGui::setWindowShape(-1);
	
	ui.setup();

	setupImGuizmo();	
	
	cam.setPosition({ 0,0,100 });
	cam.lookAt({ 0,0,0 });
}

//--------------------------------------------------------------
void ofApp::setupImGuizmo()
{

	op_ = ImGuizmo::TRANSLATE;
}


//--------------------------------------------------------------
void ofApp::drawScene() {
	ofPushStyle();
	ofNoFill();
	ofDrawRectangle(rect);
	ofPopStyle();
	
	
	cam.begin(rect);
	
#if 0
	// Convert the raw camera projection matrix to ofMatrix4x4
	ofMatrix4x4 projectionMatrix(
		cameraProjection[0], cameraProjection[1], cameraProjection[2], cameraProjection[3],
		cameraProjection[4], cameraProjection[5], cameraProjection[6], cameraProjection[7],
		cameraProjection[8], cameraProjection[9], cameraProjection[10], cameraProjection[11],
		cameraProjection[12], cameraProjection[13], cameraProjection[14], cameraProjection[15]
	);

	// Save the current transformation matrix
	ofPushMatrix();

	// Load the custom projection matrix
	ofLoadMatrix(projectionMatrix);
#endif


	ofDrawAxis(10);

	//// Draw your scene here...
	//node_.draw();


	//TODO
	//float sz = 10;
	//ofDrawCone(myNode.getPosition(), sz * myNode.getScale().x, sz * 1.5 * myNode.getScale().y);


#if 0
	// Restore the original transformation matrix
	ofPopMatrix();
#endif

	cam.end();
}

//--------------------------------------------------------------
void ofApp::drawImGuizmo()
{
	ImGuiIO& io = ImGui::GetIO();

#if 1
	// camera
	if (isPerspective)
	{
		Perspective(fov, io.DisplaySize.x / io.DisplaySize.y, 0.1f, 100.f, cameraProjection);
		
		rect.setWidth(io.DisplaySize.x);
		rect.setHeight(io.DisplaySize.y);
	}
	else
	{
		float viewHeight = viewWidth * io.DisplaySize.y / io.DisplaySize.x;
		OrthoGraphic(-viewWidth, viewWidth, -viewHeight, viewHeight, 1000.f, -1000.f, cameraProjection);

		rect.setWidth(viewWidth);
		rect.setHeight(viewHeight);
	}
	ImGuizmo::SetOrthographic(!isPerspective);
#endif

	ImGuizmo::BeginFrame();


	//ofPushStyle();
	//ofNoFill();
	//ofDrawBox(5);
	//ofPopStyle();



	//TODO: ofxImGuizmo
	auto mat = node_.getGlobalTransformMatrix();
	if (ImGuizmo::Manipulate(cam, mat, op_, mode_)) {
		glm::mat4 transformation;
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(mat, scale, rotation, translation, skew, perspective);
		node_.setPosition(translation);
		node_.setScale(scale);
		node_.setOrientation(rotation);
	}


#if 0
	// editor
	ImGui::SetNextWindowPos(ImVec2(1024, 100), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(256, 256), ImGuiCond_Appearing);

	// create a window and insert the inspector
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(320, 340), ImGuiCond_Appearing);
#endif

	ImGui::Begin("Editor", NULL, ImGuiWindowFlags_AlwaysAutoResize);
	{
		if (ImGui::RadioButton("Full view", !useWindow)) useWindow = false;
		ImGui::SameLine();
		if (ImGui::RadioButton("Window", useWindow)) useWindow = true;

		// camera
		ImGui::Text("Camera");
		bool viewDirty = false;
		if (ImGui::RadioButton("Perspective", isPerspective)) isPerspective = true;
		ImGui::SameLine();
		if (ImGui::RadioButton("Orthographic", !isPerspective)) isPerspective = false;
		if (isPerspective)
		{
			ImGui::SliderFloat("Fov", &fov, 20.f, 110.f);
		}
		else
		{
			ImGui::SliderFloat("Ortho width", &viewWidth, 1, 20);
		}
		viewDirty |= ImGui::SliderFloat("Distance", &camDistance, 1.f, 10.f);
		ImGui::SliderInt("Gizmo count", &gizmoCount, 1, 4);
		ImGui::SliderInt("Select", &lastUsing, 0, gizmoCount - 1);

		// update cam when required
		if (viewDirty || firstFrame)
		{
			float eye[] = { cosf(camYAngle) * cosf(camXAngle) * camDistance, sinf(camXAngle) * camDistance, sinf(camYAngle) * cosf(camXAngle) * camDistance };
			float at[] = { 0.f, 0.f, 0.f };
			float up[] = { 0.f, 1.f, 0.f };
			LookAt(eye, at, up, cameraView);
			firstFrame = false;

			//TODO
			{
				// Convert the raw camera view matrix to ofMatrix4x4
				//ofMatrix4x4 viewMatrix(
				glm::mat4 viewMatrix(
					cameraView[0], cameraView[1], cameraView[2], cameraView[3],
					cameraView[4], cameraView[5], cameraView[6], cameraView[7],
					cameraView[8], cameraView[9], cameraView[10], cameraView[11],
					cameraView[12], cameraView[13], cameraView[14], cameraView[15]
				);

				// Convert the raw camera projection matrix to ofMatrix4x4
				ofMatrix4x4 projectionMatrix(
					cameraProjection[0], cameraProjection[1], cameraProjection[2], cameraProjection[3],
					cameraProjection[4], cameraProjection[5], cameraProjection[6], cameraProjection[7],
					cameraProjection[8], cameraProjection[9], cameraProjection[10], cameraProjection[11],
					cameraProjection[12], cameraProjection[13], cameraProjection[14], cameraProjection[15]
				);

				// Decompose the view matrix into position, rotation (as a quaternion), and scale
				glm::vec3 position, scale;
				glm::quat orientation;
				glm::vec3 skew;
				glm::vec4 perspective;
				glm::decompose(viewMatrix, scale, orientation, position, skew, perspective);

				// Set the position, orientation and scale
				cam.setPosition(position);
				cam.setOrientation(glm::eulerAngles(orientation));
				cam.setScale(scale.x, scale.y, scale.z);  // Assuming uniform scaling
			}
		}

		//--

		// debug info
		ImGui::Text("X: %f Y: %f", io.MousePos.x, io.MousePos.y);
		if (ImGuizmo::IsUsing())
		{
			ImGui::Text("Using gizmo");
		}
		else
		{
			ImGui::Text(ImGuizmo::IsOver() ? "Over gizmo" : "");
			ImGui::SameLine();
			ImGui::Text(ImGuizmo::IsOver(ImGuizmo::TRANSLATE) ? "Over translate gizmo" : "");
			ImGui::SameLine();
			ImGui::Text(ImGuizmo::IsOver(ImGuizmo::ROTATE) ? "Over rotate gizmo" : "");
			ImGui::SameLine();
			ImGui::Text(ImGuizmo::IsOver(ImGuizmo::SCALE) ? "Over scale gizmo" : "");
		}
		ImGui::Separator();

		//--

		// gizmos/objects
		for (int matId = 0; matId < gizmoCount; matId++)
		{
			ImGuizmo::SetID(matId);

			EditTransform(cameraView, cameraProjection, objectMatrix[matId], lastUsing == matId);

			if (ImGuizmo::IsUsing())
			{
				lastUsing = matId;
			}
		}

		////TODO:
		//// get object 0
		//const glm::mat4 m44 = glm::make_mat4(objectMatrix[0]);
		//setOfNodeTransformMatrix(&myNode, m44);
	}
	ImGui::End();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	if (!bGui) return;

	ui.Begin();
	{
		drawImGuizmo();
	}
	ui.End();


	drawScene();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'g') { bGui = !bGui; }
	
	//TODO: ofxImGuizmo
	switch (key) {
	case 'w': op_ = ImGuizmo::TRANSLATE; mCurrentGizmoOperation = ImGuizmo::TRANSLATE; break;
	case 'e': op_ = ImGuizmo::SCALE; mCurrentGizmoOperation = ImGuizmo::SCALE; break;
	case 'r': op_ = ImGuizmo::ROTATE; mCurrentGizmoOperation = ImGuizmo::ROTATE; break;
	case ' ': mode_ = mode_ == ImGuizmo::LOCAL ? ImGuizmo::WORLD : ImGuizmo::LOCAL; mCurrentGizmoMode = mode_; break;
	}
}