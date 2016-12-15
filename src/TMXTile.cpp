#include "TMXTile.h"

TMXTile::TMXTile() {
	gid = 0;
}

TMXTile::TMXTile(int gid) : gid(gid) {

}

int TMXTile::getGid() {
	return gid;
}

void TMXTile::setGid(int gid) {
	gid = gid;
}

void TMXTile::setImage(ofImage img) {
	this->img = img;
}

void TMXTile::setProperty(string key, string value) { // Sirve como diccionario, a cada llave le toca una propiedad
	properties.insert(std::make_pair(key, value)); // Agregamos todas las propiedades
}

string TMXTile::getProperty(string key) {
	string prop = "none";
	if (properties.count(key)) { // Valida que exista las propiedades del diccionario
		prop = properties.at(key); // Regresa un valor del diccionario
	}
	return prop;
	//return properties[key];
}