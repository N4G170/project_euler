#ifndef DEFINES_H
#define DEFINES_H

//for some reason g++ does not let me use #elifdef
#if defined(__linux__) || defined(__gnu_linux__)
    #include <boost/multiprecision/gmp.hpp>
    #undef BigInt_t
    #define BigInt_t boost::multiprecision::mpz_int

    #undef BigFloat_t
    #define BigFloat_t boost::multiprecision::mpf_float
//#endif // __linux__

#elif defined(_WIN32) || defined(_WIN64)
    #include <boost/multiprecision/cpp_int.hpp>
    #undef BigInt_t
    #define BigInt_t boost::multiprecision::int1024_t

    #undef BigFloat_t
    #define BigFloat_t boost::multiprecision::cpp_dec_float
//#endif // _WIN32
#else

#error No Big Numbers Lib Available for your platform

#endif

#endif // DEFINES_H
