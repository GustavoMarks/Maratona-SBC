#include <iostream>
#include <algorithm>
#include <vector>

int main(){
    int n, c;
    std::cin >> n;
    std::cin >> c;

    int i = 0;
    std::vector<int> A;
    while (i < n){
        int m;
        std::cin >> m;
        A.push_back(m);
        i++;
    }

    std::sort (A.begin(), A.end());

    std::vector<int> B;

    for(std::vector<int>::iterator it = A.end() -1 ; it != A.begin() - 1; it--){
        B.push_back(*it);
    }

    if(B[c - 1] =! B[c]){
        std::cout << c << std::endl;
    } else{
        int i = 1;
        while(B[c] == B[c + i] && (c + i) <= n ){
            i++;
        }
        std::cout << i + c << std::endl;
    }

    return 0;
}
