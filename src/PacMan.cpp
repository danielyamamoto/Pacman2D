#include "PacMan.h"

PacMan::PacMan() {
	pos.set(0, 0);
	stop();
	radius = 10;
	rect.set(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
}

PacMan::PacMan(float x, float y, float rad) : pos(x, y), radius(rad) {
	velX = 3;
	velY = 3;	
	rect.set(pos.x - radius, pos.y - radius, radius * 2, radius * 2);
	move = false;
	stop();
}

void PacMan::update(float delta) {
	if (pos.x + radius < 0) { // Teletransporta a PacMan del otro lado de la pantalla
		pos.x = ofGetWidth() - radius;
		direction = LEFT;
		move = true;
	}
	else if (pos.x + radius > ofGetWidth()) { // Teletransporta a PacMan del otro lado de la pantalla
		pos.x = -radius;
		direction = RIGHT;
		move = true;
	}
	
	if (move) {
		switch (direction) {
		case UP:
			pos.y -= velY;
			break;
		case DOWN:
			pos.y += velY;
			break;
		case LEFT:
			pos.x -= velX;
			break;
		case RIGHT:
			pos.x += velX;
			break;
		}
	}
}

void PacMan::draw() {
	// Dibuja PacMan
	ofSetColor(255, 255, 0);
	ofDrawCircle(pos.x, pos.y, radius + 4);
	// Dibuja Rectángulo 
	//ofNoFill();
	//ofDrawRectangle(rect);
	//ofFill();
}

void PacMan::loadImage() {
	img.load("pacman.png");
	img.resize(pos.x, pos.y);
}

void PacMan::setPosition(ofVec2f &p) {
	pos = p;
	rect.setPosition(pos.x - radius, pos.y - radius);
}

void PacMan::setPosition(float x, float y) {
	pos.set(x, y);
	rect.setPosition(pos.x - radius, pos.y - radius);
}

void PacMan::moveRight() {
	direction = RIGHT;
	move = true;
}

void PacMan::moveLeft() {
	direction = LEFT;
	move = true;
}

void PacMan::moveUp() {
	direction = UP;
	move = true;
}

void PacMan::moveDown() {
	direction = DOWN;
	move = true;
}

void PacMan::stop() {
	move = false;
}