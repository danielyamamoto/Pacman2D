#include "TMXTileSet.h"

TMXTileSet::TMXTileSet() {

}

TMXTileSet::TMXTileSet(string name, ofImage img, int tileWidth, int tileHeight, int tileCount, int columns) // Usar los parámetros directamente hacen que el código se más eficiente
	:name(name), img(img), tileWidth(tileWidth), tileHeight(tileHeight), tileCount(tileCount), columns(columns){ // Usar THIS, hace más lento al código
}

TMXTile* TMXTileSet::getTile(int gid) {
	if (gid > 0 && gid <= tiles.size())
		return &tiles[gid - 1];
	return NULL;
}

void TMXTileSet::draw() {
	TMXTile *tile = getTile(1);

	if (tile != NULL) {
		tile->img.draw(0, 0);
	}
}

void TMXTileSet::cutTiles() {
	int rows = tileCount / columns; // Nos da el número total de tiles

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			ofImage tileImg;
			tileImg.allocate(tileWidth, tileHeight, OF_IMAGE_COLOR); // Reservamos memoria para la primera imagen
			tileImg.cropFrom(img, (tileWidth + spacing)*j, (tileHeight + spacing)*i, tileWidth, tileHeight);
			TMXTile tile;
			tile.setImage(tileImg);
			tiles.push_back(tile);
		}
	}

	for (int i = 0; i < tiles.size(); i++) {
		tiles[i].setGid(i + 1);
	}
}

int TMXTileSet::getTileWidth() {
	return tileWidth;
}

int TMXTileSet::getTileHeight() {
	return tileHeight;
}

int TMXTileSet::getColumns() {
	return columns;
}

int TMXTileSet::getTileCount() {
	return tileCount;
}

int TMXTileSet::getFirstGid() {
	return firstGid;
}