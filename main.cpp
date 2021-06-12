//C0F4DFE8B340D81183C208F70F9D2D797908754D


#include "Tables.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin >> std::boolalpha;
    cout << std::boolalpha;
    Tables tabless;
    tabless.get_opt(argc,argv);
    tabless.read_in();
    cout << "Thanks for being silly!" << '\n';
     return 0;
}