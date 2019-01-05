// Animal.h
#pragma once

#include <string>

using namespace std;


class Animal {
public:
	Animal();
	Animal(string name, string type);
	string food_;
	string getType();
	void setType(string type);
	string getFood();
	void setFood(string food);
	virtual string print();
private:
	string type_;
};