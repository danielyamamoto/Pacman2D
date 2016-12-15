#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(false);
	render.loadMap("puckman.tmx");
	ofSetBackgroundColor(0);
	map = render.getMap();
	puck = PacMan(13 * map->getTileWidth() + map->getTileWidth() / 2, 17 * map->getTileHeight() + map->getTileHeight() / 2, 5);
	puck.loadImage();
	tileGid = 0;
	lives = 3;
	scores = 0;
	type = "Hoa";
	pause = true;
	prevPos = puck.pos;
	initGhosts();

	if (eatSnd.loadSound("pacman_chomp.wav")) {
		cout << "Se cargó audio" << endl;
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!pause) {
		for (Ghost *g : ghosts) { // Arreglo de vectores de fantasmas
			g->update();
		}
		puck.update(ofGetLastFrameTime());
		checkGhostCollision();
		checkMazeCollision();
		checkPalletCollision();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 255, 255);
	render.draw();
	float fps = ofGetFrameRate();
	ofDrawBitmapString(ofToString(fps), 20, 20); // Muestra los fps en la pantalla
	puck.draw();
	for (Ghost *g : ghosts) {
		g->draw();
	}
	//ofDrawBitmapString(ofToString(indexX) + "," + ofToString(indexY), mouseX, mouseY); // Muestra los índices de cada tile
	ofDrawBitmapString("Vidas: " + ofToString(lives), 20, 350);
	ofDrawBitmapString("Puntos: " + ofToString(scores), 20, 400);
}

void ofApp::resetActorsPosition() {
	puck.setPosition(13 * map->getTileWidth() + map->getTileWidth() / 2, 17 * map->getTileHeight() + map->getTileHeight() / 2);
	ghosts[0]->setPosition(12 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2);
	ghosts[1]->setPosition(13 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2);
	ghosts[2]->setPosition(14 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2);
	ghosts[3]->setPosition(15 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2);
}

void ofApp::resetGame() {
	if (lives = 0) {
		setup();
	}
}

void ofApp::initGhosts() {
	TMXMap *map = render.getMap();
	ghosts.push_back(new Blinky());
	ghosts.back()->init(12 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2, 24, 24, *map);
	ghosts.back()->pacman = &puck; // Obtiene el ùltimo elemento del arreglo de vectores
	ghosts.push_back(new Pinky());
	ghosts.back()->init(13 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2, 24, 24, *map);
	ghosts.back()->pacman = &puck; // Obtiene el ùltimo elemento del arreglo de vectores
	ghosts.push_back(new Inky());
	ghosts.back()->init(14 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2, 24, 24, *map);
	ghosts.back()->pacman = &puck; // Obtiene el ùltimo elemento del arreglo de vectores
	ghosts.back()->ghost = ghosts.at(0);
	ghosts.push_back(new Clyde());
	ghosts.back()->init(15 * map->getTileWidth() + map->getTileWidth() / 2, 11 * map->getTileHeight() + map->getTileHeight() / 2, 24, 24, *map);
	ghosts.back()->pacman = &puck; // Obtiene el ùltimo elemento del arreglo de vectores
}

void ofApp::checkGhostCollision() {
	for (Ghost *g : ghosts) {
		if (g->rect.intersects(puck.rect)) {
			if (g->currentState == Ghost::FRIGHTENED) {

			}
			else {
				lives--;
				resetActorsPosition();
			}
		}
	}
}

