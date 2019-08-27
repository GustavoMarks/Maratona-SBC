#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

int Particiona(int *a, int inicio, int fim)
{
    int pivo = a[fim];

    int P_index = inicio;
    int aux; 

    for (int i = inicio; i < fim; i++)
    {
        if (a[i] <= pivo)
        {
            aux = a[i];
            a[i] = a[P_index];
            a[P_index] = aux;
            P_index++;
        }
    }
    
    aux = a[fim];
    a[fim] = a[P_index];
    a[P_index] = aux;

    return P_index;
}
void Quicksort(int *a, int inicio, int final)
{
    if (inicio < final)
    {
        int q = Particiona(a, inicio, final);
        Quicksort(a, inicio, q - 1);
        Quicksort(a, q + 1, final);
    }
}

#endif