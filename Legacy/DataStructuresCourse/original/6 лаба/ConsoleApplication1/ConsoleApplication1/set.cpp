#include "set.h"

void Set::init(int size)
{
    for (int i = 0; i < size; ++i)
    {
        hashtable_container::iterator it = hashtable.insert(rand() % 10 + 1);
        lst.push_back( make_pair(it, *it) );
    }
}

void Set::output()
{
    cout << "HASHTABLE: { ";
    for (auto x : hashtable)
        cout << x << " ";
    cout << " }" << endl;

    cout << "SEQUENCE: { ";
    for (auto x : lst)
        cout << x.second << " ";
    cout << " }" << endl;
}

void Set::renewList()
{
    lst.clear();
    for(hashtable_container::iterator it = hashtable.begin(); it != hashtable.end(); ++it)
        lst.push_back( make_pair(it, *it) );
}

void Set::renewHashtable()
{
    hashtable.clear();
    for (auto x : lst)
        hashtable.insert(x.second);
}

const Set& Set::operator & (const Set & b) const
{
    Set *result = new Set();
    vector<int> v1, v2, vr;
    for(auto x : hashtable)
        v1.push_back(x);
    for(auto x : b.hashtable)
        v2.push_back(x);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(vr));

    for(auto x : vr)
        result->hashtable.insert(x);
    result->renewList();

    return *result;
}

const Set& Set::operator - (const Set & b) const
{
    Set *result = new Set();
    vector<int> v1, v2, vr;
    for(auto x : hashtable)
        v1.push_back(x);
    for(auto x : b.hashtable)
        v2.push_back(x);
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(vr));

    for(auto x : vr)
        result->hashtable.insert(x);
    result->renewList();

    return *result;
}

bool cmp(const pair<hashtable_container::iterator, int> p1,
         const pair<hashtable_container::iterator, int> p2)
{
    return (p1.second < p2.second);
}

void Set::merge(const Set & b)
{
    for(auto x : b.lst)
        lst.push_back(x);
    lst.sort(cmp);

    renewHashtable();
}

void Set::subst(const Set &b, int p)
{
    list_container::const_iterator it = lst.begin();
    advance(it, p);
    for (auto x : b.lst)
        lst.insert(it, x);

    renewHashtable();
}

void Set::mul(int n)
{
    vector<int> v;
    for(auto x : lst)
        v.push_back(x.second);

    for(int i = 1; i <= n; ++i)
        for(auto x : v)
        {
            hashtable_container::iterator it = hashtable.insert(x);
            lst.push_back( make_pair(it, *it) );
        }
}


void Set::removeAll()
{
    hashtable.clear();
    lst.clear();
}
