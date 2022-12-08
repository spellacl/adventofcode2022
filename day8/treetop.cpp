#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    bool part2 = false;
    if(argc == 3)
        part2 = true;

    std::map<std::pair<int, int>, int> height;
    std::map<std::pair<int, int>, bool> visible;

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        int row = 0;
        while(std::fgets(line, sizeof(line), file))
        {
//            std::cout << line << std::endl;
            for(int col = 0; col < std::strlen(line)-1; col++)
            {
                height[std::pair(row, col)] = line[col] - '0';
            }
            row += 1;
        };
        int size=  row;

        std::cout << "TreeTop of size " << size << std::endl;

        int count = size*2 + (size-2)*2;
        std::cout << "Before count " << count << std::endl;
        int max = INT_MIN;
        for(int i = 1; i < size-1; i++)
        {
            for(int j = 1; j < size-1; j++)
            {
                bool visible_above = true;
                int visible_above_count = 0;
                // above
                for(int row = i-1; row >= 0; row--)
                {
                    visible_above_count += 1;
                    if(height[std::pair(row, j)] >= height[std::pair(i,j)])
                    {
                        visible_above = false;
                        break;
                    }
                }

                bool visible_below = true;
                int visible_below_count = 0;
                // below
                for(int row = i+1; row < size; row++)
                {
                    visible_below_count += 1;
                    if(height[std::pair(row, j)] >= height[std::pair(i,j)])
                    {
                        visible_below = false;
                        break;
                    }
                }

                bool visible_left = true;
                int visible_left_count = 0;
                // left
                for(int col = j-1; col >= 0; col--)
                {
                    visible_left_count += 1;
                    if(height[std::pair(i, col)] >= height[std::pair(i,j)])
                    {
                        visible_left = false;
                        break;
                    }
                }

                bool visible_right = true;
                int visible_right_count = 0;
                // right
                for(int col = j+1; col < size; col++)
                {
                    visible_right_count +=1;
                    if(height[std::pair(i, col)] >= height[std::pair(i,j)])
                    {
                        visible_right = false;
                        break;
                    }
                }

                count += visible_right || visible_left || visible_below || visible_above;
                int visible_count = visible_right_count * visible_left_count * visible_below_count * visible_above_count;
                max = std::max(max, visible_count);
            }
        }
        std::cout << "After count " << count << std::endl;
        std::cout << "Max visible count " << max << std::endl;
        fclose(file);
    }
    return 0;
}

