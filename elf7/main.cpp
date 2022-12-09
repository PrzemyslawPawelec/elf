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
#include <filesystem>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

using namespace std;


int main() {
  std::filesystem::path cwd = std::filesystem::current_path().filename();
  cout << "Hello World: " << cwd << endl;

  string filename("test_input_file");
  // string filename("input_file");
  // vector<list<string>> elves_stacks{};
  // list<string> elves_stack{};
  ifstream input_file(filename);

  string line{};
  stringstream ss;
  // ParserMode parserMode = PARSING_INITIAL;


  if (not input_file.is_open()) {
    cout << "Could not open the file: " << filename << endl;
    return EXIT_FAILURE;
  }

  while (getline(input_file, line, '\n')) 
  {

    
    // cout << "->" << line.at(0) << endl;
    // ss << line;

    // if (PARSING_INITIAL == parserMode)
    // {
    //   // cout << "line size: " << line.size() << endl;

    //   if (line.find('[') != std::string::npos)
    //   {
    //     int stack_count = 1;
    //     for (int i=1; i<line.size(); i=i+4, stack_count++)
    //     {
    //       if (std::isalpha(line.at(i))) 
    //         {
    //           if (elves_stacks.size() < stack_count)
    //           {
    //             elves_stacks.resize(stack_count);
    //           }
    //           cout <<  line.at(i) << " ";
    //           elves_stacks.at(stack_count-1).emplace_front(string(1,line.at(i)));
    //         }
    //     }
    //     cout << endl;
    //   }
    // }
    // else if (PARSING_PROCEDURES == parserMode)
    // {
    //   // ss << line;
    //   string move{"move"};
    //   string from{"from"};
    //   string to{"to"};
    //   int param0{}, param1{}, param2{};
    //   // ss >> temp;
    //   // line.substr(line.find(move) + move.size());
    //   stringstream(line.substr(line.find(move) + move.size())) >> param0;
    //   // cout << "param0: " << param0;
    //   stringstream(line.substr(line.find(from) + from.size())) >> param1;
    //   // cout << " param1: " << param1;
    //   stringstream(line.substr(line.find(to) + to.size())) >> param2;
    //   // cout << " param2: " << param2 << endl;

    //   executeProcedures2(elves_stacks, param0, param1, param2);
    // }

    // if (line.empty())
    // {
    //   cout << "blank line" << endl;
    //   parserMode = PARSING_PROCEDURES;
    // } 
  }

  input_file.close();

  return EXIT_SUCCESS;
}
