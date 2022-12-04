#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
#include <cctype>

template<class T>
std::vector<char> return_intersection(T& first, T& second)
{
    std::vector<char> intersection;

    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    std::set_intersection(first.begin(), first.end(),
                      second.begin(), second.end(),
                      std::back_inserter(intersection));

    assert(intersection.size() > 0);

    return intersection;
}

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

        long int total = 0;
        while(fgets(line, sizeof(line), file))
        {
            char val;
            if(!part2)
            {
                // HI STU :)
                long len = std::strlen(line) - 1; // for null '\0' at the end
                assert(len %2 == 0);

                long half_len = len/2;

                std::string first(line, half_len);
                std::string second(line + half_len, half_len);

                std::vector<char> intersection = return_intersection(first, second);
                val = intersection.at(0);
            }
            else
            {
                // need to read two more elves.
                std::string first(line, std::strlen(line)-1);
                fgets(line, sizeof(line), file);
                std::string second(line, std::strlen(line)-1);
                fgets(line, sizeof(line), file);
                std::string third(line, std::strlen(line)-1);

                std::vector<char> intersection1, intersection2, intersection3;
                intersection1 = return_intersection(first, second);
                intersection2 = return_intersection(second, third);
                intersection3 = return_intersection(intersection1, intersection2);

                val = intersection3.at(0);
            }
            // A in 65 in ASCII, a is 97 in ASCII
            long score = std::isupper(val) ? val%64 + 26 : val%96;

            total += score;
        };
        fclose(file);

        std::cout << "Score: " << total << std::endl;

    }
    return 0;
}
