#include <iostream>
#include "Quote.h"

using namespace std;

// If the specified number of items are purchased, use discounted price
double Bulk_quote::net_price(size_t cnt) const {
    if (cnt >= quantity) {
        return cnt * (1 - discount) * price;
    } else {
        return cnt * price;
    }
    
}

// Calculate and print the price for the given number of copies, apply any discounts
double print_total(ostream &os, const Quote &item, size_t n) {
    // Depend on the type of object bound to the item parameter, 
    // calls either Quote::net_price or Bulk_quote::net_price
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() // calls Quote::isbn
       << " # sold: " << n << " total due: " << ret << endl;
    return ret;
}

double Basket::total_receipt(ostream &os) const{
    double sum = 0.0; // holds the running total
    
    // iter refers to the first element in a batch of elements with the same ISBN
    // upper_bound returns an iterator to the element just past the end of that batch
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        // we know there's at least one element with this key in the Basket
        // print the line item for this book
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total sale: " << sum << endl; // print the final overall total
    return sum;
}

