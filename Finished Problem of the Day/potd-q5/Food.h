// Your code here
#pragma once
#include <string>

using namespace std;

class Food {
	
	public:
		Food();
		string get_name();
		int get_quantity();
		void set_name(string newName);
		void set_quantity(int newQuantity);

	private:
		string name_;
		int quantity_;
};