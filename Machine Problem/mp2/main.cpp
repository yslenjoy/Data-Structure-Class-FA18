#include "Image.h"
#include "StickerSheet.h"
#include <iostream>
using namespace std;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
	Image base;
	base.readFromFile("pubg.png");

	Image layer1;
	layer1.readFromFile("8timesScope.png");
	// layer1.scale(0.5);

	Image layer2;
	layer2.readFromFile("AWM.png");

	Image layer3;
	layer3.readFromFile("225.png");
	layer3.scale(0.5);
	
	// Image alma; alma.readFromFile("tests/alma.png");
	// Image i;    i.readFromFile("tests/i.png");

	// StickerSheet sheet(alma, 5);
	// sheet.addSticker(i, 20, 200);
	// sheet.render().writeToFile("tests/myTest-render.png");
	// // std::cout << "LINE :" << __LINE__ << std::endl;
	// Image expected;
	// expected.readFromFile("tests/expected.png");
  return 0;
}
