#pragma once
#include "ofMain.h"
#include "TMXMapRenderer.h"
#include "TMXTileSet.h"
#include "TMXLoader.h"
#include "PacMan.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

class ofApp : public ofBaseApp{

	public:
		TMXMapRenderer render;
		TMXTileSet tileset;
		TMXMap *map;
		PacMan puck;
		ofSoundPlayer eatSnd;
		string type;
		ofVec2f prevPos;
		vector <Ghost*> ghosts;

		bool keyIsDown[255];
		bool pause;
		int tileGid;
		int lives, scores;
		//int indexX, indexY;

		void resetActorsPosition();
		void resetGame();
		void initGhosts();
		void checkGhostCollision();
		void checkMazeCollision();
		void checkPalletCollision();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
