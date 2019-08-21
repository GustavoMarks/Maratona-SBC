#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    cin >> s;

    string aux;
    
    //coloco na string aux as vogais
    for(int i = 0 ; i < s.length(); i++ ){
        if( s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'){
            aux.push_back(s[i]);
        }
    }

    string aux2;

    //crio a string aux2 com as vogais de tras pra frente
    for(auto it = aux.end() - 1; it != aux.begin() - 1; it--){
        aux2.push_back(*it);
    }

    //comparo se as strings sao iguais
    if(aux.compare(aux2) != 0){
        cout << "N" << endl;
    }
    else{
        cout << "S" << endl;
    }
}