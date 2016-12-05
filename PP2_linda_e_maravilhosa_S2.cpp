#include <iostream>
#include <cstdlib>
#include <vector>


#define MAX 10000

using namespace std;

typedef int Vertex;

enum Cor{
	preto,
	branco,
	cinza
};

template <class T>
class Vertice{
	private:
		int valor;
		int adjI[100];
		float dist[100];
		Vertice *pi;
		int d;
		int f;
		int cont;
		T cor;

	public:
		
		Vertice(){
			cont = 0;
		}
		
		float getDistanciaPara(int num){
			for(int i = 0; i < cont; i++){
				if(adjI[i] == num){ 
					return dist[i];
				}
			}
			return 0;
		}
		
		void setValor(int valor){
			this->valor = valor;
		}
		
		void setPi(Vertice *pi){
			this->pi = pi;
		}
		
		Vertice* getPi(){
			return pi;
		}
		
		void setCor(T cor){
			this->cor = cor;
		}
		
		T getCor(){	
			return cor;
		}
		
		int getValor(){
			return valor;
		}
		
		void setD(int d){
			this->d = d;
		}
		
		int getD(){
			return d;
		}
		
		void setF(int f){
			this->f = f;
		}
		
		int getF(){
			return f;
		}
		
		void adicionaVertice(Vertice *v, float dist){
			bool estaNaLista = false;
			for(int i = 0; i < cont; i++){
				if(v->getValor() == adjI[i]){
					estaNaLista = true;
				}
			}
			if(estaNaLista == false){
				adjI[cont] = v->getValor();
				this->dist[cont] = dist;
				cont++;	
			}
		}
		
		int getQtddVertice(){
			return cont;
		}
		
		int* getAdjI(){
			return adjI;
		}
		
};

template <class T>
class Lista{
	private:
		T lista[100];
		int cont;
	public:
		
		Lista(){
			cont = 0;
		}
		
		void insere(T v){
			lista[cont] = v;
			cont++;
		}
	
		T getPrimeiro(){
			return lista[0];
		}
	
		void selectSort(){
			int min;
			T aux;
			for(int i=0; i < getTam()-1; i++){
				
				min = i;
				
				for(int j = i + 1; j< getTam();j++){
					if(lista[j].getPeso() < lista[min].getPeso()){
						min = j;
					}
				}
				
				if(min != i){
					aux = lista[i];
					lista[i] =lista[min];
					lista[min] = aux;
				}
			}
		}
				
		bool contem(int num){
			for(int i = 0; i < cont; i++){
				if(lista[i].getValor() == num){
					return true;
				}
			}
			return false;
		}
		
		T* getVerticeDe(int num){
			for(int i = 0; i < cont; i++){
				if(lista[i].getValor() == num){
					return &lista[i];
				}
			}
			return 0;
		}
		
		T* getIntDe(int num){
			for(int i = 0; i < cont; i++){
				if(lista[i] == num){
					return &lista[i];
				}
			}
			return 0;
		}
		
		T* getVerticeEm(int position){
			return &lista[position];
		}
		
		void retiraUltimo(){
			lista[cont] = NULL;
			cont--;
		}
		
		void retira(int num){
			for(int i = 0; i < cont; i++){
				if(lista[i] == num){
					lista[i] = -1;
				}
			}
		}
		
		int getTam(){
			return cont;
		}
		bool estaVazia(){
			for(int i = 0; i < cont; i++){
				if(lista[i] != -1){
					return false;
				}
			}
			return true;
		}
};

template <class T>
class Aresta{
	private:
		int origem;
		int destino;
		float peso;
		bool ehValido;
	public:
		void setAresta(T origem, T destino, float peso){
			this->origem = origem;
			this->destino = destino;
			this->peso = peso;
		}
		
		void setEhValido(bool ehValido){
			this->ehValido = ehValido;
		}
		
		float getPeso(){
			return peso;
		}
		
		int* getOrigem(){
			return &origem;
		}
		
		int* getDestino(){
			return &destino;
		}
};

template <class T>
class Graph{
	private:
	
		int ordem;
		int tamanho;
	
		int tempo;
		int nArestas;
		
		Lista<T> lista;
		Lista< Aresta<int> > arestas;
		
		float custo;
	
	
	public:
		Graph(int ordem, int tamanho){
			tempo = 0;
			this->ordem = ordem;
			//custo = 0;
		}
		
		int getOrdem(){
			return ordem;
		}
		
