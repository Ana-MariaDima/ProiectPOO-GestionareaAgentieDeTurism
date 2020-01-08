#include <iostream>
#include<cstring>
#include <string.h>
#include <vector>
#include <typeinfo>
#include <cstdlib>

using namespace std;

///rtti
///set pt specializarea facuta la ultimul laborator
///supraincarcare operatori de citire prin transmitere
int nr_locuinte;
class locuinta{

protected:
    char *nume_client;
    int suprafata_utila;
    float discount;


public:
    locuinta();
    locuinta(char *, int, float);
    ~locuinta();
    locuinta (const locuinta &);
    locuinta &operator=(const locuinta &);


   virtual void citire()=0;
    virtual void afisare()
    {
        cout<<"Nume client: "<<nume_client<<endl;
        cout<<"Suprafata utila: "<<suprafata_utila<<" m^2"<<endl;
        cout<<"Discountul aplicat: "<<discount<<"%"<<endl;
    }
    virtual void chirie()=0;
    friend class apartament;

    friend istream& operator >>(istream&, locuinta&);
};
 istream& operator >> (istream& in, locuinta& l)
    {
         cout<<"introduceti numele propietarului"<<endl;

        char x[100];
       cin>>x;
        l.nume_client=new char [strlen(x)+1];
        strcpy(l.nume_client,x);
       // in>>l.nume_client;
        if(in.fail())
        {
            in.clear();
            in.ignore();
            cout<<"Ai introdus tipul de data gresit!"<<endl;
            cout<<"numele corect al clientului este = "<<endl;
            in>>l.nume_client;
            }
        cout<<"Suprafata utila a locuintei este:"<<endl;

        in>>l.suprafata_utila;
         if(in.fail())
        {
            in.clear();
            in.ignore();
            cout<<"Ai introdus tipul de data gresit!"<<endl;
            cout<<"Suprafata utila corecta a locuintei este = "<<endl;
            in>>l.suprafata_utila;
        }

        cout<<"Discountul aplicat este:"<<endl;
        in>>l.discount;
 if(in.fail())
        {
            in.clear();
            in.ignore();
            cout<<"Ai introdus tipul de data gresit!"<<endl;
            cout<<"Discount-ul corect aplicat locuintei este = "<<endl;
            in>>l.discount;
        }
        else
        {
            if(l.discount<0 || l.discount>10)
            {
                in.clear();
                in.ignore();
                cout<<"Discount-ul se afla numai in intervalul 0-10%"<<endl;
                cout<<"Discount-ul citit corect este = "<<endl;
                in>>l.discount;
            }
        }

        return in;
    }
locuinta::locuinta(){}

locuinta::locuinta(char * x, int y, float z)
{
    nume_client=new char [strlen(x)+1];
    strcpy(nume_client,x);
    suprafata_utila=y;
    discount=z;
}
locuinta::~locuinta(){
cout <<"";
}

