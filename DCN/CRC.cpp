#include <iostream>
#include <string>

using namespace std;

string xorOperation(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (tmp[0] == '1')
            tmp = xorOperation(divisor, tmp) + dividend[pick];
        else
            tmp = xorOperation(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    if (tmp[0] == '1')
        tmp = xorOperation(divisor, tmp);
    else
        tmp = xorOperation(string(pick, '0'), tmp);

    return tmp;
}

int main() {
    string data, divisor;
    cout << "Enter binary data: ";
    cin >> data;
    cout << "Enter generator (divisor): ";
    cin >> divisor;

    int m = divisor.length() - 1;
    string appendedData = data + string(m, '0');
    string remainder = mod2div(appendedData, divisor);
    string transmitted = data + remainder;

    cout << "Transmitted data: " << transmitted << endl;

    string received;
    cout << "Enter received data: ";
    cin >> received;

    string receivedRemainder = mod2div(received, divisor);
    if (receivedRemainder.find('1') != string::npos)
        cout << "Error detected in received data.\n";
    else
        cout << "No error detected in received data.\n";

    return 0;
}