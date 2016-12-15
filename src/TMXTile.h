#pragma once
#include "ofImage.h"
#include <map>

using namespace std;

class TMXTile {
public:
	int gid;
	ofImage img;
	map<string, string> properties; // <Llave, Propiedad>

	TMXTile();
	TMXTile(int gid);
	int getGid();
	void setGid(int gid);
	void setImage(ofImage img);
	void setProperty(string key, string value);
	string getProperty(string key);
};