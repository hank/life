#include <iostream>
#include <cstdlib>
#include <fstream>
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
  void parse_file(ifstream& fs)
  {
    string line;
    string name, comment;
    enum {START, COORD} state;
    while(!fs.eof())
    {
      getline(fs, line);
      cout << "Line: " << line << endl;
      if(state == START)
      {
        if(line.size() >= 4 && strncmp(line.c_str(), "NAME", 4) == 0)
        {
          name = line;
        }
        else if(line.size() >= 4 && strncmp(line.c_str(), "NAME", 4) == 0)
        {
          
        }
      }
    }
    cout << "Name: " << name << endl;
    cout << "Comment: " << comment << endl;
  }
};


int main()
{
  cout << "Simulated Annealing" << endl;
  TSPGraph tsp("djibouti.txt");
}
