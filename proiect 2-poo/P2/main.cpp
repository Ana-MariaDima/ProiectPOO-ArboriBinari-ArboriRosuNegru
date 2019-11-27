#include <iostream>

using namespace std;

class node
{
protected:
    int key;

    node *st;
    node *dr;

public:
    //constructori
    node();
    node(int);

    //copiere
    node(const node&);

    //destructor
    ~node();
    friend istream& operator >>(istream&, node&);
    friend ostream& operator <<(ostream&, node&);
    friend  void  operator ==(node,node);
    friend class ABC;
};
//constructor
node::node() {}
//parametrizare
node::node(int x)
{
    key=x;
}
//copiere
node::node(const node &n)
{

    key=n.key;
    st=n.st;
    dr=n.dr;
    cout<<"c";
}
node::~node()
{
    cout<<"d_nod ";
}
//supraincarcare citire
istream& operator >>(istream& in, node& ob)
{
    in>>ob.key;
    ob.st=NULL;
    ob.dr=NULL;
    return in;
}

//supraincarcare afisare
ostream& operator <<(ostream& out, node& ob)
{
    out<<ob.key<<endl;
    return out;

}
void  operator ==(node a,node b)
{
    if(a.key==b.key)
        cout<<"nodurile au aceiasi valoare";
    else
        cout <<"Nu";

}

class Nod_rosu_negru:public node
{
    //public:
    Nod_rosu_negru *parent;
    char color;
public:
    //constructori cu evidentiere
    Nod_rosu_negru():node()
    {
        parent=NULL;
        color='b';
    }
    Nod_rosu_negru(int x, char y):node(x)
    {
        parent=NULL;
        color=y;
    }
    /*
            Nod_rosu_negru(const Nod_rosu_negru  &n): node(const node &n)
            {
            parent=n.parent;
            color=n.color;
            }*/
    ~Nod_rosu_negru();
    friend istream& operator >>(istream&, Nod_rosu_negru&);
    friend ostream& operator <<(ostream&, Nod_rosu_negru&);
    friend  void  operator ==(Nod_rosu_negru,Nod_rosu_negru);
    friend class RBtree;
};
Nod_rosu_negru::~Nod_rosu_negru()
{
    cout<<"d_nod_rn ";
}
istream& operator >>(istream& in, Nod_rosu_negru& ob)
{
    in>>ob.key;
    ob.st=NULL;
    ob.dr=NULL;
    ob.parent=NULL;
    ob.color='b';
    return in;
}

//supraincarcare afisare
ostream& operator <<(ostream& out, Nod_rosu_negru& ob)
{
    out<<ob.key<<endl;
    return out;

}
void  operator ==(Nod_rosu_negru a,Nod_rosu_negru b)
{
    if(a.key==b.key&&a.color==b.color)
        cout<<"nodurile au aceiasi valoare si culoare";
    else
        cout <<"Nu";

}
class Arbore
{
protected:
    int nr_noduri;
    virtual void citire_nr_noduri()=0;
    virtual void adancime_rad_neagra(Nod_rosu_negru *p)=0;
    virtual void adancime()=0;
};
int n;
class ABC:public Arbore
{

protected:
    node *radacina;
public:
    ABC();
    ~ABC();

    void insert(int key);
    node *search(int key);
    void destroy_tree();
    void inorder_print();
    void postorder_print();
    void preorder_print();
    virtual void citire_nr_noduri()
    {
        cout<<"introduceti nr de noduri"<<endl;
        cin>>nr_noduri;
        insert(nr_noduri);
    }
    virtual void adancime_rad_neagra(Nod_rosu_negru *p) {}
    virtual void adancime() {}

    void destroy_tree(node *frunza);
    void insert(int key, node *frunza);
    node *search(int key, node *frunza);
    void inorder_print(node *frunza);
    void postorder_print(node *frunza);
    void preorder_print(node *frunza);

    friend istream& operator >>(istream&, ABC&);
    friend ostream& operator <<(ostream&, ABC&);
//    friend  ABC  operator =(ABC,ABC);


};
istream& operator >>(istream& in, ABC& ob)
{
    in>>(node&)ob;

    return in;
}

