#include "TMXMap.h"

TMXMap::TMXMap():width(0), height(0), tileWidth(0),tileHeight(0) {

}

TMXLayer *TMXMap::getLayer(string name) { // Esta función sirve para obtener un layer específico y salirse cuando lo obtienes
	TMXLayer *layer = NULL; // Evita obtener un layer inválido
	for (TMXLayer &l : layers) {
		if (l.name == name) {
			layer = &l;
			break; // Se sale del for
		}
	}
	return layer;
}

void TMXMap::setWidth(int w) {
	width = w;
}

void TMXMap::setHeight(int h) {
	height = h;
}

void TMXMap::setTileWidth(int tw) {
	tileWidth = tw;
}

void TMXMap::setTileHeight(int th) {
	tileHeight = th;
}

int TMXMap::getWidth() {
	return width;
}

int TMXMap::getHeight() {
	return height;
}

int TMXMap::getTileWidth() {
	return tileWidth;
}

int TMXMap::getTileHeight() {
	return tileHeight;
}