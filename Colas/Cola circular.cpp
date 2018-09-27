/*
   Estructuras de datos
   Autor: José Juan Gurrola Cota
   Programa: Programa que implementa la estructura de cola circular(FiFo)

*/
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

template <class Tipo>
class Cola;

class Excepcion{
public:
   Excepcion(const char *cadena){ strcpy(Msn,cadena); }
   const char *QuePasa(){ return Msn; }
private:
   char Msn[100];
};
//------------------------------------------------------------------------------
template <class Tipo>
class Elemento{
	friend class Cola<Tipo>;
public:
    Elemento(Tipo _valor, Elemento<Tipo> *_Sig = NULL, Elemento<Tipo> *_Circulo = NULL): valor(_valor),Sig(_Sig),Circulo(_Circulo){}
private:
    Tipo valor;
    Elemento<Tipo> *Sig;
    Elemento<Tipo> *Circulo; //Variable para obtener la referencia al primer elemento de la cola
};
//------------------------------------------------------------------------------

template <class Tipo>
class Cola{
public:
    Cola() : Ultimo(NULL), Primero(NULL) {}
    Cola(const Cola<Tipo> &C): Ultimo(NULL), Primero(NULL) { *this=C; }
    ~Cola();
    void Encolar(Tipo);
    Tipo Desencolar();
    bool ColaVacia(){ return !Ultimo; }
    Tipo ValorUltimo(){ return Primero->valor; }
    void Imprimir();
	Cola & operator=(const Cola &);
private:
    Elemento<Tipo> *Primero;
    Elemento<Tipo> *Nuevo;
    Elemento<Tipo> *Ultimo;

};
//------------------------------------------------------------------------------
//Destructor de la Cola
template <class Tipo>
Cola<Tipo>::~Cola()
{
	while(!ColaVacia()) Desencolar();
}
//------------------------------------------------------------------------------
template <class Tipo>
void Cola<Tipo>::Encolar(Tipo _valor)
{
    try{
        Nuevo = new Elemento<Tipo>(_valor);
        if(ColaVacia()){
            Primero = Nuevo;
        }else{
            Ultimo->Sig = Nuevo;
        }
        Ultimo = Nuevo;
        Nuevo->Circulo = Primero;
    }catch(...){
        Excepcion("No hay memoria...");
    }
}
//------------------------------------------------------------------------------
template <class Tipo>
Tipo Cola<Tipo>::Desencolar()
{
    if (ColaVacia()) throw Excepcion("La cola esta vacia");
	Elemento<Tipo> *aux = Primero;
	Primero = Primero -> Sig;
	Nuevo->Circulo = Primero;
	if ( Primero == NULL ) Ultimo = NULL;
	Tipo valorAux = aux->valor;
    delete aux;
	return valorAux;
}
//------------------------------------------------------------------------------
template <class Tipo>
void Cola<Tipo>::Imprimir()
{
    if (ColaVacia()) throw Excepcion("La cola esta vacia");
	Elemento<Tipo> *aux = Primero;

	Elemento<Tipo> *auxU = Ultimo;
    cout<<"\nEl "<<auxU->valor<<" tiene una referencia al "<<aux->valor<<endl;


	cout<<"Primero-> ";
	while(aux){
		cout<<aux->valor<<" ";
		aux = aux->Sig;
	}

	cout<<endl<<endl;
}
//------------------------------------------------------------------------------
template <class Tipo>
Cola<Tipo> & Cola<Tipo>::operator=(const Cola<Tipo> &C)
{
   if(this!=&C){
   	  Elemento<Tipo> *aux = C.Primero;
      while(aux){
         Encolar(aux->valor);
         aux = aux->Sig;
      };
   }
   return *this;
}
//------------------------------------------------------------------------------
//    usuario de la cola
int main()
{
    Cola<int> cInt;

	try{
		cout<<"Cola de enteros:\n";
		for(int i=1;i<10;++i) cInt.Encolar(i);
		cInt.Imprimir();
		cout<<"Sale de la cola el: "<<cInt.Desencolar()<<endl;
		cInt.Imprimir();
		cout<<endl;

	}catch(Excepcion E){
		cout<<E.QuePasa()<<endl;
	}
	cout<<endl;
	system("pause");
	return 0;
}
