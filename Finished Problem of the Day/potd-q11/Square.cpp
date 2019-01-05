#include <iostream>
#include <string>
using namespace std;

#include "Square.h"

Square::Square() {
    name = "mysquare";
    lengthptr = new double;
    *lengthptr = 2.0;
}

void Square::setName(string newName) {
  name = newName;
}

void Square::setLength(double newVal) {
  *lengthptr = newVal;
}

string Square::getName() const {
  return name;
}


double Square::getLength() const {
  return *lengthptr;
}

Square::Square(const Square & other) {
    name = other.getName();
    lengthptr = new double;
    *lengthptr = other.getLength();
}

Square::~Square() {
    delete lengthptr;
}
Square & Square::operator=(const Square & other){
  this->name = other.getName();
  this->lengthptr = new double;
  *lengthptr = other.getLength();
  // delete other.lengthptr;
  return *this;
}
Square Square::operator+(const Square & other) {
  // some error in the operator: should keep Square a remain the same?
  // cout << "here +" << endl;
  double newLength = this->getLength() + other.getLength();
  string newName = this->getName() + other.getName();
  // delete lengthptr;
  Square d = Square();
  d.setName(newName);
  d.setLength(newLength);
  return d;
}

