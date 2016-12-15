#include "Clyde.h"

void Clyde::init(int x, int y, int w, int h, TMXMap & map) {
	this->map = &map;
	pos.set(x, y);
	rect.set(pos.x - w / 2, pos.y - h / 2, w, h);
	img.load("clyde.png");
	img.resize(rect.getWidth(), rect.getHeight());
	speed = 1;
	state = SCATTER;
	scatterTarget.set(28, 31);
	target = scatterTarget;
	direction = RIGHT;
	nextDirection = RIGHT;
	Index index = getTileIndex(pos.x, pos.y);
	nextTile = getNextTileIndex(index.x, index.y);
}

void Clyde::updateChaseTarget() {
	float dist = ofDist(pacman->pos.x, pacman->pos.y, pos.x, pos.y);
	dist = dist / map->getTileWidth();
	if (dist > 8) {
		target = getTileIndex(pacman->pos.x, pacman->pos.y);
	}
	else {
		target = scatterTarget;
	}
}
