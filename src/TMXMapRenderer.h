#pragma once
#include "TMXLoader.h"
#include "TMXMap.h"
#include "ofGraphics.h"

class TMXMapRenderer {
public:
	TMXLoader loader;

	void loadMap(string filename);
	void draw();
	TMXMap* getMap();
};