#include "fibo.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

int main() {

    Fibo a("1001");
    Fibo b = a << 6;

    //odpalaj asercje pojedynczo


    // to nie działa
    //assert((a << 6) == (a <<= 6));

    //a to już tak...
    //assert(b == (a<<=6));

}

