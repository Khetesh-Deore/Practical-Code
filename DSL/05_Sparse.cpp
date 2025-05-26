#include <bits/stdc++.h>
using namespace std;

class Element {
public:
    int row;
    int col;
    int value;
};

class Sparse {
    Element element[100];
    int totalrow;
    int totalcol;
    int totalvalue;

public:
    void read();
    void display();
    void add(Sparse &result, Sparse b);
};

void Sparse::read() {
    cout << "Enter the no. of rows, cols, and total non-zero values: ";
    cin >> totalrow >> totalcol >> totalvalue;
    element[0].row = totalrow;
    element[0].col = totalcol;
    element[0].value = totalvalue;

    cout << "Enter non-zero elements (row col value):\n";
    for (int i = 1; i <= totalvalue; i++) {
        cin >> element[i].row >> element[i].col >> element[i].value;
    }
}

void Sparse::display() {
    cout << "Sparse Matrix:\nRow Col Value\n";
    for (int i = 0; i <= totalvalue; i++) {
        cout << element[i].row << " " << element[i].col << " " << element[i].value << "\n";
    }
}

void Sparse::add(Sparse &result, Sparse b) {
    if (!(totalrow == b.totalrow && totalcol == b.totalcol)) {
        cout << "Matrix sizes do not match.\n";
        return;
    }

    result.totalrow = totalrow;
    result.totalcol = totalcol;
	 result.element[0].row= totalrow;
    result.element[0].col= totalcol;

    int i = 1, j = 1, k = 1;

    while (i <= totalvalue && j <= b.totalvalue) {
        if (element[i].row == b.element[j].row && element[i].col == b.element[j].col) {
            result.element[k] = element[i];
            result.element[k].value += b.element[j].value;
            i++, j++, k++;
        } else if (
            element[i].row < b.element[j].row ||
            (element[i].row == b.element[j].row && element[i].col < b.element[j].col)) {
            result.element[k++] = element[i++];
        } else {
            result.element[k++] = b.element[j++];
        }
    }

    while (i <= totalvalue) result.element[k++] = element[i++];
    while (j <= b.totalvalue) result.element[k++] = b.element[j++];

    result.totalvalue = k - 1;
}

int main() {
    Sparse a, b, sum;

    cout << "Enter matrix A:\n";
    a.read();
    a.display();

    cout << "Enter matrix B:\n";
    b.read();
    b.display();

    a.add(sum, b);
    cout << "Sum of matrices:\n";
    sum.display();

    return 0;
}
