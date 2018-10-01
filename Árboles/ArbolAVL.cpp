/*
  Programa: ArbolAVL.cpp
  Autor: José Juan Gurrola Cota
  Fecha: //2014
  Descripcion: Programa que implementa un arbol AVL (arbol semibalanceado)
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
//*************************Clase Excepcion**************************************
class Excepcion{
   public:
      Excepcion(const char *mensaje){strcpy(msn, mensaje);}
       char* getMsn(){return msn;}
   private:
       char msn[50];
};
//****************************Clase Nodo****************************************
template <class Tipo> class Arbol;
template <class Tipo>
class Nodo{
	friend class Arbol<Tipo>;
public:
    Nodo(const int V, Nodo<Tipo> *izq=NULL, Nodo<Tipo> *der=NULL) :
        valor(V), Izq(izq), Der(der) {}
private:
    Tipo valor;
    Nodo<Tipo> *Izq, *Der;
    int FE; //Factor de equilibrio en cada nodo
};
//*************************Clase Arbol******************************************
template <class Tipo>
class Arbol{
public:
    Arbol() : Raiz(NULL){}
    Arbol(const Arbol<Tipo> &A){ *this=A; }
    ~Arbol() { Vaciar(Raiz); }
    Arbol &operator=(const Arbol<Tipo> &);
    void Insertar(const Tipo);
    bool Eliminar(Tipo);
    bool EstaVacio(Nodo<Tipo> *n){ return n==NULL;}
    Tipo ObtenerRaiz(){
        if(EstaVacio()) throw Excepcion ("No hay Arbol!\n");
        return Raiz->valor;
    }
    bool EsHoja(const Nodo<Tipo> *n){  return !n->Izq && !n->Der;}
    void Imprimir();
    int Altura(Nodo<Tipo> *);

    Nodo<Tipo> * Buscar(Tipo);
    void Vaciar(Nodo<Tipo>* &);
private:
    Nodo<Tipo> *Raiz;
    void Inorden(Nodo<Tipo> *); //ascendiente
    void Inordenaux(Nodo<Tipo> *); //funcion auxiliar para ser utilizada por el operador = en su sobrecarga
};
//******************************************************************************
template <typename Tipo>
Arbol<Tipo> &Arbol<Tipo>::operator=(const Arbol<Tipo> &A)
{
    Nodo<Tipo> *aux = A.Raiz;
    Inordenaux(aux);
    return *this;
}
//******************************************************************************
template <typename Tipo>
void Arbol<Tipo>::Insertar(const Tipo dato)
{
    Nodo<Tipo> *actual;
    try{
        Nodo<Tipo> *padre=NULL;
        actual = Raiz;

        while(!EstaVacio(actual) && dato != actual->valor) {
            padre = actual;
            if(dato > actual->valor) actual = actual->Der;
            else if(dato < actual->valor) actual = actual->Izq;
       }

       if(!EstaVacio(actual)) return;

       if(EstaVacio(padre)) Raiz = new Nodo<Tipo>(dato);
       else if(dato < padre->valor) padre->Izq = new Nodo<Tipo>(dato);
       else if(dato > padre->valor) padre->Der = new Nodo<Tipo>(dato);

    }catch(...){
        cout<<"No hay memoria... \n";
    }
}
//******************************************************************************
template <typename Tipo>
bool Arbol<Tipo>::Eliminar(const Tipo dato)
{

}
//******************************************************************************
template <class Tipo>
void Arbol<Tipo>::Imprimir()
{
     if(EstaVacio(Raiz)) throw Excepcion("El arbol esta vacio!");
     else   Inorden(Raiz);
}
//******************************************************************************
template <typename Tipo>
int Arbol<Tipo>::Altura(Nodo<Tipo> *a)
{

}
//******************************************************************************
template <typename Tipo>
void Arbol<Tipo>::Inorden(Nodo<Tipo> *a)
{
  if(a){
    Inorden(a->Izq);
    cout<<a->valor<<" ";
    Inorden(a->Der);
  }
}
//******************************************************************************
template <typename Tipo>
void Arbol<Tipo>::Inordenaux(Nodo<Tipo> *a)
{
  if(a){
    Insertar(a->valor);
    Inordenaux(a->Izq);
    Inordenaux(a->Der);
  }
}
//******************************************************************************
template<typename Tipo>
Nodo<Tipo> * Arbol<Tipo>::Buscar(Tipo V)
{
   Nodo<Tipo> *actual = Raiz;

   while(!EstaVacio(actual)) {
      if(V == actual->valor) return actual;
      else if(V < actual->valor) actual = actual->Izq;
      else if(V > actual->valor) actual = actual->Der;
   }
   return NULL;
}
//******************************************************************************
template<typename Tipo>
void Arbol<Tipo>::Vaciar(Nodo<Tipo>* &nodo)
{
   if(nodo) {
      Vaciar(nodo->Izq);    //izquierdo
      Vaciar(nodo->Der);   //derecho
      delete nodo;
      nodo = NULL;
   }
}
//******************************************************************************
int main ()
{
   try{
       Arbol<int> A;
       A.Insertar(5);
       A.Insertar(21);
       A.Insertar(1);
       A.Insertar(2);
       A.Insertar(3);
       A.Imprimir();
       cout<<endl;


    }catch(Excepcion &Ex){
      cout<<Ex.getMsn();
    }

   cout<<endl;
   system("pause");
}
