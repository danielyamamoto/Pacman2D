#pragma once

class TMXCell {
private:
	int gid;
	
public:
	bool active;

	TMXCell();
	TMXCell(int gid);
	int getGid();
	void setGid(int gid);
};