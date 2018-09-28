#include <iostream>
#include <cstdlib>
#include <cstring>
#ifndef Excepcion_h
#define Excepcion_h

using namespace std;

class Excepcion{
   public:
      Excepcion(const char *mensaje){strcpy(msn, mensaje);}
      const char* getMsn(){return msn;}
   private:
      char msn[50];


};
#endif
