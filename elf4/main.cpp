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
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <boost/lexical_cast.hpp>


using namespace std;

struct SectionAssignments_t
{
  string range;
  vector<int> sections;
  static const string DELIMITER;

  SectionAssignments_t(string _range) : range(_range)
  {
    std::vector<std::string> splitResult;
    boost::algorithm::split(splitResult, range, boost::is_any_of(SectionAssignments_t::DELIMITER));

    if(splitResult.size() > 0)
    {
      int begin = boost::lexical_cast<int>(splitResult.at(0));
      int end = boost::lexical_cast<int>(splitResult.at(1));
      sections.resize(end-begin+1);
      std::iota(sections.begin(), sections.end(), begin);
    }
    else
    {
      cout << "Wrong range" << endl;
    }
  }
};

const string SectionAssignments_t::DELIMITER = "-";

struct SectionAssignmentsGroup_t
{
  vector<SectionAssignments_t> assigments;
  bool isSubset;
  bool isOverlapping;

  SectionAssignmentsGroup_t(vector<SectionAssignments_t> _assigments) : assigments(_assigments)
  {
    isSubset = (std::includes(assigments.at(0).sections.begin(), assigments.at(0).sections.end(), assigments.at(1).sections.begin(), assigments.at(1).sections.end()) ||
      std::includes(assigments.at(1).sections.begin(), assigments.at(1).sections.end(), assigments.at(0).sections.begin(), assigments.at(0).sections.end()));

    vector<int> intersection;
    std::set_intersection(assigments.at(0).sections.begin(),
                          assigments.at(0).sections.end(),
                          assigments.at(1).sections.begin(),
                          assigments.at(1).sections.end(),
                          std::back_inserter(intersection));
    isOverlapping = (intersection.size() > 0);
    if (intersection.size() == 0) {
      // cout << "no intersection found!" << endl;
    }
  }
};


int main() {
  cout << "Hello World\n";

  constexpr int ELVES_GROUP_SIZE = 2;
  constexpr std::string_view DELIM{","};

  // string filename("test_input_file");
  string filename("input_file");
  vector<SectionAssignmentsGroup_t> elves_all_groups_vector{};
  vector<SectionAssignments_t> elves_single_group_vector{};
  ifstream input_file(filename);

  string line{};
  stringstream ss;

  if (not input_file.is_open()) {
    cout << "Could not open the file: " << filename << endl;
    return EXIT_FAILURE;
  }

  while (getline(input_file, line, '\n')) {
    vector<char> items;
    // cout << "->" << line.at(0) << endl;
    // ss << line;

    std::vector<std::string> splitResult;
    boost::algorithm::split(splitResult, line, boost::is_any_of(","));

    for(const std::string& s : splitResult) 
    {
      elves_single_group_vector.emplace_back(s);
        // std::cout << s << std::endl;
    }
    // std::cout << std::endl;
    elves_all_groups_vector.emplace_back(elves_single_group_vector);
    elves_single_group_vector.clear();
  
  }

  input_file.close();

  cout << "size of elves groups: " << elves_all_groups_vector.size() << endl;

  int total_result =
      std::accumulate(elves_all_groups_vector.begin(), elves_all_groups_vector.end(), 0,
                      [](int res, SectionAssignmentsGroup_t s) { return res + static_cast<int>(s.isSubset); });
  cout << "total result: " << total_result << endl;

  int total_result2 =
      std::accumulate(elves_all_groups_vector.begin(), elves_all_groups_vector.end(), 0,
                      [](int res, SectionAssignmentsGroup_t s) { return res + static_cast<int>(s.isOverlapping); });
  cout << "total result2: " << total_result2 << endl;



  
  return EXIT_SUCCESS;

  return 0;
}