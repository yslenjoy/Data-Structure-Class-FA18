// your code here
#include "Bar.h"
#include "Foo.h"

#include <string>
#include <iostream>

using namespace std;
using namespace potd;


Bar::Bar(string name) {
	// It should be stored on heap, everything related to pointer
	// should be stored on heap
	Foo * foo1 = new Foo(name);
	this->f_ = foo1;
	// this->name_ = f_->get_name();

	// Using this->name_, but can also using name_ unless 
	// there is other variable called name_ in the class
}
Bar::Bar(const Bar & that) { // should be deep copy
	string nameTmp = that.get_name();
	Foo * foo2 = new Foo(nameTmp);
	this->f_ = foo2;
}
Bar::~Bar() {
	delete f_;
	f_->~Foo();// reduce the count (private variable in Foo)
}
Bar & Bar::operator=(const potd::Bar &that) {
	delete this->f_;
	string nameTmp = that.get_name();
	Foo * foo3 = new Foo(nameTmp);
	this->f_ = foo3;
	return *this;
}
string Bar::get_name() const {
	return f_->get_name();
}

// 1: line 15, stored on the heap;
// 2: no private variable name_ is needed based on the specification >> call f->get_name() to return the name
// 3: (comment from 19 to 20)
// 4: Copy constructor should be deep copy
// 5: destructor: calling Foo's function
// 7: using Foo in Bar class: include both namespece potd and Foo.h file
// 8: delete v.s destrutor: delete key word invokes the destrutor
// 9: operator= part: combination of copy constructor (copy the name) and destruotr (decrese the count)
// 10: in operator=, copy constructor and constructor, some line of code are essentially the same, but they're all necessary
// 11: const is needed for get_name function, since some constant object is calling that function

