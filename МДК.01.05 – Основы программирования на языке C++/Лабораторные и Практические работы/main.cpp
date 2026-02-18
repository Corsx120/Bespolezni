#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <map>
#include <exception>
#include <cstdlib>   // system
#include <clocale>   // setlocale

using namespace std;

struct Record {
    int id;
    string type;      // "income" or "expense"
    string category;
    double amount;
    string date;      // YYYY-MM-DD
    string description;
};

vector<Record> records;
int next_id = 1;
bool unsaved_changes = false;
const string DEFAULT_FILENAME = "data.csv";

void trim(string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    if (a == string::npos) s = "";
    else s = s.substr(a, b - a + 1);
}

bool validDate(const string& d) {
    if (d.size() != 10) return false;
    if (d[4] != '-' || d[7] != '-') return false;
    string ys = d.substr(0, 4), ms = d.substr(5, 2), ds = d.substr(8, 2);
    try {
        int y = stoi(ys), m = stoi(ms), day = stoi(ds);
        if (m < 1 || m > 12) return false;
        if (day < 1 || day > 31) return false;
        int mdays[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        bool leap = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
        if (leap) mdays[2] = 29;
        if (day > mdays[m]) return false;
        return true;
    }
    catch (...) {
        return false;
    }
}

string readLineNonEmpty(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) {
            cin.clear();
            continue;
        }
        trim(s);
        if (!s.empty()) return s;
        cout << "Empty input — please try again.\n";
    }
}

double readAmount(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) { cin.clear(); continue; }
        trim(s);
        try {
            double v = stod(s);
            if (v <= 0) {
                cout << "Amount must be positive. Try again.\n";
                continue;
            }
            return v;
        }
        catch (...) {
            cout << "Invalid amount format. Enter a number, e.g. 123.45\n";
        }
    }
}

string readDate(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        if (!getline(cin, s)) { cin.clear(); continue; }
        trim(s);
        if (validDate(s)) return s;
        cout << "Invalid date format. Expected YYYY-MM-DD. Try again.\n";
    }
}

void addRecord() {
    cout << "\n--- Add record ---\n";
    string type;
    while (true) {
        cout << "Operation type (1 - income, 2 - expense): ";
        string t;
        if (!getline(cin, t)) { cin.clear(); continue; }
        trim(t);
        if (t == "1") { type = "income"; break; }
        if (t == "2") { type = "expense"; break; }
        cout << "Invalid choice. Enter 1 or 2.\n";
    }
    string category = readLineNonEmpty("Category: ");
    double amount = readAmount("Amount: ");
    string date = readDate("Date (YYYY-MM-DD): ");
    cout << "Description (optional): ";
    string desc;
    getline(cin, desc);
    trim(desc);

    Record r;
    r.id = next_id++;
    r.type = type;
    r.category = category;
    r.amount = amount;
    r.date = date;
    r.description = desc;
    records.push_back(r);
    unsaved_changes = true;
    cout << "Record added (id=" << r.id << ").\n\n";
}

void printRecord(const Record& r) {
    cout << "ID: " << r.id
        << " | " << r.date
        << " | " << r.type
        << " | Category: " << r.category
        << " | Amount: " << fixed << setprecision(2) << r.amount;
    if (!r.description.empty()) cout << " | " << r.description;
    cout << "\n";
}

void viewAll() {
    cout << "\n--- All records ---\n";
    if (records.empty()) { cout << "No records.\n\n"; return; }
    for (const auto& r : records) printRecord(r);
    cout << "\n";
}

void viewByType() {
    cout << "\n--- View by type ---\n";
    string type;
    while (true) {
        cout << "Choose type (1 - income, 2 - expense): ";
        string t;
        if (!getline(cin, t)) { cin.clear(); continue; }
        trim(t);
        if (t == "1") { type = "income"; break; }
        if (t == "2") { type = "expense"; break; }
        cout << "Invalid choice. Enter 1 or 2.\n";
    }
    bool found = false;
    for (const auto& r : records) {
        if (r.type == type) { printRecord(r); found = true; }
    }
    if (!found) cout << "No records found.\n";
    cout << "\n";
}

void viewByPeriod() {
    cout << "\n--- View by period ---\n";
    string from = readDate("Start date (YYYY-MM-DD): ");
    string to = readDate("End date (YYYY-MM-DD): ");
    if (from > to) swap(from, to);
    bool found = false;
    for (const auto& r : records) {
        if (r.date >= from && r.date <= to) { printRecord(r); found = true; }
    }
    if (!found) cout << "No records found in this period.\n";
    cout << "\n";
}

void deleteRecord() {
    cout << "\n--- Delete record by ID ---\n";
    cout << "Enter ID to delete: ";
    string s;
    if (!getline(cin, s)) { cin.clear(); return; }
    trim(s);
    try {
        int id = stoi(s);
        auto it = find_if(records.begin(), records.end(), [&](const Record& r) { return r.id == id; });
        if (it == records.end()) {
            cout << "Record with ID=" << id << " not found.\n\n";
            return;
        }
        cout << "Found record:\n";
        printRecord(*it);
        cout << "Confirm deletion? (y/n): ";
        string c;
        if (!getline(cin, c)) { cin.clear(); return; }
        trim(c);
        if (!c.empty() && (c[0] == 'y' || c[0] == 'Y')) {
            records.erase(it);
            unsaved_changes = true;
            cout << "Record deleted.\n\n";
        }
        else {
            cout << "Deletion cancelled.\n\n";
        }
    }
    catch (...) {
        cout << "Invalid ID.\n\n";
    }
}

