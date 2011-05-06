#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

struct TSPGraph
{
  TSPGraph(string file)
  {
    // Create a graph from a given file
    cout << "Opening File: " << file << "... ";
    ifstream fs;
    fs.open(file.c_str(), ifstream::in);
    if(!fs.good())
    {
      cout << "Failed.  " << endl;
    }
    else
    {
      cout << "Succeeded." << endl << "Parsing... " << endl;
      parse_file(fs);
    }
  }

  struct node
  {
    node(int num, float c1, float c2)
    : num(num)
    , c1(c1)
    , c2(c2)
    {}

    friend ostream& operator<<(ostream& os, TSPGraph::node n)
    {
      os << "Node: " << n.num << " " 
         << n.c1 << " " << n.c2 << endl;
      return os;
    }

    int num;
    float c1;
    float c2;
  };

  void parse_file(ifstream& fs)
  {
    string line;
    string name, comment;
    enum {START, COORD} state = START;
    while(!fs.eof())
    {
      getline(fs, line);
      //cout << "Line: " << line << endl;
      if(state == START)
      {
        if(line.size() >= 4 && strncmp(line.c_str(), "NAME", 4) == 0)
        {
          name += line.substr(6);
        }
        else if(line.size() >= 7 && strncmp(line.c_str(), "COMMENT", 7) == 0)
        {
          comment += line.substr(9) + "\n";
        }
        else if(line.size() >= 18 && 
                strncmp(line.c_str(), "NODE_COORD_SECTION", 18) == 0)
        {
          state = COORD;
        }
      }
      else if(state == COORD)
      {
        stringstream ss(stringstream::in | stringstream::out);
        int num;
        float c1, c2;
        ss << line;
        ss >> num >> c1 >> c2;
        // Add it to our nodes
        this->nodes.push_back(node(num, c1, c2));
      }
    }
    cout << "Name: " << name << endl;
    cout << "Comment: " << comment << endl;
    vector<node>::const_iterator i = this->nodes.begin();
    while(i != this->nodes.end())
    {
      cout << *i;
      ++i;
    }
  }
  private:
  vector<node> nodes;
};

int main()
{
  cout << "Simulated Annealing" << endl;
  TSPGraph tsp("djibouti.txt");
}
