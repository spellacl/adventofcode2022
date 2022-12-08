#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <climits>

class Dir
{
public:
    Dir(std::string name, int depth, Dir* parent) : dirParent(parent),
                                                    dirName(name),
                                                    dirDepth(depth) {}

    std::string name(){ return dirName; }
    int depth(){return dirDepth;}
    Dir* parent(){ return dirParent; }

    // getting lazy now - no more private members
    std::vector<Dir *> subDirectories;
    std::map<std::string, long int> files;
    long long int size;
private:
    Dir *dirParent;
    std::string dirName;
    int dirDepth;

};

void print_directory(Dir *directory)
{
    if(directory != nullptr)
    {
        std::cout << std::string(directory->depth()*2, ' ') << " - " << directory->name() << " " << directory->size << std::endl;
        for( auto & file : directory->files)
        {
            std::cout << std::string((directory->depth()+1)*2, ' ') << " * " << file.first << " " << file.second << std::endl;
        }
        for(auto &dir: directory->subDirectories)
        {
            print_directory(dir);
        }
    }
}

void part1(long long int& answer, Dir *directory)
{
    if(directory)
    {
        if(directory->size <= 100000)
        {
            answer += directory->size;
        }
        for(auto &dir: directory->subDirectories)
        {
            part1(answer, dir);
        }
    }
}

void part2(long long int free, long long int& min, Dir *directory)
{
    if(directory)
    {
        if(directory->size + free > 30000000)
        {
            min = std::min(directory->size, min);
        }
        for(auto &dir: directory->subDirectories)
        {
            part2(free, min, dir);
        }
    }
}

void size_tree(Dir *directory)
{
    if(directory != nullptr)
    {
        for(auto & file : directory->files)
        {
            directory->size += file.second;
        }
        for(auto &dir : directory->subDirectories)
        {
            size_tree(dir);
            directory->size += dir->size;
        }
    }
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    Dir *currDir = nullptr;
    Dir *HEAD = nullptr;

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        while(std::fgets(line, sizeof(line), file))
        {
            std::string str(line, std::strlen(line)-1);
            std::cout << str << std::endl;
            int len = str.size();

            std::string::size_type position = std::string::npos;

            if(std::string::npos != str.find("$ cd .."))
            {
                currDir = currDir->parent();
            }
            else if(std::string::npos != str.find("$ cd "))
            {
                std::string::size_type pos = str.find("$ cd ");
                if(str.substr(pos+5, len) == "/")
                {
                    currDir = new Dir(str.substr(pos+5, len), 0, nullptr);
                    HEAD = currDir;
                }
                else
                {
                    for(Dir *dir : currDir->subDirectories)
                    {
                        if(dir->name() == str.substr(pos+5, len))
                        {
                            currDir = dir;
                            break;
                        }
                    }
                }
            }
            else if(std::string::npos != str.find("$ ls"))
            {
                // no-op
            }
            else if((position = str.find("dir ")) != std::string::npos)
            {
                Dir *next = new Dir(str.substr(position+4, len), currDir->depth()+1, currDir);
                currDir->subDirectories.push_back(next);
            }
            else // add file to existing directory pointed to by currDir
            {
               position = str.find(" ");
               long int size = std::stol(str.substr(0, position));
               std::string filename = str.substr(position+1, len);

               currDir->files[filename] = size;
            }
        };
        size_tree(HEAD); // traverse tree calculating sizes
        print_directory(HEAD);

        long long int answer = 0;
        part1(answer, HEAD);
        std::cout << "Part1: " << answer << std::endl;

        long long int free = 70000000 - HEAD->size;
        long long int min = LONG_MAX;
        part2(free, min, HEAD);
        std::cout << "Part2: " << free << " " << min << std::endl;
    }
    return 0;
}
