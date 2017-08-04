#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <iostream>
#include <vector>
#include <memory>
#include <set>

using namespace std;

class QueryResult {
    friend ostream& print(ostream &, const QueryResult &);
    public:
        using line_no = vector<string>::size_type;
        QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f): 
            sought(s), lines(p), file(f) {}
    private:
        string sought; // word this query represents
        shared_ptr<set<line_no>> lines; // lines isn't on
        shared_ptr<vector<string>> file; // input file
};

ostream &print(ostream &os, const QueryResult &qr);

#endif