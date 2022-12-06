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
        char line[4096];

        int first_packet = -1;
        while(std::fgets(line, sizeof(line), file))
        {
            //std::cout << line << std::endl;

            int len = std::strlen(line)-1;

            int markers = 4;
            if(part2)
            {
                markers = 14;
            }
            for(int i = 0; i <= len - markers; i++)
            {
                std::set<char> sub;
                for(int j = 0; j < markers; j++)
                {
                    sub.insert(line[i+j]);
                //    std::cout << line[i+j];
                }
                //std::cout << std::endl;
                if( sub.size() == markers)
                {
                    first_packet =  i + markers;
                    break;
                }
            }
        };
        std::cout << "First Packet: " << first_packet << std::endl;
        fclose(file);
    }
    return 0;
}
