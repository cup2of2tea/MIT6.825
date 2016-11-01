#include <iostream>
#include "Algorithms.hpp"
#include "Parser.hpp"

using namespace std;

int main() {
    Instance i = parseFile("test.in");

    i.display();

    map<Variable,bool> m = bruteForce(i);

    for(map<Variable,bool>::iterator it = m.begin(); it != m.end(); it++) {
        cout<<(it->first.name)<<" "<<(it->second?"True":"False")<<endl;
    }
}