//supraincarcare afisare
ostream& operator <<(ostream& out, ABC& ob)
{
    out<<(node&)ob<<endl;
    return out;

}
/*
ABC operator =(ABC a,ABC b)
{
    (node&)a=(node&)b

}*/

//constructor
ABC::ABC()
{
    radacina = NULL;
}
//destructor
ABC::~ABC()
{
    destroy_tree();
    //functia destroy_tree va fi apelata recursiv pt fiecare frunza
}

void ABC::destroy_tree(node *frunza)
{
    if(frunza != NULL)
    {
        destroy_tree(frunza->st);
        destroy_tree(frunza->dr);
        delete frunza;
    }
}

void ABC::destroy_tree()
{
    destroy_tree(radacina);
}

void ABC::insert(int key, node *frunza)
{

    if(key < frunza->key)
    {
        if(frunza->st!= NULL)
        {
            insert(key, frunza->st);
        }
        else
        {
            frunza->st = new node;
            frunza->st->key = key;
            frunza->st->st = NULL;
            frunza->st->dr = NULL;
        }
    }
    else if(key >= frunza->key)
    {
        if(frunza->dr  != NULL)
        {
            insert(key, frunza->dr );
        }
        else
        {
            frunza->dr  = new node;
            frunza->dr ->key = key;
            frunza->dr ->dr  = NULL;
            frunza->dr ->st = NULL;
        }
    }
}

void ABC::insert(int nr_noduri)
{
    int i;
    int key;
    for(i=0; i<nr_noduri; i++)
    {
        cout<<"Valoare nod: ";
        cin>>key;
        if(radacina != NULL)
        {
            insert(key, radacina);
        }
        else
        {
            radacina = new node;
            radacina->key = key;
            radacina->st = NULL;
            radacina->dr = NULL;
        }
    }
}

node *ABC::search(int key, node *frunza)
{
    if(frunza != NULL)
    {
        if(key == frunza->key)
        {
            cout<< "elementul "<<frunza->key<<" a fost gasit in arborele dat"<<endl;
            return frunza;
        }
        if(key < frunza->key)
        {
            return search(key, frunza->st);
        }
        else
        {
            return search(key, frunza->dr);
        }
    }
    else
    {
        cout<<"elementul "<<key<<" nu a fost gasit in arborele dat";
        return NULL;
    }
}

node *ABC::search(int key)
{
    return search(key, radacina);
}


void ABC::inorder_print()
{
    if(radacina != NULL)
        inorder_print(radacina);
    else if  (radacina == NULL)
        cout<<"Arborele este gol"<<endl;


    cout << "\n";
}

void ABC::inorder_print(node *frunza)
{
    if(frunza != NULL)
    {
        inorder_print(frunza->st);
        cout << frunza->key << " ";
        inorder_print(frunza->dr);
    }
}

void ABC::postorder_print()
{
    postorder_print(radacina);
    cout << "\n";
}

void ABC::postorder_print(node *frunza)
{
    if(frunza != NULL)
    {
        inorder_print(frunza->st);
        inorder_print(frunza->dr);
        cout << frunza->key << " ";
    }
}

void ABC::preorder_print()
{
    preorder_print(radacina);
    cout << "\n";
}

void ABC::preorder_print(node *frunza)
{
    if(frunza != NULL)
    {
        cout << frunza->key << " ";
        inorder_print(frunza->st);
        inorder_print(frunza->dr);
    }
}

///Arbore Rosu Negru

