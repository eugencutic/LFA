#include "AFN_header.h"

class AFD:public AFN
{
public:
    AFD(const AFN&);

    friend ostream& operator<<(ostream&, AFD&);
};

AFD::AFD(const AFN& a)
{
    nrStari=a.nrStari;
    alfabet=a.alfabet;
    stInit=a.stInit;
    stFin=a.stFin;

    tabel = new vector<int>* [nrStari + 1];
    for(int i=0; i<=nrStari; i++)
    {
        tabel[i]=new vector<int> [ alfabet.size() + 1];
        for(int j=0; j<=alfabet.size(); j++)
            if(j==0)
                tabel[i][j]=i;
            else
                tabel[i][j]=a.tabel[i-1][j-1];
    }

}

ostream& operator<<(ostream& out, AFD&)
{
    for(int i=1; i<=nrStari; i++)
    {
        for(int j=1; j<=alfabet.size(); j++)
            out<<tabel[i][j];
    }
    return out;
}
