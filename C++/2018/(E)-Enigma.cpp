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

    int ind = 0; 
    int indvetor;
    while (ultimoIndexs2 <= ultimoIndexs1){
        indvetor = 0; //indice para posicao no vetor
        teste = true;
        //deslocando os indices na string1 para a comparacao com a string2
        for(int i = ind ; i < ultimoIndexs2; i++){ 
            if(s1[i] == s2[indvetor]){
                teste = false;
                break;
            }
            indvetor++;
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
