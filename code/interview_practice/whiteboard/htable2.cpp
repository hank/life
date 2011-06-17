#include <list>
#include <vector>
#include <cstdio>
using namespace std;

template<class KEY, class VALUE, class HASH_FN>
class HashTable
{
  public:
    HashTable(const int& size) 
    : size(size)
    {
      // Groom our table
      this->table.resize(size);
    }

    struct Data
    {
      Data(KEY key, VALUE value)
      : key(key)
      , value(value)
      {}

      KEY key;
      VALUE value;
    };

    bool insert(const KEY& key, const VALUE& value)
    {
      int hash = HASH_FN()(key) % size;
      list<Data>& i_list = this->table[hash];
      typename list<Data>::const_iterator l_iter = i_list.begin();
      while(l_iter != i_list.end())
      {
        if(l_iter->key == key)
        {
          return false;
        }
        ++l_iter;
      }
      i_list.push_back(Data(key, value));
      return true;
    }

    const VALUE* get(const KEY& key)
    {
      int hash = HASH_FN()(key) % size;
      list<Data>& i_list = this->table[hash];
      typename list<Data>::const_iterator l_iter = i_list.begin();
      while(l_iter != i_list.end())
      {
        if(l_iter->key == key)
        {
          return &(l_iter->value);
        }
        ++l_iter;
      }
      return NULL;
    }

  private:
    vector<list<Data> > table;
    int size;
};

// Dumbest hash ever
struct hash
{
  int operator()(const int& key) const
  {
    return key;
  }
};

int main()
{
  HashTable<int, int, hash> h(1000);
  h.insert(4,5);
  h.insert(2000,5);
  h.insert(4000,7);
  h.insert(6,5);
  const int* data = h.get(4);
  printf("Retrieved 4 => %d\n", *data);
  data = h.get(2000);
  printf("Retrieved 2000 => %d\n", *data);
  data = h.get(4000);
  printf("Retrieved 4000 => %d\n", *data);
  return 0;
}
