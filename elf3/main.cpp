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

using namespace std;

struct Rucksack_t {
  vector<char> items_vector;
  vector<char> first_compartment_vector;
  vector<char> second_compartment_vector;
  char common_item;
  int priority;

  Rucksack_t(vector<char> items) : items_vector(items) {
    this->first_compartment_vector = {this->items_vector.begin(),
                                      this->items_vector.begin() +
                                          this->items_vector.size() / 2};
    this->second_compartment_vector = {this->items_vector.begin() +
                                           this->items_vector.size() / 2,
                                       this->items_vector.end()};
    this->find_common_item();
    this->priority = Rucksack_t::prioritize(this->common_item);
  }

  void find_common_item() {
    vector<char> intersection;

    std::sort(this->first_compartment_vector.begin(),
              this->first_compartment_vector.end());
    std::sort(this->second_compartment_vector.begin(),
              this->second_compartment_vector.end());
    std::set_intersection(this->first_compartment_vector.begin(),
                          this->first_compartment_vector.end(),
                          this->second_compartment_vector.begin(),
                          this->second_compartment_vector.end(),
                          std::back_inserter(intersection));
    if (intersection.size() == 0) {
      cout << "no intersection found!" << endl;
      return;
    }
    this->common_item = intersection.at(0);
  }

  static int prioritize(char item) {
    if (std::isalpha(item)) {
      if (std::islower(item)) {
        return 1 + (item - 'a');
      } else {
        return 27 + (item - 'A');
      }
    }
    return 0;
  }
};

struct ElvesGroup_t {
  vector<Rucksack_t> rucksacks_vector;
  char common_item;
  int priority;

  ElvesGroup_t(vector<Rucksack_t> rucksacks) : rucksacks_vector(rucksacks) {
    // cout << "1common item: " << this->common_item << endl;
    this->find_common_item();
    this->priority = Rucksack_t::prioritize(this->common_item);
    // cout << "common item: " << this->common_item << endl;
    // cout << "priority: " << this->priority << endl;
  }

  void find_common_item() {
    for (auto &rucksack : this->rucksacks_vector) {
      std::sort(rucksack.items_vector.begin(), rucksack.items_vector.end());
    }

    auto last_intersection = this->rucksacks_vector.at(0).items_vector;
    vector<char> current_intersection;

    for (std::size_t i = 1; i < this->rucksacks_vector.size(); i++) {
      std::set_intersection(last_intersection.begin(), last_intersection.end(),
                            this->rucksacks_vector.at(i).items_vector.begin(),
                            this->rucksacks_vector.at(i).items_vector.end(),
                            std::back_inserter(current_intersection));
      std::swap(last_intersection, current_intersection);
      current_intersection.clear();
    }
    if (last_intersection.size() == 0) {
      cout << "no intersection found!!" << endl;
      return;
    }
    this->common_item = last_intersection.at(0);
  }
};

int main() {
  cout << "Hello World\n";

  const static int ELVES_GROUP_SIZE = 3;

  // string filename("test_input_file");
  string filename("input_file");
  vector<ElvesGroup_t> elves_groups_vector;
  vector<Rucksack_t> elves_rucksacks_vector;
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

    std::ranges::copy(line | std::views::filter([](unsigned char c) {
                        return std::isalpha(c);
                      }) | std::views::transform([](unsigned char c) {
                        return static_cast<char>(c);
                      }),
                      std::back_inserter(items));

    elves_rucksacks_vector.emplace_back(items);
    if (ELVES_GROUP_SIZE == elves_rucksacks_vector.size()) {
      elves_groups_vector.emplace_back(elves_rucksacks_vector);
      elves_rucksacks_vector.clear();
    }
    // cout << "sizeof items: " << items.size() << endl;
    if (items.size() % 2 != 0) {
      cout << "ODD!" << endl;
    }
  }

  input_file.close();

  // Rucksack_t r = elves_rucksacks_vector.at(0);
  // cout << "intersection at: " << r.common_item << endl;
  // cout << "priority: " << r.priority << endl;

  cout << "size of elves groups: " << elves_groups_vector.size() << endl;

  int total_result =
      std::accumulate(elves_groups_vector.begin(), elves_groups_vector.end(), 0,
                      [](int res, ElvesGroup_t r) { return res + r.priority; });
  cout << "total result: " << total_result << endl;

  
  return EXIT_SUCCESS;

  return 0;
}