class RBtree:Arbore
{
    Nod_rosu_negru *root;
    Nod_rosu_negru *q;

public :
    RBtree()
    {
        q=NULL;
        root=NULL;
    }
    ~RBtree()
    {
        cout<<"d_rbt";
    }
    void insert(int nr_noduri);
    void insertfix(Nod_rosu_negru *);
    void leftrotate(Nod_rosu_negru *);
    void rightrotate(Nod_rosu_negru *);
    void del();
    Nod_rosu_negru* successor(Nod_rosu_negru *);
    void delfix(Nod_rosu_negru *);
    void disp();
    void display( Nod_rosu_negru *);
    void search();
    virtual void citire_nr_noduri()
    {
        cout<<"introduceti nr de noduri"<<endl;
        cin>>nr_noduri;
        insert(nr_noduri);
    }
    virtual void adancime()
    {
        adancime_rad_neagra(root);
    }
    int c_dr=1, c_st=1;
    virtual void adancime_rad_neagra(Nod_rosu_negru *p)
    {

        Nod_rosu_negru *a=(Nod_rosu_negru*)p->st;
        Nod_rosu_negru *b=(Nod_rosu_negru*)p->dr;
        if(root==NULL)
        {
            cout<<"\nArbore gol";
            cout<<"Adancimea neagra a acestui arbore este 0"<<endl;
            return ;
        }
        if(p!=NULL)
        {

            if(p->color=='b')



                if(p->dr!=NULL&&b->color=='b')
                    c_dr++;
            if(p->st!=NULL&&a->color=='b')
                c_st++;
            cout<<endl;
            if(p->st)
            {
                //cout<<"\n\nStanga:\n";
                adancime_rad_neagra((Nod_rosu_negru*)p->st);
            }
            /*else
             cout<<"\nNo Left Child.\n";*/
            if(p->dr)
            {
                // cout<<"\n\nDreapta:\n";
                adancime_rad_neagra((Nod_rosu_negru*)p->dr);
            }
            /*else
             cout<<"\nNo Right Child.\n"*/


        }
        cout<<"Adancime pe partea stanga: "<<c_st<<endl<<"Adancime pe parte dreapta: "<<c_dr<<endl;

    }

    friend istream& operator >>(istream&, RBtree&);
    friend ostream& operator <<(ostream&, RBtree&);
//    friend RBtree operator =(RBtree, RBtree);

    friend class Nod_rosu_negru;
    friend class node;
};
istream& operator >>(istream& in, RBtree& ob)
{
    in>>(Nod_rosu_negru&)ob;

    return in;
}

//supraincarcare afisare
ostream& operator <<(ostream& out, RBtree& ob)
{
    out<<(Nod_rosu_negru&)ob<<endl;
    return out;

}
/*
RBtree operator =(RBtree a,RBtree b)
{
    (Nod_rosu_negru&)a=(Nod_rosu_negru&)b;

}
*/
void RBtree::insert(int n)
{
    for(int i=0; i<n; i++)
    {

        int z;
        cout<<"\nIntoduceti valoare pe care doriti sa o adaugati in nod: ";
        cin>>z;
        Nod_rosu_negru *q, *p;
        Nod_rosu_negru *t=new Nod_rosu_negru;

        t->key=z;
        t->st=NULL;
        t->dr=NULL;
        t->color='r';
        p=root;
        q=NULL;
        if(root==NULL)
        {
            root=t;
            t->parent=NULL;
        }
        else
        {
            while(p!=NULL)
            {
                q=p;
                if(p->key<t->key)
                    p=(Nod_rosu_negru*)p->dr;
                else
                    p=(Nod_rosu_negru*)p->st;
            }
            t->parent=q;
            if(q->key<t->key)
                q->dr=t;
            else
                q->st=t;
        }
        insertfix(t);
    }
}

