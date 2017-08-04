#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "QueryResult.h"

using namespace std;

class QueryResult; // declaration needed for return type in the query function
class TextQuery {
    public:
        using line_no = vector<string>::size_type;
        TextQuery(ifstream &);
        QueryResult query(const string &) const;
    private:
        shared_ptr<vector<string>> file; // input file
        // map of each word to the set of lines in which that word appears
        map<string, shared_ptr<set<line_no>>> wm;
};

#endif