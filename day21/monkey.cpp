#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    bool part2 = false;
    if(argc == 3)
        part2 = true;

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[128];
        std::map<std::string, unsigned long long> solved;

        std::map<std::string, std::tuple<std::string, char, std::string>> remaining;

        while(std::fgets(line, sizeof(line), file))
        {
            char *name = strtok(line, " :");

            char *second = strtok(nullptr, " ");

            char *third = strtok(nullptr, " ");
            if(third)
            {
                char *fourth = strtok(nullptr, " ");

                remaining[name] = std::make_tuple(second, third[0], std::string(fourth, std::strlen(fourth)-1));
            }
            else
            {
                solved[name] = atoll(second);
            }
        };

        auto [a, op, b] = remaining.at("root");
        std::cout << a << " " << op << " " << b << std::endl;

        if(!part2)
        {
            while( solved.count("root") == 0)
            {
                for(auto it = remaining.begin(); it!= remaining.end(); )
                {
                    auto [tmp_a, tmp_op, tmp_b] = it->second;

                    if(solved.count(tmp_a) && solved.count(tmp_b))
                    {
                        if( tmp_op == '+' ) solved[it->first] = solved.at(tmp_a) + solved.at(tmp_b);
                        else if(tmp_op == '-') solved[it->first] = solved.at(tmp_a) - solved.at(tmp_b);
                        else if(tmp_op == '/') solved[it->first] = solved.at(tmp_a) / solved.at(tmp_b);
                        else if(tmp_op == '*') solved[it->first] = solved.at(tmp_a) * solved.at(tmp_b);

                        it = remaining.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            };
            std::cout << solved.at("root") << std::endl;
        }

        fclose(file);
    }
    return 0;
}
