#pragma once
#include "TMXMap.h"
#include "ofxXmlSettings.h"

class TMXLoader {
	public:
		ofxXmlSettings xmlMap;
		TMXMap map;
		string fileName;

		TMXLoader();
		bool load(string fileName);
		void parseMapAttributes();
		void parseTileSets();
		void parseLayers();
		void parseTileSetProperties();

};