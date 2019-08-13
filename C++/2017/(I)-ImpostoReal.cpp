#include <iostream>
#include <vector>
#include <string>
#include <new>
using namespace std;

class Aresta{
public:
    int origem;
    int destino;
    int peso;
    Aresta *prox;

    Aresta(int origem, int destino, int peso);
    int GetPeso();
    int GetOrigem();
    int GetDestino();
};
Aresta::Aresta(int origem, int destino, int peso){
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
    this->prox = 0; // 0
}
int Aresta::GetPeso(){
    return this->peso;
}
int Aresta::GetOrigem(){
    return this->origem;
}
int Aresta::GetDestino(){
    return this->destino;
}


class Vertice{
public:
    string cor;
    int pai;
    int f;
    int d;

    Vertice(string cor, int pai);
    void SetCor(string cor);
    void SetPai(int pai);
    string GetCor();
    int GetPai();
};
Vertice::Vertice(string cor, int pai){
    this->cor = cor;
    this->pai = pai;
}
void Vertice::SetCor(string cor){
    this->cor = cor;
}
void Vertice::SetPai(int pai){
    this->pai = pai;
}
string Vertice::GetCor(){
    return this->cor;
}
int Vertice::GetPai(){
    return this->pai;
}


class Grafo{
public:
    int v;
    Aresta **adj;
    vector<Vertice> vert;


    Grafo(int v);
    void adicionarAresta(Aresta *e);
    void imprimirGrafo();
};
Grafo::Grafo(int v){
    this->v = v;
    this->adj = new(nothrow) Aresta*[v];
    for(int i = 0; i < v; i++){
        this->adj[i] = 0; // 0
    }
    for (int i = 0; i < this->v; i++){
        //Vertice *vertex = new Vertice("branco", NULL);
        this->vert.push_back(Vertice("branco", NULL));
    }

}
void Grafo::adicionarAresta(Aresta *e){
    e->prox = this->adj[e->GetOrigem() - 1];
    this->adj[e->GetOrigem() - 1] = e;
}
void Grafo::imprimirGrafo(){
    for (int i = 0; i < this->v; i++)
    {
        Aresta *p = this->adj[i];
        cout << "index: " << i << endl;
        while (p != 0) //0
        {
            cout << p->GetOrigem() << endl;
            cout << p->GetDestino() << endl;
            cout << p->GetPeso() << endl;
            p = p->prox;
        }
        cout << "--------------------" << endl;
    }
}


int *pImpCidades;

int *p_C;

int contadorFinal = 0;

int tempo = 0;

void DFSvisita(Grafo *g, int index, int pesoAresta_pai){
    g->vert[index].SetCor("cinza");
    tempo = tempo + 1;
    g->vert[index].d = tempo;

    Aresta *e = g->adj[index];
    while(e != 0){
        if(g->vert[e->GetDestino() - 1].GetCor() == "branco"){
            g->vert[e->GetDestino() -1].SetPai(index);
            contadorFinal += e->GetPeso();
            DFSvisita(g, e->GetDestino() - 1, e->GetPeso());
        }
        e = e->prox;
    }
    g->vert[index].SetCor("preto");
    tempo = tempo + 1;
    g->vert[index].f = tempo;

    bool teste = true;
    while(teste){

        if(pImpCidades[index] - *p_C <= 0){
            pImpCidades[g->vert[index].GetPai()] += pImpCidades[index];
            pImpCidades[index] = 0;
            contadorFinal += pesoAresta_pai;
            teste = false;
        }
        else{
            pImpCidades[index] = pImpCidades[index] - *p_C;
            pImpCidades[g->vert[index].GetPai()] += *p_C;
            contadorFinal += 2*pesoAresta_pai;
        }

    }

}
int DFS(Grafo *g){
    int index = 0;

    for (vector<Vertice>::iterator i = g->vert.begin(); i != g->vert.end(); i++, index++){
        if(i->cor == "branco"){
            DFSvisita(g, index, 0);
        }
    }
}




int main(){
    int N, C;
    cin >> N >> C;

    p_C = &C;

    int ImpCidades[N];
    for(int i = 0; i < N; i++)
    {
        cin >> ImpCidades[i];
    }
    pImpCidades = ImpCidades;



    Grafo *g = new Grafo(N);

    for (int  i = 0; i < N - 1; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        Aresta *arestaIda = new Aresta(A, B, C);
        g->adicionarAresta(arestaIda);
        Aresta *arestaVolta = new Aresta(B, A, C);
        g->adicionarAresta(arestaVolta);
    }

    DFS(g);

    //g->imprimirGrafo();

    cout << contadorFinal << endl;



}
