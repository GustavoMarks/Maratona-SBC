#ifndef BFS_HPP
#define BFS_HPP

void BFS(Grafo *g, int s){

    for (auto i = g->vert.begin(); i != g->vert.end(); i++){
        i->SetCor("branco");
        i->SetDistancia(-1);
        i->SetPai(NULL);
    }
    g->vert[s].SetDistancia(0);
    g->vert[s].SetCor("cinza");

    int fila[g->v];
    //ponteiros para a fila
    int *prim = fila;
    int *ult = prim;
    *ult = s;
    ult++;
    
    while(prim != ult){
        int u = *prim;
        prim++;
        
        Aresta *e = g->adj[u];
        while(e != 0){
            if(g->vert[ e->GetDestino() ].GetCor() == "branco"){

                int d = g->vert[ e->GetDestino() ].GetDistancia();
                g->vert[ e->GetDestino() ].SetDistancia( d + 1);
                g->vert[e->GetDestino()].SetPai(u);
                g->vert[e->GetDestino()].SetCor("cinza");
                *ult = e->GetDestino();
                ult++;
                
            }
            e = e->prox;
        }
        g->vert[u].SetCor("preto");
    }
    
}


#endif