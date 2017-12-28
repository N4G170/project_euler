#include "eulerproblems.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <bitset>
#include <algorithm>
#include <array>

#include "message_writer.hpp"
#include "clock.hpp"
#include "graphs_and_grids.hpp"
#include "utils.hpp"

std::string Problem034()
{
    auto clock_id = Clock::Instance()->StartClock();

    //pre-calculate factorials for each digit
    std::array<unsigned int, 10> factorials;
    for(unsigned int i = 0; i < factorials.size(); i++)
        factorials[i] = Factorial(i);

    unsigned int limit = 362880;// 9! will be the limit
    unsigned int total_digit_factorial_sum = 0;

    for(unsigned int i = 10; i < limit; i++)//start at 10 as single digit numbers are not valid for this problem
    {
        unsigned int number = i;
        unsigned int digit_factorial_sum = 0;

        while(number > 0)
        {
            unsigned int digit = number % 10;//get last digit from number
            number /= 10;//remove last digit

            digit_factorial_sum += factorials[digit];
        }

        if(i == digit_factorial_sum)
            total_digit_factorial_sum += i;
    }

    //MessageWriter::Instance()->WriteToOutputBox("P036: "+std::to_string(double_palindrome_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P034: "+std::to_string(total_digit_factorial_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

std::string Problem035()
{
    auto clock_id = Clock::Instance()->StartClock();

    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(1000000));

    std::string prime_str = "";
    std::string prime_str_permutation = "";
    unsigned int total_circular_primes = 0;

    for(unsigned long prime : primes)
    {
        prime_str = std::to_string(prime);
        prime_str_permutation = prime_str;

        bool circular_prime = true;

        do
        {
            if(!IsPrime(std::stoul(prime_str_permutation)))
            {
                circular_prime = false;
                break;
            }

            //find next prime to check (the digits rotate like 123->231, moved 1 to the left)
            prime_str_permutation += prime_str_permutation[0];
            prime_str_permutation.erase(0,1);//remove the first element as it is the last one now
        }
        while(prime_str != prime_str_permutation);

        if(circular_prime)
        {
            total_circular_primes++;
            // std::cout<<prime<<std::endl;
        }
    }

    //MessageWriter::Instance()->WriteToOutputBox("P036: "+std::to_string(double_palindrome_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P035: "+std::to_string(total_circular_primes)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

std::string Problem036()
{
    auto clock_id = Clock::Instance()->StartClock();

    unsigned int limit = 1000000;
    unsigned int double_palindrome_sum = 0;

    for(unsigned int i = 1; i < limit; i += 2)//for a binary number to be palindrome, the base 10 number HAS to be odd so the binary ends in 1
    {
        std::bitset<32> b2 (i);

        if( IsPalindrome(i) && IsPalindrome(std::stoul( b2.to_string() )) )//the std::stoul will remove any leading zeros
        {
            double_palindrome_sum += i;
        }
    }

    //MessageWriter::Instance()->WriteToOutputBox("P036: "+std::to_string(double_palindrome_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P036: "+std::to_string(double_palindrome_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

std::string Problem038()
{
    auto clock_id = Clock::Instance()->StartClock();
    int result{0};


    MessageWriter::Instance()->WriteToOutputBox("P036: "+std::to_string(result)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return "";
}

std::string Problem040()
{
    auto clock_id = Clock::Instance()->StartClock();


    // unsigned int digits{0};
    // unsigned int number{1};
    //
    // while(true)
    // {
    //     digits += NumberOfDigits(number);
    //
    //     if(digits >= 1000000)
    //         break;
    //     number++;
    // }

    unsigned int limit = 185185;//this number was calculated using the commented code above
    std::string number_str{"."};

    for(unsigned int i = 1; i <= limit; i++)
        number_str += std::to_string( i );

    //d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000
    int result = CharToUnsignedInt( number_str[1] ) * CharToUnsignedInt( number_str[10] ) * CharToUnsignedInt( number_str[100] ) * CharToUnsignedInt( number_str[1000] ) *
                 CharToUnsignedInt( number_str[10000] ) * CharToUnsignedInt( number_str[100000] ) * CharToUnsignedInt( number_str[1000000] );

    // MessageWriter::Instance()->WriteToOutputBox("P040: "+std::to_string(result)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P040: "+std::to_string(result)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}
