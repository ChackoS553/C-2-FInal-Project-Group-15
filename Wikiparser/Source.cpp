//Wikiparser
#include <iostream>
using namespace std;
#include <string>

class Search {
	string word;
		string searchword;
		int i=0;
public:
	string commitsearch() {
		
		getline(cin, searchword);
		cout << searchword << endl;
		space2underscore(searchword);
		return searchword;
	}
	string space2underscore(string searchword)
	{
		for (int i = 0; i < searchword.length(); i++)
		{
			if (searchword[i] == ' ')
				searchword[i] = '_';
		}
		cout << searchword;
		return searchword;
	}


		
	
};
	
int main() {
	Search s;
	s.commitsearch();
}