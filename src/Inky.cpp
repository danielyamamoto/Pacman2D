#include "Inky.h"

void Inky::init(int x, int y, int w, int h, TMXMap & map) {
	this->map = &map;
	pos.set(x, y);
	rect.set(pos.x - w / 2, pos.y - h / 2, w, h);
	img.load("inky.png");
	img.resize(rect.getWidth(), rect.getHeight());
	speed = 1;
	state = SCATTER;
	scatterTarget.set(0, 31);
	target = scatterTarget;
	direction = LEFT;
	nextDirection = LEFT;
	Index index = getTileIndex(pos.x, pos.y);
	nextTile = getNextTileIndex(index.x, index.y);
}

void Inky::updateChaseTarget() {
	Index index = getTileIndex(pacman->pos.x, pacman->pos.y);
	Index indexGhost = getTileIndex(ghost->pos.x, ghost->pos.y);

	switch (direction) {
	case UP:
		index.y -= 2;
		break;
	case DOWN:
		index.y += 2;
		break;
	case LEFT:
		index.x -= 2;
		break;
	case RIGHT:
		index.x += 2;
		break;
	}
	index.x = (index.x - indexGhost.x) * 2;
	index.y = (index.y - indexGhost.y) * 2;
	index.x = (index.x + indexGhost.x);
	index.y = (index.y + indexGhost.y);

	if (index.x < 0) { index.x = 0; }
	else if (index.x > map->getWidth()) { index.x = map->getWidth(); }
	else if (index.y < 0) { index.y = 0; }
	else if (index.y > map->getHeight()) { index.y = map->getHeight(); }
	target = index;
}
