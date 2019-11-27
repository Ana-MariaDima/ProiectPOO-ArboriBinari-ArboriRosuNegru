#include<iostream>

using namespace std;

class node{
//public:
protected:
int key;

node *st;
node *dr;
};
class Nod_rosu_negru:public node
{
    //public:
       Nod_rosu_negru *parent;
       char color;

       friend class RBtree;
};
class RBtree
{

      Nod_rosu_negru *root;
      // (node*)root;
      Nod_rosu_negru *q;
      // (Nod_rosu_negru*)q;
   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      void insert();
      void insertfix(Nod_rosu_negru *);
      void leftrotate(Nod_rosu_negru *);
      void rightrotate(Nod_rosu_negru *);
      void del();
      Nod_rosu_negru* successor(Nod_rosu_negru *);
      void delfix(Nod_rosu_negru *);
      void disp();
      void display( Nod_rosu_negru *);
      void search();
      friend class Nod_rosu_negru;

        friend class node;
};
void RBtree::insert()
{
     int z;
     cout<<"\nEnter key of the Nod_rosu_negru to be inserted: ";
     cin>>z;
     Nod_rosu_negru *q, *p;
//(Nod_rosu_negru*)p;
   //   (Nod_rosu_negru*)q;
     Nod_rosu_negru *t=new Nod_rosu_negru;
     //(Nod_rosu_negru*)t;
     //Nod_rosu_negru *p=new Nod_rosu_negru;
//  <Nod_rosu_negru *>(t).
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
           cout<<"\nEmpty Tree." ;
           return ;
     }
     int x;
     cout<<"\nEnter the key of the Nod_rosu_negru to be deleted: ";
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
            cout<<"\nElement Not Found.";
            return ;
     }
     else
     {
         cout<<"\nDeleted Element: "<<p->key;
         cout<<"\nColour: ";
         if(p->color=='b')
     cout<<"Black\n";
    else
     cout<<"Red\n";
        Nod_rosu_negru *a=(Nod_rosu_negru*)p->dr;
         Nod_rosu_negru *b=(Nod_rosu_negru*)p->st;
         if(p->parent!=NULL)

               cout<<"\nParent: "<<p->parent->key;
         else
               cout<<"\nThere is no parent of the Nod_rosu_negru.  ";
         if(p->dr!=NULL)
               cout<<"\nRight Child: "<<a->key;
         else
               cout<<"\nThere is no right child of the Nod_rosu_negru.  ";
         if(p->st!=NULL)
               cout<<"\nLeft Child: "<<b->key;
         else
               cout<<"\nThere is no left child of the Nod_rosu_negru.  ";
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
   // node s;
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
                  t=(Nod_rosu_negru*)s->st;
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
    //Nod_rosu_negru *x;
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
int main()
{
    int ch,y=0;
    RBtree obj;
    do
    {
                cout<<"\n\t RED BLACK TREE " ;
                cout<<"\n 1. Insert ";
                cout<<"\n 2. Delete nod";
                cout<<"\n 3. Search ";
                cout<<"\n 4. Display  ";
                cout<<"\n 5. Exit " ;
                cout<<"\nEnter Your Choice: ";
                cin>>ch;
                switch(ch)
                {
                          case 1 : obj.insert();
                                   cout<<"\nNod de inserat.\n";
                                   break;
                          case 2 : obj.del();
                                   break;
                          case 3 : obj.search();
                                   break;
                          case 4 : obj.disp();
                                   break;
                          case 5 : y=1;
                                   break;
                          default : cout<<"\nintrodu o varianta valida.";
                }
                cout<<endl;

    }while(y!=1);
    return 1;
}
