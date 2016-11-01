#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <vector>
#include <map>


using namespace std;


class Variable {
    public:

        string name;

        Variable(){}
        Variable(string _name):name(_name){}
};

bool operator<(const Variable &v1, const Variable &v2) {
    return v1.name < v2.name;
};

class Litteral {
    public:

        Variable variable;
        bool neg;

        Litteral(){}
        Litteral(Variable _variable, bool _neg):variable(_variable),neg(_neg){}

        void display() {
            cout<<(neg?"~":"")<<variable.name;
        }

};


class Clause {
    public:

        vector<Litteral> litterals;

        Clause(){}
        Clause(vector<Litteral> _litterals):litterals(_litterals){}

        void display() {
            for(int c=0;c<litterals.size();c++) {
                litterals[c].display();
                if(c + 1 < litterals.size()) {
                    cout<<" v ";
                }
            }
        }
};

class Instance {

    public:

        vector<Clause> clauses;

        Instance(){}
        Instance(vector<Clause> _clauses):clauses(_clauses){}

        void display(){
            cout<<"Instance : "<<endl;
            for(int c=0;c<clauses.size();c++) {
                cout<<"( ";
                clauses[c].display();
                cout<<") ^\n";
            }
        }
};



#endif
