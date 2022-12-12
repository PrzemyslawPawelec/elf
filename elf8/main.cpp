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
#include <boost/range/adaptors.hpp>

using namespace std;

enum ParserMode : uint8_t
{
  PARSING_COMMAND = 0,
  PARSING_LS = 1
};


struct ElvesTree_t
{
  int x;
  int y;
  int height;
  int scenicScore;
  bool isVisible;
  ElvesTree_t(int _x, int _y, int _height) : x(_x), y(_y), height(_height) {}
  int GetX() const {return x;}
  int GetY() const {return y;}
  int GetHeight() const {return height;}
  bool GetIsVisible() const {return isVisible;}
  int GetScenicScore() const {return scenicScore;}
  void CheckIfIsVisible(const vector<ElvesTree_t> &trees, const int maxX, const int maxY)
  {
    if ( (this->x == 0)     || 
         (this->x == maxX)  ||
         (this->y == 0)     ||
         (this->y == maxY) )
    {
      this->isVisible = true;
      // cout << "visible tree of coordinates: x: " << this->x << ", y: " << this->y << endl;
      return;
    }

    // LEFT
    if (std::ranges::all_of(trees
                             | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.y == this->y) && (tree.x < this->x) );}),
                             [this](const ElvesTree_t &tree){return (tree.height < this->height);}))
    {
      this->isVisible = true;
      cout << "visible tree of coordinates: x: " << this->x << ", y: " << this->y << endl;
      return;
    }
    // RIGHT
    if (std::ranges::all_of(trees
                             | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.y == this->y) && (tree.x > this->x) );}),
                             [this](const ElvesTree_t &tree){return (tree.height < this->height);}))
    {
      this->isVisible = true;
      cout << "visible tree of coordinates: x: " << this->x << ", y: " << this->y << endl;
      return;
    }
    // TOP
    if (std::ranges::all_of(trees
                             | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.x == this->x) && (tree.y < this->y));}),
                             [this](const ElvesTree_t &tree){return (tree.height < this->height);}))
    {
      this->isVisible = true;
      cout << "visible tree of coordinates: x: " << this->x << ", y: " << this->y << endl;
      return;
    }
    // BOTTOM
    if (std::ranges::all_of(trees
                             | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.x == this->x) && (tree.y > this->y));}),
                             [this](const ElvesTree_t &tree){return (tree.height < this->height);}))
    {
      this->isVisible = true;
      cout << "visible tree of coordinates: x: " << this->x << ", y: " << this->y << endl;
      return;
    }
    this->isVisible = false;

    // isVisible = visible;
  }

  void CheckScenicScore(const vector<ElvesTree_t> &trees, const int maxX, const int maxY)
  {
    // LEFT
    int score1{};
    vector<ElvesTree_t> sortedTrees;
    // std::ranges::sort(trees
    //                   | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.y == this->y) && (tree.x > this->x));}),
    //                   [](const ElvesTree_t &t1, const ElvesTree_t &t2) {return (t1.x > t2.x);} );

    std::ranges::copy(trees
                       | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.y == this->y) && (tree.x < this->x));}),
                       std::back_inserter(sortedTrees));
    // cout << "LEFT: ";
    // std::ranges::for_each(sortedTrees, [](const auto &t){cout << t.height << " ";});
    // cout << endl;
    std::sort(sortedTrees.begin(), sortedTrees.end(), [](ElvesTree_t &t1, ElvesTree_t &t2){return (t1.x > t2.x);});
    // cout << "LEFT SORTED: ";
    // std::ranges::for_each(sortedTrees, [](const auto &t){cout << t.height << " ";});
    // cout << endl;
    for (const auto &t : sortedTrees)
    {
      score1++; 
      if (t.height >= this->height)
      {
        break;
      }
    }
    sortedTrees.clear();
    // RIGHT
    int score2{};
    std::ranges::copy(trees
                       | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.y == this->y) && (tree.x > this->x));}),
                       std::back_inserter(sortedTrees));
    std::sort(sortedTrees.begin(), sortedTrees.end(), [](ElvesTree_t &t1, ElvesTree_t &t2){return (t1.x < t2.x);});
    for (const auto &t : sortedTrees)
    {
      score2++; 
      if (t.height >= this->height)
      {
        break;
      }
    }
    sortedTrees.clear();
    // TOP
    int score3{};
    std::ranges::copy(trees
                       | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.x == this->x) && (tree.y < this->y));}),
                       std::back_inserter(sortedTrees));
    std::sort(sortedTrees.begin(), sortedTrees.end(), [](ElvesTree_t &t1, ElvesTree_t &t2){return (t1.y > t2.y);});
    for (const auto &t : sortedTrees)
    {
      score3++; 
      if (t.height >= this->height)
      {
        break;
      }
    }
    sortedTrees.clear();
    // BOTTOM
    int score4{};
    std::ranges::copy(trees
                       | std::views::filter([this](const ElvesTree_t &tree){return ( (tree.x == this->x) && (tree.y > this->y));}),
                       std::back_inserter(sortedTrees));
    std::sort(sortedTrees.begin(), sortedTrees.end(), [](ElvesTree_t &t1, ElvesTree_t &t2){return (t1.y < t2.y);});
    for (const auto &t : sortedTrees)
    {
      score4++; 
      if (t.height >= this->height)
      {
        break;
      }
    }

    this->scenicScore = score1 * score2 * score3 * score4;
    cout << "scenicScore: " << this->scenicScore 
         << ", left: " << score1 << ", right: " << score2 << ", top: " << score3 << ", bottom: " << score4 << endl;
  }

  // std::ranges::copy(line | std::views::filter([](unsigned char c) {
  //                       return std::isalpha(c);
  //                     }) | std::views::transform([](unsigned char c) {
  //                       return static_cast<char>(c);
  //                     }),
  //                     std::back_inserter(items));
};