void RBtree::insertfix(Nod_rosu_negru *t)
{
    Nod_rosu_negru *u;
    if(root==t)
    {
        t->color='b';
        return;
    }
    while(t->parent!=NULL&&t->parent->color=='r')
    {
        Nod_rosu_negru *g=t->parent->parent;
        if(g->st==t->parent)
        {
            if(g->dr!=NULL)
            {
                u=(Nod_rosu_negru*)g->dr;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->dr==t)
                {
                    t=t->parent;
                    leftrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                rightrotate(g);
            }
        }
        else
        {
            if(g->st!=NULL)
            {
                u=(Nod_rosu_negru*)g->st;
                if(u->color=='r')
                {
                    t->parent->color='b';
                    u->color='b';
                    g->color='r';
                    t=g;
                }
            }
            else
            {
                if(t->parent->st==t)
                {
                    t=t->parent;
                    rightrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                leftrotate(g);
            }
        }
        root->color='b';
    }
}

void RBtree::del()
{
    if(root==NULL)
    {
        cout<<"\nArbore gol" ;
        return ;
    }
    int x;
    cout<<"\nIntroduceti elementul pe care doriti sa il stergeti din arborele rosu negru: ";
    cin>>x;
    Nod_rosu_negru *p;
    p=root;
    Nod_rosu_negru *y=NULL;
    Nod_rosu_negru *q=NULL;
    int found=0;
    while(p!=NULL&&found==0)
    {
        if(p->key==x)
            found=1;
        if(found==0)
        {
            if(p->key<x)
                p=(Nod_rosu_negru*)p->dr;
            else
                p=(Nod_rosu_negru*)p->st;
        }
    }
    if(found==0)
    {
        cout<<"\nElementul nu a fost gasit";
        return ;
    }
    else
    {
        cout<<"\nElement sters: "<<p->key;
        cout<<"\nCuloare: ";
        if(p->color=='b')
            cout<<"Negru\n";
        else
            cout<<"Rosu\n";
        Nod_rosu_negru *a=(Nod_rosu_negru*)p->dr;
        Nod_rosu_negru *b=(Nod_rosu_negru*)p->st;
        if(p->parent!=NULL)

            cout<<"\Parinte: "<<p->parent->key;
        else
            cout<<"\nNu exista parinte al acestui nod.  ";
        if(p->dr!=NULL)
            cout<<"\nCopilul din dreapta: "<<a->key;
        else
            cout<<"\nNu exista copil drept al acestui nod. ";
        if(p->st!=NULL)
            cout<<"\nCopil din stanga: "<<b->key;
        else
            cout<<"\nNu existacopil stang al acestui nod. ";
        cout<<"\nNod_rosu_negru Deleted.";
        if(p->st==NULL||p->dr==NULL)
            y=p;
        else
            y=successor(p);
        if(y->st!=NULL)
            q=(Nod_rosu_negru*)y->st;
        else
        {
            if(y->dr!=NULL)
                q=(Nod_rosu_negru*)y->dr;
            else
                q=NULL;
        }
        if(q!=NULL)
            q->parent=y->parent;
        if(y->parent==NULL)
            root=q;
        else
        {
            if(y==y->parent->st)
                y->parent->st=q;
            else
                y->parent->dr=q;
        }
        if(y!=p)
        {
            p->color=y->color;
            p->key=y->key;
        }
        if(y->color=='b')
            delfix(q);
    }
}

void RBtree::delfix(Nod_rosu_negru *p)
{
    Nod_rosu_negru *s;
    Nod_rosu_negru *t;
    Nod_rosu_negru *y;
    while(p!=root&&p->color=='b')
    {
        if(p->parent->st==p)
        {
            s=(Nod_rosu_negru*)p->parent->dr;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                leftrotate(p->parent);
                s=(Nod_rosu_negru*)p->parent->dr;
            }
            y=(Nod_rosu_negru*)s->dr;
            Nod_rosu_negru* t=(Nod_rosu_negru*)s->st;
            if(y->color=='b'&&t->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(y->color=='b')
                {
                    t->color='b';
                    s->color='r';
                    rightrotate(s);
                    s=(Nod_rosu_negru*)p->parent->dr;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                y->color='b';
                leftrotate(p->parent);
                p=root;
            }
        }
        else
            s=(Nod_rosu_negru*)p->parent->st;
        if(s->color=='r')
        {
            s->color='b';
            p->parent->color='r';
            rightrotate(p->parent);
            s=(Nod_rosu_negru*)p->parent->st;
        }
        if(t->color=='b'&&y->color=='b')
        {
            s->color='r';
            p=p->parent;
        }
        else
        {
            if(t->color=='b')
            {
                y->color='b';
                s->color='r';
                leftrotate(s);
                s=(Nod_rosu_negru*)p->parent->st;
            }
            s->color=p->parent->color;
            p->parent->color='b';
            t->color='b';
            rightrotate(p->parent);
            p=root;
        }
    }
    p->color='b';
    root->color='b';
}

void RBtree::leftrotate(Nod_rosu_negru *p)
{
    if(p->dr==NULL)
        return ;
    else
    {
        Nod_rosu_negru *y=(Nod_rosu_negru*)p->dr;
        Nod_rosu_negru *x=(Nod_rosu_negru*)y->st;
        if(y->st!=NULL)
        {
            p->dr=(Nod_rosu_negru*)y->st;
            x->parent=p;
        }
        else
            p->dr=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)
            root=y;
        else
        {
            if(p==p->parent->st)
                p->parent->st=y;
            else
                p->parent->dr=y;
        }
        y->st=p;
        p->parent=y;
    }
}

