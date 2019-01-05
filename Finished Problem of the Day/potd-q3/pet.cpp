#include <string>
#include "pet.h"

using namespace std;

// Put your constructor code here!
Pet::Pet() {
	name = "Rover";
	birth_year = 2018;
	type = "dog";
	owner_name = "Wade";
}

Pet::Pet(string newName, int newBY, string newType, string newNameO) {
	setName(newName);
	setBY(newBY);
	setType(newType);
	setOwnerName(newNameO);
}


void Pet::setName(string newName) {
  name = newName;
}

void Pet::setBY(int newBY) {
  birth_year = newBY;
}

void Pet::setType(string newType) {
  type = newType;
}

void Pet::setOwnerName(string newNameO) {
  owner_name = newNameO;
}

string Pet::getName() {
  return name;
}

int Pet::getBY() {
  return birth_year;
}

string Pet::getType() {
  return type;
}

string Pet::getOwnerName() {
  return owner_name;
}
