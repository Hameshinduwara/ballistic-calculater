#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

// Global Variables
double x, High, u, g, x2, u2, a, c, tana1, tana2, cone1, cone2;
double mula, tan_c, tan_c90;
string mark10;

// Function to check and handle negative inputs
double im_negative(double xo) {
    if (xo < 0) {
        mark10 = "i";
        return -xo;
    } else {
        mark10 = " ";
        return xo;
    }
}

// Function A: Calculates acceleration
double A() {
    x2 = pow(x, 2);
    u2 = pow(u, 2);
    double a_up = g * x2;
    double a_down = 2 * u2;
    a = a_up / a_down;
    return a;
}

// Function C: Calculates intermediate value c
double C() {
    double c_left = A();
    c = c_left - High;
    return c;
}

// Function to handle square root of discriminant
double formula() {
    double ac4 = 4 * a * c;
    double in_mula = x2 - ac4;
    double negative = im_negative(in_mula);
    mula = sqrt(negative);

    // Calculate tan(c) and tan(90-c)
    double tan_c_up = -x + mula;
    double tan_c_down = 2 * a;
    tan_c = tan_c_up / tan_c_down;

    double tan_c90_up = -x - mula;
    tan_c90 = tan_c90_up / tan_c_down;

    return tan_c;
}

// Function to initialize variables
void floati(double x1, double y1, double u1, double g1) {
    x = x1;
    High = y1;
    u = u1;
    g = g1;
}

// Function to calculate cone angles
void cone() {
    tana1 = formula();
    tana2 = tan_c90;

    cone1 = atan(tana2) * 180 / M_PI;
    cone2 = atan(tana1) * 180 / M_PI;
}

// Function to write history to a file
void history(double x1, double y1, double u1, double g1) {
    ofstream f("report.txt", ios::app);
    f << x1 << "\t" << y1 << "\t" << u1 << "\t" << g1 << endl;
    f.close();
}

// Function to read history
void reeed() {
    ifstream f("report.txt");
    string line;
    while (getline(f, line)) {
        cout << line << endl;
    }
    f.close();
}

// Menu System
void menusys() {
    cout << "     /\\             //|                              " << endl;
    cout << "     |            //   |           tan@              " << endl;
    cout << "     |          //      |            ballistic       " << endl;
    cout << "hight|        //         |                 calculetor" << endl;
    cout << "     |      //            |                          " << endl;
    cout << "     |    // ;             |                         " << endl;
    cout << "     |  // @  ;            |                         " << endl;
    cout << "     \\/                                              " << endl;
    cout << "     <--------------------->           v1.4           " << endl;
    cout << "             length                                   " << endl;
}

// Main Function
int main() {
    bool loop = true;

    while (loop) {
        menusys();
        
        double x1, y1, u1, g1 = 9.87;
        cout << "Enter length<m>: ";
        cin >> x1;
        cout << "Enter height<m>: ";
        cin >> y1;
        cout << "Enter speed<m/s>: ";
        cin >> u1;

        history(x1, y1, u1, g1);
        floati(x1, y1, u1, g1);

        A();
        C();
        cone();

        if (mark10 == "i") {
            cout << "Wrong calculation --------------------------------" << endl;
            string doContinue;
            cout << "Do you want to continue? (Y/N): ";
            cin >> doContinue;
            if (doContinue != "Y") {
                continue;
            }
        }

        cout << "Total tan@ is: " << tana1 << mark10 << endl;
        cout << "or " << endl;
        cout << "Total tan@ is: " << tana2 << mark10 << endl;
        cout << "_____________________________________________________" << endl;
        cout << "Cone is: " << cone1 << mark10 << endl;
        cout << "Cone is: " << cone2 << mark10 << endl;
        cout << "_________Sometimes only one cone is correct_________" << endl;

        string loopC;
        cout << "\nRedo (Yes/y) or History (?): ";
        cin >> loopC;

        if (loopC == "Yes" || loopC == "y") {
            loop = true;
        } else if (loopC == "?") {
            cout << "\nHistory:\nHeight\tLength\tSpeed\tg\n";
            reeed();

            string clearHistory;
            cout << "Clear history? (Y): ";
            cin >> clearHistory;
            if (clearHistory == "Y") {
                ofstream f("report.txt", ios::trunc);
                f << x1 << "\t" << y1 << "\t" << u1 << "\t" << g1 << endl;
                f.close();
                reeed();
            }
        } else {
            loop = false;
            cout << "\nDone ----------------------------------------" << endl;
        }
    }

    return 0;
}

