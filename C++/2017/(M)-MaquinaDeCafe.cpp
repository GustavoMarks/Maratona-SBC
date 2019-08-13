#include <iostream>
 
using namespace std;
 
int main() {
 
    int a1, a2, a3;
    int melhortemp;
    cin >> a1;
    cin >> a2;
    cin >> a3;

    int andar1 = a2 * 2 + a3 * 4;
    int andar2 = a1 * 2 + a3 * 2;
    int andar3 = a1 * 4 + a2 * 2;

    melhortemp = andar1;
    
    if(andar2 < melhortemp) melhortemp = andar2;
    if(andar3 < melhortemp) melhortemp = andar3;

    cout << melhortemp << endl;
 
    return 0;
}