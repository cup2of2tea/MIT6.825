#ifndef PARSER_H
#define PARSER_H

#include "Instance.hpp"
#include <fstream>

string trim(string s, string remove) {
    while(s.size() && remove.find(s[0]) != string::npos) s = s.substr(1);
    while(s.size() && remove.find(s[s.size()-1]) != string::npos) s = s.substr(0,s.size()-1);
    return s;
}

vector<string> split(string s, string sep) {
    string act = "";
    vector<string> res;
    for(int c=0;c<s.size();c++) {
        if(sep.find(s[c]) != string::npos) {
            if(act.size()) {
                res.push_back(act);
            }
            act = "";
        } else {
            act += s[c];
        }
    }
    if(act.size()) {
        res.push_back(act);
    }
    return res;
}

Litteral parseLiteral(string s) {
    s = trim(s,"() v^");
    bool neg = (s[0]=='~');
    s = trim(s,"~");
    Variable v(s);
    return Litteral(v,neg);
}

Clause parseClause(string s) {
    Clause res;
    s = trim(s,"^ ()");
    vector<string> literals = split(s,"v");
    for(int c=0;c<literals.size();c++) {
        Litteral l = parseLiteral(literals[c]);
        res.litterals.push_back(l);
    }
    return res;
}

Instance parseInstance(string s) {
    Instance res;
    s = trim(s," ");
    vector<string> clauses = split(s,"^");
    for(int c=0;c<clauses.size();c++) {
        Clause cl = parseClause(clauses[c]);
        res.clauses.push_back(cl);
    }
    return res;
}

Instance parseFile(string filepath) {
    ifstream in(filepath.c_str());
    string all = "";
    while(!in.eof()) {
        string line;
        getline(in,line);
        all += line;
    }
    return parseInstance(all);
}


#endif
