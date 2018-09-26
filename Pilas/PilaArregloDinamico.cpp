/*
  Programa:
  Autor: Erick Fernando Lopez Fimbres
  Fecha:
  Descripcion:
*/

#include <iostream>
#include <cstdlib>
using namespace std;

//*************************Clase Excepcion**************************************
class Excepcion{
   public:
      Excepcion(char *mensaje){strcpy(msn, mensaje);};
      char* getMsn(){return msn;};
   private:
      char msn[50];


};
//******************************************************************************
template <class Tipo>
class Pila{
    public:
        explicit Pila(int);
        Pila(const Pila &);
        ~Pila();
        bool EstaLlena() const { return Tope == tam-1;}
        bool EstaVacia() const { return Tope == -1;}
        void Imprimir()const;
        void Push(const Tipo &);
        Tipo Pop();
        Tipo & operator= (const Tipo&);
        Tipo ObtenerTope() const {if(!EstaVacia()) return Arreglo[Tope];}
    private:
        int Tope,tam;
        Tipo *Arreglo;
};
//------------------------------------------------------------------------------
template <class Tipo> 
Pila<Tipo>::Pila(int t):tam(t),Tope(-1)
{ 
    if(Arreglo = new (nothrow) Tipo[tam])
        cout<<"\n";
    else
        throw Excepcion("No hay suficiente memoria");
}
//------------------------------------------------------------------------------
template <class Tipo> 
Pila<Tipo>::Pila(const Pila &P):tam(P.tam) , Tope(P.Tope)
{ 
    if(Arreglo = new (nothrow) Tipo[tam])
        for(int i=0;i<tam;i++) Arreglo[i] = P.Arreglo[i];
   else
        throw Excepcion("No hay suficiente memoria");
}
//******************************************************************************
template <class Tipo> 
Pila<Tipo>::~Pila()
{ 
    delete[] Arreglo;
}
//******************************************************************************
template <class Tipo>
void Pila <Tipo>::Push(const Tipo &X)
{
   if (!EstaLlena())  Arreglo[++Tope]=X;

}
//------------------------------------------------------------------------------
template <class Tipo>
Tipo Pila <Tipo>::Pop()
{
    if (!EstaVacia()){
        Tipo Aux = Arreglo[Tope--];
        return Aux;
    }
}
//------------------------------------------------------------------------------
template <class Tipo>
void Pila<Tipo>::Imprimir()const
{
   cout<<"Tope => "; 
   for(int i=Tope; i>=0; --i) cout<<Arreglo[i]<<"  ";
}
//------------------------------------------------------------------------------
template <class Tipo>
Tipo & Pila<Tipo>::operator=(const Tipo &A)
{ 
    if(this!=&A){
    if(tam!=A.tam){
        if (Arreglo)delete []Arreglo;
        tam=A.tam;
        if(!(Arreglo = new (nothrow) Tipo[tam])){
            throw Excepcion("No hay suficiente memoria para redimencionar la Pila");
        }
    }
    for(int i=0;i<tam;++i) Arreglo[i] = A.Arreglo[i];
    }
   return *this; 
}
//******************************************************************************
int main ()
{
   
   try{
   int valor,m;
   cout<<"Tamaño de la pila ";
   cin>>m;
   Pila<int> pInt(m);
  
   for (int i=0; i<m; ++i){
      cout<<"Valor: "; cin>>valor;
      pInt.Push(valor);
      cout<<endl;
   }
   
   while(!pInt.EstaVacia()){
      cout<<"Valor eliminado: "<<pInt.Pop()<<endl;
      pInt.Imprimir();
      cout<<endl;
   }
   
    }catch(Excepcion Ex){
        cout<< Ex.getMsn() <<endl;
    }
   system("pause");
   return 0;
}

