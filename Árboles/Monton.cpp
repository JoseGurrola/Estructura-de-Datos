/*
  Programa: Monton.cpp
  Autor: José Juan Gurrola Cota
  Fecha: 23 /11/2014
  Descripcion: Programa que implementa un montón minimo y un maximo
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
//****************************Clase Monton**************************************
template <class Tipo>
class Monton{
public:
    explicit Monton(int);//contructor
    Monton(const Monton<Tipo> &M): dim(0), Comp(NULL){ *this=M;} //constructor de copias
    ~Monton(){ borrar();}
    Monton<Tipo> &operator=(const Monton &);
    void Imprimir() const;
    void InsertarMinimo(const Tipo);
    void InsertarMaximo(const Tipo);
    void Eliminar();
    Tipo ObtenerPrimero(){return Comp[0];}
    void borrar(){ delete[] Comp; }
private:
    Tipo *Comp;
    int dim, cont;
};
//******************************************************************************
template <typename Tipo>
Monton<Tipo>::Monton(int tam): dim(tam), cont(0)
{
    if(Comp= new (nothrow) Tipo[tam])
       for (int i=0;i<dim;Comp[i++]=0);
    else throw Excepcion("No hay memoria disponible...\n");
}
//******************************************************************************
template <typename Tipo>
Monton<Tipo> & Monton<Tipo>::operator=(const Monton<Tipo> &M )
{
    if(this!=&M){
        if(dim!=M.dim){
            if(Comp) delete [] Comp;
            dim=M.dim;
            if(!(Comp=new (nothrow) float[dim])){
                throw Excepcion("No hay memoria disponible...");
            }
        }
        for(int i=0; i<dim; ++i) Comp[i]= M.Comp[i];
    }
    return *this;
}
//******************************************************************************
template <typename Tipo>
void Monton<Tipo>::InsertarMinimo(const Tipo dato)
{
    int ant=cont-1, actual=cont;
    Tipo aux;


    if(ant==-1) Comp[cont]= dato;
    else{
        Comp[actual]=dato;
        while(dato<Comp[ant] && ant>-1){
           aux=Comp[ant];
           Comp[ant]=Comp[actual];
           Comp[actual]= aux;
           --ant;
           --actual;
        }
    }
    ++cont;
}
//******************************************************************************
template <typename Tipo>
void Monton<Tipo>::InsertarMaximo(const Tipo dato)
{
    int ant=cont-1, actual=cont;
    Tipo aux;


    if(ant==-1) Comp[cont]= dato;
    else{
        Comp[actual]=dato;
        while(dato>Comp[ant] && ant>-1){
           aux=Comp[ant];
           Comp[ant]=Comp[actual];
           Comp[actual]= aux;
           --ant;
           --actual;
        }
    }
    ++cont;
}
//******************************************************************************
template <typename Tipo>
void Monton<Tipo>::Eliminar()
{
    if(cont==0)  throw Excepcion("No hay Elementos en el monton\n");
    int i=0;
    while(i<cont){
       Comp[i]=Comp[i+1];
       ++i;
    }
     --cont;
}
//******************************************************************************
template <typename Tipo>
void Monton<Tipo>::Imprimir() const
{
    cout<<"(";
    for(int i=0;i<cont;++i) cout<<Comp[i]<<", ";
    cout<<"\b\b)"<<endl;
}
//******************************************************************************
//******************************************************************************
int main()
{
    try{
        cout<<"\n\t\t\tMonton minimo\n\n";
        Monton<int> Mmin(100);
        Mmin.InsertarMinimo(3);
        Mmin.InsertarMinimo(5);
        Mmin.InsertarMinimo(4);
        Mmin.InsertarMinimo(6);
        Mmin.Imprimir();
        Mmin.InsertarMinimo(1);
        Mmin.InsertarMinimo(2);
        Mmin.InsertarMinimo(-5);
        Mmin.InsertarMinimo(0);
        Mmin.Imprimir();
        Mmin.Eliminar();
        Mmin.Imprimir();
        cout<<"El minimo es: "<<Mmin.ObtenerPrimero()<<endl;
    //---------------------------------------------------------------------------
        cout<<"\n\t\t\tMonton maximo\n\n";
        Monton<int> Mmax(100);
        Mmax.InsertarMinimo(-3);
        Mmax.InsertarMaximo(-5);
        Mmax.InsertarMaximo(0);
        Mmax.InsertarMaximo(8);
        Mmax.Imprimir();
        Mmax.InsertarMaximo(11);
        Mmax.InsertarMaximo(5);
        Mmax.InsertarMaximo(-5);
        Mmax.InsertarMaximo(7);
        Mmax.Imprimir();
        Mmax.Eliminar();
        Mmax.Imprimir();
        cout<<"El maximo es: "<<Mmax.ObtenerPrimero()<<endl;

    }catch(Excepcion Ex){
        cout<< Ex.getMsn() <<endl;
    }
    cout<<endl<<endl;
    system("PAUSE");
    return 0;
}

