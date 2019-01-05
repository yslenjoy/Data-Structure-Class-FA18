#include <string>
#include <vector>
using namespace std;

vector<string> NoProblem(int start, vector<int> created, vector<int> needed) {

    // your code here
	vector<string> result;
	string good = "No problem! :D";
	string bad = "No problem. :(";

	int stock = start;
	for (unsigned i = 0; i < created.size(); i++) {
		if (i == 0) {
			stock -= needed[i];
		} else {
			stock += created[i-1];
			stock -= needed[i];
		}
		if (stock >= 0) {
			result.push_back(good);
		} else {
			stock += needed[i]; // all contests are canceled, problems are saved for next month
			result.push_back(bad);
		}
		// stock = 0;
	}
	return result;
}
