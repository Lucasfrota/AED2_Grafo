#include <iostream>
#include <cstdlib>
#include <vector>

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
		Vertice *pi;
		int d;
		int f;
		int cont = 0;
		T cor;
	public:
		void setValor(int valor){
			this->valor = valor;
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
		
		void setPi(Vertice *pi){
			this->pi = pi;
		}
		
		Vertice* getPi(){
			return pi;
		}
		
		void setCor(T cor){
			switch(cor){//retirar depois
				case 0: cout<< "colocando cor: preto" <<endl;  
					break;
				case 1:cout<< "colocando cor: branco" <<endl; 
					break;
				case 2:cout<< "colocando cor: cinza" <<endl; 
					break;
			}
			this->cor = cor;
		}
		
		T getCor(){
			switch(this->cor){//retirar switch depois
				case 0: cout<< "preto" <<endl;  
					break;
				case 1:cout<< "branco" <<endl; 
					break;
				case 2:cout<< "cinza" <<endl; 
					break;
			}	
			return cor;
		}
		
		int getValor(){
			return valor;
		}
		
		void adicionaVertice(Vertice *v){
			adjI[cont] = v->getValor();
			cont++;
		}
		
		int getQtddVertice(){
			return cont;
		}
		
		int* getAdjI(){
			return adjI;
		}
		
};


template <class T>
class ListaVertice{
	private:
		T lista[100];
		int cont = 0;
	public:
		
		void insere(T v){
			lista[cont] = v;
			cont++;
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
		}
		
		T* getVerticeEm(int position){
			return &lista[position];
		}
		
		void print(){
			for(int i = 0; i < cont; i++){
				cout << lista[i].getValor() <<"\n";
			}
		}
		
		T* getLista(){
			return &lista[100];
		}
		
};

template <class T>
class Graph{
	public://mudar depois
		int ordem;
		int tamanho;
		int tempo;
		ListaVertice<T> lista;
	public:
		Graph(int ordem){
			tempo = 0;
			this->ordem = ordem;
		}
		
		int getOrdem(){
			return ordem;
		}
		
		void insertEdge(int v, int u){
			if(lista.contem(v) == false){
				Vertice<Cor> v1;
				v1.setValor(v);
				lista.insere(v1);
			}
			if(lista.contem(u) == false){
				Vertice<Cor> v2;
				v2.setValor(u);
				lista.insere(v2);
			}
			T *vertV = lista.getVerticeDe(v);
			T *vertU = lista.getVerticeDe(u);
			
			vertU->adicionaVertice(vertV);
			vertV->adicionaVertice(vertU);
		}
		
		void printTemp(){//apagar mais tarde
			for(int i = 0; i < ordem; i++){
				cout << "[" << lista.getVerticeEm(i)->getValor() << "]= ";
				lista.getVerticeEm(i)->printAdjs();
			}
			
		}
		
		ListaVertice<T>* getListaVertices(){
			return &lista;
		}
		
		T* getVerticeDe(int num){
			return lista.getVerticeDe(num);
		}
		
		void DFS(){
			for(int i = 0; i < getOrdem(); i++){
				lista.getVerticeEm(i)->setCor(branco);
				lista.getVerticeEm(i)->setPi(NULL);
			}
			DFS_VISITA(getVerticeDe(1));
		}
		
		void DFS_VISITA(Vertice<Cor> *u){
			int *listaAdj;
			listaAdj = getVerticeDe(u->getValor())->getAdjI();
			cout << "\n-----" << u->getValor() << "---- ABRE\n";
			tempo++;
			getVerticeDe(u->getValor())->setD(tempo);
			getVerticeDe(u->getValor())->setCor(cinza);	

			for(int i = 0; i < u->getQtddVertice();i++){
				if(getVerticeDe(listaAdj[i])->getCor() == branco){
					getVerticeDe(listaAdj[i])->setPi(u);
					DFS_VISITA(getVerticeDe(listaAdj[i]));
				}
			}
			tempo++;
			getVerticeDe(u->getValor())->setF(tempo);
			getVerticeDe(u->getValor())->setCor(preto);
			
			cout << "\n-----" << u->getValor() << "---- FECHA\n";
		}
		
		void cores(){//isso aparentemente prova que isso funciona
			getVerticeDe(1)->getCor();
			getVerticeDe(2)->getCor();
			getVerticeDe(3)->getCor();
		}
		
		
};


int main(int argc, const char * argv[]) {
	Graph<Vertice<Cor> > a(3);

	//teste 1
	
	a.insertEdge(1, 2);
	a.insertEdge(2, 3);
	a.insertEdge(3, 1);
	
	//teste 2
	/*
	a.insertEdge(1, 2);
	a.insertEdge(1, 3);
	a.insertEdge(1, 4);
	a.insertEdge(3, 5);
	a.insertEdge(5, 6);
	a.insertEdge(5, 7);
	*/
	
	//teste3
	/*
	a.insertEdge(1, 2);
	a.insertEdge(1, 3);
	a.insertEdge(1, 5);
	a.insertEdge(2, 4);
	a.insertEdge(3, 4);
	a.insertEdge(3, 5);
	a.insertEdge(3, 6);
	*/

	
	a.DFS();
	a.cores();
	
}
