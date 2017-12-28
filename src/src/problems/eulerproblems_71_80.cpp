#include "eulerproblems.hpp"
#include "utils.hpp"
#include "message_writer.hpp"
#include "fraction.hpp"

#include "clock.hpp"

#include <map>
#include <unordered_map>
#include <stack>
#include <set>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "defines.hpp"//big numbers
#include <fstream>
#include <utility>
#include <cstdlib>
#include <numeric>
#include <functional>
#include <boost/multiprecision/number.hpp>
#include <thread>


std::string Problem071()
{//farey sequence - tried Calkin–Wilf tree and Stern-Brocot Tree
    auto clock_id = Clock::Instance()->StartClock();

    long n1{2}, d1{5}, n2{3}, d2{7};//values from sequence in the problem description
    long cn{0}, cd{0};

    while(true)
    {
        cn = n1 + n2;
        cd = d1 + d2;

        if(cd >= 1000000)
            break;

        n1 = cn, d1 = cd;
    }

    // MessageWriter::Instance()->WriteToOutputBox("P071: "+std::to_string(n1)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return "P071: "+std::to_string(n1)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms";
}


//this problem is mathematically correct (incrementaly tested the math function at http://www.wolframalpha.com/input/?i=sum(phi(n))+1%3Cn%3C10001 )
//Although when the limit > 100000 I get float precision error and the result deviats
std::string Problem072()
{
    auto clock_id = Clock::Instance()->StartClock();

    //Farey sequence( F(n) ) allows us to calculate all the reduced proper fractions for an interval from 1 to 'n'
    //The total number of elements in the sequence until a given 'n' can be calculated as |F(n)| = |F(n-1)| + phi(n);
    //That can be simplified to |F(n)| = 1 + sum( phi(m) ) where m=1 and goes to 'n'
    //Being phi the number of coprimes for the number 'n'.

    //phi also known as Euler's totient function can be calculated using the expression
    //
    //phi(n) = n * (1 - 1/p1) * ... * (1 - 1/pn), where p1...pn are the prime factors or n

    int inclusive_limit = 1000000;
    long long total_coprimes = 0;

    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(inclusive_limit + 1));
    // std::cout << "P: "<<primes[primes.size()-1] << "\n";
    //calculate prime factors of numbers
    for(int i = 1; i <= inclusive_limit; ++i)//|F(n)| = 1 + sum( phi(m) ) where m=1 and goes to 'inclusive_limit'
    {
        //find prime factors and calculate phi for number
        //total_coprimes += Phi(i, PrimeFactorsOfNumber(i, primes));//correct but slow as hell
        total_coprimes += Phi(i, primes);
    }
    //as the expression dictates
    total_coprimes += 1;

    //as the fractions 0/1 and 1/1 are not valid for the problem
    total_coprimes -= 2;

    // MessageWriter::Instance()->WriteToOutputBox("P072: "+std::to_string(total_coprimes)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P072: "+std::to_string(total_coprimes)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");

}
//more preformance remove multiset
std::string Problem073()
{
    auto clock_id = Clock::Instance()->StartClock();
    int total{0};

    //for this problem we calculate the Forey sequence of order 'n'
    double order = 12000;

    //std::function<bool(Fraction, Fraction)> lambda_compare = [](const Fraction& left, const Fraction& right){ return left.numerator/left.denominator < right.numerator/right.denominator; };
    //std::multiset< Fraction, Fraction > fractions;
    std::vector<Fraction<double>> fr;
    // The first two fractions are  0/1 and 1/n
    Fraction<double> previous{0, 1};
    Fraction<double> current{1, order};
    Fraction<double> next{0, 0};

    while (next.Denominator() != 1.0)
    {
        // Using recurrence relation to find the next term
        next.Numerator( floor((previous.Denominator() + order) / current.Denominator()) * current.Numerator() - previous.Numerator() );
        next.Denominator( floor((previous.Denominator() + order) / current.Denominator()) * current.Denominator() - previous.Denominator() );

        //store fraction in orderer set
        //fractions.insert(next);
        fr.push_back(next);
        // update var for next loop
        previous = current;
        current = next;
    }

    auto search_result = std::find_if(fr.begin(), fr.end(),
                            [](const Fraction<double>& stored_fraction)
                            {
                                //std::cout <<stored_fraction.ToString()<< " E:"<< stored_fraction.Equals(3, 7) << "\n";
                                return stored_fraction.Equals(1, 3);
                            });
    search_result++;//we jump to next result as we need to exclude 1/3

    while(true)
    {
        if(search_result->Equals(1, 2))
            break;
        total++;
        search_result++;
    }

    // MessageWriter::Instance()->WriteToOutputBox("P073: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return "P073: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms";
}

