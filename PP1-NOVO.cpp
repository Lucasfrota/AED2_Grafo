#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Vertice{
	public://mudar depois
		int valor;
		//Vertice *adj;
		int adjI[100];
		Vertice *pi;
		int d;
		int f;
		int cont = 0;
		string cor;
	public:
		void setValor(int valor){
			this->valor = valor;
			//adj = new Vertice[100];
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
		
		void setCor(string cor){
			this->cor = cor;
		}
		
		string getCor(){
			return cor;
		}
		
		int getValor(){
			return valor;
		}
		
		void adicionaVertice(Vertice *v){
			adjI[cont] = v->getValor();
			//adj[cont] = *v;
			cont++;
		}
		
		void printAdjs(){
			for(int i = 0; i < cont; i++){
				//cout << adj[i].getValor() <<" ";
			}
			cout << "\n";
		}
		
		/*
		Vertice* getAdjs(){//ver se eh realmente necessaria depois 
			return adj;
		}
		*/
		
		int getQtddVertice(){
			return cont;
		}
		
		int* getAdjI(){
			return adjI;
		}
		
};

class ListaVertice{
	private:
		Vertice lista[100];// = new Vertice[100];
		int cont = 0;
	public:
		
		void insere(Vertice v){
			cout << "helo world\n";
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
		
		Vertice* getVerticeDe(int num){
			for(int i = 0; i < cont; i++){
				if(lista[i].getValor() == num){
					return &lista[i];
				}
			}
		}
		
		Vertice* getVerticeEm(int position){
			return &lista[position];
		}
		
		void print(){
			for(int i = 0; i < cont; i++){
				cout << lista[i].getValor() <<"\n";
			}
		}
		
		Vertice* getLista(){
			return &lista[100];
		}
		
};

class Graph{
	private:
		int ordem;
		int tamanho;
		ListaVertice lista;
	public:
		Graph(int ordem){
			this->ordem = ordem;
		}
		
		int getOrdem(){
			return ordem;
		}
		
		void insertEdge(int v, int u){
			if(lista.contem(v) == false){
				Vertice v1;
				v1.setValor(v);
				lista.insere(v1);
			}
			if(lista.contem(u) == false){
				Vertice v2;
				v2.setValor(u);
				lista.insere(v2);
			}
			Vertice *vertV = lista.getVerticeDe(v);
			Vertice *vertU = lista.getVerticeDe(u);
			
			vertU->adicionaVertice(vertV);
			vertV->adicionaVertice(vertU);
		}
		
		void printTemp(){//apagar mais tarde
			for(int i = 0; i < ordem; i++){
				cout << "[" << lista.getVerticeEm(i)->getValor() << "]= ";
				lista.getVerticeEm(i)->printAdjs();
			}
			
		}
		
		ListaVertice* getListaVertices(){
			return &lista;
		}
		
		Vertice* getVerticeDe(int num){
			return lista.getVerticeDe(num);
		}
		
		
};

class Busca{
	private:
		int tempo;
		ListaVertice *lista;
	public:
		void DFS(Graph g){
//			ListaVertice *lista;
			this->lista = g.getListaVertices();
			for(int i = 0; i < g.getOrdem(); i++){
				lista->getVerticeEm(i)->setCor("branco");
				lista->getVerticeEm(i)->setPi(NULL);
			}
			cout << "Os vertices sao agora todos brancos\n";
			tempo = 0;
			cout << "tempo recebeu 0\n";
			cout << "O primeiro vertice branco sera escolhido\n";
			/*
			for(int i = 0; i < g.getOrdem(); i++){
				if(lista->getVerticeEm(i)->getCor() == "branco"){
					cout << "Um vertice branco foi encontrado\n";
					DFS_VISITA(g, lista->getVerticeEm(i));
				}
			}
			*/
			DFS_VISITA(g, g.getVerticeDe(1));
		}
		
