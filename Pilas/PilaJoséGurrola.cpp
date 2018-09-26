/*
   Estructuras de Datos
   Autor: José Juan Gurrola Cota
   Programa: Pila con memoria dinamica
   03/10/2014
*/
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;


template <class Tipo>
class Pila;
//******************Clase excepcion ********************************
class Excepcion{
   public:
      Excepcion(char *mensaje){strcpy(msn, mensaje);}
      char* getMsn(){return msn;}
   private:
      char msn[50];
};
//*****************Clase Elemento***********************************************
template <class Tipo>
class Elemento{
	friend class Pila<Tipo>;
public:
    Elemento(Tipo _valor, Elemento<Tipo> *_Sig = NULL): valor(_valor),Sig(_Sig){}
private:  
    Tipo valor;
    Elemento<Tipo> *Sig;    
};
//******************************************************************************
//*************************Clase Pila con plantillas****************************
template <class Tipo>
class Pila{
public:
    Pila() : Tope(NULL) {}
    Pila(const Pila<Tipo> &P): Tope(NULL){ *this=P; }
    ~Pila();
    void Push(Tipo);
    Tipo Pop();
    bool PilaVacia(){ return !Tope; }
    Tipo ValorTope(){ return Tope->valor; }
    void Imprimir();
	Pila<Tipo> & operator=( Pila<Tipo> &);
private:
    Elemento<Tipo> *Tope; 
    int NumElementos; //Numero de elementos de la pila   
};
//-------------------------------------------------------------------------------
// Destructor
template <class Tipo>
Pila<Tipo>::~Pila()
{
	while(!PilaVacia()) Pop();
}
//-------------------------------------------------------------------------------
template <class Tipo>
void Pila<Tipo>::Push(Tipo _valor)
{
    try{
        Tope = new Elemento<Tipo>(_valor,Tope);
        ++NumElementos; //Incrementando en 1 el número de elementos de la pila
    }catch(...){
        Excepcion("No hay memoria...");    
    }
}
//-------------------------------------------------------------------------------
template <class Tipo>
Tipo Pila<Tipo>::Pop()
{
    if (PilaVacia()) throw Excepcion("La pila esta vacia...");
	Elemento<Tipo> *aux = Tope;
	Tope = Tope->Sig;
	Tipo valorAux = aux->valor;
	delete (aux);
	--NumElementos;//disminuyendo en 1 el número de elementos de la pila
	return valorAux;
}
//------------------------------------------------------------------------------
template <class Tipo>
Pila<Tipo> & Pila<Tipo>::operator=( Pila<Tipo> &A)
{
    Pila<Tipo> PAux;  //Pila auxiliar donde se guardará los datos de la pila
    Tipo a; //Variable auxiliar donde se guarda el valor del dato
    while(!PilaVacia())   PAux.Push(Pop()); //Copiamos en la pila auxiliar la instancia pila
    
    while(PAux.PilaVacia()==false){ //ciclo para pasar la pila auxiliar a la instancia y a la pila parametro
        a=PAux.Pop();
        A.Push(a);
        Push(a);
    };
    return A;
    
}
//------------------------------------------------------------------------------
template <class Tipo>
void Pila<Tipo>::Imprimir()
{
	Elemento<Tipo> *aux = Tope;
    cout<<"Tope-> ";
	while(aux){
		cout<<aux->valor<<" ";
		aux = aux->Sig;
	}
	cout<<endl;
}
//*********************************************************************************************************
//*********************************************************************************************************
//*********************************************************************************************************

int main()
{
    try{
        cout<<"Pila de caracteres:\n";
        Pila<char> Pchar;
        Pchar.Push('a');
        Pchar.Push('b');
        Pchar.Push('c');
        Pchar.Imprimir();
        cout<<"Saque el numero: "<<Pchar.Pop()<<endl;
        Pchar.Imprimir();
        
        cout<<"\nPila de enteros:\n";
        Pila<int> Pint, _Pint;
        Pint.Push(1);
        Pint.Push(2);
        Pint.Push(3);
        Pint.Imprimir();
        
        cout<<"\nPila de flotantes:\n";      
        Pila<float> Pfloat;
        Pfloat.Push(1.1f);
        Pfloat.Push(2.2f);
        Pfloat.Push(3.3f);
        Pfloat.Push(4.4f);
        Pfloat.Imprimir();
        
        Pint=_Pint;
        cout<<"\nImpresion de la copia de pila de enteros:\n";
        _Pint.Imprimir();
        
        cout<<"\nVaciando pila copiada..\n";
        while(!_Pint.PilaVacia()) cout<<"Quite el : "<<_Pint.Pop()<<endl;
        _Pint.Imprimir();
        _Pint.Pop();
        
	}catch(Excepcion Ex){
        cout<< Ex.getMsn() <<endl;
    }
	cout<<endl;
	system("pause");
	return 0;
}
