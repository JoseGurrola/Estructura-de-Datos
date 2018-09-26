
#include <iostream>
#include <cstdlib>
#define MAX 10
using namespace std;

class Pila{
    public:
        Pila(){Tope = -1;}
        bool EstaLLena() const { (Tope == MAX-1) ? true : false;}
        bool EstaVacia() const { (Tope == -1) ? true : false;}
        void Imprimir() const;
        void Push(const int &);
        void Pop();
        int ObtenerTope() const {return Arreglo[Tope];}
    private:
        int Tope;
        int Arreglo[MAX];
};
//-------------------------------------------------------------------------------------------------------------------------------------------
void Pila::Push(const int &X)
{
   if (!EstaLLena()){
      ++Tope;
      Arreglo[Tope]=X;
      //cout<<Arreglo[Tope]<<endl;
   }
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void Pila::Pop()
{
    bool Pila = EstaVacia();
    if (Pila == false){
        int Aux;
        Aux = Arreglo[Tope];
        --Tope;
    }
}
//------------------------------------------------------------------------------------------------------------------
void Pila::Imprimir() const
{
    cout<<"Tope-> ";
    for(int i=Tope;i>=0;--i)
        cout<< Arreglo[i]<<" "; cout<<endl;
}
//-----------------------------------------------------------------------------------------------
int main ()
{
    Pila P;
    P.Push(5);
    P.Push(8);
    P.Push(4);
    P.Push(1);
    P.Push(2);
    P.Push(3);
    P.Imprimir();
    P.Pop();
    P.Imprimir();
    cout<<"El tope es: "<<P.ObtenerTope()<<endl;
    P.Pop();
    P.Imprimir();



    system("pause");
    return 0;
}
