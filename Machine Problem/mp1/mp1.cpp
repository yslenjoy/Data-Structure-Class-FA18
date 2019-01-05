#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>
#include <cmath>



void rotate(std::string inputFile, std::string outputFile) {
  // Read input file
  PNG* original;
  original = new PNG();

  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();

  // Create out.png
  PNG* output;
  output = new PNG(width, height);

  // Rotate the image 180 degrees
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel & pixel = original->getPixel(width - x - 1, height - y - 1);

      HSLAPixel & currOutPixel = (*output).getPixel(x, y);
      currOutPixel = HSLAPixel (pixel.h, pixel.s, pixel.l);
    }
  }


  output->writeToFile(outputFile);
  delete output;
  delete original;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  HSLAPixel *sea, *sun, *sky;
  // TODO: Part 3

  // The sea
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 2 * height / 3; y < height; y++) {
    	HSLAPixel & seaPixel = png.getPixel(x, y);
      sea = new HSLAPixel (210, 0.5, 0.3);
   		seaPixel = *sea;
   	}
  }

  // The sun and the sky
  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y <= 2 * height / 3; y++) {
    	// casting to make the sun can be drawn
    	double yCenter = (double)2 * height/3; // yCenter: assigned to avoid the round from int heigth / 3
    	double yTmp = (double)y;
    	double xTmp = (double)x;

    	double circleSqure = (double)(xTmp - width/2) * (xTmp - width/2) + (yTmp - yCenter) * (yTmp - yCenter);
    	double rSqure = (double)std::pow(width, 2) / 100;
    	// std::cout << circle << "," << yTmp << "," << yCenter << "," << (yTmp - 2 * height/3) <<std::endl;
    	if (circleSqure <= rSqure) { // the sun
    		HSLAPixel & sunPixel = png.getPixel(x, y);
    		sun = new HSLAPixel (20, 1, 0.5);
   			sunPixel = *sun;
    	} else { // the sky
    		HSLAPixel & skyPixel = png.getPixel(x, y);
    		double l = 1 - 3 * (double) y / (5 * height);
    		sky = new HSLAPixel (30, 1, l);
   			skyPixel = *sky;
    	}
    }
  }

  delete sky;
  // delete sun;
  delete sea;

  return png;
}
