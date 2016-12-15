#pragma once
#include "Ghost.h"

class Clyde : public Ghost { // Fantasma Naranja
public:
	void init(int x, int y, int w, int h, TMXMap & map);
	void updateChaseTarget();
};