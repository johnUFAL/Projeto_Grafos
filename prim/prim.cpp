#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Vertice {
    int id; //cd v eh unico
    int key; //menor p entre u,v
    int pre; //predecessor na agm
};

struct Aresta {
    int u, v, p;
};

//comparação da fila de prioridade 
struct compararV {
    //ordena com operator
    //usa par pra ficar com dois valores juntos first e second
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; //min-heap
    }
};

int Prim(vector<vector<pair<int, int>>>& G, int n, int v0, vector<int>& pre, vector<int>& key) {
    int tot = 0;

    for (int i = 0; i < n; i++) {
        key[i] = numeric_limits<int>::max();
        pre[i] = -1;
    }

    key[v0] = 0;
    // fila prioridade min(v, key)
    priority_queue<pair<int, int>, vector<pair<int, int>>, compararV> F;
    //v na fila?
    vector<bool> NaFila(n, true);

    //todos os v na fila
    for (int i = 0; i < n; i++) {
        F.push({i, key[i]});
    }

    while (!F.empty()){
        int u = F.top().first;
        F.pop();
         
        if (!NaFila[u]) continue;
        NaFila[u] = false;

        //p total
        if (pre[u] != -1) {
            tot +=key[u];
        }

        //auto pra achar o tipo automaticamente
        for (auto& adj : G[u]) {
            int v = adj.first;
            int p = adj.second;

            //v na fila e p é nemor que o atual
            if (NaFila[v] && p < key[v]) {
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
    Prim(G, n, v_init, pre, key);

    int pTot = Prim(G, n, v_init, pre, key);
    
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