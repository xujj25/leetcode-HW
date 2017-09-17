#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
	static bool strlencompare(string a, string b) {
		return a.length() > b.length();
	}

	static bool strcompare(string a, string b) {
		return a < b;
	}

    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(), d.end(), strlencompare);
        string tempstr;
        int i, j, pos;
        bool isfinish;
        vector<string> resultVector;

        int slen = s.length();

        for (i = 0; i < d.size(); i++) {
        	cout << "\n\nin string[" << i << "] dealing" << endl;
        	if (d[i].length() > s.length())
        		continue;
        	tempstr = s;
        	isfinish = true;

        	for (j = 0; j < d[i].length(); j++) {
        		if ((pos = tempstr.find(d[i][j])) < tempstr.length()) {
        			tempstr = tempstr.substr(pos);

        			cout << "j = " << j << ", postion = " << slen - tempstr.length() << endl;
        			// cout << "string s: " << s[slen - tempstr.length()] << endl;
        			// cout << "string tempstr: " << tempstr[0] << endl;
        			cout << "tempstr = " << tempstr << endl;

        		} else {
        			isfinish = false;
        			break;
        		}
        	}
        	
        	if (isfinish) {
        		if (resultVector.empty()) {
        			resultVector.push_back(d[i]);
        		} else {
        			if (resultVector.back().length() > d[i].length())
        				break;
        			else
        				resultVector.push_back(d[i]);
        		}
        	}
        }
        
        if (resultVector.empty()) {
        	return "";
        } else {
        	sort(resultVector.begin(), resultVector.end(), strcompare);
        	return resultVector[0];
        }
    }
};

int main() {

	string str, tempstr;
	int dictLen;
	vector<string> dict;

	cout << "Please input a string: ";
	cin >> str;
	cout << "Please input the length of string dict: ";
	cin >> dictLen;
	cout << "Please input " << dictLen << "string(s): " << endl;
	for (int i = 0; i < dictLen; i++) {
		cin >> tempstr;
		dict.push_back(tempstr);
	}
	Solution solu;
	cout << "Output: " << solu.findLongestWord(str, dict) << endl;
	return 0;
}