#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Aresta {
    int u, v, p;
    //construtor: quando criar u,v,p guardar em u,v,p
    Aresta(int u, int v, int p) 
    : u(u), v(v), p(p) 
    {}

    //pra ordenar aretas, compara pelo menos o peso
    bool operator<(const Aresta& other) const {
        return p < other.p;
    }
};


//Disjoint Set Union, gerencia coloeções de conjutnos que não se sobrepoe
struct DSU {
    vector<int> par, sz;

    //cria um novo conj
    void make_set(int n) {  
        //ajusta tamanhos para n+1
        par.resize(n+1);
        sz.resize(n+1, 1);
        for (int i = 1; i <= n; i++) par[i] = i;
    }

    //encontra o representante de um conj
    int find(int x) {
        return x == par[x] ? x : par[x] = find(par[x]);
    }

    //mescla dois conj
    bool union_set(int x, int y) {
        x= find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }
};

class Kruskal {
    private: 
        vector<Aresta> e;
        int n, m;

    public:
        void grafo(const string& arq) {
            ifstream file(arq);
            if (!file.is_open()) {
                cerr << "Erro ao abrir arquivo " << arq << endl;
                exit(1);
            }
            
            file >> n >> m;
            for (int i = 0; i < m; i++) {
                int u, v, p;
                file >> u >> v >> p;
                e.push_back(Aresta(u, v, p));
            }
            file.close();
        }

        int AGM(bool solucao) {
            //ordena entrada por custo
            sort(e.begin(), e.end());

            //cada v começa isolado
            DSU dsu;
            dsu.make_set(n); 
            int custo = 0;
            vector<Aresta> agm;

            //constroi a aresta
            for (const auto& aresta : e) {
                if (dsu.union_set(aresta.u, aresta.v)) {
                    custo += aresta.p;
                    agm.push_back(aresta);
                }

            }
            
            if (solucao) {
                for (size_t i = 0; i < agm.size(); i++) {
                    cout << "(" << agm[i].u << "," << agm[i].v << ")";
                    if (i < agm.size() - 1) cout << " ";
                }
                cout << endl;
            }
            return custo;
        }
};

//f. para as tags
void ajuda() {
    cout << "Uso: ./kruskal [parametros]" << endl;
    cout << "Parametros:" << endl;
    cout << " -h          Mostrar esta ajuda" << endl;
    cout << " -f <arquivo> Arquivo de entrada com o grafo" << endl;
    cout << " -s          Mostrar a solucao" << endl;
    cout << " -o <arquivo> Arquivode saida" << endl;
}

int main(int argc, char* argv[]) {
    string arquivo;
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
        else if (string(argv[i]) == "-s") {
            solucao = true;
        }
        else if (string(argv[i]) == "-o" && i + 1 < argc) {
            saida = argv[++i];
        }
    }

    if (arquivo.empty()) {
        cerr << "erro ao abrir arquivo" << endl;
        return 1;
    }

    Kruskal kruskal;
    kruskal.grafo(arquivo);

    int custo = kruskal.AGM(solucao);

    //se tiver um arq de saida espeficico
    if (!saida.empty()) {
        ofstream out(saida);
        if (out.is_open()) {
            out << custo << endl;
            out.close();
        }
    } else if (!solucao) {
        cout << custo << endl;
    }
    
    return 0;
}