void ofApp::checkMazeCollision() {
	TMXMap *map = render.getMap();
	TMXLayer *layer = render.getMap()->getLayer("maze");
	int tileWidth = map->getTileWidth();
	int tileHeight = map->getTileHeight();
	int	mapWidth = map->getWidth()*map->getTileWidth();
	int mapHeight = map->getHeight()*map->getTileHeight();

	ofRectangle *rect = &puck.rect;
	int left = rect->getLeft() / tileWidth;
	int right = rect->getRight() / tileWidth;
	int top = rect->getTop() / tileHeight;
	int bottom = rect->getBottom() / tileHeight;

	if (left < 0) {	left = 0; }
	if (top < 0 ) { top = 0; }
	if (right > mapWidth) { right = mapWidth; }
	if (bottom > mapHeight) { bottom = mapHeight; }

	for (int i = left; i <= right; i++) {
		for (int j = top; j <= bottom; j++) {
			TMXCell *cell = layer->getCell(i, j);
			if (cell != NULL) {
				tileGid = cell->getGid();
				TMXTileSet *tileset = &map->tilesets[0];
				TMXTile *tile = tileset->getTile(tileGid);
				if (tile != NULL) {
					string tileProp = tile->getProperty("type");
					if (tileProp == "wall") {
						puck.stop();
						puck.setPosition(prevPos);
					}
				}
			}
		}
	}
	prevPos = puck.pos;
}

void ofApp::checkPalletCollision() {
	TMXLayer *layer = render.getMap()->getLayer("pils");
	int tileWidth = map->getTileWidth();
	int tileHeight = map->getTileHeight();
	int	mapWidth = map->getWidth()*map->getTileWidth();
	int mapHeight = map->getHeight()*map->getTileHeight();

	ofRectangle *rect = &puck.rect;
	int left = rect->getLeft() / tileWidth;
	int right = rect->getRight() / tileWidth;
	int top = rect->getTop() / tileHeight;
	int bottom = rect->getBottom() / tileHeight;
	
	if (left < 0) { left = 0; }
	if (top < 0) { top = 0; }
	if (right > mapWidth) { right = mapWidth; }
	if (bottom > mapHeight) { bottom = mapHeight; }

	for (int i = left; i <= right; i++) {
		for (int j = top; j <= bottom; j++) {
			TMXCell *cell = layer->getCell(i, j);
			if (cell != NULL) {
				if (cell->active) {
					tileGid = cell->getGid();
					TMXTileSet *tileset = &map->tilesets[0];
					TMXTile *tile = tileset->getTile(tileGid);
					if (tile != NULL) {
						float x = i*tileWidth + tileWidth / 2;
						float y = j*tileHeight + tileHeight / 2;
						float dist = ofDist(puck.pos.x, puck.pos.y, x, y);
						if (dist < puck.radius + tileWidth / 4) {
							string tileProp = tile->getProperty("type");
							if (tileProp == "pellet") {
								if (!eatSnd.isPlaying()) {
									eatSnd.play();
									scores++;
								}
								cell->active = false;
								// Score++;
							}
							else if (tileProp == "powerUp") {
								if (!eatSnd.isPlaying()) {
									eatSnd.play();
								}
								cell->active = false;
							}
						}
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key < 255) {
		if (key == 'w') { puck.moveUp(); }
		if (key == 's') { puck.moveDown(); }
		if (key == 'a') { puck.moveLeft(); }
		if (key == 'd') { puck.moveRight(); }
		pause = false;
		//keyIsDown[key] = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//if (key < 255) {
	//	if (key == 'w') { puck.moveUp(); }
	//	else if (key == 's') { puck.moveDown(); }
	//	else if (key == 'd') { puck.moveRight(); }
	//	else if (key == 'a') { puck.moveLeft(); }
	//	keyIsDown[key] = false;
	//}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
	TMXLayer *layer = map->getLayer("maze");
	int mapWidth = map->getHeight()*map->getTileWidth();
	int mapHeight = map->getWidth()*map->getTileHeight();

	int indexX = floor(x / map->getTileWidth()); // FLOOR redondea los valores 
	int indexY = floor(y / map->getTileHeight()); // FLOOR redondea los valores

	TMXCell *cell = layer->getCell(indexX, indexY); // Guarda los índices temporalmente 

	if (cell != NULL) { // Función preventiva
		tileGid = cell->getGid();
		TMXTile *tile = map->tilesets[0].getTile(tileGid);
		if (tile != NULL) {
			type = tile->getProperty("type");
		}
		else {
			type = "none";
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
