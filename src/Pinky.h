#pragma once
#include "Ghost.h"

class Pinky : public Ghost { // Fantasma Rosa
public:
	void init(int x, int y, int w, int h, TMXMap & map);
	void updateChaseTarget();
};