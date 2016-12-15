#include "TMXMapRenderer.h"

void TMXMapRenderer::loadMap(string fileName) {
	loader.load(fileName); // Carga el mapa
}

TMXMap * TMXMapRenderer::getMap() {
	return &loader.map;
}

void TMXMapRenderer::draw() {
	TMXMap *map = &loader.map;
	int columns = map->getWidth();
	int rows = map->getHeight();
	int tileWidth = map->getTileWidth();
	int tileHeight = map->getTileHeight();
	int layersCount = map->layers.size();

	for (int k = 0; k < map->layers.size(); k++) {
		TMXLayer * layer = &map->layers[k];
		if (layer->visible) {
			int cellNum = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int x = tileWidth*j;
					int y = tileHeight*i;
					TMXCell *cell = &layer->cells[cellNum];
					if (cell->active) {
						int gid = cell->getGid();
						TMXTileSet * tileset = &map->tilesets[0];
						TMXTile *tile = tileset->getTile(gid);
						if (tile != NULL) {
							tile->img.draw(x, y);
						}
					}
					cellNum++;
				}
			}
		}
	}
}