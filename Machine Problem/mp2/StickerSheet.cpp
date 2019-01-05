#include "StickerSheet.h"
#include <iostream>

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
	givenImage = new Image();
	*givenImage = picture;
	// givenImage->writeToFile("tests/myTest-ctor.png");


	maxImages = max;
	images = new Image*[max]; // make
	layer = new int[max]; // whether this layer has sticker nor not
	for (int i = 0; i < (int)max; i++) {
		images[i] = NULL;
		layer[i] = 0;
	}
	xCoord = new int[max];
	yCoord = new int[max];
}

StickerSheet::~StickerSheet() {
	clear();
}

void StickerSheet::clear() {
	for (int i = 0; i < (int)maxImages; i++) {
		if (images[i] != NULL) {
			delete images[i];
			images[i] = NULL;
		}
	}
	delete[] xCoord;
	delete[] yCoord;
	delete[] layer;
	delete[] images;
	if (givenImage != NULL) {
		delete givenImage;

	}
	xCoord = NULL;
	yCoord = NULL;
	layer = NULL;
	images = NULL;
	givenImage = NULL;
}

void StickerSheet::copy(const StickerSheet & other) {
	// 1. *images[i] = *other.images[i] rather than images[i] = other.images[i], the same as givenImage;
	//    need to copy the content of the pointer by dereference the pointer, rather than change where the pointer points to (images[i] = other.images[i])
	// 2. initialize the images[i] to NULL first, or it cannot copy (if some trash exists)
	// 3. make sure to copy all the private variables in the header file, including the givenImage variable

	// initialize
	maxImages = other.maxImages;
	images = new Image*[maxImages];
	xCoord = new int[maxImages];
	yCoord = new int[maxImages];
	layer = new int[maxImages];
	givenImage = new Image();
	*(givenImage) = *(other.givenImage);
	for (int i = 0; i < maxImages; i++) {
		images[i] = NULL;
		layer[i] = 0;
	}

	// copy
	for (int i = 0; i < (int)maxImages; i++) {
		xCoord[i] = other.xCoord[i];
		yCoord[i] = other.yCoord[i];
		layer[i] = other.layer[i];
		if (other.images[i] != NULL) {
			images[i] = new Image();
			*images[i] = *(other.images[i]);
		} else {
			images[i] = NULL;
		}
	}
}

StickerSheet::StickerSheet(const StickerSheet & other) {
	copy(other);
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other) {
	if (this == &other) {
		return *this;
	}
	clear();
	copy(other);
	return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){
	// intitialize
	int* tmpX = new int[max];
	int* tmpY = new int[max];
	int* tmpLayer = new int[max];
	Image** tmpImage = new Image*[max];
	for (int i = 0; i < (int)max; i++) {
		tmpImage[i] = NULL;
		tmpX[i] = 0;
		tmpY[i] = 0;
		tmpLayer[i] = 0;
	}

	// find the scope for later copy
	int furthest = 0;
	if ((int)max < maxImages) {
		furthest = max;
	} else {
		furthest = maxImages;
	}

	// copy
	for (int i = 0; i < furthest; i++) {
		tmpX[i] = xCoord[i];
		tmpY[i] = yCoord[i];
		tmpLayer[i] = layer[i];
		tmpImage[i] = images[i];
	}

	// clear old
	// clear();
	delete[] xCoord;
	delete[] yCoord;
	delete[] layer;
	for (int i = 0; i < maxImages; i++) {
		// delete images[i];
		if (images[i] != NULL) {
			// delete images[i];
			images[i] = NULL;
		}
	}
	delete images;
	images = NULL;
	xCoord = tmpX;
	yCoord = tmpY;
	layer = tmpLayer;
	images = tmpImage;
	maxImages = (int)max;

}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
	// Image & newSticker = sticker;
	// Image * newSticker = new Image(sticker);
	// newSticker = &sticker;
	// int returnI = maxImages;
	for (int i = 0; i < maxImages; i++) {
		if (layer[i] == 0) {
			if (images[i] != NULL) {
				delete images[i];
			}
			// images[i] = &newSticker;
			images[i] = &sticker;
			// See summary comments
			xCoord[i] = (int)x;
			yCoord[i] = (int)y;
			layer[i] = 1;
			return i;
		}
	}
	// delete newSticker;
	// if (returnI != maxImages) {
	// 	return returnI;
	// } else {
	// 	return -1;
	// }
	return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
	if (((int)index >= maxImages) || images[index] == NULL){
		return false;
	}
	xCoord[index] = (int)x;
	yCoord[index] = (int)y;
	return true;
}

