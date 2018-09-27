/*
  Programa: Lista Simple Ordenada de forma ascendente
  Autor: José Juan Gurrola Cota
  Fecha: 20/10/2014
  Descripcion: Lista Simple Ordenada de forma ascendente
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
    Lista() :Primero(NULL){}
    Lista(const Lista<Tipo> &);
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
    bool Buscar(Tipo _valor){
        if(Buscar(_valor,0)) return true;
        else return false;
    } 
    void Vaciar();
private:
    Elemento<Tipo> *Primero;    
    Elemento<Tipo> * Buscar(Tipo,int);
};
//******************************************************************************
template <typename Tipo>
Lista<Tipo>::Lista(const Lista<Tipo> &L):Primero(NULL)
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
    }catch(...){
        cout<<"No hay memoria... \n";    
    }
}
//******************************************************************************
template <typename Tipo>
bool Lista<Tipo>::Quitar(Tipo _valor)
{
    Elemento<Tipo> *Anterior = Buscar(_valor,0);
    Elemento<Tipo> *aux = (Anterior)? Anterior -> Sig : Primero;
      
    if(!aux || aux->valor!=_valor){
       cout<<"\nEl "<<_valor<<" no esta en la lista\n";
       return false;
    }else{
       if(aux==Primero) Primero= Primero->Sig;
       else Anterior->Sig=aux->Sig;
       delete aux;
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
    cout<<"\nLista =>  ";
	while(aux){
		cout<<aux->valor<<", ";
		aux = aux->Sig;
	}
	cout<<"\b\b ";
}
//******************************************************************************
//Devuelve NULL si el elemento va antes del Primero
//de lo contrario va despues del valor devuelto.
template<typename Tipo>
Elemento<Tipo> * Lista<Tipo>::Buscar(Tipo V, int x)
{
   Elemento<Tipo> *aux = Primero;
   Elemento<Tipo> *Anterior = NULL;
   while(aux && aux->valor<V){
      Anterior = aux;
      aux = aux->Sig;
   }
   return Anterior;
}
//******************************************************************************

//******************************************************************************

//******************************************************************************
int main ()
{
   try{
        Lista<int> A,B;
        cout<<"\t\t\tLista de enteros.\n";
        A.Poner(2);
        A.Poner(4);
        A.Poner(-1);
        A.Poner(3);
        A.Poner(1);
        A.Imprimir();
        A.Quitar(2);  A.Imprimir();
        A.Quitar(-1); A.Imprimir();
        A.Quitar(4);  A.Imprimir();
        A.Quitar(8);
        
        B=A;
        B.Imprimir();
        
    }catch(Excepcion &Ex){
      cout<<Ex.getMsn(); 
    }
   
   cout<<endl;
   system("pause");
}
