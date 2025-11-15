#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

void ajuda() {
    cout << "Uso: ./kosaraju -f <arquivo> [-o <saida]" << endl;
    cout << "Parametros:" << endl;
    cout << " -h          Mostrar esta ajuda" << endl;
    cout << " -f <arquivo> Arquivo de entrada com o grafo" << endl;
    cout << " -o <arquivo> Arquivode saida" << endl;
}

void dfs1(int u, vector<vector<int>>& G, vector<bool>& visitado, stack<int>& ordem) {
    stack<pair<int, int>> p;
    p.push({u, 0});
    visitado[u] = true;

    while(!p.empty()) {
        auto &top = p.top();
        int v = top.first;
        int &indice = top.second;

        if (indice < (int)G[v].size()) {
            int w = G[v][indice];
            indice++;
            if (!visitado[w]) {
                visitado[w] = true;
                p.push({w, 0});
            }
        } else {
            p.pop();
            ordem.push(v);
        }
    }
}

void dfs2(int u, vector<vector<int>>& GT, vector<bool>& visitado, vector<int>& comp) {
    stack<int> p;
    p.push(u);
    visitado[u] = true;
    comp.push_back(u+1); //pra indice começando em 1
    
    while(!p.empty()) {
        int v = p.top();
        p.pop();
        
        for (int w : GT[v]) {
            if (!visitado[w]) {
                visitado[w] = true;
                p.push(w);
                comp.push_back(w+1); 
            }
        }
    }
}


vector<vector<int>> Kosaraju(vector<vector<int>>& G, vector<vector<int>>& GT, int n) {
    stack<int> ordem;
    vector<bool> visitado(n, false);
    vector<vector<int>> comps;

    //DFS 1
    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            dfs1(i, G, visitado, ordem);
        }
    }

    //Grafo transposto DFS 2
    fill(visitado.begin(), visitado.end(), false);

    while (!ordem.empty()) {
        int u = ordem.top();
        ordem.pop();

        if (!visitado[u]) {
            vector<int> comp;
            dfs2(u, GT, visitado, comp);
            comps.push_back(comp);
        }
    }
    return comps;
}

int main(int argc, char* argv[]) {
    string arquivo, saida = "";
    bool solucao = false;

    //parametros
    for (int i = 1 ; i < argc; i++) {
        if (string(argv[i]) == "-h") {
            ajuda();
            return 0;
        }
        else if (string(argv[i]) == "-f" && i+1 < argc) {
            arquivo = argv[++i];
        }
        else if (string(argv[i]) == "-o" && i + 1 < argc) {
            saida = argv[++i];
            solucao = true;
        }
    }

    if (arquivo.empty()) {
        cerr << "Arquivo de entrada nao especificado." << endl;
        ajuda();
        return 1;
    }

    ifstream arq(arquivo);  //abrindo arquivo 
    if (!arq) {
        cerr << "Erro ao abrir arquivo." << arquivo << endl;
        return 1;
    }

    int n, m; //le primeira linha
    arq >> n >> m;
    
    vector<vector<int>> G(n), GT(n);

    //lendo aresta
    for (int i = 0; i < m; i++) {
        int u, v;
        arq >> u >> v;
        
        u--; v--;
        G[u].push_back(v);
        GT[v].push_back(u); //transposto
    }
    arq.close();

    vector<vector<int>> comps = Kosaraju(G, GT, n);

    //pra ordenar a saida 
    for (auto &c : comps) sort(c.begin(), c.end());
    sort(comps.begin(), comps.end(), [](auto &a, auto &b){
        return a[0] < b[0];
    });
    
    ostream *out = &cout;
    ofstream fout;
    if (solucao) {
        fout.open(saida);
        if (!fout) {
            cerr << "Erro ao criar a saida: " << saida << endl;
            return 1;
        }
        out = &fout;
    }

    for (const auto &comp : comps) {
        for (size_t j = 0; j < comp.size(); j++) {
            *out << comp[j];
            if (j < comp.size() - 1) *out << " ";
        }
        *out << endl;
    }

    if (solucao) fout.close();

    return 0;
}