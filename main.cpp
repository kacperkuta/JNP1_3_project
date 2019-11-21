#include "fibo.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

int main() {

    Fibo a(1);
    Fibo b(4);

    a+=b;
    cout << a.printFibo();
}