void calcStats() {
    cout << "\n--- Financial statistics ---\n";
    double total_income = 0.0, total_expense = 0.0;
    map<string, double> categorySums;
    for (const auto& r : records) {
        if (r.type == "income") {
            total_income += r.amount;
            categorySums[r.category] += r.amount;
        }
        else {
            total_expense += r.amount;
            categorySums[r.category] -= r.amount;
        }
    }
    cout << "Total income: " << fixed << setprecision(2) << total_income << "\n";
    cout << "Total expenses: " << fixed << setprecision(2) << total_expense << "\n";
    cout << "Current balance (income - expenses): " << fixed << setprecision(2) << (total_income - total_expense) << "\n\n";
    cout << "Category breakdown (positive = net income, negative = net expense):\n";
    if (categorySums.empty()) cout << "No category data.\n";
    for (const auto& p : categorySums) {
        cout << "  " << p.first << " : " << fixed << setprecision(2) << p.second << "\n";
    }
    cout << "\n";
}

vector<string> split(const string& s, char sep) {
    vector<string> out;
    string cur;
    for (char c : s) {
        if (c == sep) {
            out.push_back(cur);
            cur.clear();
        }
        else cur.push_back(c);
    }
    out.push_back(cur);
    return out;
}

void saveToFile(const string& filename) {
    try {
        ofstream fout(filename, ios::trunc);
        if (!fout) {
            cout << "Error opening file for writing: " << filename << "\n";
            return;
        }
        fout << "id;type;category;amount;date;description\n";
        for (const auto& r : records) {
            string cat = r.category; replace(cat.begin(), cat.end(), ';', ',');
            string desc = r.description; replace(desc.begin(), desc.end(), ';', ',');
            string type = r.type; replace(type.begin(), type.end(), ';', ',');
            fout << r.id << ";" << type << ";" << cat << ";" << fixed << setprecision(2) << r.amount
                << ";" << r.date << ";" << desc << "\n";
        }
        fout.close();
        unsaved_changes = false;
        cout << "Data saved to file: " << filename << "\n\n";
    }
    catch (const exception& e) {
        cout << "Exception while saving: " << e.what() << "\n";
    }
}

void loadFromFile(const string& filename) {
    try {
        ifstream fin(filename);
        if (!fin) {
            cout << "Data file not found (" << filename << "). Using empty database.\n";
            return;
        }
        string line;
        getline(fin, line); // header
        records.clear();
        int maxid = 0;
        while (getline(fin, line)) {
            if (line.empty()) continue;
            vector<string> parts = split(line, ';');
            if (parts.size() < 6) continue;
            try {
                Record r;
                r.id = stoi(parts[0]);
                r.type = parts[1];
                r.category = parts[2];
                r.amount = stod(parts[3]);
                r.date = parts[4];
                r.description = parts[5];
                records.push_back(r);
                if (r.id > maxid) maxid = r.id;
            }
            catch (...) {
                continue;
            }
        }
        fin.close();
        next_id = maxid + 1;
        unsaved_changes = false;
        cout << "Data loaded from file: " << filename << " (records: " << records.size() << ")\n\n";
    }
    catch (const exception& e) {
        cout << "Exception while loading: " << e.what() << "\n";
    }
}

void printMenu() {
    cout << "=== Personal Finance Tracker ===\n";
    cout << "1. Add record\n";
    cout << "2. View all records\n";
    cout << "3. View records by type (income/expense)\n";
    cout << "4. View records by period\n";
    cout << "5. Delete record by ID\n";
    cout << "6. Show financial statistics\n";
    cout << "7. Save data to file\n";
    cout << "8. Load data from file\n";
    cout << "9. Exit\n";
    cout << "Choose action (1-9): ";
}

int main() {
    // Set locale: prefer English locale; do not change code page on Windows here
#ifdef _WIN32
    // Try to set English locale on Windows; exact name may vary by system.
    setlocale(LC_ALL, "English");
#else
    setlocale(LC_ALL, "en_US.UTF-8");
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Try to load default data file
    loadFromFile(DEFAULT_FILENAME);

    while (true) {
        printMenu();
        string choice;
        if (!getline(cin, choice)) { cin.clear(); continue; }
        trim(choice);
        if (choice == "1") {
            addRecord();
        }
        else if (choice == "2") {
            viewAll();
        }
        else if (choice == "3") {
            viewByType();
        }
        else if (choice == "4") {
            viewByPeriod();
        }
        else if (choice == "5") {
            deleteRecord();
        }
        else if (choice == "6") {
            calcStats();
        }
        else if (choice == "7") {
            cout << "Enter filename to save (Enter for " << DEFAULT_FILENAME << "): ";
            string fname;
            getline(cin, fname);
            trim(fname);
            if (fname.empty()) fname = DEFAULT_FILENAME;
            saveToFile(fname);
        }
        else if (choice == "8") {
            cout << "Enter filename to load (Enter for " << DEFAULT_FILENAME << "): ";
            string fname;
            getline(cin, fname);
            trim(fname);
            if (fname.empty()) fname = DEFAULT_FILENAME;
            loadFromFile(fname);
        }
        else if (choice == "9") {
            if (unsaved_changes) {
                cout << "There are unsaved changes. Save before exit? (y/n): ";
                string c;
                if (!getline(cin, c)) { cin.clear(); continue; }
                trim(c);
                if (!c.empty() && (c[0] == 'y' || c[0] == 'Y')) {
                    saveToFile(DEFAULT_FILENAME);
                }
            }
            cout << "Exit.\n";
            break;
        }
        else {
            cout << "Invalid choice. Enter a number from 1 to 9.\n\n";
        }
    }

    return 0;
}