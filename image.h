#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <SOIL.h>

class Image
{
private:
	unsigned char* image;
	int mwidth; 
	int mheight; 
	float *mHeightMap;
	void load(std::string filename); 
public:

	Image(std::string filename);
	int width();
	int height();
	unsigned char* data();
	void makeHeightMap();
	float getColorAt(int x, int y);
	~Image(void);
};


#endif