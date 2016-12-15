#include "TMXLoader.h"
#include "TMXTileSet.h"
#include "TMXLayer.h"
#include "TMXCell.h"
#include "ofImage.h"

TMXLoader::TMXLoader() {

}

bool TMXLoader::load(string fileName) {
	if (xmlMap.load(fileName)) {
		cout << "se cargó: " << fileName << endl;
		parseMapAttributes();
		parseTileSets();
		parseLayers();
	}
	else { 
		cout << "no se carga: " << fileName << endl; 
	}
	return true;
}

void TMXLoader::parseMapAttributes() {
	int width = xmlMap.getAttribute("map", "width", 0);
	int height = xmlMap.getAttribute("map", "height", 0);
	int tileWidth = xmlMap.getAttribute("map", "tilewidth", 0);
	int tileHeight = xmlMap.getAttribute("map", "tileheight", 0);
	map.setWidth(width);
	map.setHeight(height);
	map.setTileWidth(tileWidth);
	map.setTileHeight(tileHeight);

	/*cout << "parseMapAttributes: " << "width: " << map.getTileWidth() << "heigth: " << map.getHeight() <<
		"tileWidth: " << map.getTileHeight() << "tileHeight: " << map.getTileWidth() << endl;*/
}
void TMXLoader::parseTileSets() {
	xmlMap.pushTag("map"); // Nos mete en la siguiente jerarquía
	int tilesetCount = xmlMap.getNumTags("tileset");

	for (int i = 0; i < tilesetCount; i++) {
		string tilesetName = xmlMap.getAttribute("tileset","name","no_name",i);
		int firstGid = xmlMap.getAttribute("tileset","firstGid",0,i);
		int tileWidth = xmlMap.getAttribute("tileset","tilewidth",0, i);
		int tileHeight = xmlMap.getAttribute("tileset", "tileheight", 0, i);
		int spacing = xmlMap.getAttribute("tileset", "spacing", 0, i);
		int tileCount = xmlMap.getAttribute("tileset", "tilecount", 0, i);
		int columns = xmlMap.getAttribute("tileset", "columns", 0, i);
		
		xmlMap.pushTag("tileset", i); // Accedimos a un nuevo tag
		string imgName = xmlMap.getAttribute("image", "source", "none", 0);
		int width = xmlMap.getAttribute("image", "width", 0, 0);
		int height = xmlMap.getAttribute("image", "height", 0, 0);
		
		ofImage img;
		img.load(imgName);
		img.resize(width, height);
		
		TMXTileSet tileset = TMXTileSet(tilesetName,img, tileWidth, tileHeight, tileCount, columns); // Objeto destruible cuando termina el ciclo
		tileset.firstGid = firstGid;
		tileset.spacing=spacing;
		tileset.cutTiles();
		map.tilesets.push_back(tileset); // Crea una copia permante de "tileset" || Esto evita que el objeto sea destruido cuando termine el ciclo
		xmlMap.popTag(); // Nos regresa a la jerarquía anterior

		/*cout << "parseTilesets:c" << "TilesetName: " << tilesetName <<
			"tileWidth: " << tileWidth << "tileHeight: " << tileHeight <<
			"tileCount: " << tileCount << "columns: " << columns << endl;
		cout << "imageName: " << imgName << "width: " << width << "height: " << height << endl;*/
	}
}

void TMXLoader::parseLayers() {
	int layerCount = xmlMap.getNumTags("layer");
	for (int i = 0; i < layerCount; i++) {
		string name = xmlMap.getAttribute("layer","name","none",i);
		int width = xmlMap.getAttribute("layer", "width", 0, i);
		int height = xmlMap.getAttribute("layer", "height", 0, i);
		int visible = xmlMap.getAttribute("layer", "visible", 1, i);
		TMXLayer layer(name, width, height); // Variable temporal
		layer.visible = (bool)visible;

		cout << "parseLayers: " << "name: " << name << "width: " << width << "height: " << height << endl;

		xmlMap.pushTag("layer", i); // Accedemos a un nuevo tag
		xmlMap.pushTag("data", 0); // Accedemos a un nuevo tag
		int tileCount = xmlMap.getNumTags("tile");
		for (int j = 0; j < tileCount; j++) {
			int gid = xmlMap.getAttribute("tile","gid",0,j);
			TMXCell cell(gid);
			layer.addCell(cell);

			//cout << "Tile: index:" << j << "gid: " << cell.getGid() << endl;
		}
		map.layers.push_back(layer); // Creamos una copia permanente de "layer" 
		xmlMap.popTag(); // Regresamos a la jerarquía anterior "data"
		xmlMap.popTag(); // Regresamos a la jerarquía anterior "layers"
	}
}

void TMXLoader::parseTileSetProperties() {
	TMXTileSet *tileSet = &map.tilesets.back();
	int tilesProperties = xmlMap.getNumTags("tile");
	for (int i = 0; i < tilesProperties; i++) {
		int gid = xmlMap.getAttribute("title", "id", 0, i) + 1;
		xmlMap.pushTag("tile"); // Accedemos a un nuevo tag
		xmlMap.pushTag("properties"); // Accedemos a un nuevo tag
		int propCount = xmlMap.getNumTags("property");
		for (int j = 0; j < propCount; j++) {
			string propName = xmlMap.getAttribute("property", "name", "null", j);
			string propVal = xmlMap.getAttribute("property", "value", "null", j);

			TMXTile *tile = tileSet->getTile(gid);
			tile->setProperty(propName, propVal);
			cout << propName << "," << propVal << endl;
		}
		xmlMap.popTag(); // Regresamos a la jerarquía anterior "properties"
		xmlMap.popTag(); // Regresamos a la jerarquía anterior "tile"
	}
}