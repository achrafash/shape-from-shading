#include "vecteur.hpp"
#include <cmath>
#include <cstdlib>

//utilitaire de messages d'erreur
void stop(const char *msg)
{
    cout << "ERREUR classe vecteur, " << msg;
    exit(-1);
}
void test_dim(int d1, int d2, const char *org)
{
    if (d1 == d2)
        return;
    cout << org << " (" << d1 << "," << d2 << ") dimensions incompatibles";
    exit(-1);
}

// constructeurs-destructeur
template <typename T>
vecteur<T>::vecteur(int d, const T &v0) //dim et val constante
{
    init(d);
    for (int i = 0; i < dim_; i++)
        val_[i] = v0;
}
template <typename T>
vecteur<T>::vecteur(const vecteur<T> &v) //constructeur par copie
{
    init(v.dim_);
    for (int i = 0; i < dim_; i++)
        val_[i] = v.val_[i];
}
template <typename T>
vecteur<T>::~vecteur()
{
    clear();
}

template <typename T1>
void vecteur<T>::init(int d) //initialisation avec allocation dynamique
{
    if (d < 0)
        stop("init() : dimension <0");
    dim_ = d;
    val_ = 0;
    if (d > 0)
        val_ = new T[d];
}
template <typename T>
void vecteur<T>::clear() //d�sallocation
{
    if (val_ != 0)
        delete[] val_;
    dim_ = 0;
}

// //assignation
// template <typename T>
// vecteur<T> &vecteur<T>::operator=(const vecteur<T> &v) //assignation d'un vecteur
// {
//   if (dim_ != v.dim_) //redimensionnement
//   {
//     clear();
//     init(v.dim_);
//   }
//   //recopie
//   for (int i = 0; i < dim_; i++)
//     val_[i] = v.val_[i];
//   return *this;
// }
template <typename T>
vecteur<T> &vecteur<T>::operator=(const T &x) //assignation d'une valeur
{
    for (int i = 0; i < dim_; i++)
        val_[i] = x;
    return *this;
}

// //op�rateurs alg�briques
// vecteur& vecteur::operator +=(const vecteur & v)
// {
//   test_dim(dim_,v.dim_,"op +=");
//   for(int i=0;i<dim_;i++) val_[i]+=v.val_[i];
//   return *this;
// }
// vecteur& vecteur::operator -=(const vecteur & v)
// {
//   test_dim(dim_,v.dim_,"op -=");
//   for(int i=0;i<dim_;i++) val_[i]-=v.val_[i];
//   return *this;
// }
// vecteur& vecteur::operator +=(double x)
// {
//   for(int i=0;i<dim_;i++) val_[i]+=x;
//   return *this;
// }
// vecteur& vecteur::operator -=(double x)
// {
//   for(int i=0;i<dim_;i++) val_[i]-=x;
//   return *this;
// }
// vecteur& vecteur::operator *=(double x)
// {
//   for(int i=0;i<dim_;i++) val_[i]*=x;
//   return *this;
// }
// vecteur& vecteur::operator /=(double x)
// {
//   if(x==0) stop("op /= : division par 0");
//   for(int i=0;i<dim_;i++) val_[i]/=x;
//   return *this;
// }

// //op�rateurs externes
// template <typename T>
// vecteur<T> operator+(const vecteur<T> &u) //+ unaire (ne fait rien)!
// {
//   return u;
// }
// vecteur<T> operator-(const vecteur<T> &u) //- unaire : chgt de signe
// {
//   vecteur<T> w = u;
//   return w *= -1.;
// }
// vecteur operator +(const vecteur & u,const vecteur & v)
// {vecteur w=u; return w+=v;}
// vecteur operator -(const vecteur & u,const vecteur & v)
// {vecteur w=u; return w-=v;}
// vecteur operator +(const vecteur & u,double x)
// {vecteur w=u; return w+=x;}
// vecteur operator -(const vecteur & u,double x)
// {vecteur w=u; return w-=x;}
// vecteur operator *(const vecteur & u,double x)
// {vecteur w=u; return w*=x;}
// vecteur operator /(const vecteur & u,double x)
// {vecteur w=u; return w/=x;}
// vecteur operator +(double x,const vecteur & u)
// {vecteur w=u; return w+=x;}
// vecteur operator -(double x,const vecteur & u)
// {vecteur w=-u; return w-=x;}
// vecteur operator *(double x,const vecteur & u)
// {vecteur w=u; return w*=x;}
// double operator|(const vecteur & u,const vecteur & v)
// {
//     test_dim(u.dim(),v.dim(),"op |");
//     double s=0;
//     for(int i=1;i<=u.dim();i++) s+=u(i)*v(i);
//     return s;
// }
// double norme(const vecteur & u)
// {return sqrt(u|u);}

// //op�rateurs de comparaison
// bool operator == (const vecteur & u,const vecteur & v)
// {
//     if(u.dim()!=v.dim()) return false;
//     for(int i=1;i<=u.dim();i++)
//         if(u(i)!=v(i)) return false;
//     return true;
// }
// bool operator != (const vecteur & u,const vecteur & v)
// {return !(u==v);}

//op�rateur de flux
template <typename T>
ostream &operator<<(ostream &os, const vecteur<T> &u)
{
    if (u.dim() <= 0)
    {
        os << "()";
        return os;
    }
    os << "(";
    for (int i = 1; i < u.dim(); i++)
        os << u(i) << ",";
    os << u(u.dim()) << ")";
    return os;
}
