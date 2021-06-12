//C0F4DFE8B340D81183C208F70F9D2D797908754D

#include "table.h"
using namespace std;




void Table::insert(const string& nameOfTable) {
    size_t N;
    cin >> N;
    string junk;
    cin >> junk;
    string read_ins;
    int read_ini;
    double read_ind;
    bool read_inb;
    
    size_t startN = thisTable.size();
    thisTable.resize(thisTable.size() + N);

    for (size_t i = startN; i < thisTable.size(); ++i) {
        thisTable[i].reserve(columnsn.size());
        for (size_t j = 0; j < columnst.size(); ++j) {
            if (columnst[j] == "int") {
                cin >> read_ini;
                thisTable[i].emplace_back(read_ini);
            }
            else if (columnst[j] == "string") {
                cin >> read_ins;
                //vector subscript out of range
                thisTable[i].emplace_back(read_ins);
            }
            else if (columnst[j] == "double") {
                cin >> read_ind;
                thisTable[i].emplace_back(read_ind);
            }
            else {
                cin >> read_inb;
                thisTable[i].emplace_back(read_inb);
            }
        }
    }
    //if an index exist, we also need to revise the index
    if (indexExist) {
        if (indext == "hash") {
            for (size_t i = startN; i < thisTable.size(); ++i) {
                hash[thisTable[i][col]].push_back(i);
            }
        }
        else {
            for (size_t i = startN; i < thisTable.size(); ++i) {
                bst[thisTable[i][col]].push_back(i);
            }
        }
    }
    cout << "Added " << N << " rows to " << nameOfTable << " from position " << startN << " to " << startN + N - 1 << '\n';
}

void Table::print(const string& nameOfTable, const bool& q) {
    size_t N;
    cin >> N;
    string read_in;
    vector<size_t> index;
    bool noCol = false;
    string junk;
    for (size_t i = 0; i < N; ++i) {
        cin >> read_in;
        auto it = find(columnsn.begin(), columnsn.end(), read_in);
        if (it != columnsn.end()) {
            
            index.push_back(it - columnsn.begin());
            
        }
        else {
            cout << "Error: " << read_in << " does not name a column in " << nameOfTable << '\n';
            getline(cin, junk);
            noCol = true;
            break;
        }
    }
    if (noCol) {
        return;
    }
    cin >> junk;
    if (junk == "ALL") {
        print_all(index, nameOfTable,q);
    }
    else {
        print_where(index, nameOfTable,q);
    }
}

void Table::print_all(const vector<size_t>& index, const string& name, const bool& q) {
    if (!q) {
        for (size_t i = 0; i < index.size(); ++i) {
            cout << columnsn[index[i]] << " ";
        }
        cout << '\n';
        for (size_t i = 0; i < thisTable.size(); ++i) {
            for (size_t j = 0; j < index.size(); ++j) {
                cout << thisTable[i][index[j]] << " ";
            }
            cout << '\n';
        }
    }
    cout << "Printed " << thisTable.size() << " matching rows from " << name << '\n';
}

void Table::print_where(const vector<size_t>& index, const string& name, const bool& q) {
    string colname;
    cin >> colname;
    string junk;
    auto it1 = find(columnsn.begin(), columnsn.end(), colname);
    if (it1 == columnsn.end()) {
        cout << "Error: " << colname << " does not name a column in " << name << '\n';
        getline(cin, junk);
        return;
    }
    string op;
    cin >> op;
    //index of the compared col in the table
    size_t index1 = it1  - columnsn.begin();
    size_t print;
    if (!q) {
        for (size_t i = 0; i < index.size(); ++i) {
            cout << columnsn[index[i]] << " ";
        }
        cout << '\n';
    }
    
    if (columnst[it1-columnsn.begin()] == "string") {
        string s;
        cin >> s;
        const TableEntry s1(s);
        print = print_where_string(s1, op, index1, index,q);
    }
    else if (columnst[it1 - columnsn.begin()] == "bool") {
        bool b;
        cin >> b;
        const TableEntry b1(b);
        print = print_where_bool(b1, op, index1, index,q);
    }
    else if (columnst[it1 - columnsn.begin()] == "int") {
        int i;
        cin >> i;
        const TableEntry i1(i);
        print = print_where_int(i1, op, index1, index,q);
    }
    else {
        double d;
        cin >> d;
        const TableEntry d1(d);
        print = print_where_double(d1, op, index1, index,q);
    }
    cout << "Printed " << print << " matching rows from " << name << '\n';
}
//can improve if there exist a bst tree(> <) or hash(=)
size_t Table::print_where_string(const TableEntry& s, const string& op, const size_t& index, const vector<size_t>& row, const bool& q) {
    size_t p = 0;
    if (!q) {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(s);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < s) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(s);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > s) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                for (size_t i = 0; i < hash[s].size(); ++i) {
                    for (size_t j = 0; j < row.size(); ++j) {
                        cout << thisTable[hash[s][i]][row[j]] << " ";
                    }
                    cout << '\n';
                }
                if (!hash[s].empty()) {
                    p = hash[s].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(s);
                if (it != bst.end()) {
                    for (size_t i = 0; i < it->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == s) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
    }
    else {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(s);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < s) {
                        p++;
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(s);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > s) {
                        p++;
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                if (!hash[s].empty()) {
                    p = hash[s].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(s);
                if (it != bst.end()) {
                    p += it->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == s) {
                        p++;
                    }
                }
            }
        }
    }
    return p;
}

