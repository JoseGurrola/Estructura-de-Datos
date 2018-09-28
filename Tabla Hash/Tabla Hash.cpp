#include <iostream>
#include <cstdlib>
#include "Excepcion.h"
#include "Lista.h"
#include <cstring>
#include <conio.h>

using namespace std;

//************TablaSimbolos*******************************************************
template<class Tipo>
class TablaSimbolos{
  public:
      TablaSimbolos(int _tam) : tam(_tam), Tabla(NULL) { Tabla = new (nothrow) Lista<Tipo>[tam]; } //constructor
      TablaSimbolos(const TablaSimbolos<Tipo> &T):Tabla(NULL){*this = T;} //constructor de copias
      ~TablaSimbolos(){Vaciar();} //destructor

      int HashString(string); //Regresa la clave de la lista a la que pertenece el string
      void ReHash(); //redimenciona el tamaño de la tabla cuando una lista tenga muchos elementos
      void Insertar(const Tipo &);
      int Buscar(const Tipo &);
      bool Eliminar(const Tipo &);
      void Imprimir();
      void Vaciar(){ for(int i=0; i<tam; ++i) Tabla[i].Vaciar();}
      TablaSimbolos& operator=(const TablaSimbolos<Tipo> &); //Tabla A = Tabla B
  private:
      Lista<Tipo> *Tabla;
      int tam;
};
//**********Hashing*************************************
template<class Tipo>
int TablaSimbolos<Tipo>::HashString(string cadena)
{
    int k=cadena.size();
    int u=0,n=0;

    for (int i=0; i<k; i++){
        n=(int)cadena[i];
        u+=i*n%tam;
    }
    return u%tam;
}
//***********ReHash****************************************
//Si una de las listas es muy larga, redimenciona la tabla.
template<class Tipo>
void TablaSimbolos<Tipo>::ReHash()
{
   if(Lista<Tipo> *Tabla2= new (nothrow) Lista<Tipo>[tam*2]){
      int tam2=tam;
      tam+=tam;
      for(int i=0;i<tam2;++i){
      while(!Tabla[i].EstaVacia()){
            Tabla2[HashString(Tabla[i].ObtenerPrimero())].Poner(Tabla[i].ObtenerPrimero());
            Tabla[i].Quitar(Tabla[i].ObtenerPrimero());
         }
      }
      Tabla = Tabla2;
          cout<<"Redimencionando Tabla "<<tam<<endl;
   }else{
      throw Excepcion("No hay memoria suficiente\n");
   }
}
//****************Insertar elemento en la tabla************************
template<class Tipo>
void TablaSimbolos<Tipo>::Insertar(const Tipo &_valor)
{
   int aux = HashString(_valor);
   Tabla[aux].Poner(_valor);

   if(Tabla[aux].TamLista()>(tam*.5))  ReHash();
}
//****************Buscar elemento en la tabla**************************
template<class Tipo>
int TablaSimbolos<Tipo>::Buscar(const Tipo &_valor)
{
   int aux = HashString(_valor);
   if(Tabla[aux].Buscar(_valor)==false){
        cout<<"El elemento "<<_valor<<" no se encuentra.\n";
	    return -1;
   }else{
     	cout<<"la tabla donde se localiza el \""<<_valor<<"\" es: F"<<aux<<endl<<endl;
     	 return aux;

   }
}
//*******************Eliminar un elemento de la tabla*****************
template<class Tipo>
bool TablaSimbolos<Tipo>::Eliminar(const Tipo &_valor)
{
   int aux = HashString(_valor);

   if(Tabla[aux].Quitar(_valor)){
      return true;
   }else{
      throw Excepcion("La cadena no se encuentra en la tabla\n");
      return false;
   }

}
//*******************Imprimir tabla***********************************
template<class Tipo>
void TablaSimbolos<Tipo>::Imprimir()
{
 for(int i=0;i<tam;++i){
   cout<<"F"<<i<<": ";
   Tabla[i].Imprimir();
   cout<<endl;
 }
}
//***************Operator=*******************************************
template<class Tipo>
TablaSimbolos<Tipo>& TablaSimbolos<Tipo>::operator=(const TablaSimbolos<Tipo>& T)
{
   if(tam!=T.tam){
      Lista<Tipo> *nuevo = new (nothrow) Lista<Tipo>[T.tam];
      delete[] Tabla;
      Tabla=nuevo;
      tam=T.tam;
   }
   Tipo *Arreglo;
   for(int i=0;i<tam;++i){
      Arreglo = T.Tabla[i].ObtenerDatos();
      for(int j=0;j<T.Tabla[i].TamLista();++j){
         Tabla[i].Poner(Arreglo[j]);
      }
   }
   return *this;
}
//*******************************************************************
int main ()
{
    int tam, opcion;
    string cadena;
    try{
    	TablaSimbolos<string> T(10);

        do{
            system("cls");
            cout<<"\n\t\t\t\tTabla De Simbolos\n";
            cout<<"Que desea hacer?:\n  0)Salir\n  1)Insertar\n  2)Eliminar\n  3)Buscar\n  4)Imprimir tabla\n";
            do{
               cout<<"\t\t\t\t\tOpcion: ";
               cin>>opcion;
               if(opcion<0 || opcion>4) cout<<"Error: Opcion incorrecta\n";
            }while(opcion<0 || opcion>4);

            if(opcion==0) exit(0);

            switch(opcion){
                case 1:
                    cout<<"Ingrese la cadena a insertar: ";
                    cin>>cadena;
                    T.Insertar(cadena);
                break;
                case 2:
                    cout<<"Ingrese la cadena a eliminar: ";
                    cin>>cadena;
                    T.Eliminar(cadena);
                break;
                case 3:
                    cout<<"Ingrese la cadena a buscar: ";
                    cin>>cadena;
                    T.Buscar(cadena);
                    system("pause");
                break;
                case 4:
                    T.Imprimir();
                    system("pause");
                break;
            }
        }while(opcion!='0');

   }catch(Excepcion &Ex){
      cout<<Ex.getMsn();
    }
   system("pause");
}
