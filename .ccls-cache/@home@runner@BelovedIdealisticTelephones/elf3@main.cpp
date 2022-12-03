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
    
    char weapon{};
    string line{};
    stringstream ss;
    
    if (not input_file.is_open())
    {
        cout << "Could not open the file: " << filename << endl;
        return EXIT_FAILURE;
    }
    
    
    while (getline(input_file, line, '\n'))
    {
        cout << "->" << line.at(0) << endl;
        ss << line;
        // ss >> single_battle.oponent_weapon;
        // ss >> single_battle.my_weapon;
        

    }
    
    input_file.close();
    
    // int total_result = std::accumulate(elves_battle_vector.begin(), elves_battle_vector.end(), 0, [](int res, Battle_t b){return res + b.result;});
    // cout << "total result: " << total_result << endl;
    
    
    return EXIT_SUCCESS;
    
    return 0;
}