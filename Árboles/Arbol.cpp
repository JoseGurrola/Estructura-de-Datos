/*
  Programa: Arbol.cpp
  Autor: José Juan Gurrola Cota
  Fecha: 16/11/2014
  Descripcion: Programa que implementa un arbol binario de busqueda
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
    void Imprimir(int); //El int es para indicar que tipo de impresión quiere
    Nodo<Tipo> * Buscar(Tipo);
    void Vaciar(Nodo<Tipo>* &);
private:
    Nodo<Tipo> *Raiz;
    void Inorden(Nodo<Tipo> *); //ascendiente
    void Postorden(Nodo<Tipo> *); //por niveles
    void Preorden(Nodo<Tipo> *); //descendiente
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
   Nodo<Tipo> *padre = NULL;
   Nodo<Tipo> *actual;
   Nodo<Tipo> *nodo;
   int aux;

   actual = Raiz;
   if(EstaVacio(actual)) throw Excepcion("El arbol esta vacio!");
   while(!EstaVacio(actual)){
      if(dato == actual->valor) { //Si se encuentra el valor
         if(EsHoja(actual)){ // Si el nodo es hoja
            if(padre) // Si no es raiz
               if(padre->Der == actual) padre->Der = NULL;
               else if(padre->Izq == actual) padre->Izq = NULL;
            delete actual;
            actual = NULL; //borramos el nodo y devolvemos true
            return true;
         }else{ // Si el valor está aqui sin ser hoja
            padre = actual;
            if(actual->Der){ // Buscando el menor de los mayores
               nodo = actual->Der;
               while(nodo->Izq){
                  padre = nodo;
                  nodo = nodo->Izq;
               }
            }else{// Buscando el mayor de los menores
               nodo = actual->Izq;
               while(nodo->Der){
                  padre = nodo;
                  nodo = nodo->Der;
               }
            }
            aux = actual->valor;
            actual->valor = nodo->valor;
            nodo->valor = aux;
            actual = nodo;
         }
      }
      else{ // para seguir buscando el valor
         padre = actual;
         if(dato > actual->valor) actual = actual->Der;
         else if(dato < actual->valor) actual = actual->Izq;
      }
   }
}
//******************************************************************************
template <class Tipo>
void Arbol<Tipo>::Imprimir(int o)
{
     if(EstaVacio(Raiz)) throw Excepcion("El arbol esta vacio!");
     else
      if(o==1) Inorden(Raiz);
      if(o==2) Postorden(Raiz);
      if(o==3) Preorden(Raiz);
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
template <typename Tipo>
void Arbol<Tipo>::Postorden(Nodo<Tipo> *a)
{
  if(a){
    Inorden(a->Izq);
    Inorden(a->Der);
    cout<<a->valor<<" ";
  }
}
template <typename Tipo>
void Arbol<Tipo>::Preorden(Nodo<Tipo> *a)
{
  if(a){
    cout<<a->valor<<" ";
    Inorden(a->Izq);
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
       Arbol<int> A, B;
       A.Insertar(1);
       A.Insertar(2);
       A.Insertar(3);
       A.Insertar(4);
       A.Insertar(5);
       A.Insertar(8);
       A.Insertar(1);
       A.Insertar(9);
       A.Imprimir(1); //el 1 es para indicar el tipo de impresión
       cout<<endl;
       A.Eliminar(2);
       A.Eliminar(1);
       cout<<"Quitamos el 1 y el 2\n";

       A.Buscar(4);
       cout<<"InOdern: "; A.Imprimir(1); cout<<endl;
       cout<<"PostOrden: "; A.Imprimir(2); cout<<endl;
       cout<<"PreOrden: "; A.Imprimir(3); cout<<endl;

       cout<<"A=B\nImprimiendo B: ";
       B=A;
       B.Imprimir(1);

    }catch(Excepcion &Ex){
      cout<<Ex.getMsn();
    }

   cout<<endl;
   system("pause");
}
