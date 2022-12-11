#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    bool part2 = false;
    if(argc == 3)
        part2 = true;

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[64];

        long x = 1;
        long cycle = 1;

        int check_cycle = 20;
        long signal_strength = 0;

        while(std::fgets(line, sizeof(line), file))
        {
            std::cout << line << std::endl;
            char *intr = strtok(line, " ");

            if( std::strcmp(intr, "addx") == 0)
            {
                if(cycle == check_cycle)
                {
                    check_cycle += 40;
                    std::cout << " -- cycle: " << cycle << " " << x << std::endl;
                    signal_strength += cycle * x;
                }
                cycle += 1;

                int add = atoi(strtok(nullptr, " "));
                if(cycle == check_cycle)
                {
                    check_cycle += 40;
                    std::cout << " --- cycle: " << cycle << " " << x << std::endl;
                    signal_strength += cycle * x;
                }
                cycle += 1;
                x += add;
            }
            else //noop
            {
                if(cycle == check_cycle)
                {
                    check_cycle += 40;
                    std::cout << " - cycle: " << cycle << " " << x << std::endl;
                    signal_strength += cycle * x;
                }
                cycle += 1;
            }
        };
        std::cout << "Signal Strength: "  << signal_strength << std::endl;

        fclose(file);
    }
    return 0;
}
