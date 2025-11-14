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

void ajuda() {
    cout << "Uso: ./dijkstra -f <arquivo> [-i <vertice>] [-o <saida>]" << endl;
    cout << "Parametros:" << endl;
    cout << " -h          Mostrar esta ajuda" << endl;
    cout << " -f <arquivo> Arquivo de entrada com o grafo" << endl;
    cout << " -i <vertice> Vertice inicial (padrao: 1)" << endl;
    cout << " -o <arquivo> Arquivo de saida" << endl;
}

int main(int argc, char* argv[]) {
    string arquivo = "";
    int v_init = 0;  
    string saida = "";

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

    if (arquivo == "") {
        cerr << "Arquivo de entrada nao especificado. Use -h para ajuda." << endl;
        return 1;
    }

    ifstream arq(arquivo);   
    if (!arq) {
        cerr << "Erro ao abrir arquivo " << arquivo << endl;
        return 1;
    }

    int n, m; 
    arq >> n >> m; 
    
    vector<vector<pair<int, int>>> G(n);
    
    for (int i = 0; i < m; i++) {
        int u, v, p = 1;
        arq >> u >> v;
        
        if (arq.peek() != '\n' && arq.peek() != EOF && arq.peek() != '\r') {
            arq >> p; 
        }

        u--; v--;
        G[u].push_back({v, p});
        G[v].push_back({u, p});
    }
    arq.close();

    vector<int> dist(n);
    vector<int> pre(n);
    Dijkstra(G, n, v_init, dist, pre);
    
    ostream* output = &cout;
    ofstream out_file;
    
    if (!saida.empty()) {
        out_file.open(saida);
        if (!out_file) {
            cerr << "Erro ao criar arquivo de saida: " << saida << endl;
            return 1;
        }
        output = &out_file;
    }
    
    for (int i = 0; i < n; i++) {
        if (i > 0) *output << " ";
        if (dist[i] == numeric_limits<int>::max()) {
            *output << (i + 1) << ":-1";
        } else {
            *output << (i + 1) << ":" << dist[i];
        }
    }
    *output << endl;
    
    if (out_file.is_open()) {
        out_file.close();
    }
    
    return 0;
}