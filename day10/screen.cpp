#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

void part1(int cycle, int x, int &check_cycle, long &signal_strength)
{
    if(cycle == check_cycle)
    {
        check_cycle += 40;
        signal_strength += cycle * x;
    }
}

void part2(int cycle, int x, std::vector<char>& CRT)
{
    int pixel = (cycle - 1)%40;
    if( pixel == (x-1) || pixel == x || pixel == (x+1) )
    {
        CRT.at(cycle - 1) = '#';
    }
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[64];

        long x = 1;
        long cycle = 1;

        int check_cycle = 20;
        long signal_strength = 0;
        std::vector<char> CRT(240, '.');

        while(std::fgets(line, sizeof(line), file))
        {
            //std::cout << line << std::endl;
            char *intr = strtok(line, " ");

            if( std::strcmp(intr, "addx") == 0)
            {
                part1(cycle, x, check_cycle, signal_strength);
                part2(cycle, x, CRT);
                //std::cout << " -- cycle: " << cycle << " " << x << " " << CRT.at(cycle-1) << std::endl;
                cycle += 1;

                int add = atoi(strtok(nullptr, " "));
                part1(cycle, x, check_cycle, signal_strength);
                part2(cycle, x, CRT);
                //std::cout << " --- cycle: " << cycle << " " << x << " " << CRT.at(cycle-1) << std::endl;
                cycle += 1;
                x += add;
            }
            else //noop
            {
                part1(cycle, x, check_cycle, signal_strength);
                part2(cycle, x, CRT);
                //std::cout << " - cycle: " << cycle << " " << x << " " << CRT.at(cycle-1) << std::endl;
                cycle += 1;
            }
        };

        int count = 0;
        for(int i = 0; i < 6; i++)
        {
            for(int j = 0; j < 40; j++)
            {
                std::cout << CRT.at(count);
                count ++;
            }
            std::cout << std::endl;
        }
        std::cout << "Signal Strength: "  << signal_strength << std::endl;

        fclose(file);
    }
    return 0;
}
