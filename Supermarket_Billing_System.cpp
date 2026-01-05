#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
private:
    int pCode;
    float price;
    float discount;
    string pName;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void Product::menu() {
    m:
    int choice;
    cout << "\n\t\t\t\t__________________________________\n";
    cout << "\t\t\t\t                                  \n";
    cout << "\t\t\t\t      Supermarket Main Menu       \n";
    cout << "\t\t\t\t__________________________________\n";
    cout << "\t\t\t\t 1) Administrator   |\n";
    cout << "\t\t\t\t 2) Buyer           |\n";
    cout << "\t\t\t\t 3) Exit            |\n";
    cout << "\n\t\t\t Please select: ";
    cin >> choice;

    switch (choice) {
        case 1: administrator(); break;
        case 2: buyer(); break;
        case 3: exit(0);
        default: cout << "Select a valid option";
    }
    goto m;
}

void Product::administrator() {
    m:
    int choice;
    cout << "\n\n\t\t Admin Menu";
    cout << "\n\t\t 1) Add product";
    cout << "\n\t\t 2) Modify product";
    cout << "\n\t\t 3) Delete product";
    cout << "\n\t\t 4) Back to Main Menu";
    cout << "\n\n\t Please enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: add(); break;
        case 2: edit(); break;
        case 3: rem(); break;
        case 4: menu(); break;
        default: cout << "Invalid choice!";
    }
    goto m;
}

void Product::add() {
    fstream data;
    int c;
    float p, d;
    string n;

    cout << "\n\n\t Add New Product";
    cout << "\n\t Product code: "; cin >> pCode;
    cout << "\n\t Name: "; cin >> pName;
    cout << "\n\t Price: "; cin >> price;
    cout << "\n\t Discount: "; cin >> discount;

    data.open("database.txt", ios::app | ios::out);
    data << " " << pCode << " " << pName << " " << price << " " << discount << "\n";
    data.close();
    cout << "\n\t Record Inserted!";
}

void Product::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n_________________________________________________\n";
    cout << "ProNo\tName\tPrice\n";
    cout << "_________________________________________________\n";
    data >> pCode >> pName >> price >> discount;
    while (!data.eof()) {
        cout << pCode << "\t" << pName << "\t" << price << "\n";
        data >> pCode >> pName >> price >> discount;
    }
    data.close();
}

void Product::receipt() {
    fstream data;
    int arrc[100], arrq[100]; // arrays for codes and quantities
    char choice;
    int c = 0;
    float amount = 0, dis = 0, total = 0;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty Database";
    } else {
        data.close();
        list();
        cout << "\n__________________________________\n";
        cout << "\n      Place your Order            \n";
        do {
            cout << "\n Enter Product Code: "; cin >> arrc[c];
            cout << "\n Enter Quantity:     "; cin >> arrq[c];
            c++;
            cout << "\n Any other product? (y/n): "; cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t__________RECEIPT__________\n";
        cout << "Product No\tName\tQuantity\tPrice\tAmount\tWith Discount\n";

        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            data >> pCode >> pName >> price >> discount;
            while (!data.eof()) {
                if (pCode == arrc[i]) {
                    amount = price * arrq[i];
                    dis = amount - (amount * discount / 100);
                    total += dis;
                    cout << pCode << "\t\t" << pName << "\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << dis << "\n";
                }
                data >> pCode >> pName >> price >> discount;
            }
            data.close();
        }
    }
    cout << "\n\n__________________________________";
    cout << "\n Total Amount : " << total;
}
void Product::buyer() {
    m:
    int choice;
    cout << "\n\t\t\t  Buyer             \n";
    cout << "\t\t\t____________________\n";
    cout << "\t\t\t 1) Buy product     \n";
    cout << "\t\t\t 2) Go back         \n";
    cout << "\n\t\t\t Enter choice : ";
    cin >> choice;

    switch (choice) {
        case 1:
            receipt(); // This calls the logic to select items and calculate the bill
            break;
        case 2:
            menu(); // Returns to the main menu
            break;
        default:
            cout << "Invalid choice";
    }
    goto m;
}

void Product::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\t\t\t Modify Record";
    cout << "\n\t\t\t Product code : ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n File doesn't exist! ";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pCode >> pName >> price >> discount;
        while (!data.eof()) {
            if (pkey == pCode) {
                cout << "\n\t Product new code : "; cin >> c;
                cout << "\n\t Name of the product : "; cin >> n;
                cout << "\n\t Price : "; cin >> p;
                cout << "\n\t Discount : "; cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited ";
                token++;
            } else {
                data1 << " " << pCode << " " << pName << " " << price << " " << discount << "\n";
            }
            data >> pCode >> pName >> price >> discount;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found sorry!";
        }
    }
}

void Product::rem() {
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete product";
    cout << "\n\t Product code : ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\t File doesn't exist";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pCode >> pName >> price >> discount;
        while (!data.eof()) {
            if (pCode == pkey) {
                cout << "\n\t Product deleted successfully";
                token++;
            } else {
                data1 << " " << pCode << " " << pName << " " << price << " " << discount << "\n";
            }
            data >> pCode >> pName >> price >> discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\t Record not found";
        }
    }
}

int main() {
    Product p;
    p.menu();
    return 0;
}
