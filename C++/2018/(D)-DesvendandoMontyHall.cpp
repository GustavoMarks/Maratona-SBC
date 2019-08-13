#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> v;
    
    //pegando os valores e inserindo no final do vetor
    for(int i = 0; i < n; i++){
        int m;
        cin >> m;
        v.push_back(m);
    }
    //contando as entradas diferentes de 1
    int resultado = 0;
    for(auto it = v.begin(); it != v.end(); it++){
        if(*it != 1){
            resultado++;
        }
    }
    cout << resultado << endl;
    
    return 0;
}