size_t Table::print_where_bool(const TableEntry& b, const string& op, const size_t& index, const vector<size_t>& row, const bool& q) {
    size_t p = 0;
    if (!q) {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(b);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < b) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(b);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > b) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                for (size_t i = 0; i < hash[b].size(); ++i) {
                    for (size_t j = 0; j < row.size(); ++j) {
                        cout << thisTable[hash[b][i]][row[j]] << " ";
                    }
                    cout << '\n';
                }
                if (!hash[b].empty()) {
                    p = hash[b].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(b);
                if (it != bst.end()) {
                    for (size_t i = 0; i < it->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == b) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
    }
    else {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(b);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < b) {
                        p++;
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(b);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > b) {
                        p++;
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                if (!hash[b].empty()) {
                    p = hash[b].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(b);
                if (it != bst.end()) {
                    p += it->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == b) {
                        p++;
                    }
                }
            }
        }
    }
    return p;
}

size_t Table::print_where_int(const TableEntry& in, const string& op, const size_t& index, const vector<size_t>& row, const bool& q) {
    size_t p = 0;
    if (!q) {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(in);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < in) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(in);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > in) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                for (size_t i = 0; i < hash[in].size(); ++i) {
                    for (size_t j = 0; j < row.size(); ++j) {
                        cout << thisTable[hash[in][i]][row[j]] << " ";
                    }
                    cout << '\n';
                }
                if (!hash[in].empty()) {
                    p = hash[in].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(in);
                if (it != bst.end()) {
                    for (size_t i = 0; i < it->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == in) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
    }
    else {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(in);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < in) {
                        p++;
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(in);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > in) {
                        p++;
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                if (!hash[in].empty()) {
                    p = hash[in].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(in);
                if (it != bst.end()) {
                    p += it->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == in) {
                        p++;
                    }
                }
            }
        }
    }
    return p;
}

size_t Table::print_where_double(const TableEntry& d, const string& op, const size_t& index, const vector<size_t>& row, const bool& q) {
    size_t p = 0;
    if (!q) {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(d);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < d) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(d);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    for (size_t i = 0; i < it1->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it1->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > d) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                for (size_t i = 0; i < hash[d].size(); ++i) {
                    for (size_t j = 0; j < row.size(); ++j) {
                        cout << thisTable[hash[d][i]][row[j]] << " ";
                    }
                    cout << '\n';
                }
                if (!hash[d].empty()) {
                    p = hash[d].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(d);
                if (it != bst.end()) {
                    for (size_t i = 0; i < it->second.size(); ++i) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[it->second[i]][row[j]] << " ";
                        }
                        cout << '\n';
                        p++;
                    }
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == d) {
                        for (size_t j = 0; j < row.size(); ++j) {
                            cout << thisTable[i][row[j]] << " ";
                        }
                        p++;
                        cout << '\n';
                    }
                }
            }
        }
    }
    else {
        if (op == "<") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.lower_bound(d);
                for (auto it1 = bst.begin(); it1 != it; ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] < d) {
                        p++;
                    }
                }
            }
        }
        else if (op == ">") {
            if (indexExist && index == col && indext == "bst") {
                auto it = bst.upper_bound(d);
                for (auto it1 = it; it1 != bst.end(); ++it1) {
                    p += it1->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] > d) {
                        p++;
                    }
                }
            }
        }
        else {
            if (indexExist && col == index && indext == "hash") {
                if (!hash[d].empty()) {
                    p = hash[d].size();
                }
            }
            else if (indexExist && col == index && indext == "bst") {
                auto it = bst.find(d);
                if (it != bst.end()) {
                    p += it->second.size();
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    if (thisTable[i][index] == d) {
                        p++;
                    }
                }
            }
        }
    }
    return p;
}

