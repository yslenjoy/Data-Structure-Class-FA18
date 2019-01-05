#ifndef _QUEEN_H
#define _QUEEN_H

#include <string>
#include <iostream>

using namespace std;

#include "Piece.h"

class Queen : public Piece {
	public:
		string getType();
};

#endif
