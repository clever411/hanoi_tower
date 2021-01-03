#ifndef LIS_TYPE_HPP
#define LIS_TYPE_HPP

#include <limits>



typedef int8_t byte;
typedef uint8_t ubyte;
typedef int64_t llong;
typedef uint64_t ullong;
typedef long double ldouble;


constexpr int  const int_inf  = std::numeric_limits<int>::max() / 2;
constexpr int  const int_max  = std::numeric_limits<int>::max();
constexpr int  const int_min  = std::numeric_limits<int>::min();
constexpr long const long_inf = std::numeric_limits<long>::max() / 2;
constexpr long const long_max = std::numeric_limits<long>::max();
constexpr long const long_min = std::numeric_limits<long>::min();

constexpr llong  const llong_inf  = std::numeric_limits<llong>::max() / 2;
constexpr llong  const llong_max  = std::numeric_limits<llong>::max();
constexpr llong  const llong_min  = std::numeric_limits<llong>::min();
constexpr ullong const ullong_inf = std::numeric_limits<ullong>::max() / 2;
constexpr ullong const ullong_max = std::numeric_limits<ullong>::max();
constexpr ullong const ullong_min = std::numeric_limits<ullong>::min();

constexpr float   const float_inf    = std::numeric_limits<float>::infinity();
constexpr float   const float_nan    = std::numeric_limits<float>::quiet_NaN();
constexpr float   const float_snan   = std::numeric_limits<float>::signaling_NaN();

constexpr double  const double_inf   = std::numeric_limits<double>::infinity();
constexpr double  const double_nan   = std::numeric_limits<double>::quiet_NaN();
constexpr double  const double_snan  = std::numeric_limits<double>::signaling_NaN();

constexpr ldouble const ldouble_inf  = std::numeric_limits<ldouble>::infinity();
constexpr ldouble const ldouble_nan  = std::numeric_limits<ldouble>::quiet_NaN();
constexpr ldouble const ldouble_snan = std::numeric_limits<ldouble>::signaling_NaN();





#endif

