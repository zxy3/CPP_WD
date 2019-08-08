#include <bits/stdc++.h>
using namespace std;

#if 1
template <class Container>
void display(const Container &c)
{
    // 定义一个迭代器，指向容器C的头部
    typename Container::const_iterator cit = c.begin();
    for (; cit != c.end(); ++cit)
    {
        // int对象 ---> string对象
        cout << cit->first << " ---> " << cit->second << endl;
    }
}

class Textstatistic
{
public:
    // 读文件
    void readFile(const string);
    // 统计词频
    void statistic(const string &);

private:
    // 是string类型的容器,存放每一行，跟随行号打印
    vector<string> lines;
    // map容器，键值对类型<string int> 保存行号
    map<string, set<int>> wordLine;
    // map容器，键值对类型<string int>
    map<string, int> dict;
};
// 读文件
void Textstatistic::readFile(const string filename)
{
    ifstream ifs(filename);
    string line;
    int cnt = 0;               //行数
    while (getline(ifs, line)) //循环读取每一行
    {
        ++cnt;
        // 字符流对象
        istringstream iss(line);
        string word;
        while (!iss.eof()) //检查是否已到达文件末尾
        {
            iss >> word;
            char *wd = new char[strlen(word.c_str()) + 1]();
            strcpy(wd, word.c_str());
            // cout << "---------" << wd << endl;
            while (wd[0] != '\0' && !((wd[0] <= 'z' && wd[0] >= 'a') || (wd[0] <= 'Z' && wd[0] >= 'A')))
            {
                // 如果拿到的一串字符含有数字，符号，则指向下一位检查
                // cout << "---------" << wd << endl;
                ++wd;
            }
            //  cities[1]通过关键字访问元素
            wordLine[wd].insert(cnt);

            ++dict[wd];
            // cout << "------------------------" << wd << endl;
            // cout << "-----------";
            display(dict);
        }
        lines.push_back(line);
        for (auto &&i : lines)
            cout << quoted(i) << ' ';
        cout << endl
             << endl;
    }
}

void Textstatistic::statistic(const string &word)
{
    dict[word];
    // 测试得出，最后要减1
    cout << word << " occurs " << dict.find(word)->second - 1 << " times" << endl;
    for (auto &elem : wordLine[word])
    {
        // 打印行号和行
        cout << "(line " << elem << ") " << lines[elem - 1] << endl;
    }
}
// test
int main(void)
{
    Textstatistic tq;
    tq.readFile("test.txt");
    tq.statistic("zhang");
    return 0;
}
#endif
