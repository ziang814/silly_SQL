//C0F4DFE8B340D81183C208F70F9D2D797908754D
#include "Tables.h"
using namespace std;

void Tables::get_opt(int argc, char** argv) {
    int option_index = 0, option = 0;
    opterr = false;
    struct option longOpts[] = { { "help", no_argument, nullptr, 'h' },
                                { "quiet", no_argument, nullptr, 'q' },
                                { nullptr, 0, nullptr, '\0' } };
    while ((option = getopt_long(argc, argv, "hq", longOpts, &option_index)) != -1) {
        switch (option) {
        case 'h':
            cout << "This program is a silly SQL";
            exit(0);
            break;
        case 'q':
            qModeOn = true;
            break;

        }
    }
}

//need to add quiet mode also
void Tables::read_in() {
    string first;
    do {
        cout << "% ";
        cin >> first;
        if (first[0] == 'C') {
            createTable();
        }
        else if (first[0] == 'I') {
            insertRows();
        }
        
        else if (first[0] == 'D') {
            string junk;
            cin >> junk;
            string name;
            cin >> name;
            auto it = tables.find(name);
            if (it == tables.end()) {
                cout << "Error: " << name << " does not name a table in the database" << '\n';
                getline(cin, name);
                continue;
            }
            tables[name].delete_rows(name);
        }
        
        else if (first[0] == 'G') {
            generate();
        }
        else if (first[0] == 'P') {
            //need revise after finishing the generate
            //here will read in and see if it's print all or print where
            string junk;
            cin >> junk;
            string name;
            cin >> name;
            auto it = tables.find(name);
            if (it == tables.end()) {
                cout << "Error: " << name << " does not name a table in the database" << '\n';
                getline(cin, junk);
                continue;
            }
            tables[name].print(name,qModeOn);
        }
        else if (first[0] == 'J') {
            string junk;
            string name1;
            cin >> name1;
            auto it = tables.find(name1);
            if (it == tables.end()) {
                cout << "Error: " << name1 << " does not name a table in the database" << '\n';
                getline(cin, junk);
                continue;
            }
            cin >> junk;
            string name2;
            cin >> name2;
            auto it1 = tables.find(name2);
            if (it1 == tables.end()) {
                cout << "Error: " << name2 << " does not name a table in the database" << '\n';
                getline(cin, junk);
                continue;
            }
            cin >> junk;
            string col1;
            cin >> col1;
            int index1 = 0;
            int index2 = 0;
            auto it2 = find(tables[name1].columnsn.begin(), tables[name1].columnsn.end(), col1);
            if (it2 == tables[name1].columnsn.end()) {
                cout << "Error: " << col1 << " does not name a column in " << name1 << '\n';
                getline(cin, junk);
                continue;
            }
            else {
                index1 = (int)(it2 - tables[name1].columnsn.begin());
            }
            /*int index1 = tables[name1].checkcolumn(col1, name1);
            if (index1 < 0) {
                getline(cin, junk);
                continue;
            }*/
            cin >> junk;
            string col2;
            cin >> col2;
            auto it3 = find(tables[name2].columnsn.begin(), tables[name2].columnsn.end(), col2);
            if (it3 == tables[name2].columnsn.end()) {
                cout << "Error: " << col2 << " does not name a column in " << name2 << '\n';
                getline(cin, junk);
                continue;
            }
            else {
                index2 = (int)(it3  - tables[name2].columnsn.begin());
            }
            /*
            int index2 = tables[name2].checkcolumn(col2, name2);
            if (index2 < 0) {
                getline(cin, junk);
                continue;
            }*/
            cin >> junk;
            cin >> junk;
            size_t N;
            cin >> N;
            string colname;
            size_t in;
            //the vector storing the respective index of printcol in each table if that colname exist;
            //the even index in this vector will be the name of printcol and the odd index will indicate
            //whether it's in the first or second table
            vector<size_t> index;
            bool error = false;
            for (size_t i = 0; i < 2 * N; ++i) {
                if (i % 2 == 0) {
                    cin >> colname;
                }
                else {
                    cin >> in;
                    if (in == 1){
                        auto it4 = find(tables[name1].columnsn.begin(), tables[name1].columnsn.end(), colname);
                        //int ind = tables[name1].checkcolumn(colname, name1);
                        if (it4 == tables[name1].columnsn.end()) {
                            getline(cin, junk);
                            error = true;
                            cout << "Error: " << colname << " does not name a column in " << name1 << '\n';
                            break;
                        }
                        else {
                            //if (it4 - tables[name1].columnsn.begin() >= (int)(tables[name1].columnsn.size() / 2)) {
                                //index.push_back((it4 - (tables[name1].columns.size() / 2)) - tables[name1].columns.begin());
                            //}
                            //else {
                            index.push_back(it4 - tables[name1].columnsn.begin());
                            //}
                            index.push_back(1);
                        }
                    }
                    else {
                        auto it4 = find(tables[name2].columnsn.begin(), tables[name2].columnsn.end(), colname);
                        //int ind = tables[name1].checkcolumn(colname, name1);
                        if (it4 == tables[name2].columnsn.end()) {
                            getline(cin, junk);
                            error = true;
                            cout << "Error: " << colname << " does not name a column in " << name2 << '\n';
                            break;
                        }
                        else {
                            //if (it4 - tables[name2].columns.begin() >= (int)(tables[name2].columns.size() / 2)) {
                                //index.push_back((it4 - (tables[name2].columns.size() / 2)) - tables[name2].columns.begin());
                            //}
                            //else {
                            index.push_back(it4 - tables[name2].columnsn.begin());
                            //}
                            index.push_back(2);
                        }
                        /*int ind = tables[name2].checkcolumn(colname, name2);
                        if (ind < 0) {
                            getline(cin, junk);
                            error = true;
                            break;
                        }
                        else {
                            index.push_back(ind);
                            index.push_back(2);
                        }*/
                    }
                }
            }
            if (error) {
                continue;
            }
            if(!qModeOn){
                for (size_t i = 0; i < index.size(); i += 2) {
                    if (index[i + 1] == 1) {
                        cout << tables[name1].columnsn[index[i]] << " ";
                    }
                    else {
                        cout << tables[name2].columnsn[index[i]] << " ";
                    }
                }
                cout << '\n';
            }
            size_t print = 0;
            if (!qModeOn) {
                //if there already exist an index
                if (tables[name2].indexExist && tables[name2].indext == "hash" && tables[name2].coln == col2) {
                    for (size_t i = 0; i < tables[name1].thisTable.size(); ++i) {
                        if (!tables[name2].hash[tables[name1].thisTable[i][(size_t)index1]].empty()) {
                            for (size_t m = 0; m < tables[name2].hash[tables[name1].thisTable[i][(size_t)index1]].size(); ++m) {
                                for (size_t j = 0; j < index.size(); j += 2) {
                                    if (index[j + 1] == 1) {
                                        cout << tables[name1].thisTable[i][index[j]] << " ";
                                    }
                                    else {
                                        cout << tables[name2].thisTable[tables[name2].hash[tables[name1].thisTable[i][(size_t)index1]][m]][index[j]] << " ";
                                    }
                                }
                                print++;
                                cout << '\n';
                            }
                        }
                    }
                }
                else {
                    unordered_map<TableEntry, vector<size_t>> temporary;
                    for (size_t x = 0; x < tables[name2].thisTable.size(); ++x) {
                        temporary[tables[name2].thisTable[x][(size_t)index2]].push_back(x);
                    }
                    for (size_t i = 0; i < tables[name1].thisTable.size(); ++i) {
                        if (!temporary[tables[name1].thisTable[i][(size_t)index1]].empty()) {
                            for (size_t m = 0; m < temporary[tables[name1].thisTable[i][(size_t)index1]].size(); ++m) {
                                for (size_t j = 0; j < index.size(); j += 2) {
                                    if (index[j + 1] == 1) {
                                        cout << tables[name1].thisTable[i][index[j]] << " ";
                                    }
                                    else {
                                        cout << tables[name2].thisTable[temporary[tables[name1].thisTable[i][(size_t)index1]][m]][index[j]] << " ";
                                    }
                                }
                                print++;
                                cout << '\n';
                            }
                        }
                    }
                }
            }
            //qmode on
            else {
                //if there already exist an index
                if (tables[name2].indexExist && tables[name2].indext == "hash" && tables[name2].coln == col2) {
                    for (size_t i = 0; i < tables[name1].thisTable.size(); ++i) {
                        if (!tables[name2].hash[tables[name1].thisTable[i][(size_t)index1]].empty()) {
                            print += tables[name2].hash[tables[name1].thisTable[i][(size_t)index1]].size();
                        }
                    }
                }
                else {
                    unordered_map<TableEntry, vector<size_t>> temporary;
                    for (size_t x = 0; x < tables[name2].thisTable.size(); ++x) {
                        temporary[tables[name2].thisTable[x][(size_t)index2]].push_back(x);
                    }
                    for (size_t i = 0; i < tables[name1].thisTable.size(); ++i) {
                        if (!temporary[tables[name1].thisTable[i][(size_t)index1]].empty()) {
                            print += temporary[tables[name1].thisTable[i][(size_t)index1]].size();
                        }
                    }
                }
            }
            cout << "Printed " << print << " rows from joining " << name1 << " to " << name2 << '\n';
        }
        else if (first[0] == 'R') {
            //need revision so that it can also remove the generated index
            remove();
        }
        else if (first == "#" || first[0] == '#') {
            (getline(cin, first));
            continue;
        }
        else if (first[0] == 'Q') {
            break;
        }
        else {
            cout << "Error: unrecognized command" << endl;
            getline(cin, first);
            continue;
        }
    } while (first != "QUIT");
}

