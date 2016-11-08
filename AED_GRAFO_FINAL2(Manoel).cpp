#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef int Vertex;

enum Cor{
	branco,
	cinza,
	preto
};

template <class T>
class Item{
	private:
		T valor;
		Item *prox;
		T *raiz;
	public:
		
		Item(T valor){
			this->valor = valor;
			this->raiz = &valor;
			
			prox = NULL;
		}
		Item(){
			
		}
		T getValor(){
			return this->valor;
		}
		Item* getProx(){
			return prox;
		}
		void setValor(T valor){
			this->valor = valor;
		}
		void setProx(Item *item){
			this->prox = item;
		}		
		bool contem(T elemento, T no){
			if(no == NULL){
				return false;
			}
			else if(elemento == no){
				return true;
			}else{
				contem(elemento, no.getProx());	
			}
		}
		void retira(T v){
			T *aux = acha(v, *raiz);
			
			if(*aux != *raiz){
				aux->setProx(aux->getProx()->getProx());
				aux->getProx()->setProx(NULL);
			}else{
				raiz = acha(v, *raiz);
				
				T auxiliar = *raiz;
				
				raiz->setProx(NULL);

				raiz = auxiliar.getProx();
			}
		}
		T acha(T elemento, T no){		
			
			if(contem(elemento, *raiz)){
			
				if(elemento == no.getProx()){
					return no;
					
				}else if(elemento == no){
					return no;
					
				}else{
					acha(elemento, no);
				}
			}
		}
		T *getVerticeEm(int posicao){					
			
			return getVerticeEmAux(posicao, 0);
		}
		int getVerticeEmAux(int num, int i){
			
			if(contem(num, *raiz)){
				if(i == num){
					return this->valor;
				}else{
					getVerticeEmAux(num, ++i);
				}
			}
			return 0;
		}	
		T *getVerticeDe(int num){						 
			return acha(num, *raiz);	
		}		
};

template <class T>
class Fila{
	private:
		
		T *items;
		T *frente;
		T *tras;
		
		int tam;
		int tamAbsoluto;
		
	public:
		
		void cria(int tam){
			this->items = (T*) malloc(sizeof(T) * tam);
			
			for(int i = 0; i < tam; i++){
				items[i].setValor(-1);
			}
			
			this->tras = items;
			this->tamAbsoluto = tam;
			this->tam = 0; 
		}
		
		bool vazia(){
			return (this->tam == 0);
		}
		
		void enfileira(T item){
			this->tam++;
			this->tras++;
			this->tras->setValor(item.getValor());
		
			this->tras->setProx(NULL);
		}
		
		int desenfileira(){

			T item;

			int saida = this->items[1].getValor();
			
			desaloque(this->items);
			
			this->tam--;
			this->tras--;
			
			return saida;
		}
		
		int getTam(){
			return this->tam;
		}
		
		void setTam(int tam){
			this->tam = tam;
		}
		
		void desaloque(T items[]){
			T aux[this->tamAbsoluto];
			
			for(int i = 0; i < tamAbsoluto; i++)
				aux[i] = items[i];
			
			for(int i = 1; i < tamAbsoluto; i++)
				items[i-1] = aux[i];
		}
};

template <class T>
class Vertice{
	private:
		int valor;
		
		int adjI[100];
		float dist[100];
		
		Vertice *pai;
		
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
		
		void setPai(Vertice *pai){
			this->pai = pai;
		}
		
		Vertice* getPai(){
			return pai;
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
		
		T* getVerticeEm(int position){
			return &lista[position];
		}
		
		void retiraUltimo(){
		
			lista[cont] = NULL;
			cont--;
		
		}
		
		int getTam(){
			return cont;
		}
};

template <class T>
class Graph{
	private:
		
		int ordem;
		int tamanho;
		int tempo;
		
		Lista<T> lista;
		
		float *inimigos;
		float custo;
	public:
		
		Graph(int ordem){
			tempo = 0;
			this->ordem = ordem;
			custo = 0;
		}
		
		int getOrdem(){
			return ordem;
		}
		
		void insertEdge(Vertex v, Vertex u, float dist){
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
			
			vertU->adicionaVertice(vertV, dist);
			vertV->adicionaVertice(vertU, dist);
		}

		void printTemp(){
			for(int i = 0; i < ordem; i++){
			
				cout << "[" << lista.getVerticeEm(i)->getValor() << "] = ";
				lista.getVerticeEm(i)->printAdj();
			
			}
		}
		
		Lista<T>* getListaVertices(){
			return &lista;
		}
		
		T* getVerticeDe(int num){
			return lista.getVerticeDe(num);
		}
		
		void DFS(){
			for(int i = 0; i < getOrdem(); i++){
			
				lista.getVerticeEm(i)->setCor(branco);
				lista.getVerticeEm(i)->setPai(NULL);
			
			}
			for(int i = 0; i < getOrdem(); i++){
			
				if(lista.getVerticeEm(i)->getCor() == branco){
					DFS_VISITA(lista.getVerticeEm(i));
			
				}
			}
		}
		
		void DFS_VISITA(Vertice<Cor> *u){
			
			int *listaAdj;
			
			listaAdj = getVerticeDe(u->getValor())->getAdjI();
			
			tempo++;
			
			getVerticeDe(u->getValor())->setD(tempo);
			getVerticeDe(u->getValor())->setCor(cinza);	

			for(int i = 0; i < u->getQtddVertice();i++){
			
				if(getVerticeDe(listaAdj[i])->getCor() == branco){
			
					getVerticeDe(listaAdj[i])->setPai(getVerticeDe(u->getValor()));
			
					custo += getVerticeDe(u->getValor())->getDistanciaPara(listaAdj[i]);
			
					DFS_VISITA(getVerticeDe(listaAdj[i]));
			
				}
			}
			
			getVerticeDe(u->getValor())->setCor(preto);
			
			tempo++;
			
			getVerticeDe(u->getValor())->setF(tempo);
		}
		
