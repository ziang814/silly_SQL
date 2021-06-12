//C0F4DFE8B340D81183C208F70F9D2D797908754D


#include "table.h"
using namespace std;

class Tables {
public:
    Tables() {
        qModeOn = false;
    }
    void get_opt(int argc, char** argv);

    void read_in();

    void createTable();

    void insertRows();

    void remove();

    void generate();

private:
    //may be can be changed to another data structure to optimize memory
    //map from table name to table
    unordered_map<string, Table> tables;

    //quiet mode
    bool qModeOn;
};