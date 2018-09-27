/*
   Estructuras de datos
   Autor: José Juan Gurrola Cota
   Programa: Programa que implementa la estructura de cola (FiFo)
   11/10/2014
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
    Elemento(Tipo _valor, Elemento<Tipo> *_Sig = NULL): valor(_valor),Sig(_Sig){}
private:  
    Tipo valor;
    Elemento<Tipo> *Sig;    
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
	Cola & operator=(const Cola &); //falta
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
	Cola<char> cChar, _cChar;
	Cola<float> cFloat;
	char expresion[30];
	try{
		cout<<"Cola de enteros:\n";
		for(int i=1;i<6;++i) cInt.Encolar(i);
		cInt.Imprimir();
		cout<<"Sale de la cola el: "<<cInt.Desencolar()<<endl;
		cInt.Imprimir();
		cout<<endl;
		
		cout<<"Cola de reales:\n";
		for(int i=1;i<6;++i) cFloat.Encolar(i+.5);
		cFloat.Imprimir();
		cout<<"Sale de la cola el: "<<cFloat.Desencolar()<<endl;
		cFloat.Imprimir();
		cout<<endl;
		
		cout<<"Cola de caracteres:\n";
		for(int i=1;i<6;++i) cChar.Encolar(i);
		cChar.Imprimir();
		cout<<"Sale de la cola el: "<<cChar.Desencolar()<<endl;
		cChar.Imprimir();
		cout<<endl;
		
		cout<<"Copiando una cola de caracteres:\n";
		_cChar=cChar;
		_cChar.Imprimir();
			
	}catch(Excepcion E){
		cout<<E.QuePasa()<<endl;
	}
	cout<<endl;
	system("pause");
	return 0;
}
