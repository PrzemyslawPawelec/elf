/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <numeric>
#include <algorithm>
#include <ranges>

using namespace std;

struct Rucksack_t
{
  vector<char> items_vector;
  vector<char> first_compartment_vector;
  vector<char> second_compartment_vector;
  char common_item;
  int priority;
  
  Rucksack_t(vector<char>items) : items_vector(items)
  {
    this->first_compartment_vector = 
        {this->items_vector.begin(), this->items_vector.begin() + this->items_vector.size() / 2};
    this->second_compartment_vector = 
        {this->items_vector.begin() + this->items_vector.size() / 2, this->items_vector.end()};
    this->find_common_item();
    this->prioritize();
  }

  void find_common_item()
  {
    vector<char> intersection;
    
    std::sort(this->first_compartment_vector.begin(), this->first_compartment_vector.end());
    std::sort(this->second_compartment_vector.begin(), this->second_compartment_vector.end());
    std::set_intersection(this->first_compartment_vector.begin(), this->first_compartment_vector.end(),
                          this->second_compartment_vector.begin(), this->second_compartment_vector.end(),
                          std::back_inserter(intersection));
    if (intersection.size() == 0)
    {
      cout << "no intersection found!" << endl;
      return;
    }
    this->common_item = intersection.at(0);
  }

  void prioritize()
  {
    if (std::isalpha(this->common_item))
    {
      if(std::islower(this->common_item))
      {
        this->priority = 1 + (this->common_item - 'a');
      }
      else
      {
        this->priority = 27 + (this->common_item - 'A');
      }
    }
  }

};

int main()
{
  cout<<"Hello World\n";
  
  // string filename("test_input_file");
  string filename("input_file");
  vector<Rucksack_t> elves_rucksacks_vector;
  ifstream input_file(filename);
  
  string line{};
  stringstream ss;
  
  if (not input_file.is_open())
  {
      cout << "Could not open the file: " << filename << endl;
      return EXIT_FAILURE;
  }
  
  
  while (getline(input_file, line, '\n'))
  {
    vector<char> items;
    // cout << "->" << line.at(0) << endl;
    // ss << line;
    
    std::ranges::copy( line | std::views::filter([](unsigned char c){return std::isalpha(c);})
                            | std::views::transform([](unsigned char c){return static_cast<char>(c);}), 
                              std::back_inserter(items) );
    
    elves_rucksacks_vector.emplace_back(items);
    // cout << "sizeof items: " << items.size() << endl;
    if (items.size() % 2 != 0)
    {
      cout << "ODD!" << endl;
    }
  }
  
  input_file.close();

  // Rucksack_t r = elves_rucksacks_vector.at(0);
  // cout << "intersection at: " << r.common_item << endl;
  // cout << "priority: " << r.priority << endl;


  int total_result = std::accumulate(elves_rucksacks_vector.begin(), elves_rucksacks_vector.end(), 0, [](int res, Rucksack_t r){return res + r.priority;});
  cout << "total result: " << total_result << endl;
  
  
  return EXIT_SUCCESS;
  
  return 0;
}