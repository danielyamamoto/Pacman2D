#include "Ghost.h"
#include "ofGraphics.h"

void Ghost::updateTarget() {
	switch (currentState) {
	case SCATTER:
		target = scatterTarget;
		break;
	case CHASE:
		updateChaseTarget();
		break;
	case FRIGHTENED:
		updateFrightenedTarget(0, 0);
		break;
	}
	rect.setPosition(pos.x - rect.width / 2, pos.y - rect.height / 2);
}

void Ghost::updateFrightenedTarget(float x, float y) {
	scatterTarget.x = x;
	scatterTarget.y = y;
}

void Ghost::updatePosition() {
	switch (direction) {
	case UP:
		pos.y -= speed;
		break;
	case DOWN:
		pos.y += speed;
		break;
	case LEFT:
		pos.x -= speed;
		break;
	case RIGHT:
		pos.x += speed;
		break;
	}
}

void Ghost::update() {
	updatePosition();
	ofVec2f tPos = getTilePosition(nextTile.x, nextTile.y);

	if (tPos == pos) {
		direction = nextDirection;
		prevTile = nextTile;
		nextTile = getNextTileIndex(nextTile.x, nextTile.y);
		vector<Index> passableTiles = getPassableTiles(nextTile.x, nextTile.y);
		updateTarget();
		Index closest = getClosestTileToTarget(passableTiles);
		nextDirection = getDirection(nextTile, closest);
	}
}

void Ghost::changeState(State s) {
	state = s;
}

void Ghost::setScatterTarget(float x, float y) {
	//scatterTarget.set(x, y);
	scatterTarget.x = x;
	scatterTarget.y = y;
}

void Ghost::setMap(TMXMap & map) {
	this->map = &map; // Fija el apuntador del mapa
}

void Ghost::draw() {
	ofSetColor(255);
	if (img.isAllocated()) {
		img.draw(rect.position.x, rect.position.y);
		//ofSetColor(0, 255, 0);
		//ofNoFill();
		//ofDrawCircle(pos.x, pos.y, 4);
		//ofFill();
	}
	else {
		ofDrawRectangle(rect);
	}
}

void Ghost::setPosition(float x, float y) {
	pos.set(x, y);
	rect.setPosition(pos.x - rect.width / 2, pos.y - rect.height / 2);

	state = SCATTER;
	Index index = getTileIndex(pos.x, pos.y);
	updateTarget();
	vector<Index> passableTiles = getPassableTiles(nextTile.x, nextTile.y);
	Index closest = getClosestTileToTarget(passableTiles);
	nextDirection = getDirection(index, closest);
	direction = nextDirection;
	nextTile = getNextTileIndex(index.x, index.y);
	prevTile = index;
}

Index Ghost::getTileIndex(int x, int y) {
	Index index;
	index.x = floor(x / map->getTileWidth()); // FLOOR redondea los valores 
	index.y = floor(y / map->getTileHeight()); // FLOOR redondea los valores
	return index;
}

Index Ghost::getNextTileIndex(int x, int y) {
	Index index;
	switch (direction) {
	case UP:
		index.x = x;
		index.y = y - 1;
		break;
	case DOWN:
		index.x = x;
		index.y = y + 1;
		break;
	case LEFT:
		index.x = x - 1;
		index.y = y;
		break;
	case RIGHT:
		index.x = x + 1;
		index.y = y;
		break;
	}
	rect.setPosition(pos.x - rect.width / 2, pos.y - rect.height / 2);
	return index; // Checar
}

vector<Index> Ghost::getPassableTiles(int x, int y) {
	vector <Index> indexes;
	TMXLayer *layer = map->getLayer("maze");
	TMXCell *up = layer->getCell(x, y - 1);
	TMXCell *down = layer->getCell(x, y + 1);
	TMXCell *left = layer->getCell(x - 1, y);
	TMXCell *right = layer->getCell(x + 1, y);

	if (up->getGid() == 0) {
		Index index;
		index.x = x;
		index.y = y - 1;
		if (index != prevTile) {
			indexes.push_back(index);
		}
	}
	if (down->getGid() == 0) {
		Index index;
		index.x = x;
		index.y = y + 1;
		if (index != prevTile) {
			indexes.push_back(index);
		}
	}
	if (left->getGid() == 0) {
		Index index;
		index.x = x - 1;
		index.y = y;
		if (index != prevTile) {
			indexes.push_back(index);
		}
	}
	if (right->getGid() == 0) {
		Index index;
		index.x = x + 1;
		index.y = y;
		if (index != prevTile) {
			indexes.push_back(index);
		}
	}
	return indexes;
}

Index Ghost::getClosestTileToTarget(vector<Index>& tiles) {
	float closet = 0;
	Index index;
	index.x = 0;
	index.y = 0;

	for (int i = 0; i < tiles.size(); i++) {
		if (i == 0) {
			closet = ofDist(tiles[i].x, tiles[i].y, target.x, target.y);
			index = tiles[i];
		}
		float dist = ofDist(tiles[i].x, tiles[i].y, target.x, target.y);
		if (dist < closet) {
			index = tiles[i];
		}
	}
	return index;
}

ofVec2f Ghost::getTilePosition(int x, int y) {
	int tileWidth = map->getTileWidth();
	int tileHeight = map->getTileHeight();
	ofVec2f pos(tileWidth*x + tileWidth / 2, tileHeight*y + tileHeight / 2);
	return pos;
}

Direction Ghost::getDirection(Index a, Index b) { // Da la dirección a la que nos vamos a mover
	if (a.x - b.x < 0) { // Derecha
		return RIGHT;
	}
	else if (a.x - b.x > 0) { // Izquierda
		return LEFT;
	}
	else if (a.y - b.y < 0) { // Abajo
		return DOWN;
	}
	else if (a.y - b.y > 0) { // Arriba
		return UP;
	}
	return direction;
}