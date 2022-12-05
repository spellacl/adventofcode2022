#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>


void print_crates(const std::vector<char> crates[10])
{
    for(int i = 0; i < 10; i++)
    {
        std::cout << i << ": ";
        for(auto c : crates[i])
        {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    bool part2 = false;
    if(argc == 3)
        part2 = true;

    std::vector<char> crates[10];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        while(std::fgets(line, sizeof(line), file) && (std::strlen(line) != 1))
        {
        //    std::cout << line << std::endl;
            std::string str(line, std::strlen(line)-1);

            size_t pos = str.find('[');
            while( pos != std::string::npos)
            {
                int num = pos/4+1;
                char in = str.at(pos+1);
                crates[num].insert(crates[num].begin(), 1, in);

                pos = str.find('[', pos +1 );
            }
        };

        print_crates(crates);

        while(std::fgets(line, sizeof(line), file))
        {
            //std::cout << line << std::endl;

            strtok(line, " ");
            int move_count = atoi(strtok(nullptr, " "));
            strtok(nullptr, " ");
            int from = atoi(strtok(nullptr, " "));
            strtok(nullptr, " ");
            int to = atoi(strtok(nullptr, " "));

            if(!part2)
            {
                for(int i = 0; i < move_count; i++)
                {
                    char popped = crates[from].back();
                    crates[to].push_back(popped);
                    crates[from].pop_back();
                }
            }
            else
            {
                std::vector<char> sub(crates[from].end() - move_count, crates[from].end());
                crates[to].insert(crates[to].end(), sub.begin(), sub.end());
                crates[from].erase(crates[from].end() - move_count, crates[from].end());
            }
            print_crates(crates);
        };
        fclose(file);

        for(int i = 1; i < 10; i++)
        {
            if(crates[i].size())
            {
                std::cout << crates[i].back();
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
