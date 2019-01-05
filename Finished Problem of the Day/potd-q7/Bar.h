// your code here
#pragma once

#include "Foo.h"

#include <string>

using namespace std;
using namespace potd;

namespace potd{
	class Bar {
		public:
			Bar(string);
			Bar(const Bar &);
			~Bar();
			Bar & operator=(const Bar &);
			string get_name() const;
		private:
			potd::Foo * f_; // f_ is needed to using the destructor of Foo
			//string name_; // since name is not needed here: store the name by creating a new foo

	};
}