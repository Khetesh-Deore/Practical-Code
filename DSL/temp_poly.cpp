#include<iostream>
using namespace std;

class Polynomial {
    int poly[100][2]; // Each term: [coefficient][exponent]
    int terms;

public:
    void accept_polynomial();
    void display_polynomial();
    void add_polynomial(Polynomial &p2);
};

void Polynomial::accept_polynomial() {
    cout << "\nEnter number of terms in the polynomial: ";
    cin >> terms;

    for (int i = 0; i < terms; i++) {
        cout << "Enter coefficient and exponent for term " << i + 1 << ": ";
        cin >> poly[i][0] >> poly[i][1];
    }
}

void Polynomial::display_polynomial() {
    cout << "\nPolynomial: ";
    for (int i = 0; i < terms; i++) {
        cout << poly[i][0] << "x^" << poly[i][1];
        if (i != terms - 1) cout << " + ";
    }
    cout << endl;
}

void Polynomial::add_polynomial(Polynomial &p2) {
    int result[100][2];
    int i = 0, j = 0, k = 0;

    while (i < terms && j < p2.terms) {
        if (poly[i][1] == p2.poly[j][1]) {
            result[k][0] = poly[i][0] + p2.poly[j][0];
            result[k][1] = poly[i][1];
            i++; j++; k++;
        }
        else if (poly[i][1] > p2.poly[j][1]) {
            result[k][0] = poly[i][0];
            result[k][1] = poly[i][1];
            i++; k++;
        }
        else {
            result[k][0] = p2.poly[j][0];
            result[k][1] = p2.poly[j][1];
            j++; k++;
        }
    }

    while (i < terms) {
        result[k][0] = poly[i][0];
        result[k][1] = poly[i][1];
        i++; k++;
    }

    while (j < p2.terms) {
        result[k][0] = p2.poly[j][0];
        result[k][1] = p2.poly[j][1];
        j++; k++;
    }

    cout << "\nResultant Polynomial after Addition: ";
    for (int t = 0; t < k; t++) {
        cout << result[t][0] << "x^" << result[t][1];
        if (t != k - 1) cout << " + ";
    }
    cout << endl;
}

int main() {
    Polynomial p1, p2;
    int choice;

    do {
        cout << "\n------- Polynomial Menu -------";
        cout << "\n1. Enter First Polynomial";
        cout << "\n2. Enter Second Polynomial";
        cout << "\n3. Display First Polynomial";
        cout << "\n4. Display Second Polynomial";
        cout << "\n5. Add Polynomials";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                p1.accept_polynomial();
                break;

            case 2:
                p2.accept_polynomial();
                break;

            case 3:
                p1.display_polynomial();
                break;

            case 4:
                p2.display_polynomial();
                break;

            case 5:
                p1.add_polynomial(p2);
                break;

            case 0:
                cout << "\nExiting program.\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
