#ifndef DFS_HPP
#define DFS_HPP

int tempo = 0;

/* ------------------------------------------------------------
Grafo implementado em uma lista de adjacencias, 
e um vetor de vertices que contem campos para a execução do DFS
------------------------------------------------------------ */
void DFSvisita(Grafo *g, int index){
    g->vert[index].SetCor("cinza");
    tempo = tempo + 1;
    g->vert[index].d = tempo;

    Aresta *e = g->adj[index];
    while(e != nullptr){
        if(g->vert[e->GetDestino()].GetCor() == "branco"){
            g->vert[e->GetDestino()].SetPai(index);
            DFSvisita(g, e->GetDestino());
        }
        e = e->prox;
    }
    g->vert[index].SetCor("preto");
    tempo = tempo + 1;
    g->vert[index].f = tempo;

}

int DFS(Grafo *g){
    for (int i = 0; i < g->v; i++){
        g->vert.push_back(Vertice("branco", NULL));
    }

    int index = 0;
    for (auto i = g->vert.begin(); i != g->vert.end(); i++, index++){
        if(i->cor == "branco"){
            DFSvisita(g, index);
        }
    }
}

#endif