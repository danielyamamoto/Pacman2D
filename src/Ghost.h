#pragma once
#include "ofVec2f.h"
#include "ofRectangle.h"
#include "ofImage.h"
#include "ofGraphics.h"
#include "TMXMap.h"
#include "TMXCell.h"
#include "PacMan.h"


struct Index {
	int x, y;

	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}

	bool operator==(const Index &a) const {
		return (x == a.x && y == a.y);
	}
	bool operator !=(const Index &a) const {
		return (x != a.x || y != a.y);
	}
};

class Ghost {
public:
	enum State { SCATTER, CHASE, FRIGHTENED}; // Máquina de Estados
	float speed;
	ofVec2f pos;
	Index scatterTarget, target; // Posición fija para el estado 
	Index prevTile, nextTile;
	State currentState, state;
	ofRectangle rect;
	ofImage img;
	PacMan *pacman;
	Ghost *ghost;
	TMXMap *map;
	Direction direction, nextDirection;

	virtual void init(int x, int y, int w, int h, TMXMap &map) = 0; // Esta función obliga a todas las herencias a utilizar pero de forma independiente
	virtual void updateChaseTarget() = 0; // Esta función obliga a todas las herencias a utilizar pero de forma independiente

	void updateTarget();
	void updateFrightenedTarget(float x, float y);
	void updatePosition();
	void update();
	void changeState(State s);
	void setScatterTarget(float x, float y);
	void setMap(TMXMap &map);
	void draw();
	void setPosition(float x, float y);
	
	Index getTileIndex(int x, int y); // Nos regresa el índice del Tile actual
	Index getNextTileIndex(int x, int y); // Sobre la posición actual, me da el siguiente Tile
	vector<Index> getPassableTiles(int x, int y); // Nos da los Tiles alrededor del fantasma, si hay paredes alrededor 
	Index getClosestTileToTarget(vector<Index> &tiles);
	ofVec2f getTilePosition(int x, int y);
	Direction getDirection(Index a, Index b);
};