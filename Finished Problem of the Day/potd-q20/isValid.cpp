#include <string>
#include <stack>

using namespace std;

bool isValid(string input) {
    stack<char> st;
    // return true;    // modify this!
    int length = input.length();
    // if (length == 0) {
    // 	return true;
    // }
    for (int i  = 0; i < length; i++) {
    	char c = input[i];
    	if (c == '['||c == '('||c == '{') {
    		st.push(c);
    	} else if (c == ']'||c == ')'||c == '}') {
    		if (st.empty() || !((st.top() == '[' && input[i] == ']') || (st.top() == '(' && input[i] == ')') || (st.top() == '{' && input[i] == '}'))) {
    			return false;
    		} else {
    			st.pop();
    		}
    	}
    }
    if (st.empty()) {
    	return true;
    } else {
    	return false;
    }
    // The implementation without stack has bugs
    // int length = input.length();
    // int leftB1 = 0; //[
    // int rightB1 = 0; 
    // int leftB2 = 0; // (
    // int leftB3 = 0; // {
    // int rightB2 = 0;
    // int rightB3 = 0;
    // if (length == 0) {
    // 	return true;
    // }
    // for (int i  = 0; i < length; i++) {
    // 	char s = input[i];
    // 	if (s == '[') {
    // 		leftB1++;
    // 	}
    // 	if (s == '(') {
    // 		leftB2++;
    // 	}
    // 	if (s == '{') {
    // 		leftB3++;
    // 	}
    // 	if (s == ']') {
    // 		rightB1++;
    // 	}
    // 	if (s == ')') {
    // 		rightB2++;
    // 	}
    // 	if (s == '}') {
    // 		rightB3++;
    // 	}
    // 	if (rightB3 > leftB3 || rightB2 > leftB2 || rightB1 > leftB1) {
    // 		return false;
    // 	}
    // }
    // if (rightB3 == leftB3 && rightB2 == leftB2 && rightB1 == leftB1) {
    // 	return true;
    // } else {
    // 	return false;
    // }


}