locuinta::locuinta(const locuinta &sursa)
{

    nume_client=new char [strlen(sursa.nume_client)+1];
    strcpy(nume_client,sursa.nume_client);
    suprafata_utila=sursa.suprafata_utila;
    discount=sursa.discount;

}
locuinta & locuinta::operator =(const locuinta &sursa )
{
    if(this!=&sursa)
    {
    delete nume_client;
    nume_client=new char [strlen(sursa.nume_client)+1];
    strcpy(nume_client,sursa.nume_client);
    suprafata_utila=sursa.suprafata_utila;
    discount=sursa.discount;

    }

    return *this;
}
/*
void locuinta::citire()
{

    cout<<"introduceti numele propietarului"<<endl;

        char x[100];
        cin>>x;
        nume_client=new char [strlen(x)+1];
        strcpy(nume_client,x);
//delete x;
    cout<<"introduceti suprafata utila"<<endl;

    cin>>suprafata_utila;

    cout<<"introduceti discount:"<<endl;
    cin >>discount;
    while(discount<0 || discount>10)
{
    cout<<" va rugam sa ointroduceti un discount cuprins intre 0 si 10 "<<endl;
    cin>>discount;
}
//cout <<"numele clientului este "<<nume_client<<endl;

}*/
/*
void locuinta::afisare()
{
    cout<<"Numele clientului este :"<<endl;
    cout <<nume_client;
}*/

 class apartament:public locuinta
 { protected:

 const string tip_locuinta = "Apartament";

     int etaj;
 public:
     apartament():locuinta(){};
     apartament(char * x, int y, float z, int q):locuinta( x, y, z)
     {
         etaj=q;
     }
     ~apartament(){};


    apartament(const apartament& A):locuinta(A)
    {
        etaj = A.etaj;

        //cout<<"CC Apartament"<<endl;
    }


    apartament &operator=(const apartament &);

    friend istream& operator >>(istream& in, apartament& A)
    {
      in>>(locuinta&) A;
        cout<<"Numarul de etaje: ";
        in>>A.etaj;

        return in;

    }



   virtual void citire()
   {
       cout<<"introduceti numele proprietarului"<<endl;

        char x[100];
        cin>>x;
        nume_client=new char [strlen(x)+1];
        strcpy(nume_client,x);
//delete x;
	//cout <<nume_client;
cout<<"introduceti suprafata utila"<<endl;

cin>>suprafata_utila;

cout<<"introduceti discount:"<<endl;
cin >>discount;
while(discount<0 || discount>10)
{
    cout<<" va rugam sa ointroduceti un discount cuprins intre 0 si 10 "<<endl;
    cin>>discount;
}
//cout <<"numele clientului este "<<nume_client<<endl;
cout<<"etaj"<<endl;
cin>>etaj;

   }

 virtual void afisare()
 {
        cout<<endl;
        cout<<"Tip locuinta"<< tip_locuinta<<endl;
        locuinta::afisare();
        cout<<"Numar etaje: "<<etaj<<endl;

    }


    virtual void chirie()
    {
        float chirie;
        int mp_ap, validare;

        cout<<"Introduceti pretul chiriei pe metrul patrat : ";
        cin>>mp_ap;
        cout <<"Doriti sa aplicam discount? "<<endl<<"1=DA"<<endl<<"0=NU"<<endl;
        //validare= cu sau fara discount aplicat
        cin >>validare;
        //validare= cu sau fara discount aplicat
        cout<<"Pretul chiriei pentru locuinta data avand suprafata utila de "<<suprafata_utila<<" metrii patrati "<<"este: ";

        chirie=float(mp_ap*suprafata_utila*(1-validare*discount/100.0));
           cout <<chirie;
    }
 };

apartament & apartament::operator =(const apartament &A )
{
    if(this != &A)
        {
            this->etaj = A.etaj;
            this->locuinta::operator=(A);
        }


    return *this;
}
float s=0;

class casa:public locuinta
{
    protected:
    int curte;
    int nrEtaje;
    float *suprafata_etaje;
    float chirie_casa;
     const string tip_locuinta = "Casa";

    public:
        casa():locuinta(){};
     casa(char * x, int y, float z, int q, int t, float * w, float c):locuinta( x, y, z)
     {
         curte=q;
         nrEtaje=t;
         chirie_casa=c;
         w=new float [t];
         for(int i=0; i<t; i++)

            {

                cin >>w[i];
                suprafata_etaje[i]=w[i];
            }

     }
     ~casa(){};


casa(const casa& C):locuinta(C)
    {
        curte = C.curte;
        nrEtaje = C.nrEtaje;
        suprafata_etaje = new float[nrEtaje+1];
        for(int i=0; i<nrEtaje; i++)
            suprafata_etaje[i] = C.suprafata_etaje[i];


    }
        friend istream& operator >>(istream& in, casa& C)
    {

        in>>(locuinta&) C;
        cout<<"Suprafata curte: ";
        in>>C.curte;
        cout<<"Numarul de etaje: ";
        in>>C.nrEtaje;
        C.suprafata_etaje = new float[C.nrEtaje+1];
        cout<<"Suprafata etajelor este:"<<endl;
        for(int i=0; i<C.nrEtaje; i++)
        {
            cout<<"Etaj "<<i+1<<": ";
            in>>C.suprafata_etaje[i];
        }

  //  C.chirie();



        return in;
    }

casa &operator=(const casa &);



