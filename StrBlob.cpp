#include <stdexcept>
#include "StrBlob.h"
#include "StrBlobPtr.h"

void StrBlob::check(size_type i, const string &msg) const {
    if ( i >= data->size())
        throw out_of_range(msg);
}

string& StrBlob::front() {
    // If the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();    
}

void StrBlob::pop_back() {
    check(0, "pop back on empty StrBlob");
    data->pop_back();
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
    auto ret = wptr.lock(); // is the vector still around? 
    if (!ret) 
        throw runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector    
}

string& StrBlobPtr::deref() const {
    auto p = check(curr, "deference past end");
    return (*p)[curr]; // (*p) is the vector to which this object points
}

// prefix: return a reference to the incremented object 
StrBlobPtr& StrBlobPtr::incr() {
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr; // advance the current state
    return *this;
}
 