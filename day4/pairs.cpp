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
        char line[256];

        int count = 0;
        while(std::fgets(line, sizeof(line), file))
        {
            //std::cout << line;
            long a = atol(std::strtok(line, "-,"));
            long z = atol(std::strtok(nullptr, "-,"));
            long A = atol(std::strtok(nullptr, "-,"));
            long Z = atol(std::strtok(nullptr, "-,"));
            //std::cout << a << " " << z << " " << A << " " << Z << std::endl;

            if(!part2)
            {
                // a-z A-z
                if(   ((a >= A && a <= Z) && (z >= A && z <= Z))    // a-z in A-Z
                  ||  ((A >= a && A <= z) && (Z >= a && Z <= z)) )   // A-Z in a-z
                {
                    count += 1;
                }
            }
            else
            {
                //               [a........z]
                //            [A....Z]  [A...Z]
                //               [A........Z]
                //            [a....z]  [a...z]
                if(   ((a >= A && a <= Z) || (z >= A && z <= Z))
                   || ((A >= a && A <= z) || (Z >= a && Z <= z)) )
                {
                    count +=1;
                }
            }
        };

        std::cout << "Total fully contained: " << count << std::endl;
        fclose(file);
    }
    return 0;
}
