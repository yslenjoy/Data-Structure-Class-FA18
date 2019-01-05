#include "Image.h"
#include "cs225/PNG.h"
#include <iostream>
#include <cmath>
using cs225::PNG;
using namespace std;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

namespace cs225 {
  void Image::lighten() {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			// std::cout << pixel.l << std::endl;
  			if (pixel.l > 0.9) {
  				pixel.l = 1;
  			} else {
  				pixel.l += 0.1;
  			}
  		}
  	}
  }
  void Image::lighten(double amount) {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (amount > 0) {
	  			if (amount > 1.0) {
	  				pixel.l = 1;
	  			} else if (pixel.l > (1.0 - amount)) {
	  				// std::cout << "here>0.8:" << pixel.l << std::endl;
	  				pixel.l = 1;
	  				// std::cout << pixel.l << std::endl;
	  			} else {
	  				pixel.l += amount;
	  				// std::cout << "here<=0.8" << std::endl;
	  			}
	  		}
	  		if (amount < 0) {
	  			if (abs(amount) > 1.0) {
	  				pixel.l = 1;
	  			} else if (pixel.l > abs(amount)) {
	  				// std::cout << "here>0.8:" << pixel.l << std::endl;
	  				pixel.l += amount ;
	  				// std::cout << pixel.l << std::endl;
	  			} else {
	  				pixel.l = 0;
	  				// std::cout << "here<=0.8" << std::endl;
	  			}
	  		}
  		}
  	}
  }
  void Image::darken() {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (pixel.l < 0.1) {
  				pixel.l = 0;
  			} else {
  				pixel.l -= 0.1;
  			}
  		}
  	}
  }
  void Image::darken(double amount) {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (amount > 0) {
	  			if (pixel.l < amount) {
	  				pixel.l = 0;
	  			} else {
	  				pixel.l -= amount;
	  			}
	  		} else {
	  			if ((pixel.l + amount) < 1) {
	  				pixel.l += amount;
	  			} else {
	  				pixel.l = 1;
	  			}
	  		}
  		}
  	}
  }
  void Image::saturate() {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (pixel.s > 0.9) {
  				pixel.s = 1;
  			} else {
  				pixel.s += 0.1;
  			}
  		}
  	}
  }
  void Image::saturate(double amount) {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (amount > 0) {
	  			if (amount > 1.0) {
	  				pixel.s = 1;
	  			} else if (pixel.s > (1.0 - amount)) {
	  				pixel.s = 1;
	  			} else {
	  				pixel.s += amount;
	  			}
	  		}
	  		if (amount < 0) {
	  			if (abs(amount) > 1.0) {
	  				pixel.s = 1;
	  			} else if (pixel.s > abs(amount)) {
	  				pixel.s += amount ;
	  			} else {
	  				pixel.s = 0;
	  			}
	  		}
  		}
  	}
  }
  void Image::desaturate() {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (pixel.s < 0.1) {
  				pixel.s = 0;
  			} else {
  				pixel.s -= 0.1;
  			}
  		}
  	}
  }
  void Image::desaturate(double amount) {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			if (amount > 0) {
	  			if (pixel.s < amount) {
	  				pixel.s = 0;
	  			} else {
	  				pixel.s -= amount;
	  			}
	  		} else {
	  			if ((pixel.s + amount) < 1) {
	  				pixel.s += amount;
	  			} else {
	  				pixel.s = 1;
	  			}
	  		}
  		}
  	}
  }
  void Image::grayscale() {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			pixel.s = 0;
  		}
  	}
  }
  void Image::rotateColor(double amount) {
  	for (unsigned x = 0; x < this->width(); x++) {
  		for (unsigned y = 0; y < this->height(); y++) {
  			HSLAPixel & pixel = this->getPixel(x, y);
  			double added = pixel.h + amount;
  			while (abs(amount) > 360.0) {
  				amount -= 360;
  			}
  			if (amount > 0) {
  				if (added > 360) {
  					pixel.h = added - 360.0;
  				} else {
  					pixel.h = added;
  				}
  				// std::cout << pixel.h << " > 360 ---------------" << std::endl;
  			} else {
  				if (added > 0) {
  					pixel.h = added;
  				} else {
  					pixel.h = added + 360.0;
  				}
  				// std::cout << pixel.h << " < 360 --------------- amount: " << amount << std::endl;
  			}
  		}
  	}
  }
  void Image::illinify() {
  	for (unsigned x = 0; x < this->width(); x++) {
  	  for (unsigned y = 0; y < this->height(); y++) {
  	    HSLAPixel & pixel = this->getPixel(x, y);
  	    int hueOrange_ = 11;
  	    int hueBlue_  = 216;
  	    int hueP_ =  pixel.h;

  	    int hueDistanceO_ = std::min(abs(hueP_ - hueOrange_), 360 - abs(hueP_ - hueOrange_));
  	    int hueDistanceB_ = std::min(abs(hueP_ - hueBlue_), 360 - abs(hueP_ - hueBlue_));

  	    if (hueDistanceO_ < hueDistanceB_) {
  	      pixel.h = (double) hueOrange_;
  	    } else {
  	      pixel.h = (double) hueBlue_;
  	    }
  	  }
  	}
  }
  void Image::scale(double factor) {
  	PNG copied = PNG(*this); // same as: PNG copied (*this)
  	int newWidth = (int)(this->width() * factor);
  	int newHeight = (int)this->height() * factor;
		this->resize(newWidth, newHeight);
		// int actualFactor = newWidth / copied.width();
		for (unsigned x = 0; x < this->width(); x++) {
  	  for (unsigned y = 0; y < this->height(); y++) {
  	  	HSLAPixel & pixel = this->getPixel(x, y);
  	  	int x0;
  	  	int y0;
  	  	x0 = x / factor - 1;
  	  	y0 = y / factor - 1;
  	  	if (x0 < 0) {
  	  		x0 = 0;
  	  	}
  	  	if (y0 < 0) {
  	  		y0 = 0;
  	  	}
  	  	pixel.l = copied.getPixel(x0, y0).l;
  	  	pixel.h = copied.getPixel(x0, y0).h;
  	  	pixel.s = copied.getPixel(x0, y0).s;
  	  }
  	}
  	// std::cout << "here" << std::endl;
  }
  void Image::scale(unsigned w, unsigned h) { //should keep the same ratio
  	PNG copied = PNG(*this);
  	int x0 = copied.width();
  	int y0 = copied.height();
  	double ratio = (double)x0 / (double) y0; // need to over-casting both side of the operator
  	// std::cout << ratio << "," << x0 << "," << y0 << endl;
  	if (w > h) {
  		if (h * ratio < w) {
  			w = h * ratio;
  			// cout<< "here, w: " << w << endl;
  		} else {
  			h = w / ratio;
  			// cout<< "here2, h: " << h << endl;
  		}
  	} else {
  		if (w * ratio < h) {
  			h = w * ratio;
  		} else {
  			w = h / ratio;
  		}
  	}
  	double factor = (double)w / (double) x0; 
  	//cout<< "here3, factor: " << factor << endl;
		this->scale(factor);
  }
}
