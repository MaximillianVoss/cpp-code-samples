#include <stdlib.h>
#include <iostream>
#include <stdio.h>
using namespace std;
class Node{
private:
	int key;				
	unsigned char heighth;
	int multiply;			//кратность узла
public:
	Node *left;
	Node *right;
	Node();
	~Node(){};
	Node(int k) {key=k; left=right=0;multiply=1;heighth=1;}
	Node* Build(int,int,int*);
	Node* remove(Node* , int );
	Node* findmin(Node* );
	Node* removemin(Node* );
	Node* insert(Node*, int );
	Node* rotateright(Node* );
	Node* rotateleft(Node*);
	void fixheight(Node*);
	int  bfactor(Node*);
	unsigned char height(Node*);
	Node* balance(Node*);

	friend class AVL;
};

Node* Build(int a,int b,int *data)
{
	if(b<=a)return 0;
	int c=(a+b)/2;
	Node *s=new Node(data[c]);
	s->left=Build(a,c,data);
	s->right=Build(c+1,b,data);
	return s;
}


Node* Node:: insert(Node* p, int k) // вставка ключа k в дерево с корнем p
{
    if( !p ) return new Node(k);
    if( k<p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
	//return p;
}



Node* Node:: findmin(Node* p) // поиск узла с минимальным ключом в дереве p 
{
    return p->left?findmin(p->left):p;
}

Node*  Node::removemin(Node* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
	return balance(p);
}

Node* Node:: remove(Node* p, int k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);	
    else //  k == p->key 
    {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if( !r ) return q;
        Node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
    }
    return balance(p);
}


Node* Node:: rotateright(Node* p) // правый поворот вокруг p
{
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}



void Node :: fixheight(Node* p) //изменение высоты дерева
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->heighth = (hl>hr?hl:hr)+1;
}



int Node:: bfactor(Node* p)
{
   return height(p->right)-height(p->left);
}



unsigned char Node ::height(Node*p){
	return p?p->heighth:0;};



Node* Node:: balance(Node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}



Node*  Node:: rotateleft(Node* q) // левый поворот вокруг q
{
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}













