#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char SYMBOL1 = 'a';
const char SYMBOL2 = 'b';

int find_largest_discrep(const string& s)
{
	int max_discrep = 0;
    int curr_discrep = 0;

    for (int step = 1; s.size() / step > max_discrep; ++step) {
        for (int start = 0; start < s.size(); ++start) {
            curr_discrep = 0;
            for (int i = start; i < s.size(); i+=step) {
                curr_discrep += (s[i] == SYMBOL1 ? 1 : -1);
                if (abs(curr_discrep) > max_discrep) {
                    max_discrep = abs(curr_discrep);
                }
            }// char loop
        }// start loop 
    }// step loop
     
	return max_discrep;
}

int main()
{
    ifstream f;
    f.open("stepstring_input.txt");
    string input;
    int count = 1;
    while (getline(f, input)) {
        int largest = find_largest_discrep(input);
        cout << "Challenge " << count << ": " << largest << endl;
        count += 1;
    }
    f.close()
    return 0;
}
