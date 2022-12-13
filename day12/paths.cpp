#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "limits.h"
#include <set>
#include <cassert>

std::vector<std::pair<int, int>> neighbours = {{-1,0}, {0,-1}, {1, 0}, {0, 1}};

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {l.first+r.first,l.second+r.second};
}

int min(int a, int b)
{
    return a < b ? a : b;
}

template <typename T>
void print(std::vector<T>& matrix, int N, int M)
{
    int ind;
    for(int i = 0; i < N; i ++)
    {
        for(int j = 0; j < M; j++)
        {
            ind = i * M + j;
            if(matrix.at(ind) == 0)
                printf("\e[0m%2d  \e[0m", matrix.at(ind));
            else
                printf("%2d  ", matrix.at(ind));
        }
        printf("\n");
    }
    printf("\n");
}

std::pair<int, int> min(std::map<std::pair<int, int>, int> distance, std::set<std::pair<int, int>> Q)
{
    std::pair<int, int> min_v = std::make_pair(-1,-1);
    int min = INT_MAX;

    for( auto pair : Q )
    {
        if(distance.at(pair) < min)
        {
            min = distance.at(pair);
            min_v = pair;
        }
    }

//    std::cout << (min == INT_MAX) << std::endl;
    return min_v;
}

int update(std::vector<int> matrix, int N, int M, int start_x, int start_y, int end_x, int end_y)
{
    std::map<std::pair<int, int>, int> distance;
    std::set<std::pair<int, int>> Q;
    std::set<std::pair<int, int>> visited;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            distance[std::make_pair(i,j)] = INT_MAX;
        }
    }
    distance.at(std::make_pair(start_x,start_y)) = 0;
    Q.insert(std::make_pair(start_x,start_y));

    while(!Q.empty())
    {
        std::pair<int, int> v = min(distance, Q);
        Q.erase(v);
        visited.insert(v);

        for(auto & neighbour : neighbours)
        {
            std::pair<int, int> u = v + neighbour;

            if(visited.count(u) == 0 && u.first >= 0 && u.second >= 0 && u.first <= N-1 && u.second <= M-1)
            {
                int diff = matrix.at(u.first * M + u.second) - matrix.at(v.first * M + v.second);
                if(diff <= 1)
                {
                    int alt = distance.at(v) + 1;
                    if( alt < distance.at(u))
                    {
                        Q.insert(u);
                        distance.at(u) = alt;
                    }
                }
            }
        }

    }

    std::cout << "distance(" << end_x << "," << end_y << ") " << distance.at(std::make_pair(end_x, end_y)) << std::endl;
    return distance.at(std::make_pair(end_x, end_y));
}

int main(int argc, char * argv[])
{
    const char * filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file)
    {
        char line[256];

        std::vector<int> matrix;

        int end_x = -1, end_y = -1;
        int start_x = -1, start_y = -1;

        int N = 0; int M = 0;

        std::vector<std::pair<int, int>> allAs;
        while(fgets(line, sizeof(line), file))
        {
            M = strlen(line)-1;
            line[strlen(line)-1] = '\0';
            std::string str(line, strlen(line));

            for(int j = 0; j < strlen(line); j++)
            {
                if(str.at(j) == 'S')
                {
                    str.at(j) = 'a';
                    start_x = N;
                    start_y = j;
                }
                if(str.at(j) == 'E')
                {
                    end_x = N;
                    end_y = j;
                    str.at(j) = 'z';
                }
                if(str.at(j) == 'a')
                {
                    allAs.push_back(std::make_pair(N,j));
                }
                matrix.push_back(int(str.at(j) - '`'));
            }
            N += 1;
        };
        fclose(file);

        print(matrix, N, M);

        // part 1
        update(matrix, N, M, start_x, start_y, end_x, end_y);

        std::vector<int> path_lengths;
        for(auto &pair : allAs)
        {
            std::cout << pair.first << " " << pair.second << std::endl;
            path_lengths.push_back(update(matrix, N, M, pair.first, pair.second, end_x, end_y));
        }
        sort(path_lengths.begin(), path_lengths.end());
        std::cout << path_lengths.at(0) << " from " << allAs.size() << " different starts" << std::endl;
    }
    return 0;
}
