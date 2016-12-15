#pragma once
#include "ofGraphics.h"
#include "ofVec2f.h"
#include "ofRectangle.h"
#include "ofAppRunner.h"
#include "ofImage.h"

enum Direction {UP, DOWN, LEFT, RIGHT}; // Movimientos

class PacMan {
public:
	ofRectangle rect;
	ofVec2f pos;
	Direction direction;
	ofImage img;

	float radius;
	float velX, velY;
	bool move;

	PacMan();
	PacMan(float x, float y, float rad);
	void update(float delta);
	void draw();
	void loadImage();
	void setPosition(ofVec2f &p);
	void setPosition(float x, float y);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void stop();
};