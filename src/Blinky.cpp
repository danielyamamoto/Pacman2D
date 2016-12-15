#include "Blinky.h"

void Blinky::init(int x, int y, int w, int h, TMXMap & map) {
	this->map = &map;
	pos.set(x, y);
	rect.set(pos.x - w / 2, pos.y - h / 2, w, h);
	img.load("blinky.png");
	img.resize(rect.getWidth(), rect.getHeight());
	speed = 1;
	state = SCATTER;
	scatterTarget.set(28, 0);
	target = scatterTarget;
	direction = RIGHT;
	nextDirection = RIGHT;
	Index index = getTileIndex(pos.x, pos.y);
	nextTile = getNextTileIndex(index.x, index.y);
}

void Blinky::updateChaseTarget() {
	target = getTileIndex(pacman->pos.x, pacman->pos.y);
}