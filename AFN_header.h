class AFN
{
protected:
    int nrStari;

    string alfabet;

    vector<int> **tabel;

    int stInit;

    vector<int> stFin;

public:
    AFN();

    void setNrStari(int x){ nrStari=x; }
    int getNrStari() const { return nrStari; }

    void setAlfabet(string& s){ alfabet=s; }
    string& getAlfabet() const { string temp = alfabet; return temp; }

    void setStInit(int x){ stInit=x; }
    int getStInit() const { return stInit; }

    void setStFin(vector<int> x){ stFin=x; }
    vector<int> getStFin() const { return stFin; }

    void setTabel(vector<int> **x){ tabel=x; }
    vector<int>** getTabel() const { return tabel; }

    friend istream& operator>>(istream&, AFN&);

};

AFN::AFN()
{
    nrStari=0;
    alfabet="/0";
    stInit=-1;
}

istream& operator>>(istream& in, AFN& a)
{
    int x;
    in>>x;
    a.setNrStari(x);


    string s;
    in>>s;
    a.setAlfabet(s);

    in>>x;
    a.setStInit(x);

    vector<int> v;
    in>>x; //nr stari finale
    for(int i=0; i<x; i++)
    {
        int y;
        in>>y; //stare finala
        v.push_back(y);
    }
    a.setStFin(v);
    v=a.getStFin();

    vector<int> **temp;
    string alfabet=a.getAlfabet();

    temp = new vector<int>*[a.getNrStari()];

    for(int i=0; i<a.getNrStari(); i++)
    {
        temp[i] = new vector<int>[ alfabet.size() ];
    }

    for(int i=0; i<a.getNrStari(); i++)
    {
        for(int j=0; j<alfabet.size(); j++)
            temp[i][j].push_back(-1);
    }

    int stCur, stUrm;
    char lit;
    in>>x; //nr de tranzitii
    for(int i=0; i<x; i++)
    {
        in>>stCur>>stUrm>>lit;
        if(temp[stCur][lit-'a'][0]==-1)
            temp[stCur][lit-'a'].pop_back();
        temp[stCur][lit-'a'].push_back(stUrm);
    }
    a.setTabel(temp);
    temp=a.getTabel();

    for(int i=0; i<a.getNrStari(); i++)
    {
        for(int j=0; j<alfabet.size(); j++)
        {
            for(int it=0; it<temp[i][j].size(); it++)
                cout<<temp[i][j][it];
            cout<<" ";
        }
        cout<<endl;
    }

}

class AFD:public AFN
{
    vector< vector<int> > newStFin;
public:

    void addStare(vector<int>&);
    void toAFD();

    AFD& operator=(const AFN&);


    friend ostream& operator<<(ostream&, AFD&);
};

AFD& AFD::operator=(const AFN& a)
{
    nrStari=a.getNrStari();
    alfabet=a.getAlfabet();
    stInit=a.getStInit();
    stFin=a.getStFin();

    vector<int>** temp = new vector<int>*[nrStari];
    for(int i=0; i<nrStari; i++)
        temp[i]=new vector<int>[alfabet.size()];

    temp=a.getTabel();

    tabel = new vector<int>* [nrStari];
    for(int i=0; i<nrStari; i++)
    {

        tabel[i]=new vector<int> [ alfabet.size() + 1];

        for(int j=0; j<=alfabet.size(); j++)
        {
            if(j==0)
                tabel[i][j].push_back(i);
            else
                tabel[i][j]=temp[i][j-1];

        }
    }



    delete[] temp;

    return *this;

}

void AFD::addStare(vector<int>& v)
{
    vector<int> **temp = new vector<int>*[nrStari + 1];

    for(int i=0; i<=nrStari; i++)
    {
        temp[i] = new vector<int>[ alfabet.size() + 1];
    }

    for(int i=0; i<nrStari; i++)
    {
        for(int j=0; j<=alfabet.size(); j++)
            temp[i][j]=tabel[i][j];
    }

    temp[nrStari][0]=v;

    nrStari++;

    tabel=temp;
}

ostream& operator<<(ostream& out, AFD& a)
{
    for(int i=0; i<a.nrStari; i++)
    {
        for(int j=0; j<=a.alfabet.size(); j++)
        {
            for(int k=0; k<a.tabel[i][j].size(); k++)
                out<<a.tabel[i][j][k];
            out<<" ";
        }

        out<<endl;
    }
    out<<"Stari fin: ";
    for(int i=0; i<a.newStFin.size(); i++)
    {
        for(int j=0; j<a.newStFin[i].size(); j++)
            out<<a.newStFin[i][j];
        out<<" ";
    }
    return out;
}

void AFD::toAFD()
{

    for(int j=1; j<=alfabet.size(); j++)
    {
        int i=0;
        while(i<nrStari)
        {
            int k=0, gasit=0;
            while(k<nrStari)
            {
                if( tabel[i][j]==tabel[k][0] )
                    gasit=1;
                k++;
            }
            if(!gasit)
            {
                vector<int> temp;
                addStare(tabel[i][j]);
                for(int l=0; l<nrStari-1; l++)
                {
                    if(tabel[l][0].size()==1)
                    {
                        int x=tabel[l][0][0], found=0;
                        for(int it=0; it<tabel[nrStari-1][0].size(); it++)
                        {
                            if(tabel[nrStari-1][0][it]==x)
                                found=1;
                        }

                        if(found){

                        for(int c=1; c<=alfabet.size(); c++)
                        {
                            for(int it=0; it<tabel[l][c].size(); it++)
                                tabel[nrStari-1][c].push_back(tabel[l][c][it]);

                            vector<int>::iterator it;
                            it = unique( tabel[nrStari-1][c].begin(), tabel[nrStari-1][c].end() );
                            tabel[nrStari-1][c].resize( distance(tabel[nrStari-1][c].begin(), it) );

                        }

                        }
                    }
                }
            }

            i++;
        }
        for(int i=0; i<nrStari; i++)
        {
            bool ok=false;
            for(int j=0; j<stFin.size(); j++)
                for(int k=0; k<tabel[i][1].size(); k++)
                    if( stFin[j]==tabel[i][1][k] )
                        ok=true;
            if(ok)
                newStFin.push_back( tabel[i][1] );
        }
    }
}

