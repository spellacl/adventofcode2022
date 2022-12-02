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

    std::map<char, int> them{{'A', 1}, {'B', 2}, {'C', 3}};
    std::map<char, int> you{{'X', 1}, {'Y', 2}, {'Z', 3}};

    std::map<std::pair<char, char>, int> score{
      {std::pair('A', 'X'), 3}, // rock, rock
      {std::pair('B', 'Y'), 3}, // paper, paper
      {std::pair('C', 'Z'), 3}, // scissors, scissors
      {std::pair('A', 'Y'), 6}, // rock, paper
      {std::pair('A', 'Z'), 0}, // rock, scissors
      {std::pair('B', 'X'), 0}, // paper, rock
      {std::pair('B', 'Z'), 6}, // paper, scissors
      {std::pair('C', 'X'), 6}, // scissors, rock
      {std::pair('C', 'Y'), 0}, // scissors, paper
      };

    std::map<std::pair<char, char>, char> outcome{
      {std::pair('A', 'X'), 'Z'}, // rock, lose
      {std::pair('B', 'Y'), 'Y'}, // paper, draw
      {std::pair('C', 'Z'), 'X'}, // scissors, win
      {std::pair('A', 'Y'), 'X'}, // rock, draw
      {std::pair('A', 'Z'), 'Y'}, // rock, win
      {std::pair('B', 'X'), 'X'}, // paper, lose
      {std::pair('B', 'Z'), 'Z'}, // paper, win
      {std::pair('C', 'X'), 'Y'}, // scissors, lose
      {std::pair('C', 'Y'), 'Z'}, // scissors, draw
        };


    long int total_score = 0;
    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        while(std::fgets(line, sizeof(line), file))
        {
            char* first = std::strtok(line, " ");
            char* second = std::strtok(nullptr, " ");

            char they_play = first[0];
            char you_play;

            if(!part2)
            {
                you_play = second[0];
            }
            else
            {
                you_play = outcome[std::pair(they_play, second[0])];
            }
            total_score += you[you_play] + score[std::pair(they_play, you_play)];
        };
        fclose(file);
        std::cout << "Total_score " << total_score << std::endl;
    }
    return 0;
}