   virtual void citire()
   {
       suprafata_utila=0;
    cout<<"introduceti numele propietarului"<<endl;

        char x[100];
        cin>>x;
        nume_client=new char [strlen(x)+1];
        strcpy(nume_client,x);
//delete x;
	//cout <<nume_client;

cout<<"introduceti discount:"<<endl;
cin >>discount;
while(discount<0 || discount>10)
{
    cout<<" va rugam sa ointroduceti un discount cuprins intre 0 si 10 "<<endl;
    cin>>discount;
}
//cout <<"numele clientului este "<<nume_client<<endl;
cout<<"introduceti suprafata curtii: "<<endl;
cin>>curte;

cout<<"nr de etaj"<<endl;

cin>>nrEtaje;
float *suprafata_etaje=new float [nrEtaje];
         for(int i=0; i<nrEtaje; i++)

            {

                cout<<"Introduceti suprafata etaj "<<i+1<<" ";
                cin >>suprafata_etaje[i];
                //suprafata_etaje[i]=w[i];
                suprafata_utila=suprafata_utila+suprafata_etaje[i];
            }
/*for(int i=0; i<nrEtaje; i++)
{
    cout<<"Suprafatat etajului "<<i+1<<" este "<<suprafata_etaje[i]<<endl;
}
*/
chirie();
//chirie_casa=chirie_aux;

   }
 virtual void afisare()

{
    cout<<"Tip locuinta: "<<tip_locuinta<<endl;
    cout<<"Numele clientului este :"<<endl;
    cout <<nume_client<<endl;
    cout<<"suprafata uila :"<<suprafata_utila<<endl;
    cout<<"discount: "<<discount<<endl;
    cout<<"dimensiune curte: "<<curte<<endl;
    cout<<"Nr etaje: "<<nrEtaje<<endl;


for(int i=0; i<nrEtaje; i++)
{
    cout<<"Suprafatat etajului "<<i+1<<" este "<<suprafata_etaje[i]<<endl;
}
//cout<<"pretul chiriei este "<<chirie<<endl;
    //cout <<"Chiria casei este "<<chirie_casa<<endl;

}

virtual void chirie()
    {
        int mp_ap, mp_curte,validare;

        cout<<"Introduceti pretul chiriei pe metrul patrat : ";
        cin>>mp_ap;
        cout<<"Introduceti pretul chiriei pe metrul patrat al curtii :";
        cin>>mp_curte;
        cout <<"Doriti sa aplicam discount? "<<endl<<"1=DA"<<endl<<"0=NU"<<endl;
        //validare= cu sau fara discount aplicat

        cin >>validare;
         cout<<"Pretul chiriei pentru locuinta data avand suprafata utila de "<<suprafata_utila
         <<" metrii patrati si cu o gradina de "<<curte<<" metrii patrati este: "<<endl;
        chirie_casa=float((mp_ap*suprafata_utila+mp_curte*curte)*(1-validare*discount/100.0));
           cout <<chirie_casa<<endl;

           s=s+chirie_casa;
           cout<<endl;
           cout<<"profitul firmei este in urma chiriilor este "<<s<< endl<<endl;
    }

};

casa & casa::operator =(const casa &sursa )
{
    if(this!=&sursa)
    {
    delete nume_client;
    nume_client=new char [strlen(sursa.nume_client)+1];
    strcpy(nume_client,sursa.nume_client);
    suprafata_utila=sursa.suprafata_utila;
    discount=sursa.discount;
    curte=sursa.curte;
    nrEtaje=sursa.nrEtaje;


    }

    return *this;
}

template <class T>
class gestiune
{
    vector <pair<T, int> > v;
    static int id;

public:
    void citire();
    void afisare();
    gestiune();
    gestiune<T> &operator +=(T &ob)
    {
        ob.id++;
    }


};


template <class T>
int gestiune <T>::id=0;


template<class T>

gestiune<T>::gestiune()
{
    id++;
}

