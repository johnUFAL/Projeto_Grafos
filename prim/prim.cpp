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

int Prim(vector<vector<pair<int, int>>>& G, int n, int v0, vector<int>& pre, vector<pair<int, int>>& agm_edges) {
    vector<int> key(n, numeric_limits<int>::max());
    vector<bool> in_agm(n, false);

    for (int i = 0; i < n; i++) {
        pre[i] = -1;
    }
    
    key[v0] = 0;
    // fila prioridade min(v, key)
    priority_queue<pair<int, int>, vector<pair<int, int>>, compararV> F;
    F.push({v0, 0});    
    
    int tot = 0;
    agm_edges.clear();

    while (!F.empty()){
        int u = F.top().first;
        int w_u = F.top().second;
        F.pop();

        if(in_agm[u]) continue;

        in_agm[u] = true;
        tot += w_u;

        //p total
        if (pre[u] != -1) {
            agm_edges.push_back({min(pre[u], u), max(pre[u], u)});
        }

        //auto pra achar o tipo automaticamente
        for (auto& adj : G[u]) {
            int v = adj.first;
            int p = adj.second;

            //p é nemor que o atual
            if (!in_agm[v] && p < key[v]) {
                pre[v] = u;
                key[v] = p;
                F.push({v, key[v]});
            }
        }
    }
    return tot;
}
 //f. para as tags
void ajuda() {
    cout << "Uso: ./prim -f <arquivo> [-i <vertice>] [-s] [-o <saida]" << endl;
    cout << "Parametros:" << endl;
    cout << " -h          Mostrar esta ajuda" << endl;
    cout << " -f <arquivo> Arquivo de entrada com o grafo" << endl;
    cout << " -i <vertice> Vertice inicial" << endl;
    cout << " -s          Mostrar a AGM" << endl;
    cout << " -o <arquivo> Arquivode saida" << endl;
}

int main(int argc, char* argv[]) {
    string arquivo = "";
    int v_init = 0;
    bool solucao = false;
    string saida = "";

    //parametros
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
        else if (string(argv[i]) == "-s") {
            solucao = true;
        }
        else if (string(argv[i]) == "-o" && i + 1 < argc) {
            saida = argv[++i];
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

    //armazenar pre e key
    vector<int> pre(n);
    vector<pair<int, int>> agm_edges;

    int pTot = Prim(G, n, v_init, pre, agm_edges);
    
    sort(agm_edges.begin(), agm_edges.end());

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

    if (solucao) {
        for (size_t i = 0; i < agm_edges.size(); i++) {
            *output << "(" << agm_edges[i].first + 1 << "," << agm_edges[i].second + 1 << ")";
            if (i < agm_edges.size() - 1) *output << " ";
        }
        *output << endl;
    } else {
        *output << pTot << endl;
    }
    
    if (out_file.is_open()) {
        out_file.close();
    }
    
    return 0;
}