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


//contem os campos para a execucao do dfs
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
    this->v = v; //setando o numero de vertices
    this->adj = new(nothrow) Aresta*[v]; //criando a lista de adjacencias
    //apontando para nullo todos os ponteiros da lista de adj 
    for(int i = 0; i < v; i++){
        this->adj[i] = nullptr;
    }
}
void Grafo::adicionarAresta(Aresta *e){
    //ponteiro do 'noh' aresta apontando para onde o ponteiro na lista esta apontando
    e->prox = this->adj[e->GetOrigem() - 1];
    //ponteiro da lista apontando para a aresta
    this->adj[e->GetOrigem() - 1] = e;

    /*IMPORTANTE: Na questao os vertice comecam de 1 ate n, mas como os indices dos vetores
    comecam em 0, foi decidido subtrair 1 das entradas dos vertice para relacionar os indices dos
    vetores com os vertices*/
}
//metodo para exibir a lista de adjacencias 
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

//variaveis globais usadas no dfs
int *pImpCidades;
int CapaciCarga;
int contadorFinal = 0;
int tempo = 0;

//DFSvisita recebe o grafo, o vertice, e o peso da aresta que incide no pai
void DFSvisita(Grafo *g, int index, int pesoAresta_pai){
    g->vert[index].SetCor("cinza");
    tempo = tempo + 1;
    g->vert[index].d = tempo;

    //visitando as adjacencias do vertice na lista
    Aresta *e = g->adj[index];
    while(e != nullptr){
        /* se o vertice vizinho for branco, vou visitalo setando o seu pai
        e somando o peso da aresta percorrida */
        if(g->vert[e->GetDestino() - 1].GetCor() == "branco"){
            g->vert[e->GetDestino() -1].SetPai(index);
            contadorFinal += e->GetPeso();
            DFSvisita(g, e->GetDestino() - 1, e->GetPeso());
        }
        e = e->prox; //passando para o proximo vizinho
    }
    g->vert[index].SetCor("preto");
    tempo = tempo + 1;
    g->vert[index].f = tempo;

    //contagem do caminho percorrido para a arrecadacao de todo o dinheiro
    bool teste = true;
    while(teste && index != 0){

        /* se o dinheiro a ser arrecadado for menor ou igual a carga, 
        soh preciso colocar o dinheiro no cofre do pai e somar o percurso de volta */  
        if(pImpCidades[index] <= CapaciCarga){
            pImpCidades[g->vert[index].GetPai()] += pImpCidades[index];
            pImpCidades[index] = 0;
            contadorFinal += pesoAresta_pai;
            teste = false;
        }
        else{ // senao, preciso pegar tudo que posso, deixar no cofre do pai e voltar enquanto nao quitar, somando o percurso
            pImpCidades[index] = pImpCidades[index] - CapaciCarga;
            pImpCidades[g->vert[index].GetPai()] += CapaciCarga;
            contadorFinal += 2*pesoAresta_pai;
        }
    }
}

int DFS(Grafo *g){
    //inicilizacao do dfs
    for (int i = 0; i < g->v; i++){
        g->vert.push_back(Vertice("branco", NULL));
    }

    //visitando todos os vertices brancos
    int index = 0; //o indice do vetor eh o vertice
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

    for (int  i = 0; i < N - 1; i++)
    {
        int A, B, C;
        cin >> A >> B >> C;

        //criando as arestas do grafo
        Aresta *arestaIda = new Aresta(A, B, C);
        g->adicionarAresta(arestaIda);
        Aresta *arestaVolta = new Aresta(B, A, C); //o grafo nao eh direcionado, logo preciso setar a aresta de volta
        g->adicionarAresta(arestaVolta);
    }

    //chamada do dfs, onde vai ocorrer o calculo do percuso
    DFS(g);

    //g->imprimirGrafo();

    cout << contadorFinal << endl;

}