int main() {
  std::filesystem::path cwd = std::filesystem::current_path().filename();
  cout << "Hello World: " << cwd << endl;

  // string filename("test_input_file");
  string filename("input_file");
  ifstream input_file(filename);
  vector<ElvesTree_t> elvesTreesVector;

  string line{};
  ParserMode parserMode = PARSING_COMMAND;

  if (not input_file.is_open()) {
    cout << "Could not open the file: " << filename << endl;
    return EXIT_FAILURE;
  }

  int x = 0;
  int y = 0;
  while (getline(input_file, line, '\n')) 
  {
    x = 0;

    for (const auto &c : line)
    {
      elvesTreesVector.emplace_back(x, y, c - '0');
      x++;
    }
    y++;
  }

  input_file.close();

  int yy = elvesTreesVector.at(0).GetY();
  for (const auto &t : elvesTreesVector)
  {
    if (t.GetY() > yy)
    {
      yy++;
      cout << endl;
    }
    cout << t.GetHeight();
  }
  cout << endl;

  x--;
  y--;
  cout << "maxX: " << x << ", maxY: " << y << endl;


  std::ranges::for_each(elvesTreesVector, [x,y,&elvesTreesVector](auto &t){t.CheckIfIsVisible(elvesTreesVector, x, y);});

  int res = std::accumulate(elvesTreesVector.begin(), elvesTreesVector.end(), 0,
      [](int res, const ElvesTree_t &tree)
      {
        return res + (tree.GetIsVisible() ? 1 : 0);
      });
  cout << "res: " << res << endl;

  ElvesTree_t tr = elvesTreesVector.at(7);
  cout << "x: " << tr.x << ", y: " << tr.y << endl;
  tr.CheckScenicScore(elvesTreesVector, x, y);
  tr = elvesTreesVector.at(17);
  cout << "x: " << tr.x << ", y: " << tr.y << endl;
  tr.CheckScenicScore(elvesTreesVector, x, y);

  std::ranges::for_each(elvesTreesVector, [x,y,&elvesTreesVector](auto &t){t.CheckScenicScore(elvesTreesVector, x, y);});

  auto max_el = std::max_element(elvesTreesVector.begin(), elvesTreesVector.end(), [](const ElvesTree_t &tree1, const ElvesTree_t &tree2){
    return (tree1.GetScenicScore() < tree2.GetScenicScore());
  });
  cout << "Max scenic score: " << (*max_el).GetScenicScore() << endl;


  return EXIT_SUCCESS;
}