		void insertEdge(Vertex v, Vertex u, float dist){
			if(lista.contem(v) == false){
				Vertice<int> v1;
			
				v1.setValor(v);
				lista.insere(v1);
			}
			if(lista.contem(u) == false){
				Vertice<int> v2;
			
				v2.setValor(u);
				lista.insere(v2);
			}
			
			if(v != u){
				nArestas++;
					
				T *vertV = lista.getVerticeDe(v);
				T *vertU = lista.getVerticeDe(u);
				
				vertV->adicionaVertice(vertU, dist);
				vertU->adicionaVertice(vertV, dist);
				
				Aresta<int> aux;
				
				aux.setAresta(v, u, dist);
				arestas.insere(aux);
				
				aux.setAresta(u, v, dist);
				arestas.insere(aux);
			}
			
		}
		
		Lista< Aresta<T> > getArestas(){
			return this->arestas;
		}
		
		Lista<T>* getListaVertices(){
			return &lista;
		}
		
		T* getVerticeDe(int num){
			return lista.getVerticeDe(num);
		}
		
		T* getVerticeEm(int num){
			return lista.getVerticeEm(num);
		}		
		int getNArestas(){
			return this->nArestas;
		}
		
		void MSTPrim(int primeiro){
			
			Graph<Vertice<Vertex> > arvore(ordem, tamanho);
			
			Lista<int> dentro;
			Lista<int> fora;
			
			dentro.insere(primeiro);
			
			for(int i = 0; i < getOrdem(); i++){
				int valorAux = lista.getVerticeEm(i)->getValor();
				if(valorAux != primeiro){
					fora.insere(valorAux);
				}
			}
			
			while(fora.estaVazia() == false){
				Lista<Aresta <int> > candidatas;
				for(int i = 0; i < dentro.getTam(); i++){
					for(int j = 0; j < fora.getTam(); j++){
						for(int l = 0; l < arestas.getTam(); l++){
							if(*dentro.getVerticeEm(i) == *arestas.getVerticeEm(l)->getOrigem() && *fora.getVerticeEm(j) == *arestas.getVerticeEm(l)->getDestino()){
								candidatas.insere(*arestas.getVerticeEm(l));
							}
						}
					}
				}
				candidatas.selectSort();
				dentro.insere(*candidatas.getPrimeiro().getDestino());
				fora.retira(*candidatas.getPrimeiro().getDestino());
				
				arvore.insertEdge(*candidatas.getPrimeiro().getOrigem(), *candidatas.getPrimeiro().getDestino(), candidatas.getPrimeiro().getPeso());
			}

			custo = arvore.DFS();
			std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
			std::cout.precision(2);
			std::cout << custo;
		}
		
		float DFS(){
			custo = 0;
			for(int i = 0; i < getOrdem(); i++){
				lista.getVerticeEm(i)->setCor(branco);
				lista.getVerticeEm(i)->setPi(NULL);
			}
			for(int i = 0; i < getOrdem(); i++){
				if(lista.getVerticeEm(i)->getCor() == branco){
					DFS_VISITA(lista.getVerticeEm(i));
				}
			}
			return custo;
		}
		
		void DFS_VISITA(Vertice<int> *u){
			
			int *listaAdj;
			listaAdj = getVerticeDe(u->getValor())->getAdjI();
			tempo++;
			getVerticeDe(u->getValor())->setD(tempo);
			getVerticeDe(u->getValor())->setCor(cinza);	

			for(int i = 0; i < u->getQtddVertice();i++){
				if(getVerticeDe(listaAdj[i])->getCor() == branco){
					getVerticeDe(listaAdj[i])->setPi(getVerticeDe(u->getValor()));
					custo += getVerticeDe(u->getValor())->getDistanciaPara(listaAdj[i]);
					DFS_VISITA(getVerticeDe(listaAdj[i]));
				}
			}
			getVerticeDe(u->getValor())->setCor(preto);
			tempo++;
			getVerticeDe(u->getValor())->setF(tempo);
		}		
};

int main(int argc, const char * argv[]) {
	
	int ordem, tamanho, u, v, infectoso;
	float peso;
	
	cin>> ordem;
	cin>> tamanho;
	
	Graph<Vertice<Vertex> > pacientes(ordem, tamanho);
	
	for(int i=0; i< tamanho; i++){
		cin >> u;
		cin >> v;
		cin >>peso;
		pacientes.insertEdge(u, v, peso);
	}
	
	cin>>infectoso;

	pacientes.MSTPrim(infectoso);
}
