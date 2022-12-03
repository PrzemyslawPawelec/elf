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
    Rucksack_t(vector<char>items) : items_vector(items){}
};

int main()
{
    cout<<"Hello World\n";
    
    string filename("test_input_file");
    // string filename("input_file");
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
        
      // cout << "sizeof items: " << items.size() << endl;
      if (items.size() % 2 != 0)
      {
        cout << "ODD!" << endl;
      }
    }
    
    input_file.close();
    
    // int total_result = std::accumulate(elves_battle_vector.begin(), elves_battle_vector.end(), 0, [](int res, Battle_t b){return res + b.result;});
    // cout << "total result: " << total_result << endl;
    
    
    return EXIT_SUCCESS;
    
    return 0;
}