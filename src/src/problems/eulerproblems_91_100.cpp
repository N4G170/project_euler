#include "eulerproblems.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <bitset>
#include <cmath>
#include <boost/multiprecision/number.hpp>
#include <algorithm>

#include "message_writer.hpp"
#include "clock.hpp"
#include "graphs_and_grids.hpp"
#include "utils.hpp"
#include "defines.hpp"
#include "enums.hpp"


std::string Problem092()
{
    auto clock_id = Clock::Instance()->StartClock();

    int limit{10000000};
    int target_element{89};
    int break_element{1};
    int total{0};
    //first = source number; second = target number
    // std::unordered_map<int,int> elements_cache;//for some reason the use of this cache makes the algorithm run +- 4x slower
    std::vector<int> powers(10);

    //prepare powers
    for(unsigned int i{0}; i < powers.size(); i++)
        powers[i] = i * i;

    for(int i = 1; i < limit; i++)
    {
        int number{i};

        while(number != break_element && number != target_element)
        {
            int element{0};

            // if(elements_cache[number] > 0)//element already calculated
            // {
            //     number = elements_cache[number];
            // }
            // else
            // {
                //break number into digits
                while(number > 0)
                {
                    element += powers[number % 10];
                    number /= 10;
                }
                number = element;
            // }
        }//while

        if(number == target_element)//found target loop
            total++;
    }

    // MessageWriter::Instance()->WriteToOutputBox("P092: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return "P092: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms";
}


std::string Problem094()
{
    auto clock_id = Clock::Instance()->StartClock();

    long perimeter_sum = 0;
    long perimeter_limit = 1000000000;

    long side{0};
    long perimeter_1{0};
    long perimeter_2{0};

    auto HasIntegralArea = [](const long& a, const long& b)->bool
    {
        //if(b % 2 != 0)
        //    return false;

        long h_squared{ (a * a - b * b / 4) };
        long root_of_h{ static_cast<long>(std::sqrt(h_squared)) };

        if(root_of_h * root_of_h == h_squared && h_squared > 1)
        {
            // std::cout<<"("<<a<<","<<a<<","<<b<<") - "<< root_of_h<<" ^2 - "<<(root_of_h * root_of_h) <<" | "<< h_squared <<"\n";
            return true;
        }
        return false;
    };

    for(side = 1; perimeter_1 < perimeter_limit || perimeter_2 < perimeter_limit; side += 2 )//b has to be even
    {
        perimeter_1 = side * 3 + 1;
        perimeter_2 = side * 3 - 1;

        if(perimeter_1 < perimeter_limit )//side + 1
        {
            //Heron of Alexandria area formula a=SQRT(s(s-a)(s-b)(s-c)) where s = perimeter/2
            // s = (perimeter_1/BigFloat_t(2));
            // a = s * (s-side) * (s-side) * (s-base_1);
            // area = boost::multiprecision::sqrt( a );

            if(HasIntegralArea(side, side + 1))
                perimeter_sum += perimeter_1;
        }
        if(perimeter_2 < perimeter_limit )//side - 1
        {
            //Heron of Alexandria area formula a=SQRT(s(s-a)(s-b)(s-c)) where s = perimeter/2
            // s = (perimeter_2/BigFloat_t(2));
            // a = s * (s-side)*(s-side)*(s-base_2);
            // area = boost::multiprecision::sqrt( a );

            if(HasIntegralArea(side, side - 1))
                perimeter_sum += perimeter_2;
        }
    }

    // MessageWriter::Instance()->WriteToOutputBox("P094: "+std::to_string(perimeter_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id, TimeScale::SECONDS) + " s");
    return "P094: "+std::to_string(perimeter_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id, TimeScale::SECONDS) + " s";
}