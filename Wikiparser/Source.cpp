
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>//I found this in appendix H
#include <vector>

using namespace std;

class Search {
    string word;

    int i = 0;
public:
    string searchword;
    
};
class prompt :public Search {
public:
        string commitsearch() {
        cout << "Search up something on wikipedia and get the basic information of you search." << endl;
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
        cout << searchword << endl;

        return searchword;
    }
};
string parse() {
    // Open the web page
    Search s;
    string address = "https://en.wikipedia.org/wiki/" + s.searchword;
    ifstream page(address);

    // Parse the infobox
    string line;
    bool start = false;
    bool end = false;
    while (getline(page, line)) {
        // Check if the infobox has started
        if (line.find("<table class=\"infobox") != string::npos) {
            start = true;
        }
        else {
            throw "Could not find infobox, Did you type in the right thing?";
            prompt p;
            p.commitsearch();
        }
        // Check if the infobox has ended
        if (start && line.find("</table>") != string::npos) {
            end = true;
        }

        // Extract the infobox content
        if (start && !end) {
            // Check if the line contains a field and a value
            size_t fieldpos = line.find("<th");
            size_t valuepos = line.find("<td");
            if (fieldpos != string::npos && valuepos != string::npos) {
                // Extract the field and the value
                string field = line.substr(fieldpos, line.find("</th>") - fieldpos + 5); // I found the find function in Appednix H
                string value = line.substr(valuepos, line.find("</td>") - valuepos + 5);
                // In HTML there are tags that the content of the info box are with in the tags

                // Remove any HTML tags from the field and the value
                field.erase(remove_if(field.begin(), field.end(), [](char c) { return c == '<' || c == '>'; }), field.end());
                value.erase(remove_if(value.begin(), value.end(), [](char c) { return c == '<' || c == '>'; }), value.end());

                // Print the field and the value
                cout << field << ": " << value << endl;

                const int length = line.length();

                // declaring character array (+1 for null terminator)
                char* char_array = new char[length + 1];

                // copying the contents of the
                // string to char array
                strcpy(char_array, line.c_str()); 

                for (int i = 0; i < length; i++)
                {
                    std::cout << char_array[i];
                }
                vector<string> words; //I wanted to see what happens if it output each elemt to console
                words.push_back(line);
                words.push_back(char_array);
                cout << "The names in the vector are:" << endl;
                for (int i = 0; i < words.size(); i++) {
                    cout << words[i] << endl;
                    delete[] char_array;
                }

                return field, value, line;
            }

        }

        return line;
    }
};
template<typename T>
    class MyString {
    /* This class will take searchword put it in a character array store the string and length of the string 
    in user defined template class fashion*/
private:
    Search s;
    T* str;
    int len;
public:
    MyString(const T* s) {
        len = std::strlen(s);
        str = new T[len + 1];
        std::strcpy(str, s);

    }
    ~MyString() {
        delete[] str;
    }
    void print() {
        std::cout << str << std::endl;
    }
    
};
/* Myclass and Myclass2 are very similiar one is for string and the other is for length of the address operator+ function is defined as a member function inside both classes*/
class MyClass {
    string str;

public:
    MyClass(string s) : str(s) {}

    MyClass operator+(MyClass& other) {
        return MyClass(str + other.str);
    }

    void print() {
        cout << str << endl;
    }
};
class MyClass2 {
    int x;
public:
    MyClass2(int a) : x(a) {}
    MyClass2 operator+(const MyClass2& rhs) const {
        return MyClass2(x + rhs.x);
    }
};
int main() {
    Search s;
    prompt p;
    p.commitsearch();
    MyString<char> str1(s.searchword.c_str());
    string address = "https://en.wikipedia.org/wiki/" + s.searchword;
    MyClass str3(address);
    MyClass2 a(address.length());
    parse();



    return 0;
}
