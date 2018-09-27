/*
  Programa: Polinomios
  Autor: José Juan Gurrola Cota
  Fecha: 30/10/2014
  Descripcion:
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
//************************Clase Elemento****************************************
template <class Tipo> class Polinomio;
template <class Tipo>
class Elemento{
	friend class Polinomio<Tipo>;
public:
    Elemento(Tipo V, Elemento<Tipo> *S = NULL):
        valor(V),Sig(S){}
private:
    Tipo valor;
    Elemento<Tipo> *Sig;
};
//*********************Clase racional*******************************************
class Racional{
    friend ostream & operator<<(ostream &,const Racional &);
    friend istream & operator>>(istream &,Racional &);
public:
    Racional(int _num=1,int _den=1): num(_num),den(_den) //constructor!
    {
        if(den==0) throw Excepcion("El denominador no puede ser 0!\n");
        if(den<0){
            num=-num;
            den*=-1;
        }
        int b=2;//ciclo para reducir o simplificar el numero racional
        while(b<=fabs(num)){
		    if(den%b==0 && num%b==0){
			    den=den/b;
			    num=num/b;
            }else   b++;
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
ostream & operator<<(ostream &salida,const Racional &C)
{
    salida<<C.num<<"/"<<C.den;
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
//******************************Clase Monomio***********************************
class Monomio{
    friend ostream & operator<<(ostream &,const Monomio &);
    friend istream & operator>>(istream &,Monomio &);
public:
    Monomio(Racional _coef=1,int _grado=1): coef(_coef),grado(_grado){} //constructor!
    void Capturar();
    void Imprimir(){ cout<<"(("<<coef<<"),"<<grado<<") "; }
    bool operator>(const Monomio &M) const { if(M.grado>grado) return true; else return false;}
    bool operator<(const Monomio &M) const { if(M.grado<grado) return true; else return false;}
    bool operator==(const Monomio &M) const { if(M.grado==grado) return true; else return false;}
    Monomio operator+(const Monomio &) const;
private:
    Racional coef;
    int grado;
};
//------------------------------------------------------------------------------
ostream & operator<<(ostream &salida,const Monomio &M)
{
    salida<<"(("<<M.coef<<"),"<<M.grado<<") ";
    return salida;
}
//------------------------------------------------------------------------------
istream & operator>>(istream &entrada,Monomio &M)
{
    Racional R(1,1);
    int _grado;
    cout<<"\nIngresa el coeficiente racional del monomio: ";
    cin>>R;
    cout<<"Ingresa el grado del monomio: ";
    entrada>>_grado;

    M.coef = R;
    M.grado = _grado;
}
//------------------------------------------------------------------------------
void Monomio::Capturar()
{
    Racional R(1,1);
    int _grado;
    cout<<"\nIngresa el coeficiente racional del monomio: ";
    cin>>R;
    cout<<"Ingresa el grado del monomio: ";
    cin>>_grado;

    coef = R;
    grado = _grado;
}
//------------------------------------------------------------------------------
Monomio Monomio::operator+(const Monomio &M) const
{
    Racional R(1);
    Monomio Maux(coef+M.coef,grado);
    return Maux;
}
//******************************Clase Polinomio*************************************
template <class Tipo>
class Polinomio{
public:
    Polinomio() :Primero(NULL){}
    Polinomio(const Polinomio<Tipo> &L){ *this=L; }
    ~Polinomio(){Vaciar();}
    Polinomio &operator=(const Polinomio<Tipo> &);
    void Capturar(int); //Capturar un polinomio de "n" monomios
    void Poner(Tipo);
    bool Quitar(Tipo);
    bool EstaVacia(){ return !Primero; }
    Tipo ObtenerPrimero(){
        if(EstaVacia()) throw Excepcion ("No hay Polinomio!\n");
        return Primero->valor;
    }
    void Imprimir();
    void Vaciar();
    Polinomio operator+(const Polinomio &) const;
private:
    Elemento<Tipo> *Primero;
    Elemento<Tipo> * Buscar(Tipo,int);
};
//******************************************************************************
template <typename Tipo>
void Polinomio<Tipo>::Poner(Tipo _valor)
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
bool Polinomio<Tipo>::Quitar(Tipo _valor)
{
    Elemento<Tipo> *Anterior = Buscar(_valor,0);
    Elemento<Tipo> *aux = (Anterior)? Anterior -> Sig : Primero;

    if(!aux || aux->valor!=_valor){
       cout<<"\nEl "<<_valor<<" no esta en la Polinomio\n";
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
void Polinomio<Tipo>::Vaciar()
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
Polinomio<Tipo> &Polinomio<Tipo>::operator=(const Polinomio<Tipo> &L)
{
    try{
       if(this!=&L){
          if(!EstaVacia()) Vaciar();
          Elemento<Tipo> *aux;

          aux = L.Primero;
          while(aux){
             Poner(aux->valor);
             aux = aux->Sig;
             if(aux == L.Primero) aux =NULL;
          }
       }
       return *this;
   }catch(Excepcion &Ex){throw Ex;}
}
//******************************************************************************
template <typename Tipo>
void Polinomio<Tipo>::Capturar(int n)
{
    Racional R(1);
    Monomio M(R);
    for(int i=0;i<n;++i){
           cin>>M;
           Poner(M);
        }
}
//******************************************************************************
template <typename Tipo>
void Polinomio<Tipo>::Imprimir()
{
	Elemento<Tipo> *aux = Primero;
    cout<<"\nPolinomio =>  ";
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
Elemento<Tipo> * Polinomio<Tipo>::Buscar(Tipo V, int x)
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
template <typename Tipo>
Polinomio<Tipo> Polinomio<Tipo>::operator+(const Polinomio &P) const
{
   Polinomio<Monomio> S;
    Racional R1, R;
    Racional R2;
    Monomio M1(R1),M(R);
    Monomio M2(R2);
    Elemento<Tipo> *aux1 = Primero;
    Elemento<Tipo> *aux2 = P.Primero;
    while(aux1 && aux2){
        M1=aux1->valor;
        M2=aux2->valor;

        if(M1==M2){
           M=M1+M2;
           S.Poner(M);
        }else{
           S.Poner(M1);
           S.Poner(M2);
        }
        aux1 = aux1->Sig;
        aux2 = aux2->Sig;
    }

    return S;
}
//******************************************************************************
int main ()
{
   try{
       int n=0;//para saber de cuantos monomios estará compuesto el polinomio
       Polinomio<Monomio> P1,P2,PS;

       cout<<"\nDe cuantos monomios estan compuestos los polinomios? ";
       cin>>n;
       P1.Capturar(n);
       P2.Capturar(n);

       PS = P1 + P2;

       P1.Imprimir();
       P2.Imprimir();
       cout<<"\nSuma de polinomios:";
       PS.Imprimir();
       cout<<PS.ObtenerPrimero();

    }catch(Excepcion &Ex){
      cout<<Ex.getMsn();
    }
   cout<<endl;
   system("pause");
}
