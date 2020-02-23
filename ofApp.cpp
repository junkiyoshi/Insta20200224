#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(300, 3);
	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->frame.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		auto index = this->mesh.getNumVertices();
		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(glm::vec4(avg * 0.01, ofGetFrameNum() * 0.005));
		
		auto noise_radius = 100;
		if (noise_value > 0.7) { noise_radius = ofMap(noise_value, 0.7, 1, 100, 350); }

		vector<glm::vec3> vertices;

		vertices.push_back(glm::normalize(triangle.getVertex(0)) * (noise_radius + 20));
		vertices.push_back(glm::normalize(triangle.getVertex(1)) * (noise_radius + 20));
		vertices.push_back(glm::normalize(triangle.getVertex(2)) * (noise_radius + 20));

		vertices.push_back(glm::normalize(triangle.getVertex(0)) * (noise_radius - 20));
		vertices.push_back(glm::normalize(triangle.getVertex(1)) * (noise_radius - 20));
		vertices.push_back(glm::normalize(triangle.getVertex(2)) * (noise_radius - 20));

		mesh.addVertices(vertices);
		frame.addVertices(vertices);

		mesh.addIndex(index + 0); mesh.addIndex(index + 1); mesh.addIndex(index + 2);
		mesh.addIndex(index + 3); mesh.addIndex(index + 4); mesh.addIndex(index + 5);

		mesh.addIndex(index + 0); mesh.addIndex(index + 3); mesh.addIndex(index + 4);
		mesh.addIndex(index + 0); mesh.addIndex(index + 4); mesh.addIndex(index + 1);

		mesh.addIndex(index + 1); mesh.addIndex(index + 4); mesh.addIndex(index + 5);
		mesh.addIndex(index + 1); mesh.addIndex(index + 5); mesh.addIndex(index + 2);
		
		mesh.addIndex(index + 2); mesh.addIndex(index + 5); mesh.addIndex(index + 3);
		mesh.addIndex(index + 2); mesh.addIndex(index + 3); mesh.addIndex(index + 0);

		frame.addIndex(index + 0); frame.addIndex(index + 1);
		frame.addIndex(index + 1); frame.addIndex(index + 2);
		frame.addIndex(index + 2); frame.addIndex(index + 0);

		frame.addIndex(index + 3); frame.addIndex(index + 4);
		frame.addIndex(index + 4); frame.addIndex(index + 5);
		frame.addIndex(index + 5); frame.addIndex(index + 3);

		frame.addIndex(index + 0); frame.addIndex(index + 3);
		frame.addIndex(index + 1); frame.addIndex(index + 4);
		frame.addIndex(index + 2); frame.addIndex(index + 5);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	ofSetColor(39);
	this->mesh.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}