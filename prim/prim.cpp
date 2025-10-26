#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

//comparação da fila de prioridade 
struct compararV {
    //ordena com operator
    //usa par pra ficar com dois valores juntos first e second
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; //min-heap
    }
};

int Prim(vector<vector<pair<int, int>>>& G, int n, int v0, vector<int>& pre) {
    vector<int> key(n, numeric_limits<int>::max());
    
    for (int i = 0; i < n; i++) {
        pre[i] = -1;
    }
    
    key[v0] = 0;
    // fila prioridade min(v, key)
    priority_queue<pair<int, int>, vector<pair<int, int>>, compararV> F;
    F.push({v0, 0});    
    
    int tot = 0;
    int v_processado = 0;

    //todos os v na fila
    for (int i = 0; i < n; i++) {
        F.push({i, key[i]});
    }

    while (!F.empty() && v_processado < n){
        int u = F.top().first;
        int w_u = F.top().second;
        F.pop();

        if(w_u > key[u]) continue;

        //p total
        if (pre[u] != -1 || u == v0) {
            tot +=key[u];
        }
        v_processado++;

        //auto pra achar o tipo automaticamente
        for (auto& adj : G[u]) {
            int v = adj.first;
            int p = adj.second;

            //p é nemor que o atual
            if (p < key[v]) {
                pre[v] = u;
                key[v] = p;
                F.push({v, key[v]});
            }
        }
    }
    return tot;
}

int main(int argc, char* argv[]) {
    string arquivo = "testee";
    int v_init = 0;
    bool solucao = false;

    //parametros
    for (int i = 1 ; i < argc; i++) {
                if (string(argv[i]) == "-f" && i+1 < argc) {
            arquivo = argv[++i];
        }
        else if (string(argv[i]) == "-i" && i+1 < argc) {
            v_init = stoi(argv[++i]) - 1;
        }
        else if (string(argv[i]) == "-s") {
            solucao = true;
        }
    }

    ifstream arq(arquivo);  //abrindo arquivo 
    if (!arq) {
        cerr << "erro ao abrir arquivo" << endl;
        return 1;
    }

    int n, m; //le primeira linha
    arq >> n >> m;

    
    vector<vector<pair<int, int>>> G(n);
    
    //lendo aresta
    for (int i = 0; i < m; i++) {
        int u, v, p;
        arq >> u >> v >> p;
        
        u--; v--;
        G[u].push_back({v, p});
        G[v].push_back({u, p});
    }
    arq.close();

    //armazenar pre e key
    vector<int> pre(n);
    vector<int> key(n);
    Prim(G, n, v_init, pre);

    int pTot = Prim(G, n, v_init, pre);
    
    if (solucao) {
        for (int i = 1; i < n; i++) {
            if (pre[i] != -1) {
                cout << "(" << pre[i] + 1 << "," << i + 1 << ") ";
            }
        }
        cout << endl;
    } else {
        cout << pTot << endl;
    }
    
    return 0;
}