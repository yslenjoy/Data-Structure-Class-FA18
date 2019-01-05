#include <iostream>
#include "Image.h"

int main() {
  cs225::Image alma;

  // std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  // alma.readFromFile("alma.png");
  // alma.lighten(0.2);
  // alma.writeToFile("lighten.png");

  // std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  // alma.readFromFile("alma.png");
  // alma.saturate(0.2);
  // alma.writeToFile("saturate.png");

  // std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  // alma.readFromFile("alma.png");
  // alma.scale(2);
  // alma.writeToFile("scale2x.png");

  // std::cout << "Using Image::illinify to create `illinified.png`..." << std::endl;
  // alma.readFromFile("alma.png");
  // alma.illinify();
  // alma.writeToFile("illinified.png");

  std::cout << "Using Image::scale to create 'scaleXY.png'..." << std::endl;
  alma.readFromFile("alma.png");
  // std::cout << alma.width() << "," << alma.height() <<  alma.width() / alma.height() << std::endl;
  // original size: 900 * 600
  alma.scale(600, 300);
  alma.writeToFile("scaleXY.png");

  return 0;
}
