class matrice
{
protected:
    unsigned int dim_l, dim_c, size_; // dimension de la matrice, taille du vecteur val_
    double *val_;                     // tableau des valeurs de la matrice

public:
    virtual ~matrice();
    unsigned int dim() const { return size_; }; // retourne la taille du vecteur val_

    void alloc(unsigned int d)
    {
        size_ = d;
        val_ = new double[size_];
    };
    void dealloc()
    {
        if (val_ != nullptr)
        {
            delete[] val_;
        }
    };

    virtual double &operator()(unsigned int i, unsigned int j) = 0;

    matrice *copie_val(double);
    matrice *copie_val(matrice &);

    // matrice &operator+=(const matrice &);
    // matrice &operator*=(const matrice &);
    // matrice &operator/=(const double);

    // virtual void print() = 0;
};

class matrice_pleine : public matrice
{
public:
    matrice_pleine(unsigned int d = 0, const double &v0 = 0); //dim et val constante
    matrice_pleine(const matrice &);                          //constructeur par copie

    double &operator()(int i, int j);
    // void print();
};

class matrice_bande : public matrice
{
public:
    matrice_bande(unsigned int d = 0, const double &v0 = 0); //dim et val constante
    matrice_bande(const matrice &);                          //constructeur par copie

    double &operator()(int i, int j);
    // void print();
};