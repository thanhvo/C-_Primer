#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <memory>
#include <string>

using namespace std;

class StrBlobPtr;
class StrBlob {
    friend class StrBlobPtr;
    public:
        typedef vector<string>::size_type size_type;
        StrBlob(): data(make_shared<vector<string>>()) {}
        StrBlob(initializer_list<string> il): data(make_shared<vector<string>>(il)) {} 
        size_type size() const {
            return data->size();
        }
        bool empty() const {
            return data->empty();            
        }
        
        // add and remove elements
        void push_back(const string &t) {
            data->push_back(t);
        }
        void pop_back();
        // element access
        string &front();
        string &back();
        
        // return StrBlobPtr to the first and one past the last elements
        shared_ptr<StrBlobPtr> begin() {
            return make_shared<StrBlobPtr>(make_shared<StrBlob>(*this));
        }
        
        shared_ptr<StrBlobPtr> end() {
            return make_shared<StrBlobPtr>(make_shared<StrBlob>(*this), data->size());            
        }
        
    private:
        shared_ptr<vector<string>> data;
        // throws msg if data[i] isn't valid
        void check(size_type i, const string &msg) const;
};

#endif