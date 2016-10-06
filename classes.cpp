#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef int Vertex;

class Item {
private:
    Vertex valor;

public:
    Item() {};
    Item(int valor): valor(valor) { }

    int getVertex() {
        return valor;
    }
 
    void setVertex(int valor) {
        this -> valor = valor;
    }
    void print(){
    	cout << getVertex() << " ";
    }
};

class No {
public:
	Item *item;
    No *prox;

    No() {}

    Item* getItem() {
        return item;
    }

    void setItem(Item *item) {
        this -> item = item;
    }

    No* getProx() {
        return prox;
    }

    void setProx(No *prox) {
        this->prox = prox;
    }
};

class Lista{
private:
	No *prim, *ult;
public:
	No* getPrim(){
		return prim;
	}

	No* getUlt(){
		return ult;
	}
	Lista(){
		prim = new No(); // cabeça
	    prim -> setProx(NULL);
    	ult = prim;
	}
	void insere(Item* x){
		ult->setProx(new No());
		ult = ult->prox;
		ult->prox = NULL;
		ult->item = x;
	}

	void print(){
		No* p = getPrim()->getProx();
		while(p != NULL){
			p->getItem()->print();
		    p = p->prox;
		}
		cout << endl;
	}
	
	void destroy(){
		No* p = getPrim()->getProx();
    	while(p != NULL){
      		delete(p);
    	}
    	p = p->prox;
	}
};

class Graph { // Não-direcionado
	
	Lista *adj;
	int n, m; // ordem e tamanho
	
	public:
	Graph(int n){
		initialize(n);
	} // construtor
	void initialize(int n){
		this->n = n;
    	adj = new Lista[n+1]; 
  	}
  	
	void insertEdge(Vertex v, Vertex u){
		Item *x = new Item(v); // chave = vértice
		adj[u].insere(x); // Insere na lista
		x = new Item (u);
		adj[v].insere(x); // Insere na lista
		m++;
	}
	void print(){
		for (int i = 1; i <= n; i++) {
    		cout << "v[" << i << "] = ";
    		adj[i].print();
  		}
	}
	void destroy(){
		for (int i = 0; i <= n; i++) {
    		adj[i].destroy(); // destroi lista
  		}
  		delete( adj );
  		n = m = 0;
	}
// métodos get/set para n, m e adj.
};

// Função auxiliar
void testaGrafo(Graph &g) {
  g.insertEdge(1, 2);
  g.insertEdge(2, 3);
  g.insertEdge(3, 4);
  g.insertEdge(4, 5);
  g.insertEdge(5, 1);
  g.insertEdge(5, 2);
  g.insertEdge(2, 4);
  g.print();
}

int main(int argc, const char * argv[]) {
  
  int n, m;
  
  cout << "ordem: "; cin >> n;
  Graph g(n);
  cout << "-----grafo-----" << endl;
  testaGrafo(g);

  return 0;

}
