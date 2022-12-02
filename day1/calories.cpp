#include <iostream>
#include <cstdlib>
#include <string.h>
#include <assert.h>
#include <vector>
#include <algorithm>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];
        int max_elf = -1;
        char *ptr = NULL;

        long int sum = 0;
        long int max_sum = -1;
        int count = 0;

        std::vector<long int> elf_counts;

        while(fgets(line, sizeof(line), file))
        {
            long int val = strtol(line, &ptr, 10);
            //std::cout << val << std::endl;

            if(val != 0)
            {
                sum += val;
            }
            else
            {
                count += 1;
                elf_counts.push_back(sum);

                if( sum > max_sum)
                {
                    max_sum = sum;
                    max_elf = count;
                }
                sum = 0;
            }
        };
        fclose(file);

        printf("max elf %d of %d max sum %ld\n", max_elf, count, max_sum);

        std::sort(elf_counts.begin(), elf_counts.end(), std::greater<>());
//        for( auto &val : elf_counts)
//            std::cout << val << " ";
//        std::cout << std::endl;

        int total = elf_counts.at(0) + elf_counts.at(1) + elf_counts.at(2);
        std::cout << "Max 3 sum " << total << std::endl;


    }

    return 0;
}
