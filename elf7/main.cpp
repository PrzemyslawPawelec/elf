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

struct ElfFile_t
{
  std::filesystem::path Path;
  int Size;
  ElfFile_t(std::filesystem::path _Path, int _Size) : Path(_Path), Size(_Size){}
  int getSize() const {return Size;}
  std::filesystem::path getPath() const {return Path;}
};

struct ElfDirectory_t
{
  std::filesystem::path Path;
  int Size;
  int TotalSize;
  vector<ElfFile_t> Files; 
  // dirs inside?
  ElfDirectory_t(std::filesystem::path _Path) : Path(_Path), Size(0), TotalSize(0) {}
  void AddFile(const ElfFile_t elfFile)
  {
    Files.emplace_back(elfFile);
    Size += elfFile.getSize();
  }
  vector<ElfFile_t> &GetFiles() {return Files;}
  int GetSize() const {return Size;}
  std::filesystem::path GetPath() const {return Path;}
  void SetTotalSize(int size) {TotalSize = size;}
  int GetTotalSize() const {return TotalSize;}
};


// struct ElfDirectory_t
// {
//   string Name;
//   list<ElfFile_t> files;
//   list<ElfDirectory_t> Children;
//   std::shared_ptr<ElfDirectory_t> Parent;
// };

enum ParserMode : uint8_t
{
  PARSING_COMMAND = 0,
  PARSING_LS = 1
};

const static string CD_COMMAND = "$ cd ";
const static string LS_COMMAND = "$ ls";
const static string DIR_ENTRY = "dir ";
const static string ROOT_DIR = "/";
const static string PARENT_DIR = "..";

int main() {
  std::filesystem::path cwd = std::filesystem::current_path().filename();
  cout << "Hello World: " << cwd << endl;

  // string filename("test_input_file");
  string filename("input_file");
  // vector<list<string>> elves_stacks{};
  // list<string> elves_stack{};
  multimap<string, ElfFile_t> elvesDirectoriesMap{};
  set<string> elvesDirectoriesSet{};
  vector<ElfDirectory_t> elvesDirectoriesVector{};
  ifstream input_file(filename);

  string line{};
  ParserMode parserMode = PARSING_COMMAND;
  std::filesystem::path currentPath{};
  size_t foundPos{};


  if (not input_file.is_open()) {
    cout << "Could not open the file: " << filename << endl;
    return EXIT_FAILURE;
  }

  while (getline(input_file, line, '\n')) 
  {

    if ('$' == line.at(0))
    {
      parserMode = PARSING_COMMAND;
    }

    switch (parserMode)
    {
    case PARSING_COMMAND:
      {
        if (std::string::npos != line.find(CD_COMMAND))
        {
          string cd = line.substr(CD_COMMAND.size());
          cout << "cd " << cd << endl;

          if (ROOT_DIR == cd)
          {
            currentPath = ROOT_DIR;
          }
          else if (PARENT_DIR == cd)
          {
            currentPath = currentPath.parent_path();
          }
          else
          {
            if (ROOT_DIR == currentPath.string())
            {
              currentPath = currentPath.string() + cd;
            }
            else
            {
              currentPath = currentPath.string() + "/" + cd;
            }
          }
          elvesDirectoriesSet.emplace(currentPath.string());
          cout << "currentPath: " << currentPath << endl;
        }
        else if (std::string::npos != line.find(LS_COMMAND))
        {
          cout << "ls" << endl;
          parserMode = PARSING_LS;
        }
        break;
      }
    case PARSING_LS:
      {
        if (std::string::npos != line.find(DIR_ENTRY))
        {
          string dir = line.substr(DIR_ENTRY.size());
          cout << "dir " << dir << endl;
        }
        else if (isdigit(line.at(0)))
        {
          int size{};
          string name{};
          std::filesystem::path fullPath{};
          stringstream ss(line); 
          ss >> size;
          ss >> name;
          if (ROOT_DIR == currentPath.string())
          {
            fullPath = currentPath.string() + name;
          }
          else
          {
            fullPath = currentPath.string() + "/" + name;
          }
          elvesDirectoriesMap.emplace(currentPath.string(), ElfFile_t(fullPath, size));
          cout << "file \"" << name << "\" of size: " << size << " fullPath: " << fullPath << endl;
        }
        break;
      }

    default:
      cout << "Wrong parsing..." << endl;
      break;
    }
  }

  input_file.close();

  const static int TOTAL_DISK_SPACE_SIZE = 70000000;
  const static int MIN_SPACE_SIZE = 30000000;
  const static int UPPER_LIMIT_SIZE = 100000;
  int freeSpace{};

  for (const auto &d : elvesDirectoriesSet)
  {
    ElfDirectory_t elfDirectory = ElfDirectory_t(d);

    auto range = elvesDirectoriesMap.equal_range(d);
    for (auto i = range.first; i != range.second; ++i)
    {
      elfDirectory.AddFile(i->second);
    }
    // cout << d << " --> files: " << elfDirectory.GetFiles().size() << ", size: " << elfDirectory.GetSize() << endl;
    elvesDirectoriesVector.emplace_back(elfDirectory);
  }

  for (auto &d : elvesDirectoriesVector)
  {
    int totalSize = std::accumulate(elvesDirectoriesVector.begin(), elvesDirectoriesVector.end(), 0,
      [&d](int res, const ElfDirectory_t &elfDirectory)
      {
        return res + ((std::string::npos != elfDirectory.GetPath().string().rfind(d.GetPath().string(), 0)) ? elfDirectory.GetSize() : 0);
      });
    d.SetTotalSize(totalSize);
    if (ROOT_DIR == d.GetPath().string())
    {
      freeSpace = TOTAL_DISK_SPACE_SIZE - totalSize;
      cout << "Free space: " << freeSpace << endl;
    }
    cout << "Directory: " << d.GetPath() << " -> TotalSize: " << d.GetTotalSize() << endl;
  }

  int res = std::accumulate(elvesDirectoriesVector.begin(), elvesDirectoriesVector.end(), 0,
      [](int res, const ElfDirectory_t &elfDirectory)
      {
        return res + ( elfDirectory.GetTotalSize() <= UPPER_LIMIT_SIZE ? elfDirectory.GetTotalSize() : 0);
      });
  cout << "res: " << res << endl;

  auto min_el = std::min_element(elvesDirectoriesVector.begin(), elvesDirectoriesVector.end(), [&freeSpace](const ElfDirectory_t &elfDir1, const ElfDirectory_t &elfDir2){

    if ( (freeSpace + elfDir1.GetTotalSize()) >= MIN_SPACE_SIZE )
    {
      if ( (freeSpace + elfDir2.GetTotalSize()) >= MIN_SPACE_SIZE )
      {
        return elfDir1.GetTotalSize() < elfDir2.GetTotalSize(); 
      }
      else return true;
    }
    else return false;
  });
  cout << "min element directory size: " << (*min_el).GetTotalSize() << endl;

  

  return EXIT_SUCCESS;
}
