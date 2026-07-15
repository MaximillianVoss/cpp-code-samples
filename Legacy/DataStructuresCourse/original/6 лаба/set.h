#ifndef SET_H
#define SET_H

#include <iostream>

#include <unordered_set>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

typedef unordered_multiset<int> hashtable_container;
typedef list< pair<unordered_multiset<int>::iterator, int> > list_container; // список пар итераторов

class Set
{
public:
    void init(int size);

    void output();

    void renewList();
    void renewHashtable();

    const Set& operator&(const Set& b) const;
    const Set& operator-(const Set& b) const;

    void merge(const Set& b);
    void subst(const Set& b, int p);
    void mul(int n);

    void removeAll();

private:
    hashtable_container hashtable;
    list_container lst;
};

#endif // SET_H
