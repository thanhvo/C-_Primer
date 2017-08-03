#ifndef STRBLOBPTR_H
#define STRBLOBPTR_H

#include "StrBlob.h"

using namespace std;

// StrBlobPtr throws an exception on attemps to access a nonexistent element
class StrBlobPtr {
    public:
        StrBlobPtr(): curr(0) {}
        //StrBlobPtr(StrBlob &a, size_t sz = 0): wptr(a.data), curr(sz) {}
        StrBlobPtr(shared_ptr<StrBlob> a, size_t sz = 0): wptr(a->data), curr(sz) {}
        string &deref() const;
        StrBlobPtr &incr(); // prefix version
        
        bool operator==(StrBlobPtr &RHS) {
            return curr == RHS.curr && wptr.lock() == RHS.wptr.lock();
        }
        
        bool operator!=(StrBlobPtr &RHS) {
            return !(*this == RHS);
        }
    private:
        // Check returns a shared_ptr to the vector if the check succeeds
        shared_ptr<vector<string>> check(size_t, const string &) const;
        // Store a weak_ptr, which means the underlying a vector might be destroyed
        weak_ptr<vector<string>> wptr;
        size_t curr; // Current position within the array        
};

#endif