#include <iostream>
#include <cstdlib>
#include <cstring>
//******************************************************************************
template <class Tipo> class Lista;
template <class Tipo>
class Elemento{
	friend class Lista<Tipo>;
public:
    Elemento(Tipo V, Elemento<Tipo> *S = NULL):
        valor(V),Sig(S){}
private:
    Tipo valor;
    Elemento<Tipo> *Sig;
};
//******************************************************************************
template <class Tipo>
class Lista{
public:
    Lista() :Primero(NULL), Tam(0){} //constructor de 0 parametros
    Lista(const Lista<Tipo> &); //constructor de 1 parametro
    ~Lista(){Vaciar();}
    Lista &operator=(const Lista<Tipo> &);
    void Poner(Tipo);
    bool Quitar(Tipo);
    bool EstaVacia(){ return !Primero; }
    Tipo ObtenerPrimero(){
        if(EstaVacia()) throw Excepcion ("No hay Lista!\n");
        return Primero->valor;
    }
    void Imprimir();
    bool Buscar(Tipo _valor){ //regresa booleano si encontra el elemento
        Elemento<Tipo> *aux=Primero;
        while(aux){
            if(aux->valor==_valor) return true;
            aux=aux->Sig;
         }
         return false;
    }
    void Vaciar();
    int TamLista(){return Tam;}
    Tipo *ObtenerDatos();
private:
    Elemento<Tipo> *Primero;
    Elemento<Tipo> * Buscar(Tipo,int); //regresa el elemento que se busca
    int Tam;
};
//******************************************************************************
template <typename Tipo>
Lista<Tipo>::Lista(const Lista<Tipo> &L):Primero(NULL), Tam(0)
{
	Lista<Tipo> c;
    Elemento<Tipo> *aux = L.Primero;
	while(aux){
		c.Poner(aux->valor);
		aux = aux->Sig;
	}

	do{
        Poner(c.Quitar());
    }while(!c.EstaVacia());
}
//******************************************************************************
template <typename Tipo>
void Lista<Tipo>::Poner(Tipo _valor)
{
    try{
       Elemento<Tipo> *nuevo = new Elemento<Tipo>(_valor);
       Elemento<Tipo> *aux = Buscar(_valor,0);
       if(!aux){
            nuevo->Sig = Primero;
       		Primero = nuevo;
       	}else {
		    nuevo->Sig = aux->Sig;
		    aux->Sig = nuevo;
		    }
		    ++Tam;
    }catch(...){
        std::cout<<"No hay memoria... \n";
    }
}
//******************************************************************************
template <typename Tipo>
bool Lista<Tipo>::Quitar(Tipo _valor)
{
    Elemento<Tipo> *Anterior = Buscar(_valor,0);
    //cout<<Anterior->valor<<endl;
    Elemento<Tipo> *aux = (Anterior)? Anterior -> Sig : Primero;
    //Elemento<Tipo> *aux = Primero;
    if(!aux || aux->valor!=_valor){
       return false;
    }else{
       if(aux==Primero) Primero= Primero->Sig;
       else Anterior->Sig=aux->Sig;
       delete aux;
       --Tam;
       return true;
    }
}
//******************************************************************************
template <class Tipo>
void Lista<Tipo>::Vaciar()
{
   Elemento<Tipo> *aux;
   while(!EstaVacia()){
      aux = Primero;
      Primero = Primero->Sig;
      Tam=0;
      delete aux;
   }
}
//******************************************************************************
template <typename Tipo>
Lista<Tipo> &Lista<Tipo>::operator=(const Lista<Tipo> &L)
{
    Lista<Tipo> c;
    Elemento<Tipo> *aux = L.Primero;
    if(!EstaVacia()) Vaciar();
	while(aux){
		Poner(aux->valor);
		aux = aux->Sig;
	}
    return *this;
}
//******************************************************************************
template <typename Tipo>
void Lista<Tipo>::Imprimir()
{
	Elemento<Tipo> *aux = Primero;
    std::cout<<"\n  => ";
	while(aux){
		std::cout<<aux->valor<<", ";
		aux = aux->Sig;
	}
	std::cout<<"\b\b ";
}
//******************************************************************************
//Devuelve NULL si el elemento va antes del Primero
//de lo contrario va despues del valor devuelto.
template<typename Tipo>
Elemento<Tipo> * Lista<Tipo>::Buscar(Tipo V, int x)
{
   Elemento<Tipo> *aux = Primero;
   Elemento<Tipo> *Anterior = NULL;
   while(aux && aux->valor!=V){
      Anterior = aux;
      aux = aux->Sig;
   }
   return Anterior;
}
//**************************************************************
template<typename Tipo>
Tipo* Lista<Tipo>::ObtenerDatos()
{
   Tipo *A;
   Elemento<Tipo> * aux=Primero;
   A = new (nothrow) Tipo[Tam];
   int i=0;

   while(aux){
      A[i]=aux->valor;
      ++i;
      aux=aux->Sig;
   }
   return A;
}
