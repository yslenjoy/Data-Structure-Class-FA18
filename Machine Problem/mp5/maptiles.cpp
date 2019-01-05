/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     if (theTiles.empty()) return NULL;

     int row = theSource.getRows();
     int column = theSource.getColumns();
     MosaicCanvas* out = new MosaicCanvas(row, column);
     // TileImage should be stored as memory address in the map,
     // since if call out->setTile(i,j, &found), after the function ends,
     // the memory for that function on the heap will be freed
     // SHOULD use the reference of theTiles, since the address of this variable
     // is out side of the function, after function call, it's still there.
     map<Point<3>, TileImage*> point_tile; // points and corresponding tiles
     std::vector<Point<3>> points; // vector of points (tiles) used to build the KD tree

     // build point_tile map and the points vector vector
     for (size_t i = 0; i < theTiles.size(); i++) {
       LUVAPixel ave_pixel = theTiles[i].getAverageColor();
       Point<3> pt = convertToXYZ(ave_pixel);
       point_tile[pt] = &theTiles[i];
       points.push_back(pt);
     }
     // build the KDTree
     KDTree<3>* tile_tree = new KDTree<3>(points);

     // fill in tiles to mosaic canvas using findNearestNeighbor
     for (int i = 0; i < row; i++) {
       for (int j = 0; j < column; j++) {
         LUVAPixel source_pixel = theSource.getRegionColor(i, j);
         Point<3> source_points = convertToXYZ(source_pixel);
         Point<3> nearest = tile_tree->findNearestNeighbor(source_points); // fnn based on soure
         TileImage *found = point_tile[nearest];
         out->setTile(i, j, found);
       }
     }
     return out;
}
