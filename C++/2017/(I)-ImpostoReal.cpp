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
    Aresta *prox; //para a list de adj

    Aresta(int origem, int destino, int peso);
    int GetPeso();
    int GetOrigem();
    int GetDestino();
};
Aresta::Aresta(int origem, int destino, int peso){
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
    this->prox = nullptr;
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
    int v; //numero de vertices
    Aresta **adj; //lista de adjacencias
    vector<Vertice> vert; //vetor com os vertices, e propriedades que serao usadas no dfs

    Grafo(int v);
    void adicionarAresta(Aresta *e);
    void imprimirGrafo();
};
Grafo::Grafo(int v){
    this->v = v;
    this->adj = new(nothrow) Aresta*[v];
    for(int i = 0; i < v; i++){
        this->adj[i] = nullptr;
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
        while (p != nullptr)
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

int CapaciCarga;

int contadorFinal = 0;

int tempo = 0;

void DFSvisita(Grafo *g, int index, int pesoAresta_pai){
    g->vert[index].SetCor("cinza");
    tempo = tempo + 1;
    g->vert[index].d = tempo;

    Aresta *e = g->adj[index];
    while(e != nullptr){
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
    while(teste && index != 0){
        if(pImpCidades[index] - CapaciCarga <= 0){
            pImpCidades[g->vert[index].GetPai()] += pImpCidades[index];
            pImpCidades[index] = 0;
            contadorFinal += pesoAresta_pai;
            teste = false;
        }
        else{
            pImpCidades[index] = pImpCidades[index] - CapaciCarga;
            pImpCidades[g->vert[index].GetPai()] += CapaciCarga;
            contadorFinal += 2*pesoAresta_pai;
        }
    }
}

int DFS(Grafo *g){
    for (int i = 0; i < g->v; i++){
        g->vert.push_back(Vertice("branco", NULL));
    }

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

    CapaciCarga = C; //variavel global para ser udada no dfs

    //vetor com os impostos das cidades
    int ImpCidades[N];
    for(int i = 0; i < N; i++)
    {
        cin >> ImpCidades[i];
    }
    pImpCidades = ImpCidades; //ponteiro global apontando para o vetor


    Grafo *g = new Grafo(N);

    //criando as arestas do grafo
    for (int  i = 0; i < N - 1; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;
        Aresta *arestaIda = new Aresta(A, B, C);
        g->adicionarAresta(arestaIda);
        Aresta *arestaVolta = new Aresta(B, A, C);
        g->adicionarAresta(arestaVolta);
    }

    //chamada do dfs, onde vai ocorrer o calculo do percuso
    DFS(g);

    //g->imprimirGrafo();

    cout << contadorFinal << endl;



}
