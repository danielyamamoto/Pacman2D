#include "TMXLayer.h"

TMXLayer::TMXLayer() {
	name = "empty";
	visible = true;
}

TMXLayer::TMXLayer(string name, int width, int height)
	: name(name), width(width), height(height) {
}

TMXCell* TMXLayer::getCell(int x, int y) { // Esta función nos ayuda a obtener los índices de los tiles
	if (x < width && y < height) {
		int index = y * width + x; // Convierte el valor de bidimensional a unidimensional
		if (index >= 0 && index < cells.size()) {
			return &cells[index];
		}
	}
	return NULL;
}

void TMXLayer::addCell(TMXCell cell) {
	cells.push_back(cell);
}