void RBtree::rightrotate(Nod_rosu_negru *p)
{
    if(p->st==NULL)
        return ;
    else
    {
        Nod_rosu_negru *y=(Nod_rosu_negru*)p->st;
        Nod_rosu_negru *x=(Nod_rosu_negru*)p->dr;
        if(y->dr!=NULL)
        {
            p->st=y->dr;
            x->parent=p;
        }
        else
            p->st=NULL;
        if(p->parent!=NULL)
            y->parent=p->parent;
        if(p->parent==NULL)

            root=y;

        else
        {
            if(p==p->parent->st)
                p->parent->st=y;
            else
                p->parent->dr=y;
        }
        y->dr=p;
        p->parent=y;
    }
}

Nod_rosu_negru* RBtree::successor(Nod_rosu_negru *p)
{
    Nod_rosu_negru *y=NULL;
    if(p->st!=NULL)
    {
        y=(Nod_rosu_negru*)p->st;
        while(y->dr!=NULL)
            y=(Nod_rosu_negru*)y->dr;
    }
    else
    {
        y=(Nod_rosu_negru*)p->dr;
        while(y->st!=NULL)
            y=(Nod_rosu_negru*)y->st;
    }
    return y;
}

void RBtree::disp()
{
    display(root);
}

void RBtree::display(Nod_rosu_negru *p)
{

    Nod_rosu_negru *a=(Nod_rosu_negru*)p->st;
    Nod_rosu_negru *b=(Nod_rosu_negru*)p->dr;
    if(root==NULL)
    {
        cout<<"\nArbore gol";
        return ;
    }
    if(p!=NULL)
    {
        cout<<"\n\t NOD: ";
        cout<<"\n valoare: "<<p->key;
        cout<<"\n Culoare: ";
        if(p->color=='b')
            cout<<"Black";
        else
            cout<<"Red";
        if(p->parent!=NULL)
            cout<<"\n Parinte: "<<p->parent->key;
        else
            cout<<"\n Nu exista parinte al acestui nod  ";
        if(p->dr!=NULL)
            cout<<"\n Fiu drept: "<<b->key;
        else
            cout<<"\n Nu exista fiu drept al acestui nod  ";
        if(p->st!=NULL)
            cout<<"\n Fiu stang: "<<a->key;
        else
            cout<<"\n  Nu exista fiu stang al acestui nod    ";
        cout<<endl;
        if(p->st)
        {
            cout<<"\n\nStanga:\n";
            display((Nod_rosu_negru*)p->st);
        }
        /*else
         cout<<"\nNo Left Child.\n";*/
        if(p->dr)
        {
            cout<<"\n\nDreapta:\n";
            display((Nod_rosu_negru*)p->dr);
        }
        /*else
         cout<<"\nNo Right Child.\n"*/
    }
}