		void DFS_VISITA(Graph g, Vertice *u){
			//cout << "O vertice " << u->getValor() << " esta agora em DFS_VISITA e esta da cor " << u->getCor() << "\n";
			
			tempo++;
			g.getVerticeDe(u->getValor())->setD(tempo);
			g.getVerticeDe(u->getValor())->setCor("cinza");	

			
			cout << "\n-----" << u->getValor() << "---- ABRE\n";
			/*
			cout << "O vertice: " << lista->getVerticeEm(0)->getValor() << "\nesta da cor: " << lista->getVerticeEm(0)->getCor() << "\n";
			cout << "O vertice: " << lista->getVerticeEm(1)->getValor() << "\nesta da cor: " << lista->getVerticeEm(1)->getCor() << "\n";
			cout << "O vertice: " << lista->getVerticeEm(2)->getValor() << "\nesta da cor: " << lista->getVerticeEm(2)->getCor() << "\n";
			cout << "----------\n";
			*/

			for(int i = 0; i < u->getQtddVertice();i++){
				int *listaAdj;
				listaAdj = g.getVerticeDe(u->getValor())->getAdjI();
				
				if(g.getVerticeDe(listaAdj[i])->getCor() == "branco"){//!= "preto" && g.getVerticeDe(listaAdj[i])->getCor() != "cinza"){
					//cout << "entra\n";
					g.getVerticeDe(listaAdj[i])->setPi(u);
					//cout << g.getVerticeDe(listaAdj[i])->getValor() << " esta da cor " << g.getVerticeDe(listaAdj[i])->getCor() << "\n";
					DFS_VISITA(g, g.getVerticeDe(listaAdj[i]));
				}
			}
			tempo++;
			g.getVerticeDe(u->getValor())->setF(tempo);
			g.getVerticeDe(u->getValor())->setCor("preto");
			//cout << "==> vertice " << u->getValor() << " esta da cor " << g.getVerticeDe(u->getValor())->getCor();
			cout << "\n-----" << u->getValor() << "---- FECHA\n";
			/*
			cout << "O vertice: " << lista->getVerticeEm(0)->getValor() << "\nesta da cor: " << lista->getVerticeEm(0)->getCor() << "\n";
			cout << "O vertice: " << lista->getVerticeEm(1)->getValor() << "\nesta da cor: " << lista->getVerticeEm(1)->getCor() << "\n";
			cout << "O vertice: " << lista->getVerticeEm(2)->getValor() << "\nesta da cor: " << lista->getVerticeEm(2)->getCor() << "\n";
			cout << "----------\n";
			*/
		}
};

/* apagar depois...
bool test(Vertice *v){
	if(v->getCor() == "branco"){
		return true;
	}
	v->setCor("branco");
	test(v);
}
*/

int main(int argc, const char * argv[]) {
	Busca b;
	Graph a(7);
	
	/*
	a.insertEdge(1, 2);
	a.insertEdge(1, 3);
	a.insertEdge(1, 4);
	a.insertEdge(3, 5);
	a.insertEdge(5, 6);
	a.insertEdge(5, 7);
	*/
	/*
	a.insertEdge(1, 2);
	a.insertEdge(1, 3);
	a.insertEdge(1, 5);
	a.insertEdge(2, 4);
	//a.insertEdge(2, 1);
	//a.insertEdge(3, 1);
	a.insertEdge(3, 4);
	a.insertEdge(3, 5);
	a.insertEdge(3, 6);
	//a.insertEdge(4, 2);
	//a.insertEdge(4, 3);
	//a.insertEdge(6, 3);
	*/
	
	a.insertEdge(1, 2);
	a.insertEdge(2, 3);
	a.insertEdge(3, 1);
	a.printTemp();
	
	/* apagar depois...
	Vertice *v1;
	v1 = a.getVerticeDe(1);
	v1->setCor("preto");
	cout << v1->getCor();
	test(v1);
	*/
	
	b.DFS(a);
}

