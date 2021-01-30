#include <cstdlib>
#include <cmath>
#include "vecteur.hpp"

//utilitaire de messages d'erreur
void stop(const char * msg)
{
  cout<<"ERREUR classe vecteur, " << msg;
  exit(-1);
}

void test_dim(int d1, int d2, const char * org)
{
  if(d1==d2)  return;
  cout<<org<<" ("<<d1<<","<<d2<<") dimensions incompatibles";
  exit(-1);
}
