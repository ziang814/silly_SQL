//C0F4DFE8B340D81183C208F70F9D2D797908754D

#include <vector>
#include<unordered_map>
#include <map>
#include "TableEntry.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <getopt.h>
using namespace std;

class Table {
public:
    Table() {
        created = true;
        indexExist = false;
    }
    //new functions, which can help Tables to get access to the private member of table
    Table(const string& nameOfTable,const vector<string>& col, const size_t& countOfCol) {
        created = true;
        indexExist = false;
        for (size_t i = 0; i < countOfCol; ++i) {
            columnst.push_back(col[i]);
        }
        for(size_t i = countOfCol; i < col.size(); ++i){
            columnsn.push_back(col[i]);
        }
        cout << "New table " << nameOfTable << " with column(s) ";
        for (size_t i = 0; i < columnsn.size(); ++i) {
            cout << columnsn[i] << " ";
        }
        cout << "created" << '\n';
    }
   

    //some of the functions below need to be revised or deleted
    //void get_opt(int argc, char** argv);

    //void read_in();

    //revised
    //void create(const string& nameOfTable);

    void insert(const string& nameOfTable);

    void print(const string& nameOfTable, const bool& q);

    void print_all(const vector<size_t>& index, const string& name, const bool& q);

    void print_where(const vector<size_t>& index, const string& name,const bool& q);

    size_t print_where_string(const TableEntry& s, const string& op, const size_t& index, const vector<size_t>& row, const bool& q);

    size_t print_where_bool(const TableEntry& b, const string& op, const size_t& index, const vector<size_t>& row, const bool& q);

    size_t print_where_int(const TableEntry& in, const string& op, const size_t& index, const vector<size_t>& row, const bool& q);
    
    size_t print_where_double(const TableEntry& d, const string& op, const size_t& index, const vector<size_t>& row, const bool& q);
    
    void delete_rows(const string& nameOfTable);

    void delete_string_helper(const TableEntry& s, const string& op, const size_t& index);

    void delete_bool_helper(const TableEntry& b, const string& op, const size_t& index);

    void delete_int_helper(const TableEntry& i, const string& op, const size_t& index);

    void delete_double_helper(const TableEntry& d, const string& op, const size_t& index);

    void generateIndex(const string& nameOfTable);

    //return the index of the colname in the column if it exists, else return -1
    int checkcolumn(const string& colname, const string& tableName) {
        auto it = find(columnsn.begin(),columnsn.end(),colname);
        if (it == columnsn.end()) {
            cout << "Error: " << colname << " does not name a column in " << tableName << '\n';
            return -1;
        }
        return (int)(it - columnsn.begin());
    }

    vector<vector<TableEntry>> thisTable;

    //the column names and types of this table; first half are types and second half are names
    vector<string> columnst;
    vector<string> columnsn;

    unordered_map<TableEntry, vector<size_t>> hash;
    map<TableEntry, vector<size_t>> bst;

    //check if the index exist on this table
    bool indexExist;
    //these three only have valuse when indexExist is true
    //indextype
    string indext;
    //colname
    string coln;
    //column index
    size_t col;

private:
    

    //just for the default constructor
    bool created;
 
    struct largerComparator {
        largerComparator(const size_t index, const TableEntry& original): idxOfCol(index), Compared(original){}
        bool operator()(const vector<TableEntry>& read_in) const {
            if (read_in[idxOfCol] > Compared) {
                return true;
            }
            return false;
        }
        //the index of the column we are going to compare
        const size_t idxOfCol;
        //the tableEntry we compare with
        const TableEntry Compared;
    };
    struct smallerComparator {
        smallerComparator(const size_t index, const TableEntry& original) : idxOfCol(index), Compared(original) {}
        bool operator()(const vector<TableEntry>& read_in) const {
            if (read_in[idxOfCol] < Compared) {
                return true;
            }
            return false;
        }
        //the index of the column we are going to compare
        const size_t idxOfCol;
        //the tableEntry we compare with
        const TableEntry Compared;
    };
    struct equalComparator {
        equalComparator(const size_t index, const TableEntry& original) : idxOfCol(index), Compared(original) {}
        bool operator()(const vector<TableEntry>& read_in) const {
            if (read_in[idxOfCol] == Compared) {
                return true;
            }
            return false;
        }
        //the index of the column we are going to compare
        const size_t idxOfCol;
        //the tableEntry we compare with
        const TableEntry Compared;
    };
};