		void pintaInimigo(float* inimigos){
			
			int i = 1;
			
			while(inimigos[i] != -1){
			
				getVerticeDe(inimigos[i])->setCor(preto);
				i++;
			
			}
		}
		
		int* BFS(Vertice<Cor> *s, int ult, float *inimigos){
			
			Fila< Item<int> > fila;
			
			int u;
			int *listaAdj;
			int cont = 0;
			int contAux;
			int *saida;
			
			saida = new int[100];
			
			fila.cria(200);
			
			for(int i = 0; i < getOrdem(); i++){
			
				lista.getVerticeEm(i)->setCor(branco);
				lista.getVerticeEm(i)->setPai(NULL);
				lista.getVerticeEm(i)->setD(-1);
			
			}
			
			pintaInimigo(inimigos);
			
			getVerticeDe(s->getValor())->setCor(cinza);
			getVerticeDe(s->getValor())->setD(0);
			getVerticeDe(s->getValor())->setPai(NULL);
			
			Item<int> aux;
			
			aux.setValor(s->getValor());
			
			fila.enfileira(aux);
			
			while(fila.getTam() > 0){
			
				u = fila.desenfileira();
			
				listaAdj = getVerticeDe(u)->getAdjI();
				
				for(int i = 0; i < getVerticeDe(u)->getQtddVertice();i++){
			
					if(getVerticeDe(listaAdj[i])->getCor() == branco){
			
						getVerticeDe(listaAdj[i])->setCor(cinza);
						getVerticeDe(listaAdj[i])->setD(getVerticeDe(getVerticeDe(u)->getValor())->getD() + 1);
						getVerticeDe(listaAdj[i])->setPai(getVerticeDe(u));
			
						aux.setValor(getVerticeDe(listaAdj[i])->getValor());
			
						fila.enfileira(aux);
			
						if(getVerticeDe(listaAdj[i])->getValor() == ult){
			
							cont = getVerticeDe(listaAdj[i])->getD();
							contAux = cont + 1;
			
							int auxVertice = getVerticeDe(listaAdj[i])->getValor();
			
							while(cont >= 0){
			
								saida[cont] = getVerticeDe(auxVertice)->getValor();
			
								if(getVerticeDe(auxVertice)->getPai() != NULL){
			
									auxVertice = getVerticeDe(auxVertice)->getPai()->getValor();	
								}
			
								cont--;
							}
			
							saida[contAux] = -1;
			
							return saida;
						}
					}
				}
				getVerticeDe(u)->setCor(preto);
			}
			return saida;
		}
		
		void cores(){
			getVerticeDe(1)->getCor();
			getVerticeDe(2)->getCor();
			getVerticeDe(3)->getCor();
			
		}
		
		float getCusto(){
			return custo;
		}
};

template <class T>
class Util{
	private:
	public:
		T* split(string str){
			int cont = 0;
			int p = 0;
			
			float *saida = new float[10];
			string aux;
			
			aux = str.at(str.length()-1);
			if(aux != " "){
				str = str + " ";
			}
			
			while(str.length() > 0){
				aux = str.at(p);
				if(aux == " "){
					saida[cont] = atof(str.substr(0, p).c_str());
					str = str.substr(p+1);
					cont++;
					p = 0;
				}
				p++;
			}
			saida[cont] = -1;
			return saida;
		}
		
		bool estaEm(int num, int *lista){
			int i = 0;
			while(lista[i] != -1){
				if(lista[i] == num){
					return true;
				}
				i++;
			}
			return false;
		}
	
};

int main(int argc, const char * argv[]) {

	Util<float> util;
	string entrada;
	
	int cont;
	
	int ordem;
	int tamanho;
	int ordemAux;
	int tamanhoAux;
	float *aux;
	float *inimigos;
	int sistInic;
	int sistFinal;
	int *caminho;
	float totalCusto = 0;
	
	getline(cin, entrada);
	aux = util.split(entrada);
	ordem = aux[0];
	tamanho = aux[1];
	
	Graph<Vertice<Cor> > universo(ordem);
	
	for(int i = 0; i < tamanho; i++){
		getline(cin, entrada);
		aux = util.split(entrada);
		universo.insertEdge(aux[0], aux[1], 0);
	}
	
	getline(cin, entrada);
	inimigos = util.split(entrada);
	
	getline(cin, entrada);
	aux = util.split(entrada);
	sistInic = aux[0];
	sistFinal = aux[1];
	
	caminho = universo.BFS(universo.getVerticeDe(sistInic), sistFinal, inimigos);
	
	cont = 0;
	for(int i = 1; i <= ordem; i++){

		getline(cin, entrada);
		aux = util.split(entrada);
		ordemAux = aux[0];
		tamanhoAux = aux[1];
		
		Graph<Vertice<Cor> > graphAux(ordemAux);
		
		for(int j = 0; j < tamanhoAux; j++){
			getline(cin, entrada);
			aux = util.split(entrada);
			graphAux.insertEdge(aux[0], aux[1], aux[2]);
		}
		
		if(util.estaEm(i, caminho) == true){
			graphAux.DFS();
			totalCusto += graphAux.getCusto();
		}
		cont++;
	}
	cout << totalCusto << ".0";
}