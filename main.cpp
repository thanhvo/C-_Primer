#include <iostream>
#include <vector>
#include <memory>
#include "Quote.h"

using namespace std;

// Use a basket of quotes
void make_a_basket_of_quotes() {
    vector<Quote> basket;
    basket.push_back(Quote("0-201-82470-1", 50));
    // ok, but copies only the Quote part of the object into basket
    basket.push_back(Bulk_quote("0-201-54848-8", 50, 10, .25));
    // calls version defined by Quote, prints 750, i.e., 15 * $50
    //cout << basket.back().net_price(15) << endl;
    for (Quote q: basket) {
        cout << q.net_price(15) << endl;
    }
    
    vector<shared_ptr<Quote>> basket2;
    basket2.push_back(make_shared<Quote>("0-201-82470-1", 50));
    basket2.push_back(make_shared<Bulk_quote>("0-201-54848-8", 50, 10, .25));
    // calls the version defined by Quote; prints 562.5, i.e, 15*$50 less the discount
    // cout << basket2.back()->net_price(15) << endl;
    for (shared_ptr<Quote> quote_ptr: basket2) {
        cout << quote_ptr->net_price(15) << endl;
    }
}

void test_basket() {
    Basket bsk;
    bsk.add_item(make_shared<Quote>("123", 45));
    bsk.add_item(make_shared<Bulk_quote>("345", 45, 3, .15)); 
    bsk.total_receipt(cout);
}

int main(int argc, char **argv)
{
    Quote basic("Hamlet", 10.0);
    Bulk_quote bulk("Hamlet", 10.0, 5, 0.2);
    print_total(cout, basic, 20);
    print_total(cout, bulk, 20);
    print_total(cout, static_cast<Quote>(bulk), 20);
    
    // Make a basket of quotes
    make_a_basket_of_quotes();
    test_basket();
	return 0;
}
