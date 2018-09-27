/*
  Programa: ListaDoble
  Autor: José Juan Gurrola Cota
  Fecha: 03/11/2014
  Descripcion: Programa que implementa la estructura de lista doblemente ordenada
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
//*************************Clase Excepcion**************************************
class Excepcion{
   public:
      Excepcion(char *mensaje){strcpy(msn, mensaje);}
      char* getMsn(){return msn;}
   private:
      char msn[50];
};
//**************************Clase Lista Doble***********************************
template <class Tipo> class ListaDoble;
template <class Tipo>
class Elemento{
	friend class ListaDoble<Tipo>;
public:
    Elemento(Tipo V, Elemento<Tipo> *S = NULL): Ant(NULL), valor(V),Sig(S){}
private:
    Tipo valor;
    Elemento<Tipo> *Sig, *Ant;
};
//******************************************************************************
template <class Tipo>
class ListaDoble{
public:
    ListaDoble() :Primero(NULL){}
    ListaDoble(const ListaDoble<Tipo> &);
    ~ListaDoble(){Vaciar();}
    ListaDoble &operator=(const ListaDoble<Tipo> &);
    void Poner(Tipo);
    bool Quitar(Tipo);
    bool Buscar(Tipo);
    bool EstaVacia(){ return !Primero; }
    Tipo ObtenerPrimero(){
        if(EstaVacia()) throw Excepcion ("No hay Lista!\n");
        return Primero->valor;
    }
    void Imprimir() const;
    void Vaciar();
private:
    Elemento<Tipo> *Primero;
    Elemento<Tipo>* Buscar(Tipo,int);
};
//------------------------------------------------------------------------------
template <typename Tipo>
ListaDoble<Tipo>::ListaDoble(const ListaDoble<Tipo> &P):Primero(NULL)
{
	ListaDoble<Tipo> A;
    Elemento<Tipo> *aux = P.Primero;
	while(aux){
		A.Poner(aux->valor);
		aux = aux->Sig;
	}

	do{
        Poner(A.Quitar());
    }while(!A.EstaVacia());
}
//------------------------------------------------------------------------------
template <typename Tipo>
void ListaDoble<Tipo>::Poner(Tipo _valor)
{
    try{
       Elemento<Tipo> *nuevo = new Elemento<Tipo>(_valor);
       Elemento<Tipo> *aux = Buscar(_valor,0);
       if(!aux ){
            nuevo->Sig = Primero;
       		Primero = nuevo;
       	}else {
            if(aux->Sig){
      		    aux = aux->Sig;
      		    nuevo->Ant = aux->Ant;
      		    nuevo->Sig = aux;
      		    aux->Ant->Sig = nuevo;
      		    aux->Ant = nuevo;
            }else{
               nuevo->Ant = aux;
               aux->Sig = nuevo;
            }
        }
    }catch(...){
        cout<<"No hay memoria... \n";
    }
}
//------------------------------------------------------------------------------
template <typename Tipo>
bool ListaDoble<Tipo>::Quitar(Tipo V)
{
   if(EstaVacia()) throw Excepcion("No hay Lista Doble!");
   Elemento<Tipo> *anterior = Buscar(V,0);
   Elemento<Tipo> *aux = (anterior)? anterior->Sig : Primero;
   if(!aux || aux->valor != V){
      cout<<"\nNo esta en la Lista Doble\n";
      return false;
   }else{
      if(aux==Primero)Primero=Primero->Sig;
      else {
         anterior->Sig=aux->Sig;
         if(anterior->Sig) anterior->Sig->Ant=anterior;
      }
      delete aux;
      return true;
   }
}
//------------------------------------------------------------------------------
template <class Tipo>
void ListaDoble<Tipo>::Vaciar()
{
   Elemento<Tipo> *aux;
   while(!EstaVacia()){
      aux = Primero;
      Primero = Primero->Sig;
      delete aux;
   }
}
//------------------------------------------------------------------------------
template <typename Tipo>
ListaDoble<Tipo> &ListaDoble<Tipo>::operator=(const ListaDoble<Tipo> &P)
{
    ListaDoble<Tipo> c;
    Elemento<Tipo> *aux = P.Primero;
    if(!EstaVacia()) Vaciar();
	while(aux){
		Poner(aux->valor);
		aux = aux->Sig;
	}
    return *this;
}
//------------------------------------------------------------------------------
template <typename Tipo>
void ListaDoble<Tipo>::Imprimir() const
{
	Elemento<Tipo> *aux = Primero;
    cout<<"Lista Doble:  ";
	while(aux){
		cout<<aux->valor<<", ";
		aux = aux->Sig;
	}
	cout<<"\b\b \n";
}
//------------------------------------------------------------------------------
template<typename Tipo>
bool ListaDoble<Tipo>::Buscar(Tipo V)
{
   Elemento<Tipo> *aux = Primero;
   Elemento<Tipo> *Anterior = NULL;
   while(aux && aux->valor<V){
      Anterior = aux;
      aux = aux->Sig;
   }
   return Anterior;
}
//------------------------------------------------------------------------------
//Devuelve NULL si el elemento va antes del Primero
//de lo contrario va despues del valor devuelto.
template<typename Tipo>
Elemento<Tipo> * ListaDoble<Tipo>::Buscar(Tipo _valor,int x)
{
   Elemento<Tipo> *aux=Primero,*anterior=NULL;

   while(aux && aux->valor < _valor){
      anterior = aux;
      aux=aux->Sig;
   }
   return anterior;
}
//******************************************************************************
int main ()
{
    try{
        ListaDoble<int> A;
        cout<<"\t\t\tLista Doble de enteros.\n\n";

        A.Poner(1);
        A.Poner(8);
        A.Poner(3);
        A.Poner(-1);
        A.Poner(9);
        A.Imprimir();
        A.Quitar(-1);
        A.Quitar(8);
        A.Imprimir();

    }catch(Excepcion &Ex){
      cout<<Ex.getMsn();
    }
   system("pause");
}
