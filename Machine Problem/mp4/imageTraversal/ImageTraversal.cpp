#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
    tra_ = NULL;
    atEnd = false;
}

ImageTraversal::Iterator::Iterator(PNG & png, Point & start, double tolerance, ImageTraversal* tra) {
    png_ = png;
    start_ = start;
    realStart_ = start_;
    tolerance_ = tolerance;
    tra_ = tra;

    for (unsigned i = 0; i < png_.width() * png_.height(); i++) {
        visited_.push_back(false);
      }
      atEnd = false;
      // visited_[start_.x + start_.y * png_.width()] = true;
      // path_.push_back(start_);

      if (canVisit(start_)) {
        visited_[start_.x + start_.y * png_.width()] = true;
        // shouldn't push start_ to tra_, see comment below
        path_.push_back(start_); 
      } else {
        // since the ctor for BFS and DFS already push start_ as required by test, if start_ can be visited, do nothing; else: remove start_ out
        Point gabage = tra_->pop();
        atEnd = true;
      }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point p1 = Point(start_.x + 1, start_.y);
  Point p2 = Point(start_.x, start_.y + 1);
  Point p3 = Point(start_.x - 1, start_.y);
  Point p4 = Point(start_.x, start_.y - 1);
  // cout << " 73 here" << endl;

  if (canVisit(p1)) tra_->add(p1);
  if (canVisit(p2)) tra_->add(p2);
  if (canVisit(p3)) tra_->add(p3);
  if (canVisit(p4)) tra_->add(p4);

  if (tra_->empty()) {
    setEnd(true);
    return *this;
  }
  Point next = tra_->pop();
  while(visited_[next.x + next.y * png_.width()]) {
    if (tra_->empty()) {
        setEnd(true);
        return *this;
    }
    next = tra_->pop();
  }
  start_ = next;
  visited_[start_.x + start_.y * png_.width()] = true;
  path_.push_back(start_);
  return *this;
}

/**
 * Helper function to check whether a point can be visited or not
 */
bool ImageTraversal::Iterator::canVisit(Point point) {
    if (point.x >= png_.width() || point.y >= png_.height()) {
        return false;
    }
    HSLAPixel& start = png_.getPixel(realStart_.x, realStart_.y);
    HSLAPixel& Point = png_.getPixel(point.x, point.y);
    if (calculateDelta(start, Point) >= tolerance_) {
        return false;
    }
    return true;
}

void ImageTraversal::Iterator::setEnd(bool End) {
    atEnd = End;
}
/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return start_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (atEnd != other.atEnd);
}

