#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <vector>
#include <memory>
#include <set>

using namespace std;

class Quote {
    public:
            // virtual function to return a dynamically allocated copy of itself
            // these numbers use reference qualifiers
            virtual Quote* clone() const & { return new Quote(*this); }
            virtual Quote* clone() && {
                return new Quote(move(*this));
            }
            Quote() = default;
            Quote(const string &book, double sales_price): bookNo(book), price(sales_price) {}
            string isbn() const { return bookNo;}
            // Returns the total sales price for the specified number of items derived classes will
            // override and apply different discount algorithms
            virtual double net_price(size_t n) const {
                return n*price;
            }
            virtual ~Quote() = default; // dynamic binding for the destructor
    private:
            string bookNo; // ISBN number
    protected:
            double price = 0.0; // normal, undiscounted price
};



class Disc_quote : public Quote {
    public:        
        Disc_quote() = default;
        Disc_quote (const string& book, double price, size_t qty, double disc):
            Quote(book, price), quantity(qty), discount(disc) {}
        double net_price(size_t) const = 0;
    protected:
        size_t quantity = 0; // purchase size for the discount to apply
        double discount = 0.0; // fractional discount to apply
};

class Bulk_quote: public Disc_quote {
    public:
        Bulk_quote* clone() const & {
            return new Bulk_quote(*this);
        }
        Bulk_quote* clone() const && { 
            return new Bulk_quote(move(*this));
        }
        // Bulk_quote inherits from Quote
        Bulk_quote() = default;
        Bulk_quote(const string &book, double __price, size_t __min_qty, double __discount): 
            Disc_quote(book, __price, __min_qty, __discount) {}
        
        // Overrides the base version in order to implement the bulk purchase discount policy
        double net_price(size_t) const override;    
};

class Basket {
    public:
        // copy the given object
        void add_items(const Quote& sale) {
            items.insert(shared_ptr<Quote>(sale.clone()));
        }
        // move the given object
        void add_items(Quote&& sale) {
            items.insert(shared_ptr<Quote>(move(sale).clone()));
        }
        // Basket uses synthesized default constructor and copy-control members
        void add_item(const shared_ptr<Quote> &sale) {
            items.insert(sale);
        }
        // prints the total price for each book and the overall total for all items in the basket
        double total_receipt(ostream&) const;
    private:
        // function to compare shared_ptrs needed by the multiset member
        static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs) {
            return lhs->isbn() < rhs->isbn(); 
        }
        // multiset to hold multiple quotes, ordered by the compare member
        multiset<shared_ptr<Quote>, decltype(compare)*> items{compare};        
};

double print_total(ostream &os, const Quote &item, size_t n);

#endif  