/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java,
PHP, Ruby, Perl, C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C,
Assembly, HTML, CSS, JS, SQLite, Prolog. Code, Compile, Run and Debug online
from anywhere in world.

*******************************************************************************/
#include <algorithm>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>


using namespace std;

void printHorizontalCrane(const vector<list<string>> &stacks)
{
  for (const auto &s : stacks)
  {
    std::string print_stack = boost::algorithm::join(
    s | boost::adaptors::transformed([&](const auto &el) 
        {
          return "[" + el + "]";
        }), " ");
    cout << print_stack << endl;
  }
}

void printVerticalCrane(const vector<list<string>> &stacks)
{
  int highest{};
  for (const auto &s : stacks)
  {
    if (s.size() > highest) highest = s.size();
  }
  cout << "highest: " << highest << endl;

  for (int i=highest; i>0; i--)
  {
    for (const auto &s : stacks)
    {
      if (s.size() >= i)
      {
        list<string>::const_iterator it = s.cbegin();
        advance(it, i-1);
        cout << "[" << *it << "]";
      }
      else cout << "   ";
      cout << " ";
    }
    cout << endl;
  }
}

void printTops(const vector<list<string>> &stacks)
{
  for (const auto &s : stacks)
  {
    cout << s.back();
  }
  cout << endl;
}

void executeProcedures(vector<list<string>> &stacks, int howMany, int from, int to)
{
  for (int i=0; i<howMany; i++)
  {
    stacks.at(to-1).emplace_back(stacks.at(from-1).back());
    stacks.at(from-1).pop_back();    
  }
}

void executeProcedures2(vector<list<string>> &stacks, int howMany, int from, int to)
{
  for (int i=howMany; i>0; i--)
  {
    list<string>::iterator it = stacks.at(from-1).begin();
        advance(it, stacks.at(from-1).size()-i);
        // cout << "[" << *it << "]";

    stacks.at(to-1).emplace_back(*it);
    stacks.at(from-1).erase(it);
  }
}

struct Stack_t
{
  list<char> stack;

  Stack_t(list<char> _stack) : stack(_stack){}

  // void PrintCargo()
  // {
  //   for (const auto &stack : stacks_vector)
  //   {

  //   }
  // }
};

enum ParserMode : uint8_t
{
  PARSING_DEFAULT = 0,
  PARSING_INITIAL = 1,
  PARSING_PROCEDURES = 2
};


int main() {
  cout << "Hello World\n";

  constexpr int ELVES_GROUP_SIZE = 2;
  constexpr std::string_view DELIM{","};

  // string filename("test_input_file");
  string filename("input_file");
  vector<list<string>> elves_stacks{};
  list<string> elves_stack{};
  ifstream input_file(filename);

  string line{};
  stringstream ss;
  ParserMode parserMode = PARSING_INITIAL;


  if (not input_file.is_open()) {
    cout << "Could not open the file: " << filename << endl;
    return EXIT_FAILURE;
  }

  while (getline(input_file, line, '\n')) {

    
    // cout << "->" << line.at(0) << endl;
    // ss << line;

    if (PARSING_INITIAL == parserMode)
    {
      // cout << "line size: " << line.size() << endl;

      if (line.find('[') != std::string::npos)
      {
        int stack_count = 1;
        for (int i=1; i<line.size(); i=i+4, stack_count++)
        {
          if (std::isalpha(line.at(i))) 
            {
              if (elves_stacks.size() < stack_count)
              {
                elves_stacks.resize(stack_count);
              }
              cout <<  line.at(i) << " ";
              elves_stacks.at(stack_count-1).emplace_front(string(1,line.at(i)));
            }
        }
        cout << endl;
      }
    }
    else if (PARSING_PROCEDURES == parserMode)
    {
      // ss << line;
      string move{"move"};
      string from{"from"};
      string to{"to"};
      int param0{}, param1{}, param2{};
      // ss >> temp;
      // line.substr(line.find(move) + move.size());
      stringstream(line.substr(line.find(move) + move.size())) >> param0;
      // cout << "param0: " << param0;
      stringstream(line.substr(line.find(from) + from.size())) >> param1;
      // cout << " param1: " << param1;
      stringstream(line.substr(line.find(to) + to.size())) >> param2;
      // cout << " param2: " << param2 << endl;

      executeProcedures2(elves_stacks, param0, param1, param2);
    }

    if (line.empty())
    {
      cout << "blank line" << endl;
      parserMode = PARSING_PROCEDURES;
    } 
  }

  input_file.close();

  // cout << "size of elves groups: " << elves_all_groups_vector.size() << endl;

  // int total_result =
  //     std::accumulate(elves_all_groups_vector.begin(), elves_all_groups_vector.end(), 0,
  //                     [](int res, SectionAssignmentsGroup_t s) { return res + static_cast<int>(s.isSubset); });
  // cout << "total result: " << total_result << endl;

  // int total_result2 =
  //     std::accumulate(elves_all_groups_vector.begin(), elves_all_groups_vector.end(), 0,
  //                     [](int res, SectionAssignmentsGroup_t s) { return res + static_cast<int>(s.isOverlapping); });
  // cout << "total result2: " << total_result2 << endl;


  list<string> lA{"A", "B", "C"};
  list<string> lB{"A", "B", "C", "D", "E"};
  list<string> lC{"A", "B"};
  vector<list<string>> stacks{};
  stacks.emplace_back(lA);
  stacks.emplace_back(lB);
  stacks.emplace_back(lC);

  // printHorizontalCrane(stacks);
  // printVerticalCrane(stacks);

  // printVerticalCrane(elves_stacks);
  // executeProcedures(elves_stacks, 1, 2, 1);
  // printVerticalCrane(elves_stacks);
  // executeProcedures(elves_stacks, 3, 1, 3);
  // printVerticalCrane(elves_stacks);
  // executeProcedures(elves_stacks, 2, 2, 1);
  // printVerticalCrane(elves_stacks);
  // executeProcedures(elves_stacks, 1, 1, 2);
  // printVerticalCrane(elves_stacks);
  printTops(elves_stacks);

  
  return EXIT_SUCCESS;
}
