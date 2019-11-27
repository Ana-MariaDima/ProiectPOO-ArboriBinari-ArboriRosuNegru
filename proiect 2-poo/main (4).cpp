#include <iostream>

using namespace std;

class node
{

    int info;

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
    friend class ABC;
};
//constructor
node::node() {}
//parametrizare
node::node(int x)
{
    info=x;
}
//copiere
node::node(const node &n)
{
    info=n.info;
    st=n.st;
    dr=n.dr;
    cout<<"c";
}
node::~node()
{
    cout<<"d";
}

class Nod_rosu_negru:node
{
    char culoare[];
    //r pt rosu si n pt negru
};

class Arbore
{
protected:
    int nr_noduri;
    virtual void citire_nr_noduri()=0;
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
//private:
    void destroy_tree(node *frunza);
    void insert(int key, node *frunza);
    node *search(int key, node *frunza);
    void inorder_print(node *frunza);
    void postorder_print(node *frunza);
    void preorder_print(node *frunza);

};

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

    if(key < frunza->info)
    {
        if(frunza->st!= NULL)
        {
            insert(key, frunza->st);
        }
        else
        {
            frunza->st = new node;
            frunza->st->info = key;
            frunza->st->st = NULL;
            frunza->st->dr = NULL;
        }
    }
    else if(key >= frunza->info)
    {
        if(frunza->dr  != NULL)
        {
            insert(key, frunza->dr );
        }
        else
        {
            frunza->dr  = new node;
            frunza->dr ->info = key;
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
            radacina->info = key;
            radacina->st = NULL;
            radacina->dr = NULL;
        }
    }
}

node *ABC::search(int key, node *frunza)
{
    if(frunza != NULL)
    {
        if(key == frunza->info)
        {
            cout<< "elementul "<<frunza->info<<" a fost gasit in arborele dat"<<endl;
            return frunza;
        }
        if(key < frunza->info)
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
{       if(radacina != NULL)
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
        cout << frunza->info << " ";
        inorder_print(frunza->dr);
    }
    //else     if(frunza == NULL)
 //cout<<"Arborele este gol"<<endl;

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
        cout << frunza->info << " ";
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
        cout << frunza->info << " ";
        inorder_print(frunza->st);
        inorder_print(frunza->dr);
    }

}

int main()
{

    //btree tree;
    /*tree->insert(10);
    tree->insert(6);
    tree->insert(14);
    tree->insert(5);
    tree->insert(8);
    tree->insert(11);
    tree->insert(18);*/
    ABC *tree = new ABC();

    int alegere,x;
    //tree->destroy_tree();

    while(1)
    {

        cout<<"1.Creare arbore binar de cautare"<<endl;
        cout<<"2.Cautarea unui element in arbore"<<endl;
        cout<<"3.Afisare arbore in preordine"<<endl;
        cout<<"4.Afisare arbore in inordine"<<endl;
        cout<<"5.Afisare arbore in postordine"<<endl;
        cout<<"6.Stergere arbore"<<endl;

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


    }

    }

    //cout<<"arborele parcurs in preordine: ";
    //tree->preorder_print();
    //cout<<"arborele parcurs in inordine: ";
    //tree->inorder_print();
    //cout<<"arborele parcurs in postordine: ";
    //tree->postorder_print();

    //delete tree;

}
