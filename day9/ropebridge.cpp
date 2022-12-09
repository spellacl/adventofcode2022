#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

double distance(const std::pair<int,int>& H, const std::pair<int,int>& T)
{
    return std::sqrt(
            (H.first - T.first)   * (H.first - T.first)
        +   (H.second - T.second) * (H.second - T.second)
        );
}

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    bool part2 = false;
    if(argc == 3)
        part2 = true;

    std::vector<std::pair<int, int>> snake;
    if(!part2)
        snake.resize(2);
    else
        snake.resize(10);

    std::map<std::pair<int,int>, int> tail_visited;

    std::map<char, std::pair<int, int>> move_set = {{'R', std::pair(0,1)},
                                                  {'U', std::pair(1,0)},
                                                  {'L', std::pair(0,-1)},
                                                  {'D', std::pair(-1,0)},
                                                  };

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[4096];

        while(std::fgets(line, sizeof(line), file))
        {
            char* move = strtok(line, " ");
            int count = atoi(strtok(nullptr, " "));
            //std::cout << move << " " << count << std::endl;

            for(int i = 0; i < count; i++)
            {
                snake.at(0) = snake.at(0) + move_set[move[0]];

                for(int j = 1; j < snake.size(); j++)
                {
                    if(distance(snake.at(j-1), snake.at(j)) > 1.5) // Diagonal distance is 1.4...
                    {
                        if(snake.at(j-1).first  < snake.at(j).first)    snake.at(j) = snake.at(j) + move_set['D'];
                        if(snake.at(j-1).first  > snake.at(j).first)    snake.at(j) = snake.at(j) + move_set['U'];
                        if(snake.at(j-1).second < snake.at(j).second)   snake.at(j) = snake.at(j) + move_set['L'];
                        if(snake.at(j-1).second > snake.at(j).second)   snake.at(j) = snake.at(j) + move_set['R'];
                    }
                    tail_visited[std::pair(snake.back().first, snake.back().second)] += 1;
                }

/*                for(int j = 0; j < snake.size(); j++)
                {
                    std::cout << j << "(" << snake.at(j).first << "," << snake.at(j).second << ") ";
                }
                std::cout << std::endl;*/
            }
        };
        std::cout << "Number of sites visited by T: " << tail_visited.size() << std::endl;

        fclose(file);
    }
    return 0;
}

