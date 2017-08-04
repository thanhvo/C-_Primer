#include <iostream>
#include <sstream>
#include <fstream>
#include "TextQuery.h"

using namespace std;

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream &is): file (new vector<string>) {
    string text;
    while (getline(is, text)) { // for each line in the file
        file->push_back(text); // remember this line of text
        int n = file->size() - 1;
        istringstream line(text); // the current line 
        string word;
        while (line >> word) { // separate the line into words
            // for each word in that line, if word isn't already in wm, subscripting adds a new entry 
            auto &lines = wm[word]; // lines is a shared_ptr
            if (!lines) // that pointer is null the first time we see word
                lines.reset(new set<line_no>); // allocate a new set
            lines->insert(n); // insert this line number            
        }
    }
}

QueryResult TextQuery::query(const string &sought) const {
    // We'll return a pointer to this set if we don't find sought
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end()) {
        return QueryResult(sought, nodata, file); // not found
    } else {
        return QueryResult(sought, loc->second, file);
    }
}

