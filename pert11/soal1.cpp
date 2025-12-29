#include <iostream>
using namespace std;

int main() {
    int n;
    long long faktorial = 1;

    cout << "Masukkan n: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        faktorial *= i;
    }

    cout << n << "! = " << faktorial << endl;

    return 0;
}
