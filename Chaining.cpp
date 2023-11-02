#include "Chaining.h"
using namespace std;
Chaining::Chaining()
{
    sz = 0;
    for (int i = 0; i < 10001; i++)
    {
        vector<Account>acc;
        bankStorage2d.push_back(acc);
    }
}
void Chaining::merge(vector<int>& v, int left, int right)
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
void Chaining::mergesort(vector<int>& vec, int left, int right)
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
void Chaining::createAccount(std::string id, int count)
{
    Account obj;
    long long j = 0;
    obj.id = id;
    obj.balance = count;
    long long index = hash(id);
    bankStorage2d[index].push_back(obj);
    sz++;
    return;
}

std::vector<int> Chaining::getTopK(int k)
{


    vector<int> sorted_balance_values;
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for(int j=0 ; j<bankStorage2d[i].size() ; j++){
            sorted_balance_values.push_back(bankStorage2d[i][j].balance);
        }
    }
    mergesort(sorted_balance_values, 0, sorted_balance_values.size()-1);
    vector<int> TopKvalues;
    int size = sorted_balance_values.size();
    if (k <= sorted_balance_values.size())
    {
        for (int r = 0; r< k; r++)
        {
            TopKvalues.push_back(sorted_balance_values[size- 1 - r]);
        }
    }
    else
    {
        for (int r = 0; r < size; r++)
        {
            TopKvalues.push_back(sorted_balance_values[size - 1 - r]);
        }
    }
    return vector<int>(TopKvalues);
}

int Chaining::getBalance(std::string id)
{
    long long j = 0;
    int index = hash(id);
    if(!doesExist(id)){
        return -1;
    }
   
    else{
        for(int i=0 ; i<bankStorage2d[index].size() ; i++){
            if(bankStorage2d[index][i].id == id){
                return bankStorage2d[index][i].balance;
            }
        }
    
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count)
{
    int index = hash(id);
    int j = 0;
    if (!doesExist(id))
    {
        createAccount(id, count);
        return;
    }
    else
    {
        for(int i=0 ; i<bankStorage2d[index].size() ; i++){
            if((bankStorage2d[index][i].id) == id){
                bankStorage2d[index][i].balance+=count;
                return;
            }
        }
    }
}

bool Chaining::doesExist(std::string id)
{
    int index = hash(id);
    long long j = 0;
    for(int i=0 ; i<bankStorage2d[index].size() ; i++){
        if((bankStorage2d[index][i].id) == id){
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id)
{
    int index = hash(id);
    if (!doesExist(id))
    {
        return false;
    }
    long long j = 0;
    for(int i=0;i<bankStorage2d[index].size();i++)
    {
        if (bankStorage2d[index][i].id == id)
        {
           bankStorage2d[index].erase(bankStorage2d[index].begin()+i);
            sz--;
            return true;
        }
    }
    return false;
}
int Chaining::databaseSize()
{
    return sz;
}

int Chaining::hash(std::string id)
{
    string h = id.substr(16, 6);
    int g = stoi(h);
    int hash_id = g % 10001;

    return hash_id;
}

