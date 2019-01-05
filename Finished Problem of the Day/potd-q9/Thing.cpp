// Your code here!
#include <string>

#include "Thing.h"
using namespace std;
using namespace potd;

Thing::Thing(int size) {
	props_max_ = size;
	properties_ = new string[props_max_];
	values_ = new string[props_max_];
	props_ct_ = 0;
}
Thing::Thing(const Thing & other) {
	_copy(other);
}
Thing& Thing::operator=(const Thing & other) {
	_destroy();
	_copy(other);
	return *this;
}
Thing::~Thing() {
	_destroy();
}
int Thing::set_property(string name, string value) {
	for (int i = 0; i < this->props_ct_; i++) {
		if (properties_[i] == name) {
			if (values_[i] != value) {
				values_[i] = value;
			}
			return i;
		} 
	}			
	if (props_ct_ == props_max_) { // cannot be put at the first of the function
		// as long as max = count, the function ends
		return -1;
	}
	props_ct_++;
	int index = props_ct_ - 1;
	properties_[index] = name;
	values_[index] = value; 
	return index;
}
string Thing::get_property(string name) {
	for (int i = 0; i < this->props_ct_; i++) {
		if (this->properties_[i] == name) {
			return this->values_[i];
		} 
	}
	return "";
}
void Thing::_copy(const Thing & other) {
	// delete[] values_; 
	// delete[] properties_;
	// delete is not needed, since this is the copy constructor, no object exixts yet (differentiate this situatin with the operator overloading: the object already constructed)
	this->props_max_ = other.props_max_;
	this->properties_ = new string[props_max_];
	this->values_ = new string[props_max_];
	for (int i = 0; i < this->props_max_; i++) {
		this->properties_[i] = other.properties_[i];
		this->values_[i] = other.values_[i];
		this->props_ct_ = other.props_ct_;
	}
}
void Thing::_destroy() {
	delete[] values_;
	delete[] properties_;
	values_ = NULL;
	properties_ = NULL;

}

// 1. delete is not needed in (copy) constructor
// 2. line 34 - 35
// string *properties_: can be string or string arryas
// constructor: deals with the private or public variables in header file: at least need to initilize them
// 4: return statement location in a function or in a for loop