#include "TMXCell.h"

TMXCell::TMXCell() {
	gid = 0;
	active = true;
}

TMXCell::TMXCell(int gid) : gid(gid) {
	active = true;
}

int TMXCell::getGid() {
	return gid;
}

void TMXCell::setGid(int gid) {
	gid = gid;
}