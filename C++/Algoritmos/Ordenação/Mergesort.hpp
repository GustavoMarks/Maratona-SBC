#ifndef MERGESORT_HPP
#define MERGESORT_HPP

//complexidade O(nlogn)

void merge(int vetor[], int vetorAux[], int comeco, int meio, int fim){
    int esq, dir;
    esq = comeco;
    dir = meio;

    for(int i=comeco; i < fim; i++){
        if(esq < meio && (dir >= fim || vetor[esq] < vetor[dir])){
            vetorAux[i] = vetor[esq];
            esq++;
        } else {
            vetorAux[i] = vetor[dir];
            dir++;
        }
    }

    for(int i = comeco; i < fim; i++){
        vetor[i] = vetorAux[i];
    }

}


void mergeSort(int vetor[], int vetorAux[], int comeco, int fim){
    if(fim - comeco < 2) return;

    int meio = (comeco + fim)/2;
    mergeSort(vetor, vetorAux, comeco, meio);
    mergeSort(vetor, vetorAux, meio, fim);
    merge(vetor, vetorAux, comeco, meio, fim);
}

#endif