void Tables::createTable() {
    string name;
    cin >> name;
    auto it = tables.find(name);
    if (it != tables.end()) {
        cout << "Error: Cannot create already existing table " << name << '\n';
        getline(cin, name);
        return;
    }
    size_t N;
    cin >> N;
    string read;
    vector<string> r;
    for (size_t i = 0; i < 2*N; ++i) {
        cin >> read;
        r.push_back(read);
    }
    
    tables[name] = Table(name, r, N);
}

void Tables::insertRows() {
    string junk;
    cin >> junk;
    string name;
    cin >> name;
    auto it = tables.find(name);
    if (it == tables.end()) {
        cout << "Error: " << name << " does not name a table in the database" << '\n';
        size_t Ns;
        cin >> Ns;
        for (size_t i = 0; i < Ns+1; ++i) {
            getline(cin, name);
        }
        return;
    }
    tables[name].insert(name); 
}

void Tables::remove() {
    string name;
    cin >> name;
    auto it = tables.find(name);
    if (it == tables.end()) {
        cout << "Error: " << name << " does not name a table in the database" << '\n';
        getline(cin, name);
        return;
    }
    tables.erase(name);
    cout << "Table " << name << " deleted" << '\n';
}

void Tables::generate() {
    string junk;
    cin >> junk;
    string name;
    cin >> name;
    //is there a more efficient to check this?
    auto it = tables.find(name);
    if (it == tables.end()) {
        cout << "Error: " << name << " does not name a table in the database" << '\n';
        getline(cin, name);
        return;
    }

    tables[name].generateIndex(name);
}