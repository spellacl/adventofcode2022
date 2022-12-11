#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>

typedef struct Monkey
{
    Monkey(long long i, std::vector<long long> v, long long op, long long test, long long mtrue, long long mfalse, char op_c) :
                                                                id{i},
                                                                items{v},
                                                                op_factor{op},
                                                                test_factor{test},
                                                                monkey_true{mtrue},
                                                                monkey_false{mfalse},
                                                                op{op_c} {}
    std::vector<long long> items;
    long long id;
    long long op_factor;
    long long test_factor;
    long long monkey_true;
    long long monkey_false;
    char op;
} Monkey;

int main(int argc, char * argv[])
{
    bool part2 = false;
    long long rounds = atoi(argv[1]);
    if(argc == 3)
    {
        part2 = true;
    }

    std::vector<Monkey> monkeys;
/*
    monkeys.emplace_back(Monkey(0,std::vector<long long>({79, 98}), 19, 23, 2, 3, '*'));
    monkeys.emplace_back(Monkey(1,std::vector<long long>({54, 65, 75, 74}), 6, 19, 2, 0, '+'));
    monkeys.emplace_back(Monkey(2,std::vector<long long>({79, 60, 97}), -1, 13, 1, 3, '*'));
    monkeys.emplace_back(Monkey(3,std::vector<long long>({74}), 3, 17, 0, 1, '+'));
    std::vector<long long> inspected_count(4);
*/


    monkeys.emplace_back(Monkey(0,std::vector<long long>({98,89,52}), 2, 5, 6, 1, '*'));
    monkeys.emplace_back(Monkey(1,std::vector<long long>({57,95,80,92,57,78}), 13, 2, 2, 6, '*'));
    monkeys.emplace_back(Monkey(2,std::vector<long long>({82, 74, 97, 75, 51, 92, 83}), 5, 19, 7, 5, '+'));
    monkeys.emplace_back(Monkey(3,std::vector<long long>({97, 88, 51, 68, 76}), 6, 7, 0, 4, '+'));
    monkeys.emplace_back(Monkey(4,std::vector<long long>({63}), 1, 17, 0, 1, '+'));
    monkeys.emplace_back(Monkey(5,std::vector<long long>({94, 91, 51, 63}), 4, 13, 4, 3, '+'));
    monkeys.emplace_back(Monkey(6,std::vector<long long>({61, 54, 94, 71, 74, 68, 98, 83}), 2, 3, 2, 7, '+'));
    monkeys.emplace_back(Monkey(7,std::vector<long long>({90,56}), -1, 11, 3, 5, '*'));
    std::vector<long long> inspected_count(8);

// I did not figure this out on my own and checked the subreddit for hints
    long long floor_factor = 1;
    if(part2)
    {
        for(auto &m: monkeys)
        {
            floor_factor *= m.test_factor;
        }
    }

    for(long long round = 0; round < rounds; round ++)
    {
        for(auto &m : monkeys)
        {
            // inspect
            for(auto & item : m.items)
            {
                inspected_count.at(m.id) += 1;
                long long worry = item;
                long long factor = m.op_factor;
                if(m.op_factor == -1) factor = worry;
                if(m.op == '*')
                    worry *= factor;
                else if(m.op == '+')
                    worry += factor;

                // divide by three
                if(!part2)
                {
                    worry = std::floor(worry/3);
                }
                else{
                    worry = worry % floor_factor;
                }

                // test
                if((worry % m.test_factor) == 0)
                {
                    monkeys.at(m.monkey_true).items.push_back(worry);
                }
                else
                {
                    monkeys.at(m.monkey_false).items.push_back(worry);
                }
            }
            m.items.clear();
        }
    
/*       for(auto &m : monkeys)
       {
            std::cout << "Monkey " << m.id << ": ";
            for(auto &i : m.items)
            {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;*/
        std::cout << "round " << round << ": ";
        for(auto &num : inspected_count)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    std::sort(inspected_count.begin(), inspected_count.end(), std::greater<long long>());
    std::cout << "Monkey business " << inspected_count.at(0) * inspected_count.at(1) << std::endl;
    return 0;
}

