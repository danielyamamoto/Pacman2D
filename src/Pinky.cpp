#include "Pinky.h"

void Pinky::init(int x, int y, int w, int h, TMXMap & map) {
	this->map = &map;
	pos.set(x, y);
	rect.set(pos.x - w / 2, pos.y - h / 2, w, h);
	img.load("pinky.png");
	img.resize(rect.getWidth(), rect.getHeight());
	speed = 1;
	state = SCATTER;
	scatterTarget.set(0, 0);
	target = scatterTarget;
	direction = RIGHT;
	nextDirection = RIGHT;
	Index index = getTileIndex(pos.x, pos.y);
	nextTile = getNextTileIndex(index.x, index.y);
}

void Pinky::updateChaseTarget() {
	Index index = getTileIndex(pacman->pos.x, pacman->pos.y);

	switch (pacman->direction) {
	case UP:
		pos.y -= 4;
		break;
	case DOWN:
		pos.y += 4;
		break;
	case LEFT:
		pos.x -= 4;
		break;
	case RIGHT:
		pos.x += 4;
		break;
	}

	if (index.x < 0) { index.x = 0; }
	else if (index.x > map->width) { index.x = 0; }
	else if (index.y < 0) { index.y = ofGetHeight(); }
	else if (index.y > map->height) { index.y = map->height; }
	target = index;
}
