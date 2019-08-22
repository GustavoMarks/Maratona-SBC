#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class Vertice{
public:
    int x, y;

    Vertice(int x, int y);
    int GetX();
    int GetY();
};
Vertice::Vertice(int x, int y){
    this->x = x;
    this->y = y;
}
int Vertice::GetX(){
    return this->x;
}
int Vertice::GetY(){
    return this->y;
}


class Aresta{
public:
    int origem;
    int destino;
    float peso;
    Aresta *prox; //para a list de adj

    Aresta(int origem, int destino, float peso);
    int GetOrigem();
    int GetDestino();
    int GetPeso();
};
Aresta::Aresta(int origem, int destino, float peso){
    this->origem = origem;
    this->destino = destino;
    this->peso = peso;
    this->prox = nullptr;
}
int Aresta::GetOrigem(){
    return this->origem;
}
int Aresta::GetDestino(){
    return this->destino;
}
int Aresta::GetPeso(){
    return this->peso;
}


class Grafo{
public:
    int v; //numero de vertices
    vector<Vertice> vert; //vetor com os vertices, e suas coordenadas
    Aresta **adj; //lista de adjacencias

    Grafo(int v);
    void AddVertice(int x, int y);
    void AddAresta(Aresta *e);
};
Grafo::Grafo(int v){
    this->v = v;
    this->adj = new Aresta*[v];
    for(int i = 0; i < v; i++){
        adj[i] = nullptr;
    }
}
void Grafo::AddVertice(int x, int y){
    this->vert.push_back(Vertice(x, y));
}
void Grafo::AddAresta(Aresta *e){
    e->prox = this->adj[e->GetOrigem()];
    this->adj[e->GetOrigem()] = e;
}


float resultado = 0;

//funcao que calcula e cria uma aresta com a menor distancia entre uma capital e as cidade
//OBS no vetor de vertices os indices de 0 a k-1 sao capitais e k a n-1 sao cidades
void CalcularArestaCapitais_Cidades(Grafo *g, int N, int K){
    float menordist;
    int vertDestino;

    //visitando todas as capitais
    for(int i = 0; i < K; i++){

        float menordist = 0;
        //visitando todas as cidades e calculando a cidade mais proxima da capital
        for(int j = K; j < N; j++){
            float distCalculada = sqrt( pow( g->vert[i].GetX() - g->vert[j].GetX() , 2) + pow( g->vert[i].GetY() - g->vert[j].GetY() , 2) );
            if(menordist == 0 || menordist > distCalculada){
                menordist = distCalculada;
                vertDestino = j; // guardando a cidade atualmente mais proxima
            }
        }
        
        //ao final, crio na minha lista de adj as arestas de ida e volta entre a capital e cidade mais proxima
        Aresta *e = new Aresta(i, vertDestino, menordist);
        g->AddAresta(e);
        Aresta *e2 = new Aresta(vertDestino, i, menordist);
        g->AddAresta(e2);
        
        resultado += menordist; //somando ao resultado final o peso da aresta

    }
}

/* funcao que calcula e cria uma aresta com a menor distancia entre uma cidade ja ligada a uma capital
a outra cidade tambem ja ligada a uma capital */
void CalcularArestaCidades_Cidades(Grafo *g, int N, int K){

    float menordist;
    int vertDestino;

    //visitando as cidades (que nao sao capitais)
    for(int i = K; i < N; i++){
        float menordist = 0;
        
        //visitando as outras cidades
        for(int j = K; j < N; j++){

            if(j != i && g->adj[j] != nullptr){ // if eu nao estiver com a mesma cidade e a cidade visitada ja tiver arestas(ligadas a capitais)
                
                bool teste = true;

                //verificando se ja tenho aresta entre as cidades para evitar erro na conectividade
                Aresta *e = g->adj[j];
                while(e != nullptr){
                    if(e->GetDestino() == i){
                        teste = false;
                        break;
                    }
                    e = e->prox; 
                }

                if(teste){
                    float distCalculada = sqrt( pow( g->vert[i].GetX() - g->vert[j].GetX() , 2) + pow( g->vert[i].GetY() - g->vert[j].GetY() , 2) );
                    if(menordist == 0 || menordist > distCalculada){
                        menordist = distCalculada;
                        vertDestino = j;
                    }
                }
            }
        }

        //ao final, crio na minha lista de adj as arestas de ida e volta entre uma cidade e outra cidade mais proxima
        Aresta *e = new Aresta(i, vertDestino, menordist);
        g->AddAresta(e);
        Aresta *e2 = new Aresta(vertDestino, i, menordist);
        g->AddAresta(e2);
        
        resultado += menordist; //somando ao resultado final o peso da aresta
    }
}

int main(){
    int N, K;
    cin >> N >> K;

    Grafo *g = new Grafo(N);

    //setando precisao de 5 casas decimais
    cout << fixed << setprecision(5);
    
    //criando os vertices
    for(int i = 0; i < N; i++){
        int x, y;
        cin >> x >> y;
        g->AddVertice(x, y);
    }

    CalcularArestaCapitais_Cidades(g, N, K);

    CalcularArestaCidades_Cidades(g, N, K);
    
    //talvez bfs p contagem

    cout << resultado << endl;

}