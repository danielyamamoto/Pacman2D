#pragma once
#include "ofImage.h"
#include "TMXTile.h"
#include "ofGraphics.h"
#include <vector>

using namespace std;

class TMXTileSet {
private:
	ofImage img;
	string name;
	vector<TMXTile> tiles;
	int tileWidth, tileHeight; 
	int tileCount, columns;

public:	
	int spacing, firstGid;

	TMXTileSet();
	TMXTileSet(string name, ofImage img, int tileWidth, int tileHeight, int tileCount, int columns);

	TMXTile* getTile(int gid);
	void draw();
	void cutTiles();
	// Getters
	int getTileWidth();
	int getTileHeight();
	int getColumns();
	int getTileCount();
	int getFirstGid();
};