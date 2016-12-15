#pragma once
#include "TMXLayer.h"
#include "TMXTileSet.h"
#include <vector>

class TMXMap {
public:
	int width, height; // N�mero de ancho y alto del map
	int tileWidth, tileHeight; // Ancho y Alto en pixeles de cada tile
	vector<TMXLayer>layers; // Capas del map
	vector <TMXTileSet> tilesets; // Im�genes que representar�n a los tiles

	TMXMap();
	TMXLayer* getLayer(string name);
	// Setters
	void setWidth(int w);
	void setHeight(int h);
	void setTileWidth(int tw);
	void setTileHeight(int th);
	// Getters
	int getWidth();
	int getHeight();
	int getTileWidth();
	int getTileHeight();
};