void StickerSheet::removeSticker(unsigned index){
	if ((int)index < maxImages) {
		if (images[index] != NULL) {
			delete images[index];
			images[index] = NULL;
			layer[index] = 0;
		}
	}
}

Image * StickerSheet::getSticker(unsigned index) const{
	if ((int)index >= maxImages) {
		return NULL;
	}
	return images[index];
}

Image StickerSheet::render() const{
	// if (givenImage == NULL) {
	// 	std::cout << "-----" << std::endl;
	// }
	int min_width = (int)givenImage->width();
	int min_height = (int)givenImage->height();
	for (int i = 0; i < (int)maxImages; i++) {
		if (images[i] != NULL) {
			// std::cout << ((int)images[i]->width() + xCoord[i]) << "-------------------------" << std::endl;
			if (min_width < ((int)images[i]->width() + xCoord[i])) {
				min_width = (int)images[i]->width() + xCoord[i];
			}
			if (min_height < ((int)images[i]->height() + yCoord[i])) {
				min_height = (int)images[i]->height() + yCoord[i];
			}
		}
	}

	// create the output image
	givenImage->resize(min_width, min_height);


	// add stickers into different layers
	for (int i = 0; i < (int)maxImages; i++) {
		if (images[i] != NULL) {
			int layerWidth = (int)images[i]->width();
			int layerHeight = (int)images[i]->height();
			for (int x = 0; x < (int)givenImage->width(); x++) {
				for (int y = 0; y < (int)givenImage->height(); y++) {
					if ((x < (xCoord[i] + layerWidth)) && (x >= xCoord[i]) && (y < (yCoord[i] + layerHeight)) && (y >= yCoord[i])) {
							HSLAPixel & layerPixel = images[i]->getPixel(x - xCoord[i], y - yCoord[i]);
							HSLAPixel & basePixel = givenImage->getPixel(x, y);
							if (layerPixel.a != 0) {
								basePixel.h = layerPixel.h;
								basePixel.s = layerPixel.s;
								basePixel.l = layerPixel.l;
								basePixel.a = layerPixel.a;
							}
					}
				}
			}
		}
	}
	return *givenImage;
}

/**
 * General Comments in Debugging Process:
 * 	1. Copy the test case with error into main, make, use valgrind to
 * 	   see where the error goes (rather than "valgrind ./test" directly)
 * 	2. Copy constructor: need to make independent copy: (see detailed comments in copy() function) needs to dereference the ptr;
 * 	3. Comparing to comment 2, changeMaxStickers() function just change
 * 	   the pointer to where the givenone points to (don't need deep copy)
 * 	4. changeMaxStickers(): don't need to call clear()
 * 		 1) don't need to delete the givenImage(the function is not
 * 		 		essentially the same asdestrctor, givenImage cannot be
 * 		 		deleted: the first comment in render() function);
 * 		 2) don't need to "delete image[i]": if images[i] is deleted,
 * 		 		since tmpImage[i] is just the shadow copy of images[i],
 * 		 		tmpImage will also be deleted;
 * 		 3) forget to set maxImage = max at the end of clearing old and
 * 		 		passing tmp to private operation
 * 	5. If all the tests passed with valgrind but has small memory leaks:
 * 		 1) using -leak-check=full to find where the leak is
 * 		 2) the leak in addSticker() hasn't fixed: don't know how
 * 		 		to delete the dynamic ptr: &sticker
 					Don't need to create the newSticker variable, just pass the given sticker's
					memory address: &
 * 	6. Tricky parts for Image** images:
 * 		 1) initilize first: images = new Image*[max];
 * 		 		then set each element to NULL: images[i] = NULL: if != NULL,
 * 		 		may has effects on other functions used later
 * 		 2) when deleting it:
 * 		 		check images[i]!= NULL first, if images[i]==NULL, images[i]
 * 		 		cannot be deleted;
 * 		 		then set images[i]= NULL;
 * 		 		alse remember to delete[] images since it's a (pointer) array
 * 		 		and set it to NULL
 *
 */
