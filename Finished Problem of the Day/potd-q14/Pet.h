// Pet.h
#pragma once

#include <string>
#include "Animal.h"
using namespace std;

class Pet : public Animal {
private:
	string name_;
	string owner_name_;
public:
	Pet();
	Pet(string type, string food, string name, string owner_name);
	void setFood(string nu_food);
	string getFood();
	void setName(string nu_name);
	string getName();
	void setOwnerName(string nu_owner_name_);
	string getOwnerName();
	string print();
};