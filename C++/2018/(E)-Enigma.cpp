#include <iostream>
#include <string>

using namespace std;

int main(){
    string s1,s2;
    cin >> s1;
    cin >> s2;

    int ultimoIndexs1 = s1.length();
    int ultimoIndexs2 = s2.length();
    int resultado = 0;
    bool teste = true;

    //caso em que o tamanho das strings sao iguais
    if(ultimoIndexs2 == ultimoIndexs1){
        for(int i = 0; i < s1.length(); i++){
            if(s1[i] == s2[i]){
                teste = false;
                break;
            }
        }
        if(teste){
            resultado++;
        }
    }

    //caso em que o tamanho das strings sao diferentes
    int ind = 0;
    int ind2;
    while (ultimoIndexs2 <= ultimoIndexs1){
        ind2 = 0;
        teste = true;
        for(int i = ind ; i < ultimoIndexs2; i++){
            if(s1[i] == s2[ind2]){
                teste = false;
                break;
            }
            ind2++;
        }
        if(teste){
            resultado++;
        }
        ind++;
        ultimoIndexs2++;
    }

    cout << resultado << endl;
    return 0;
}
