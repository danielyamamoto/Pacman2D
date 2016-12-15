#pragma once
#include "TMXCell.h"
#include<vector>

using namespace std; // Standar Library

class TMXLayer {
public: 
	vector<TMXCell> cells;
	string name;
	int width, height;
	bool visible;

	TMXLayer();
	TMXLayer(string name, int width, int height);
	void addCell(TMXCell cell);
	TMXCell *getCell(int x, int y); // NO son coordenadas, son índices
};