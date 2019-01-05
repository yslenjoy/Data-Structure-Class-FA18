// Pet.cpp
#include "Pet.h"


#include <iostream>
#include <string>
using namespace std;

Pet::Pet() {
	this->setType("cat");
	this->food_ = "fish";
	name_ = "Fluffy";
	owner_name_ = "Cinda";
}
Pet::Pet(string type, string food, string name, string owner_name) {
	this->setType(type);
	this->food_ = food;
	name_ = name;
	owner_name_ = owner_name;
}
void Pet::setFood(string nu_food) {
	this->food_ = nu_food;
}
string Pet::getFood() {
	return this->food_;
}
void Pet::setName(string nu_name) {
	name_ = nu_name;
}
string Pet::getName() {
	return name_;
}
void Pet::setOwnerName(string nu_owner_name_) {
	owner_name_ = nu_owner_name_;
}
string Pet::getOwnerName() {
	return owner_name_;
}
string Pet::print() {
	return "My name is " + name_;
}