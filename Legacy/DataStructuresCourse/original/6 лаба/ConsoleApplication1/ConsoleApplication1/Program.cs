#include <iostream>

#include <ctime>
#include <cstdlib>

#include "set.h"

using namespace std;

int main()
{
    srand(time(nullptr));

    auto size = 10;
    Set a, b, c, d, result;
    a.init(size);
    b.init(size);
    c.init(size);
    d.init(size);

    cout << "SET A: " << endl;
    a.output();
    cout << endl << "SET B: " << endl;
    b.output();
    cout << endl << "SET C: " << endl;
    c.output();
    cout << endl << "SET D: " << endl;
    d.output();

    result = a - (b & c) - d;
    cout << endl << "SET_INTERSECTION: " << endl;
    result.output();

    a.merge(b);
    cout << endl << "A.MERGE(B): " << endl;
    a.output();

    b.subst(c, 3);
    cout << endl << "B.SUBST(C, 3): " << endl;
    b.output();

    c.mul(3);
    cout << endl << "C.MUL(3): " << endl;
    c.output();

    return 0;
}