std::string Problem074()
{
    auto clock_id = Clock::Instance()->StartClock();

    std::array<int, 10> factorial_results{{0,0,0,0,0,0,0,0,0,0}};

    for(unsigned int i{0}; i < factorial_results.size(); i++)
        factorial_results[i] = Factorial(i);

    const int limit{ 1000000 };
    std::vector<int> chain;
    //std::vector<unsigned short> digits;
    int total{0};

    auto FindNumber = [&chain](const int& number)->bool
    {
        for(int element : chain)
            if(element == number)
                return true;
        return false;
    };

    auto FactorialDigitSum = [&factorial_results](int number)->int
    {
        int sum = 0;
        while (number != 0)
        {
            sum += factorial_results[number % 10];
            number /= 10;
        }
        return sum;
    };

    //std::unordered_map<int, int>length_cache;//6 seconds
    int length_cache[limit]{0};//3 seconds

    for(int i = 1; i < limit; ++i)
    {
        int element = i;
        chain.clear();
        chain.push_back(i);

        int chain_length = 0;

        while(true)//we run the cycle until we find a loop
        {
            std::cout<<element<<" - "<<limit<<std::endl;
            if(element < limit && length_cache[element] > 0)//chain for current element was found in the past
            {
                chain_length += length_cache[element];
                break;
                //element = cache[element];
            }
            else//calculate new element
            {
                //int key = element;
                element = FactorialDigitSum(element);
            }

            if(FindNumber(element))//we found a loop and we do not add the copy
            {
                for(unsigned int n{0}; n < chain.size(); ++n)
                {
                    length_cache[chain[n]] = chain.size() - n;
                    if(chain[n] == element)//found first element copy
                        break;
                }
                //cache[i] = chain_length;
                break;
            }

            ++chain_length;
            chain.push_back(element);
        }

        if(chain_length == 60)
            ++total;
    }

    // MessageWriter::Instance()->WriteToOutputBox("P074: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id, TimeScale::SECONDS) + " s");
    return "P074: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id, TimeScale::SECONDS) + " s";
}

std::string Problem080()
{
    auto clock_id = Clock::Instance()->StartClock();
    int limit{100};
    long sum{ 0 };

    std::vector<BigFloat_t> numbers_with_irrational_root;
    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector( SieveOfEratosthenes( limit ) );
    //se ignorar os ^2 tb dá
    for(int i = 2; i < limit; i++)
    {
        //first is the factor; second is the exponent
        auto prime_factors = PrimeFactorsOfNumber(i, primes);

        for( auto factor : prime_factors)
        {
            if(factor.second % 2 != 0)//odd
            {
                numbers_with_irrational_root.push_back( BigFloat_t(i) );
                break;
            }
        }
    }

    BigFloat_t root;
    root.precision(101);

    for(BigFloat_t f : numbers_with_irrational_root)
    {
        root = boost::multiprecision::sqrt(f);

        std::string str{root.str()};
        str = str.erase( str.find_first_of('.'), 1 );//remove '.'

        for(unsigned int i = 0; i < 100; i++)
            sum += (str[i] - '0');
    }

    // MessageWriter::Instance()->WriteToOutputBox("P080: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return "P080: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms";
}
