#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct compararV {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; //min-heap
    }
};


void Dijkstra(vector<vector<pair<int, int>>>& G, int n, int v0, vector<int>& dist, vector<int>& pre) {
    for (int i = 0; i < n; i++) {
        dist[i] = numeric_limits<int>::max();
        pre[i] = -1;
    }

    dist[v0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, compararV> F;
    F.push({v0, 0});

    while (!F.empty()) {
        int u = F.top().first;
        int d_u = F.top().second;
        F.pop();

        //evita processamento desnecessario
        if(d_u > dist[u]) continue;

        for (auto& adj : G[u]) {
            int v = adj.first;
            int w_uv = adj.second;

            if (dist[u] + w_uv < dist[v]) {
                dist[v] = dist[u] + w_uv;
                pre[v] = u;
                F.push({v, dist[v]});
            }
        }
    }
}


//f. para as tags
void ajuda() {
    cout << "Uso: ./dijkstra -f <arquivo> -i <vertice> [-s] [-o <saida>]" << endl;
    cout << "Parametros:" << endl;
    cout << " -h          Mostrar esta ajuda" << endl;
    cout << " -f <arquivo> Arquivo de entrada com o grafo" << endl;
    cout << " -i <vertice> Vertice inicial (OBRIGATORIO)" << endl;
    cout << " -o <arquivo> Arquivode saida" << endl;
}

int main(int argc, char* argv[]) {
    string arquivo = "";
    int v_init = -1;
    bool solucao = false;
    string saida = "";

    //processar argumentos
    for (int i = 1 ; i < argc; i++) {
        if (string(argv[i]) == "-h") {
            ajuda();
            return 0;
        }
        else if (string(argv[i]) == "-f" && i+1 < argc) {
            arquivo = argv[++i];
        }
        else if (string(argv[i]) == "-i" && i+1 < argc) {
            v_init = stoi(argv[++i]) - 1;
        }
        else if (string(argv[i]) == "-o" && i + 1 < argc) {
            saida = argv[++i];
        }
    }

    if (arquivo == "" || v_init == -1) {
        cerr << "Parametros obrigatorios faltando. Use -h para ajuda." << endl;
        return 1;
    }

    //ler grafo do arquivo
    ifstream arq(arquivo);   
    if (!arq) {
        cerr << "erro ao abrir arquivo" << arquivo << endl;
        return 1;
    }

    int n, m; 
    arq >> n >> m; 
    
    vector<vector<pair<int, int>>> G(n);
    
    //lendo aresta
    for (int i = 0; i < m; i++) {
        int u, v, p;
        arq >> u >> v >> p;

        u--; v--;
        G[u].push_back({v, p});
        G[v].push_back({u, p});  //grafo nao direcionado
    }
    arq.close();

    //executar dijkstra
    vector<int> dist(n);
    vector<int> pre(n);
    Dijkstra(G, n, v_init, dist, pre);
    
    if (solucao) {
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            if (dist[i] == numeric_limits<int>::max()) {
                cout << i + 1 << ":-1";
            } else {
                cout << i + 1 << ":" << dist[i];
            }
        }
        cout << endl;
    } else {
        //formato v0:0, v1:di...
        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            if (dist[i] == numeric_limits<int>::max()) {
                cout << i + 1 << ":-1 ";
            } else {
                cout << i + 1 << ":" << dist[i];
            }
        }
        cout << endl;
    }
    
    return 0;
}