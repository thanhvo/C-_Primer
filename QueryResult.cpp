#include "QueryResult.h"

using namespace std;

// return the plural version of word if ctr is greater than 1
string make_plural(size_t ctr, const string &word, const string &ending) {
    return (ctr > 1) ? word + ending : word;
}

ostream &print(ostream &os, const QueryResult &qr) {
    // if the word was found, print the count and all occurrences
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << endl;
    // print each line in which the word appeared
    for (auto num: *qr.lines) { // for every elment in the set, don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;        
    }
    return os;
}