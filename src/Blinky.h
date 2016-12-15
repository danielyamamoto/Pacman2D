#pragma once
#include "Ghost.h"

class Blinky : public Ghost { // Fantasma Rojo
public:
	void init (int x, int y, int w, int h, TMXMap & map);
	void updateChaseTarget();
};