void Table::delete_rows(const string& nameOfTable) {
    //regenerate the index no matter what if an index exist
    string junk;
    cin >> junk;
    string colname;
    cin >> colname;
    auto it1 = find(columnsn.begin(), columnsn.end(), colname);
    if (it1 == columnsn.end()) {
        cout << "Error: " << colname << " does not name a column in " << nameOfTable << '\n';
        getline(cin, junk);
        return;
    }
    string op;
    cin >> op;
    size_t index = it1 -columnsn.begin();
    size_t size = thisTable.size();
    if (columnst[it1 - columnsn.begin()] == "string") {
        string s;
        cin >> s;
        const TableEntry s1(s);
        delete_string_helper(s1,op,index);
    }
    else if (columnst[it1 - columnsn.begin()] == "bool") {
        bool b;
        cin >> b;
        const TableEntry b1(b);
        delete_bool_helper(b1, op, index);
    }
    else if (columnst[it1 - columnsn.begin()] == "int") {
        int i;
        cin >> i;
        const TableEntry i1(i);
        delete_int_helper(i1, op, index);
    }
    else {
        double d;
        cin >> d;
        const TableEntry d1(d);
        delete_double_helper(d1, op, index);
    }
    cout << "Deleted " << size - thisTable.size() << " rows from " << nameOfTable << '\n';
}

void Table::delete_string_helper(const TableEntry& s, const string& op, const size_t& index) {
    if (op == "<") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), smallerComparator(index, s)), thisTable.end());
    }
    else if (op == ">") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), largerComparator(index, s)), thisTable.end());
    }
    else {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), equalComparator(index, s)), thisTable.end());
    }
    if (indexExist) {
        if (indext == "hash") {
            hash.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                hash[thisTable[i][col]].push_back(i);
            }
        }
        else {
            bst.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                bst[thisTable[i][col]].push_back(i);
            }
        }
    }
}


void Table::delete_bool_helper(const TableEntry& b, const string& op, const size_t& index) {
    if (op == "<") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), smallerComparator(index, b)), thisTable.end());
    }
    else if (op == ">") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), largerComparator(index, b)), thisTable.end());
    }
    else {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), equalComparator(index, b)), thisTable.end());
    }
    if (indexExist) {
        if (indext == "hash") {
            hash.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                hash[thisTable[i][col]].push_back(i);
            }
        }
        else {
            bst.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                bst[thisTable[i][col]].push_back(i);
            }
        }
    }
}

void Table::delete_int_helper(const TableEntry& i, const string& op, const size_t& index) {
    if (op == "<") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), smallerComparator(index, i)), thisTable.end());
    }
    else if (op == ">") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), largerComparator(index, i)), thisTable.end());
    }
    else {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), equalComparator(index, i)), thisTable.end());
    }
    if (indexExist) {
        if (indext == "hash") {
            hash.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                hash[thisTable[i][col]].push_back(i);
            }
        }
        else {
            bst.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                bst[thisTable[i][col]].push_back(i);
            }
        }
    }
}

void Table::delete_double_helper(const TableEntry& d, const string& op, const size_t& index) {
    if (op == "<") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), smallerComparator(index, d)), thisTable.end());
    }
    else if (op == ">") {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), largerComparator(index, d)), thisTable.end());
    }
    else {
        thisTable.erase(remove_if(thisTable.begin(), thisTable.end(), equalComparator(index, d)), thisTable.end());
    }
    if (indexExist) {
        if (indext == "hash") {
            hash.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                hash[thisTable[i][col]].push_back(i);
            }
        }
        else {
            bst.clear();
            for (size_t i = 0; i < thisTable.size(); ++i) {
                bst[thisTable[i][col]].push_back(i);
            }
        }
    }
}


void Table::generateIndex(const string& nameOfTable) {
    string junk;
    string indexType;
    cin >> indexType;
    cin >> junk;
    cin >> junk;
    string colName;
    cin >> colName;
    auto it1 = find(columnsn.begin(), columnsn.end(), colName);
    if (it1 == columnsn.end()) {
        cout << "Error: " << colName << " does not name a column in " << nameOfTable << '\n';
        getline(cin, junk);
        return;
    }
    size_t indexInColumn = it1 - columnsn.begin();
    if (!indexExist) {
        coln = colName;
        indext = indexType;
        col = indexInColumn;
        indexExist = true;
        if (indexType == "hash") {
            for (size_t i = 0; i < thisTable.size(); ++i) {
                hash[thisTable[i][indexInColumn]].push_back(i);
            }
        }
        else {
            for (size_t i = 0; i < thisTable.size(); ++i) {
                bst[thisTable[i][indexInColumn]].push_back(i);
            }
        }
    }
    else {
        indexExist = true;
        if (colName != coln || indexType != indext) {
            if (indext == "hash") {
                hash.clear();
            }
            else {
                bst.clear();
            }
            coln = colName;
            indext = indexType;
            col = indexInColumn;
            if (indexType == "hash") {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    hash[thisTable[i][indexInColumn]].push_back(i);
                }
            }
            else {
                for (size_t i = 0; i < thisTable.size(); ++i) {
                    bst[thisTable[i][indexInColumn]].push_back(i);
                }
            }
        }
    }
    cout << "Created " << indexType << " index for table " << nameOfTable << " on column " << colName << '\n';
}
