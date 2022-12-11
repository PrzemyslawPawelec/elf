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
#include <memory>
#include <map>
#include <set>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

using namespace std;

enum ParserMode : uint8_t
{
  PARSING_COMMAND = 0,
  PARSING_LS = 1
};


int main() {
  std::filesystem::path cwd = std::filesystem::current_path().filename();
  cout << "Hello World: " << cwd << endl;

  // string filename("test_input_file");
  string filename("input_file");
  ifstream input_file(filename);

  string line{};
  ParserMode parserMode = PARSING_COMMAND;

  if (not input_file.is_open()) {
    cout << "Could not open the file: " << filename << endl;
    return EXIT_FAILURE;
  }

  while (getline(input_file, line, '\n')) 
  {

    
  }

  input_file.close();


  // int res = std::accumulate(elvesDirectoriesVector.begin(), elvesDirectoriesVector.end(), 0,
  //     [](int res, const ElfDirectory_t &elfDirectory)
  //     {
  //       return res + ( elfDirectory.GetTotalSize() <= UPPER_LIMIT_SIZE ? elfDirectory.GetTotalSize() : 0);
  //     });
  // cout << "res: " << res << endl;

  

  return EXIT_SUCCESS;
}
