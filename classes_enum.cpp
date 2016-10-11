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
template <class T>
class Graph { // Não-direcionado
	
	Lista *adj;
	int ordem;//Ordem
	int tamanho;//tamanho
	int tempo;
	
	public:
	Graph(T ordem){
		initialize(ordem);
	} // construtor
	void initialize(T ordem){
		this->ordem = ordem;
    	adj = new Lista[ordem+1];
  	}
	T getOrdem(){
  		return this->ordem;
  	}
  	
	void makeWhite(){
		for(int i = 1; i <= ordem; i++){
			adj[i].setCor(branco);
		}
	}
	
	void makePiNull(){
		for(int i = 1; i <= ordem; i++){
			adj[i].setPi(NULL);
		}
	}
  	
	void insertEdge(Vertex v, Vertex u){
		Item *x = new Item(v); // chave = vértice
		adj[u].insere(x); // Insere na lista
		x = new Item (u);
		adj[v].insere(x); // Insere na lista
		tamanho++;
	}
	void print(){
		for (int i = 1; i <= ordem; i++) {
    		cout << "v[" << i << "] = ";
    		adj[i].print();
  		}
	}
	void destroy(){
		for (int i = 0; i <= ordem; i++) {
    		adj[i].destroy(); // destroi lista
  		}
  		delete(adj);
  		ordem = tamanho = 0;
	}
	
	void DSF(){
		makeWhite();
		makePiNull();
		this->tempo = 0;
		for(int i = 1; i <= ordem; i++){
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
		cout<<"dfs_visita:after"<<endl;
	}
// métodos get/set para n, m e adj.
};

// Função auxiliar
void testaGrafo() {
	
	Graph<int> g(5);
	
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
		void DSF(Graph<int> g){
			g.makeWhite();
			g.makePiNull();
			tempo = 0;
			for(int i = 1; i <= g.getOrdem(); i++){
				
			}
		}
};

template <class T>
class util{
	public:
		T* split(string str){
			
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
	util<int> u;
	int ordem;
	int tamanho;
	string entrada;
	
	
	cout << "Insira a ordem e o tamanho" <<endl;
	getline(cin, entrada);
	aux = u.split(entrada);
	ordem = aux[0];
	tamanho = aux[1];
	
	Graph<int> universo(ordem);
	
	for(int i = 0; i < tamanho; i++){
		cout<<"vertice 1 e 2" <<endl;
		getline(cin, entrada);
		aux = u.split(entrada);
		universo.insertEdge(aux[0], aux[1]);
	}
  	
  	universo.print();
  	universo.DSF();
  	return 0;

}
