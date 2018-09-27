/*
  Programa: Lista Simple Ordenada de forma ascendente
  Autor: José Juan Gurrola Cota
  Fecha: 20/10/2014
  Descripcion: Lista Simple Ordenada de forma ascendente
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>
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
	Lista<Tipo> LAux;
    Elemento<Tipo> *aux = L.Primero;
	while(aux){
		LAux.Poner(aux->valor);
		aux = aux->Sig;
	}

	do{
        Poner(LAux.Quitar());
    }while(!LAux.EstaVacia());
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
    Lista<Tipo> LAux;
    Elemento<Tipo> *aux = LAux.Primero;
    if(!EstaVacia()) Vaciar();
	while(aux){
		Poner(aux->valor);
		aux = aux->Sig;
		Imprimir();
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
class Racional{
    friend ostream & operator<<(ostream &,const Racional &);
    friend istream & operator>>(istream &,Racional &);
public:
    Racional(int _num=1,int _den=1): num(_num),den(_den) //constructor!
    {
        if(den==0) throw Excepcion("El denominador no puede ser 0!/n");
        if(den<0){
            num=-num;
            den*=-1;
        }
        int b=2;//ciclo para reducir o simplificar el numero racional
        while(b<=fabs(num)){
		    if(den%b==0 && num%b==0){
			    den=den/b;
			    num=num/b;
            }else{
                b++;
            }
       }
}
    Racional operator+(const Racional &C) const { return Racional ((num*C.den)+(den*C.num), den*C.den);}
    Racional operator-(const Racional &C) const { return Racional ((num*C.den)-(den*C.num), den*C.den);}
    Racional operator*(const Racional &C) const { return Racional (num*C.num, den*C.den);}
    Racional operator/(const Racional &C) const { return Racional (num*C.den, den*C.num);}
    bool operator>(const Racional &C) const { if(num*C.den>den*C.num) return true; else return false; }
    bool operator>=(const Racional &C) const { if(num*C.den>=den*C.num) return true; else return false; }
    bool operator<(const Racional &C) const { if(num*C.den<den*C.num) return true; else return false; }
    bool operator<=(const Racional &C) const { if(num*C.den<=den*C.num) return true; else return false; }

private:
    int num, den; //num= numerador den=denominador
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
ostream & operator<<(ostream &salida,const Racional &C)
{
    if(fabs(C.num)==fabs(C.den)) salida<<C.num;
    else salida<<C.num<<"/"<<C.den;

    return salida;
}
//------------------------------------------------------------------------------
istream & operator>>(istream &entrada,Racional &C)
{
   cout<<"\nNumerador: ";
   entrada>>C.num;
   cout<<"Denominador: ";
   entrada>>C.den;
   if(C.den==0) throw Excepcion("El denominador no puede ser 0!\n");
    if(C.den<0){
        C.num=-C.num;
        C.den*=-1;
    }
    int b=2;//ciclo para reducir o simplificar el numero racional
    while(b<=fabs(C.num)){
		if(C.den%b==0 && C.num%b==0){
			C.den=C.den/b;
			C.num=C.num/b;
		}else{
		b++;
		}
    }
}
//******************************************************************************
//******************************************************************************
int main ()
{
   try{
        int num,den,n=0;
        Lista<Racional> L;
        Racional R(1,1);
        while(n!=1000){
           cin>>R;
           L.Poner(R);
           L.Imprimir();
        };

    }catch(Excepcion &Ex){
      cout<<Ex.getMsn();
    }

   cout<<endl;
   system("pause");
}
