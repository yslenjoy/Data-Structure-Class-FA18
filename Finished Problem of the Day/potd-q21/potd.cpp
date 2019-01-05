#include "potd.h"
#include <iostream>

// Your code here!
double sum(vector<double>::iterator start, vector<double>::iterator end) {
	if (start == end) {
		return 0.0;
	}
	double sumValue = 0.0;
	while (start != end) {
		sumValue += *start;
		start++;
	}
	return sumValue;
}
vector<double>::iterator max_iter(vector<double>::iterator start, vector<double>::iterator end) {
	if (start == end) {
		return start;
	}
	vector<double>::iterator tmp = start;
	while (start != end) {
		start++;
		if (start == end) {
			return tmp;
		}
		else if (*tmp < *start) {
			tmp = start;
		}
	}
	return tmp;

}
void sort_vector(vector<double>::iterator start, vector<double>::iterator end) {
	if (start == end) {
		return;
	}
	vector<double>::iterator tmpMax;
	while (start != end) {
		tmpMax = max_iter(start, end);
		double tmpVaule = *tmpMax;
		*tmpMax = *start; // swithc values
		*start = tmpVaule; // put max value at the head
		start++;
	}
}