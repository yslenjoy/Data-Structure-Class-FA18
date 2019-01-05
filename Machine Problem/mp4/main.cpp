
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;
using namespace std;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  PNG png;
  png.readFromFile("myPNG.png");
  FloodFilledImage image(png);

  DFS dfs(png, Point(50, 50), 0.05);
  BFS bfs(png, Point(50, 50), 0.05);

  RainbowColorPicker ggg(0.05);
  image.addFloodFill(dfs, ggg);
  image.addFloodFill(bfs, ggg);

  Animation animation = image.animate(5000);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  

  // PNG png(40, 40);
  // Point startPoint(20, 20);
  // BFS bfs(png, startPoint, 0.2);

  // bfs.add( Point(2, 2) );
  // bfs.add( Point(2, 3) );
  // bfs.add( Point(2, 4) );

  // Point a = bfs.pop();
  // Point b = bfs.pop();
  // Point c = bfs.pop();
  // Point d = bfs.pop();

  // Point a = bfs.pop();
  // Point b = bfs.pop();
  // Point c = bfs.pop();
  // Point d = bfs.pop();

  // cout << a.x << ", " << a.y << endl;
  // cout << b.x << ", " << b.y << endl;
  // cout << c.x << ", " << c.y << endl;
  // cout << d.x << ", " << d.y << endl;

  
  //   PNG png(4, 4);
  //   HSLAPixel blackPixel(180, 1, 0);
    
  //   for (unsigned i = 0; i < 4; i++) {
  //     png.getPixel(i, 0) = blackPixel;
  //     png.getPixel(0, i) = blackPixel;
  //     png.getPixel(i, 3) = blackPixel;
  //     png.getPixel(3, i) = blackPixel;
  //   }

  // Point startPoint(1, 1);
  // DFS dfs(png, startPoint, 0.2);
  // ImageTraversal::Iterator it = dfs.begin();
  // cout << (*it).x << ", " << (*it).y << endl;
  // ++it;

  // cout << (*it).x << ", " << (*it).y << endl;

  return 0;
}
