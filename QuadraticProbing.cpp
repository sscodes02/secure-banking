#include "QuadraticProbing.h"
using namespace std;
QuadraticProbing::QuadraticProbing()
{
    sz = 0;
    for (int i = 0; i < 200009; i++)
    {
        Account a;
        a.id = "";
        a.balance = -1;
        bankStorage1d.push_back(a);
    }
}
void QuadraticProbing::merge(vector<int>&v, int left, int right)
{
    int mid = (left + right) / 2;
    int l1 = mid - left + 1;
    int l2 = right - mid;
    vector<int> a = vector<int>(l1);
    vector<int> b = vector<int>(l2);
    int idx = left;
    for (int i = 0; i < l1; i++)
    {
        a[i] = v[idx++];
    }
    idx = mid + 1;
    for (int i = 0; i < l2; i++)
    {
        b[i] = v[idx++];
    }
    int i1 = 0;
    int i2 = 0;
    idx = left;
    while (i1 < l1 && i2 < l2)
    {
        if (a[i1] < b[i2])
        {
            v[idx++] = a[i1++];
        }
        else
        {
            v[idx++] = b[i2++];
        }
    }
    while (i1 < l1)
    {
        v[idx++] = a[i1++];
    }
    while (i2 < l2)
    {
        v[idx++] = b[i2++];
    }
    a.clear();
    b.clear();
}
void QuadraticProbing::mergesort(vector<int>&vec, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    mergesort(vec, left, mid);
    mergesort(vec, mid + 1, right);
    merge(vec, left, right);
}
void QuadraticProbing::createAccount(std::string id, int count)
{
    Account obj;
    long long j = 0;
    obj.id = id;
    obj.balance = count;
    long long index = hash(id);
    long long i = index;
    while (true)
    {
        if(bankStorage1d[i].balance<0){
            bankStorage1d[i]=obj;
            sz++;
            return;
        }
        j++;
        i= (index + j * j) % 200009;
    }
}

std::vector<int> QuadraticProbing::getTopK(int k)
{
    vector<int> sorted_balance_values;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].balance >= 0)
            sorted_balance_values.push_back(bankStorage1d[i].balance);
    }
    mergesort(sorted_balance_values, 0, sorted_balance_values.size() - 1);
    vector<int> TopKvalues;
    int size = sorted_balance_values.size();
    if (k <= sorted_balance_values.size())
    {
        for (int r = 0; r < k; r++)
        {
            TopKvalues.push_back(sorted_balance_values[size - 1 - r]);
        }
    }
    else
    {
        for (int r = 0; r < size; r++)
        {
            TopKvalues.push_back(sorted_balance_values[size - 1 - r]);
        }
    }
    return TopKvalues;
}

int QuadraticProbing::getBalance(std::string id)
{
    long long j = 0;
    int index = hash(id);
    long long i = index;
    if(!doesExist(id)){
        return -1;
    }
    if (bankStorage1d[index].id == id)
    {
        return bankStorage1d[index].balance;
    }
    else
    {
        while (bankStorage1d[i].id != id)

        {
            j++;
            i = (index + j * j) % 200009;
        }
        return bankStorage1d[i].balance;
    }
}

void QuadraticProbing::addTransaction(std::string id, int count)
{
    int index = hash(id);
    int j = 0;
    int i = index;
    if (!doesExist(id))
    {
        createAccount(id, count);
        return;
    }
    while (bankStorage1d[i].id != id)
    {

        j++;
        i = (index + j * j) % 200009;
    }
    bankStorage1d[i].balance = bankStorage1d[i].balance + count;
    return;
}

bool QuadraticProbing::doesExist(std::string id)
{

    int index = hash(id);
    long long j = 0;
    long long i = index;
    while (true)
    {
        if (bankStorage1d[i].id == id)
        {
            return true;
        }
        if (bankStorage1d[i].balance == -1)
        {
            return false;
        }
        j++;
        i = (index + j * j) % 200009;
    }
}

bool QuadraticProbing::deleteAccount(std::string id)
{
    int index = hash(id);
    if (!doesExist(id))
    {
        return false;
    }
    long long i = index;
    long long j = 0;
    while (true)
    {
        if (bankStorage1d[i].id == id)
        {
            bankStorage1d[i].id = "";
            bankStorage1d[i].balance = -2;
            sz--;
            return true;
        }
        j++;
        i = (index + j * j) % 200009;
    }
}

int QuadraticProbing::databaseSize()
{
    return sz;
}

int QuadraticProbing::hash(std::string id)
{
    string h = id.substr(16, 6);
    int g = stoi(h);
    int hash_id = g % 200009;

    return hash_id;
}
