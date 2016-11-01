#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Instance.hpp"
#include <set>



bool verifyLiteral(map<Variable, bool> &inter, const Litteral &l) {
    return inter.find(l.variable) != inter.end() && l.neg != inter[l.variable];
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

void complete(map<Variable, bool> &res, const Instance &i) {
    for(int c=0;c<i.clauses.size();c++)
        for(int c2=0;c2<i.clauses[c].litterals.size();c2++)
            res[i.clauses[c].litterals[c2].variable.name] |= false;
}


void applyUnaryPropagation(const Instance &i, map<Variable,bool> &res) {
    for(int c=0;c<i.clauses.size();c++) {
        if(verifyClause(res,i.clauses[c])) continue;
        set<pair<Variable,bool> > notAffected;
        for(int c2=0;c2<i.clauses[c].litterals.size();c2++) {
            string name = i.clauses[c].litterals[c2].variable.name;
            if(res.find(name) == res.end()) {
                notAffected.insert(make_pair(name,i.clauses[c].litterals[c2].neg));
            }
        }
        if(notAffected.size() == 1) {
            set<pair<Variable,bool> >::iterator it = notAffected.begin();
            res[it->first] = !it->second;
        }
    }
}

void eliminatePur(const Instance &i, map<Variable, bool> &res) {
    map<Variable, int> vals;
    for(int c=0;c<i.clauses.size();c++) {
        if(verifyClause(res,i.clauses[c])) continue;
        set<pair<Variable,bool> > notAffected;
        for(int c2=0;c2<i.clauses[c].litterals.size();c2++) {
            string name = i.clauses[c].litterals[c2].variable.name;
            if(res.find(name) == res.end()) {
                vals[name]|=(1<<i.clauses[c].litterals[c2].neg);
            }
        }
    }
    for(map<Variable, int>::iterator it = vals.begin(); it!= vals.end(); it++) {
        if(it->second == 1) {
            res[it->first] = true;
        } else if(it -> second == 2) {
            res[it->first] = false;
        }
    }
}


map<Variable,bool> DPLLRecu(const Instance &i, map<Variable,bool> &res) {

    map<Variable,bool> copie(res);

    applyUnaryPropagation(i,res);
    eliminatePur(i,res);
    if(verifyInstance(res,i))
         return res;

    for(int c=0;c<i.clauses.size();c++) {
        for(int c2=0;c2<i.clauses[c].litterals.size();c2++) {
            Variable v = i.clauses[c].litterals[c2].variable.name;
            if(res.find(v) == res.end()) {
                res[v] = true;
                res = DPLLRecu(i,res);
                if(verifyInstance(res,i)) return res;
                res = copie;
                res[v] = false;
                res = DPLLRecu(i,res);
                if(verifyInstance(res,i)) return res;
                res = copie;
                return res;
            }
        }
    }
    res = copie;
    return res;
}



map<Variable,bool> DPLL(const Instance &i) {
    map<Variable, bool> res;
    return DPLLRecu(i,res);
}


#endif
