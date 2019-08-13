#include <iostream>

using namespace std;

int main() {
    int A, B, C;
    cin >> A >> B >> C;

    if(A == B || B == C || C == A){
        cout << "S" << endl;
        return 0;
    }
    if(A + B == C || B + C == A || C + A == B) {
        cout << "S" << endl;
        return 0;
    }
    cout << "N" << endl;

    return 0;
}