void RBtree::search()
{
    if(root==NULL)
    {
        cout<<"\nArbore gol\n" ;
        return  ;
    }
    int x;
    cout<<"\n Valoarea acare trebuie cautata in arbore este: ";
    cin>>x;
    Nod_rosu_negru *p=root;
    Nod_rosu_negru *a=(Nod_rosu_negru*)p->st;
    Nod_rosu_negru *b=(Nod_rosu_negru*)p->dr;
    int found=0;
    while(p!=NULL&& found==0)
    {
        if(p->key==x)
            found=1;
        if(found==0)
        {
            if(p->key<x)
                p=(Nod_rosu_negru*)p->dr;
            else
                p=(Nod_rosu_negru*)p->st;
        }
    }
    if(found==0)
        cout<<"\nElementul cautat nu exisata in arborele dat";
    else
    {
        cout<<"\n\t Nod Gasit: ";
        cout<<"\n Key: "<<p->key;
        cout<<"\n Culoare: ";
        if(p->color=='b')
            cout<<"Black";
        else
            cout<<"Red";
        if(p->parent!=NULL)
            cout<<"\n Parinte: "<<p->parent->key;
        else
            cout<<"\n Nu exista parinte ala nodului.  ";
        if(p->dr!=NULL)
            cout<<"\n Fiu drept: "<<b->key;
        else
            cout<<"\n Nu exista fiu drept al acestui nod.  ";
        if(p->st!=NULL)
            cout<<"\n Fiu stang: "<<a->key;
        else
            cout<<"\n Nu exista fiu stang al acestui nod.  ";
        cout<<endl;

    }
}
void meniu_arn()
{

    int ch,y=0;
    RBtree obj;
    while(1)
    {
        cout<<"\n\t RED BLACK TREE " ;
        cout<<"\n 1. Insert ";
        cout<<"\n 2. Delete nod";
        cout<<"\n 3. Search ";
        cout<<"\n 4. Display  ";
        cout<<"\n 6. Exit " ;
        cout<<"\n 5. Adancimea neagra a arborelui " ;
        cout<<"\nIntroduceti alegera: ";
        cin>>ch;
        switch(ch)
        {
        case 1 :
            obj.citire_nr_noduri();
            cout<<"\nNoduri  inserate.\n";
            break;
        case 2 :
            obj.del();
            break;
        case 3 :
            obj.search();
            break;
        case 4 :
            obj.disp();
            break;
        case 5:
            obj.adancime();
            break;

        }
    }
}
void meniu_abc()
{
    ABC *tree = new ABC();

    int alegere,x;
    while(1)
    {

        cout<<"1.Creare arbore binar de cautare"<<endl;
        cout<<"2.Cautarea unui element in arbore"<<endl;
        cout<<"3.Afisare arbore in preordine"<<endl;
        cout<<"4.Afisare arbore in inordine"<<endl;
        cout<<"5.Afisare arbore in postordine"<<endl;
        cout<<"6.Stergere arbore"<<endl;
        cout<<"7.Treceti la arbore ARN"<<endl;

        cin >>alegere;
        switch(alegere)
        {
        case 1:
            tree->citire_nr_noduri();
            cout<<"arborele parcurs in inordine: ";
            tree->inorder_print();
            break;
        case 2:
            cout<<"introduceti elementul cautat ";
            cin >>x;
            tree->search( x);

            break;
        case 3:
            cout<<"arborele parcurs in preordine: ";
            tree->preorder_print();
            break;
        case 4:


            cout<<"arborele parcurs in inordine: ";
            tree->inorder_print();
            break;
        case 5:
            cout<<"arborele parcurs in postordine: ";
            tree->postorder_print();
            break;

        case 6:
            tree->destroy_tree();
            cout<<endl;
            cout <<"Arborele a fost sters"<<endl;
            //tree->inorder_print();

            break;

        case 7:

            cout<<"treceti la ARN"<<endl;
            meniu_arn();
            break;
        }

    }
}

int main()
{
    // ABC *tree = new ABC();

    // int alegere,x;
    int arbore;
    //int ch,y=0;
    // RBtree obj;

    while(1)
    {
        cout<<"Selecteaza tipul arborelui"<<endl;
        cout<<"100. ABC"<<endl;
        cout<<"200.ARN"<<endl;

        cin>>arbore;

        switch(arbore)
        {
        case 100:

            while(1)
            {
                meniu_abc();

            }

        case 200:
            while(1)
            {
                meniu_arn();

            }
        }
    }

    return 0;
}
