#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Instance.hpp"
#include <set>



bool verifyLiteral(map<Variable, bool> &inter, const Litteral &l) {
    return l.neg != inter[l.variable];
}

bool verifyClause(map<Variable, bool> &inter, const Clause &cl) {
    for(int c=0;c<cl.litterals.size();c++) {
        if(verifyLiteral(inter,cl.litterals[c])) return true;
    }
    return false;
}

bool verifyInstance(map<Variable, bool> &inter,const Instance &i) {
    for(int c=0;c<i.clauses.size();c++) {
        if(!verifyClause(inter,i.clauses[c])) return false;
    }
    return true;
}

void getAllVariables(set<Variable> &allVariables, const Litteral &l) {
    allVariables.insert(l.variable);
}

void getAllVariables(set<Variable> &allVariables, const Clause &cl) {
    for(int c=0;c<cl.litterals.size();c++) {
        getAllVariables(allVariables,cl.litterals[c]);
    }
}

set<Variable> getAllVariables(const Instance &i) {
    set<Variable> res;
    for(int c=0;c<i.clauses.size();c++) {
        getAllVariables(res,i.clauses[c]);
    }
    return res;
}

map<Variable,bool> bruteForce(const Instance &i) {
    map<Variable,bool> m;
    set<Variable> s = getAllVariables(i);
    cout<<s.size()<<endl;
    for(long long mask = 0; mask < (1<<s.size()); mask++) {
        set<Variable>::iterator it = s.begin();
        for(int c=0;c<s.size();c++) {
            if((1<<c) & mask) {
                m[*it] = true;
            } else {
                m[*it] = false;
            }
            it++;
        }
        if(verifyInstance(m,i)) {
            return m;
        }
    }
    return m;
}




#endif
