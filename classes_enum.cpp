#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef int Vertex;

enum Cor { preto, branco, cinza };

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
//  No *pi;
//	string cor;

    No() {}

    Item* getItem() {
        return item;
    }

    void setItem(Item *item) {
        this -> item = item;
    }
    
    /*
    void setCor(string cor){
    	this->cor = cor;
    }
    
    string getCor(){
    	return this->cor;
    }
    */

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
	Lista *pi;
	//string cor;	
	Cor cor;
	
public:
	
	void setCor(Cor cor){
    	this->cor = cor;
    }
    
    void setPi(Lista *pi){
    	this->pi = pi;
    }
    
    Cor getCor(){
    	return this->cor;
    }
    
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
      		p = p->prox;
    	}
	}
};

class Graph { // Não-direcionado
	
	Lista *adj;
	int n;//Ordem
	int m;//tamanho
	int tempo;
	
	public:
	Graph(int n){
		initialize(n);
	} // construtor
	void initialize(int n){
		this->n = n;
    	adj = new Lista[n+1];
  	}
	int getOrdem(){
  		return this->n;
  	}
  	
	void makeWhite(){
		for(int i = 1; i <= n; i++){
			adj[i].setCor(branco);
		}
	}
	
	void makePiNull(){
		for(int i = 1; i <= n; i++){
			adj[i].setPi(NULL);
		}
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
  		delete(adj);
  		n = m = 0;
	}
	
	void DSF(){
		makeWhite();
		makePiNull();
		this->tempo = 0;
		for(int i = 1; i <= n; i++){
			if(adj[i].getCor() == branco){
				DFS_VISITA(adj[i]);
			}
		}
	}
	
	void DFS_VISITA(Lista adj){
		int d;
		int f;
		this->tempo++;
		d = this->tempo;
		adj.setCor(cinza);
		No* p = adj.getPrim()->getProx();
		while(p != NULL){
			if(this->adj[p->getItem()->getVertex()].getCor() == branco){
				this->adj[p->getItem()->getVertex()].setPi(&adj);
				DFS_VISITA(this->adj[p->getItem()->getVertex()]); 
			}
			adj.setCor(preto);
			this->tempo++;
			f = this->tempo;
			p = p->prox;
		}
	}
// métodos get/set para n, m e adj.
};

// Função auxiliar
void testaGrafo() {
	
	Graph g(5);
	
	g.insertEdge(1, 2);
	g.insertEdge(2, 3);
	g.insertEdge(3, 4);
	g.insertEdge(4, 5);
	g.insertEdge(5, 1);
	g.insertEdge(5, 2);
	g.insertEdge(2, 4);
	g.print();
}

class busca{
	private:
		int tempo;
	public:
		void DSF(Graph g){
			g.makeWhite();
			g.makePiNull();
			tempo = 0;
			for(int i = 1; i <= g.getOrdem(); i++){
				
			}
		}
};

class util{
	public:
		int* split(string str){
			
			int cont = 0;
			int p = 0;
			int len = str.length();
			
			int *saida = new int[3];
			string aux;
			
			aux = str.at(str.length()-1);
			if(aux != " "){
				str = str + " ";
			}
			
			while(str.length() > 0){
				aux = str.at(p);
				if(aux == " "){
					saida[cont] = atoi(str.substr(0, p).c_str());
					str = str.substr(p+1);
					cont++;
					p = 0;
				}
				p++;
			}
			
			return saida;
		}
	
};

int main(int argc, const char * argv[]) {
	
	/*
 	int n;//provavelmente inutil...
	int m;
	*/
	int *aux;
	util u;
	int ordem;
	int tamanho;
	string entrada;
	  
	getline(cin, entrada);
	aux = u.split(entrada);
	ordem = aux[0];
	tamanho = aux[1];
	
	Graph universo(ordem);
	
	for(int i = 0; i < tamanho; i++){
		getline(cin, entrada);
		aux = u.split(entrada);
		universo.insertEdge(aux[0], aux[1]);
	}
  	
  	universo.print();
  	universo.DSF();
  	return 0;

}
