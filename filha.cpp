#include <iostream>
#include <cstdlib>

using namespace std;


template <class T>
class Item{
	private:
		T valor;
		Item *prox;
	public:
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
			
			for(int i = 0; i < tam; i++)
				items[i].setValor(-1);
			
			this->frente = items;
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
			tras->setProx(NULL);
		}
		
		int desenfileira(){
			
			T item;
			
			int saida = items[1].getValor();
			
			item = *frente;
			
			frente = frente->getProx();
			
			desaloque(this->items);
			
			this->tam--;
			
			return saida;
		}
		
		void mostra(){
			for(int i = 1; i < tam+1; i++)
				cout << items[i].getValor() << " | ";
			cout << endl;
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

int main(){
	
	Fila< Item<int> > fila;
	
	fila.cria(20);

	Item<char> a,b,c;
	char d;
	Item<int> aux;
	
	a.setValor('a');
	b.setValor('b');
	c.setValor('c');
	/*
	a.setProx(&b);
	b.setProx(&c);
	*/
	aux.setValor(1);
	fila.enfileira(aux);
	fila.mostra();
	
	aux.setValor(2);
	fila.enfileira(aux);
	fila.mostra();
	
	aux.setValor(3);
	fila.enfileira(aux);
	fila.mostra();
	
	fila.desenfileira();
	fila.desenfileira();
	
	aux.setValor(4);
	fila.enfileira(aux);
	fila.mostra();
	
	aux.setValor(5);
	fila.enfileira(aux);
	fila.mostra();
	
	aux.setValor(6);
	fila.enfileira(aux);
	fila.mostra();
	
	aux.setValor(7);
	fila.enfileira(aux);
	fila.mostra();
	
//	fila.desenfileira();
//	fila.mostra();
	
}
