#pragma once
#include "Ghost.h"

class Inky : public Ghost { //Fantasma Azul
public:
	void init(int x, int y, int w, int h, TMXMap & map);
	void updateChaseTarget();
};