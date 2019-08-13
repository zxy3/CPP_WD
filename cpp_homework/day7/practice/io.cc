#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int test0(void)
{
    std::ifstream ifs("io1.cc"); //定义并打开了一个ifstream对象
    if (!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    //std::string s;
    //while(ifs >> s)
    //{
    //    std::cout << s <<std::endl;
    //}

    std::vector<std::string> vec_str;
    std::string line;
    while (getline(ifs, line))
    {
        //std::cout << line << std::endl;
        vec_str.push_back(line);
    }

    std::vector<std::string>::iterator sit = vec_str.begin();
    for (; sit != vec_str.end(); ++sit)
    {
        std::cout << *sit << std::endl;
    }
    ifs.close();

    return 0;
}

int main(void)
{

    std::ifstream ifs("io1.cc");
    if (!ifs.good())
    {
        std::cout << "open file error!" << std::endl;
        return -1;
    }

    std::ofstream ofs("test.txt");
    std::string line;
    while (getline(ifs, line))
    {
        ofs << line << std::endl;
    }

    return 0;
}
