#include <deque>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

class Machine
{
    public:
        Machine() {};
        void setup(char* filename);
        void process();
        void print();
    private:
        string _state;
        string _accept;
        deque<char> _tape;
        map<tuple<string,char>, tuple<string,char,char>> _rules;
        void make_tape(string tape_string);
        void make_rules(vector<string> rule_list);
        int _start_pos = 0; //For printing '|'
        int _head_pos = 0; //For printing '^'

};

void Machine::setup(char* filename)
{
    ifstream file(filename);
    if (!file) {
        runtime_error("Couldn't open file");
    }

    string state, accept;
    file >> state >> accept;
    _state = state;
    _accept = accept;
    
    string tape_string;
    file >> tape_string;
    make_tape(tape_string);
    
    vector<string> rule_list;
    string rule;
    while (getline(file, rule, '\n')) {
        rule_list.push_back(rule);
    }
    make_rules(rule_list);
    
    file.close();
}

void Machine::make_tape(string tape_string)
{
    for (char c : tape_string) {
        _tape.push_back(c);
    }
}

void Machine::make_rules(vector<string> rule_list)
{
    for (string rule : rule_list) {
        string before_state;
        char before_sym;
        string equals;
        string after_state;
        char after_sym;
        char dir;
        
        istringstream iss(rule);
        iss >> before_state >> before_sym >> equals
            >> after_state >> after_sym >> dir;

        tuple<string,char> before = make_tuple(before_state, before_sym);
        tuple<string,char,char> after = make_tuple(after_state, after_sym, dir);

        _rules.emplace(before, after);
    }
}

void Machine::process()
{
    int pos = 0;
    while(_state != _accept) {
        if (pos < 0) {
            _tape.push_front('_');
            pos = 0;
            _start_pos += 1; //Update for printing '|'
        } else if (pos == _tape.size()) {
            _tape.push_back('_');
        }
        char symbol = _tape[pos];
        tuple<string, char> before = make_tuple(_state, symbol);
        tuple<string, char, char> after = _rules[before];
        _state = get<0>(after);
        _tape[pos] = get<1>(after);
        pos += (get<2>(after) == '>') ? 1 : -1;
        _head_pos = max(pos,0); //Update for printing '^'
    }
}

void Machine::print()
{
    for (char c : _tape) {
        cout << c;
    }
    cout << endl;

    for (int i = 0; i < _tape.size(); i++) {
        if (i == _start_pos) {
            cout << '|';
        } else if (i == _head_pos) {
            cout << '^';
        } else {
            cout << ' ';
        }
    }
    cout << endl;
}
int main(int argc, char** argv)
{
    Machine m;
    char* file = argv[1];
    m.setup(file);
    m.process();
    m.print();

    return 0;
}
