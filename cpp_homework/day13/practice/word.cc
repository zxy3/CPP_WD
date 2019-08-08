///统计词频
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <iostream>

using namespace std;

class Dictionary
{
public:
    void read(const std::string &filename);
    void store(const std::string &filename);
    void print() const;
    void printSort() const;

private:
    map<std::string, int> m_dict;
    vector<std::pair<std::string, int>> m_sortDict;
};

void dealOtherChar(std::string &line)
{
    for (auto &i : line)
    {
        if (isalpha(i))
        {
            i = tolower(i);
        }
        else
        {
            i = ' ';
        }
    }
}

bool compareDict(const std::pair<std::string, int> &lhs, const std::pair<std::string, int> &rhs)
{
    return lhs.second > rhs.second;
}

void Dictionary::read(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        cout << "error in open " << filename << endl;
        return;
    }
    std::string line, word;
    while (std::getline(ifs, line))
    {
        dealOtherChar(line);
        istringstream iss(line);
        while (iss >> word)
        {
            ++m_dict[word];
        }
    }
    for (auto &i : m_dict)
    {
        m_sortDict.push_back(i);
    }
    sort(m_sortDict.begin(), m_sortDict.end(), compareDict);
}

void Dictionary::store(const std::string &filename)
{
    std::ofstream ofs(filename);
    for (auto &i : m_sortDict)
    {
        ofs << i.first << " " << i.second << "\n";
    }
}

void Dictionary::print() const
{
    for (const auto &w : m_dict)
    {
        cout << w.first << " occurs " << w.second
             << ((w.second > 1) ? "  times" : "  time") << endl;
    }
}

void Dictionary::printSort() const
{
    for (const auto &w : m_sortDict)
    {
        cout << w.first << "--> " << w.second
             << ((w.second > 1) ? "  times" : "  time") << endl;
    }
}

int main()
{
    class Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.printSort();
    dict.store("dict.txt");
    return 0;
}