template <class T>
void gestiune<T>::citire()
{
    cout <<"introduceti nr de apartamente pe care doriti sa le cititi"<<endl;
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
    {
        T ob;
    ob.citire();
    //*this+=ob;
    v.push_back(make_pair(ob,id));
    gestiune();
    }
}
template<class T>
void gestiune <T>::afisare()
{
    vector < pair <apartament, int> >::iterator pointer;
    for(pointer=v.begin(); pointer!=v.end(); pointer++)
    {
        cout<<pointer->second << " ";
        (pointer->first).afisare();
        cout<<endl;

    }

}
template <>
 class gestiune<casa>
{
   vector <casa> ca;
   int n;
public:
    gestiune(){n=0;}
    void citire();
    void afisare();
    void suma_chirie();
};
//specializare pt case

void gestiune<casa>::citire()
{
     cout<<"Introduceti nr de casa pe care doriti sa il cititi"<<endl;

     cin>>n;
    // int vec_chirie[n];
     for(int i=0; i<n; i++)

   {

   casa x;
//cin>>x;
    x.citire();
   // x.chirie();
    ca.push_back(x);
   }
}

void gestiune <casa>::afisare()
{
    vector  <casa> ::iterator pointer;
    for(pointer=ca.begin(); pointer!=ca.end(); pointer++)
    {
        //cout<<pointer->second << " ";
        pointer->afisare();
        cout<<endl;

    }

}
int main()
{

        apartament A;

        casa C;
         gestiune<apartament> ap;
         gestiune<casa> ca;

    int alegere;
    int valid_chirie;
    while(1)
    {
        cout<<endl;
        cout <<"Alegeti nr corespunzator operatiunii pe care doriti sa o efectuati"<<endl;
        cout<<"1.Cititi informatiile corespunzatoare unui singur apartament"<<endl;
        cout<<"2.Cititi informatiile corespunzatoare unuei singure case"<<endl;
        cout<<"3.Cititi informatiile corespunzatoare mai multor apartamente (folosind gestiunea)"<<endl;
        cout<<"4.Cititi informatiile corespunzatoare mai multor case (folosind specializarea)"<<endl;
        cin>>alegere;
        switch(alegere)
        {
        case 1:
            ///Apartament
            cin>>A;
            A.afisare();
            cout <<"Doriti si calcularea chiriei corespunzatoare apartamentului citit ? "<<endl;

            cout<< "1. DA, doresc calcului chirie. "<<endl;
            cout<< "0. NU, nu doresc calculul chiriei"<<endl;
            cin>>valid_chirie;
            switch(valid_chirie)
            {


        case 1:

            A.chirie();
            break;
        case 0:
            break;
            }
    break;

        case 2:
             ///Casa
            cin>>C;
            C.afisare();
            cout <<"Doriti si calcularea chiriei corespunzatoare casei citit ? "<<endl;

            cout<< "1. DA, doresc calcului chirie. "<<endl;
            cout<< "0. NU, nu doresc calculul chiriei"<<endl;
            cin>>valid_chirie;
            switch(valid_chirie)
            {


        case 1:

            C.chirie();
            break;
        case 0:
            break;
            }
            break;

        case 3:
            //gestiune de tip apartament a n ob

    ap.citire();
  // cin>>ap;
    ap.afisare();
    break;

        case 4:
            //specializare pt gestiune a n ob de tip casa

   ca.citire();
    ca.afisare();

        }


    }

    /*
    //citire informatie pt un apartament
    apartament *a=new apartament;
    a->citire();
    a->afisare();
    a->chirie();*/
/*
    ///Apartament
    apartament A;
    cin>>A;
    A.afisare();
    A.chirie();
    /*
    //citire informatie pentru o casa
    casa *c=new casa;
    c->citire();
    c->afisare();
    c->chirie();*/
/*
    ///Casa
    casa C;
    cin>>C;
    C.afisare();
    */

/*
    //gestiune de tip apartament a n ob
    gestiune<apartament> ap;
    ap.citire();
  // cin>>ap;
    ap.afisare();
*/
/*
   //specializare pt gestiune a n ob de tip casa
   gestiune<casa> ca;
   ca.citire();
    ca.afisare();*/

    return 0;
}
