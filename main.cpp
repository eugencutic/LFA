#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#include "AFN_header.h"

int main()
{
    ifstream in("AFN.in");
    AFN a;
    in>>a;
    AFD b;
    b=a;

    b.toAFD();
    cout<<endl<<b;
    return 0;
}
