#include <iostream>
using namespace std;

long long faktorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * faktorial(n - 1);
}

int main() {
    int n;
    cout << "Masukkan n: ";
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cout << i << "! = " << faktorial(i) << endl;
    }

    return 0;
}