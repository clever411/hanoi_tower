#ifndef LIS_METATYPE_HPP
#define LIS_METATYPE_HPP

#include <lis/type.hpp>





namespace lis
{





// ------------- МЕТОПРОГРАММИРОВАНИЕ ---------------
template<typename T> struct Type
{
	typedef T value;
};



template<bool Cond, typename T, typename U>
struct IF
{
	typedef T type;
};

template<typename T, typename U>
struct IF<false, T, U>
{
	typedef U type;
};





// ----------------- КАСКАДЫ ------------------------
/*
 * bcascade находит f(a, f(b, f(c, ...)))
 * ucascade вызывает f(a), f(b), f(c)...
 * dcascade находит f(f2(a), f(f2(b), f(f2(c), ...)))
 */
template<typename F, typename T, typename U>
inline auto bcascade(F f, T t, U u)
{
	return f(t, u);
}

template<typename F, typename T, typename...Args>
inline auto bcascade(F f, T t, Args...args)
{
	return f(t, bcascade(f, args...));
}


template<typename F, typename T>
inline void ucascade(F f, T t)
{
	f(t);
	return;
}

template<typename F, typename T, typename...Args>
inline void ucascade(F f, T t, Args...args)
{
	f(t);
	ucascade(f, args...);
	return;
}


template<typename F, typename F2, typename T, typename U>
inline T dcascade(F f, F2 f2, T t, U u)
{
	return f(f2(t), f2(u));
}

template<typename F, typename F2, typename T, typename...Args>
inline T dcascade(F f, F2 f2, T t, Args...args)
{
	return f( f2(t), f2(dcascade(f, f2, args...)) );
}





// -------------------- СТРОКИ ------------------------
template<char...Chars>
struct String
{
	static constexpr char value[] = { Chars..., '\0' };
};

template< typename S, char ch >
struct PushChar;

template< char ch, char...Chars >
struct PushChar< lis::String<Chars...>, ch >
{
	typedef lis::String<Chars..., ch> string;
};

template<int N>
constexpr char CharAt(char const (&s)[N], int i)
{
	return s[i];
}



#define LIS_STR1(str) \
	typename lis::PushChar< lis::String<>, lis::CharAt(str, 0) >::string

#define LIS_STR2(str) \
	typename lis::PushChar< LIS_STR1(str), lis::CharAt(str, 1) >::string

#define LIS_STR3(str) \
	typename lis::PushChar< LIS_STR2(str), lis::CharAt(str, 2) >::string

#define LIS_STR4(str) \
	typename lis::PushChar< LIS_STR3(str), lis::CharAt(str, 3) >::string

#define LIS_STR5(str) \
	typename lis::PushChar< LIS_STR4(str), lis::CharAt(str, 4) >::string

#define LIS_STR6(str) \
	typename lis::PushChar< LIS_STR5(str), lis::CharAt(str, 5) >::string

#define LIS_STR7(str) \
	typename lis::PushChar< LIS_STR6(str), lis::CharAt(str, 6) >::string

#define LIS_STR8(str) \
	typename lis::PushChar< LIS_STR7(str), lis::CharAt(str, 7) >::string

#define LIS_STR9(str) \
	typename lis::PushChar< LIS_STR8(str), lis::CharAt(str, 8) >::string

#define LIS_STR10(str) \
	typename lis::PushChar< LIS_STR9(str), lis::CharAt(str, 9) >::string

#define LIS_STR11(str) \
	typename lis::PushChar< LIS_STR10(str), lis::CharAt(str, 10) >::string

#define LIS_STR12(str) \
	typename lis::PushChar< LIS_STR11(str), lis::CharAt(str, 11) >::string

#define LIS_STR13(str) \
	typename lis::PushChar< LIS_STR12(str), lis::CharAt(str, 12) >::string

#define LIS_STR14(str) \
	typename lis::PushChar< LIS_STR13(str), lis::CharAt(str, 13) >::string

#define LIS_STR15(str) \
	typename lis::PushChar< LIS_STR14(str), lis::CharAt(str, 14) >::string

#define LIS_STR16(str) \
	typename lis::PushChar< LIS_STR15(str), lis::CharAt(str, 15) >::string

#define LIS_STR17(str) \
	typename lis::PushChar< LIS_STR16(str), lis::CharAt(str, 16) >::string

#define LIS_STR18(str) \
	typename lis::PushChar< LIS_STR17(str), lis::CharAt(str, 17) >::string

#define LIS_STR19(str) \
	typename lis::PushChar< LIS_STR18(str), lis::CharAt(str, 18) >::string

#define LIS_STR20(str) \
	typename lis::PushChar< LIS_STR19(str), lis::CharAt(str, 19) >::string

#define LIS_STR21(str) \
	typename lis::PushChar< LIS_STR20(str), lis::CharAt(str, 20) >::string

#define LIS_STR22(str) \
	typename lis::PushChar< LIS_STR21(str), lis::CharAt(str, 21) >::string

#define LIS_STR23(str) \
	typename lis::PushChar< LIS_STR22(str), lis::CharAt(str, 22) >::string

#define LIS_STR24(str) \
	typename lis::PushChar< LIS_STR23(str), lis::CharAt(str, 23) >::string

#define LIS_STR25(str) \
	typename lis::PushChar< LIS_STR24(str), lis::CharAt(str, 24) >::string

#define LIS_STR26(str) \
	typename lis::PushChar< LIS_STR25(str), lis::CharAt(str, 25) >::string

#define LIS_STR27(str) \
	typename lis::PushChar< LIS_STR26(str), lis::CharAt(str, 26) >::string

#define LIS_STR28(str) \
	typename lis::PushChar< LIS_STR27(str), lis::CharAt(str, 27) >::string

#define LIS_STR29(str) \
	typename lis::PushChar< LIS_STR28(str), lis::CharAt(str, 28) >::string

#define LIS_STR30(str) \
	typename lis::PushChar< LIS_STR29(str), lis::CharAt(str, 29) >::string

#define LIS_STR31(str) \
	typename lis::PushChar< LIS_STR30(str), lis::CharAt(str, 30) >::string

#define LIS_STR32(str) \
	typename lis::PushChar< LIS_STR31(str), lis::CharAt(str, 31) >::string

#define LIS_STR33(str) \
	typename lis::PushChar< LIS_STR32(str), lis::CharAt(str, 32) >::string

#define LIS_STR34(str) \
	typename lis::PushChar< LIS_STR33(str), lis::CharAt(str, 33) >::string

#define LIS_STR35(str) \
	typename lis::PushChar< LIS_STR34(str), lis::CharAt(str, 34) >::string

#define LIS_STR36(str) \
	typename lis::PushChar< LIS_STR35(str), lis::CharAt(str, 35) >::string

#define LIS_STR37(str) \
	typename lis::PushChar< LIS_STR36(str), lis::CharAt(str, 36) >::string

#define LIS_STR38(str) \
	typename lis::PushChar< LIS_STR37(str), lis::CharAt(str, 37) >::string

#define LIS_STR39(str) \
	typename lis::PushChar< LIS_STR38(str), lis::CharAt(str, 38) >::string

#define LIS_STR40(str) \
	typename lis::PushChar< LIS_STR39(str), lis::CharAt(str, 39) >::string

#define LIS_STR41(str) \
	typename lis::PushChar< LIS_STR40(str), lis::CharAt(str, 40) >::string

#define LIS_STR42(str) \
	typename lis::PushChar< LIS_STR41(str), lis::CharAt(str, 41) >::string

#define LIS_STR43(str) \
	typename lis::PushChar< LIS_STR42(str), lis::CharAt(str, 42) >::string

#define LIS_STR44(str) \
	typename lis::PushChar< LIS_STR43(str), lis::CharAt(str, 43) >::string

#define LIS_STR45(str) \
	typename lis::PushChar< LIS_STR44(str), lis::CharAt(str, 44) >::string

#define LIS_STR46(str) \
	typename lis::PushChar< LIS_STR45(str), lis::CharAt(str, 45) >::string

#define LIS_STR47(str) \
	typename lis::PushChar< LIS_STR46(str), lis::CharAt(str, 46) >::string

#define LIS_STR48(str) \
	typename lis::PushChar< LIS_STR47(str), lis::CharAt(str, 47) >::string

#define LIS_STR49(str) \
	typename lis::PushChar< LIS_STR48(str), lis::CharAt(str, 48) >::string

#define LIS_STR50(str) \
	typename lis::PushChar< LIS_STR49(str), lis::CharAt(str, 49) >::string

#define LIS_STR51(str) \
	typename lis::PushChar< LIS_STR50(str), lis::CharAt(str, 50) >::string

#define LIS_STR52(str) \
	typename lis::PushChar< LIS_STR51(str), lis::CharAt(str, 51) >::string

#define LIS_STR53(str) \
	typename lis::PushChar< LIS_STR52(str), lis::CharAt(str, 52) >::string

#define LIS_STR54(str) \
	typename lis::PushChar< LIS_STR53(str), lis::CharAt(str, 53) >::string

#define LIS_STR55(str) \
	typename lis::PushChar< LIS_STR54(str), lis::CharAt(str, 54) >::string

#define LIS_STR56(str) \
	typename lis::PushChar< LIS_STR55(str), lis::CharAt(str, 55) >::string

#define LIS_STR57(str) \
	typename lis::PushChar< LIS_STR56(str), lis::CharAt(str, 56) >::string

#define LIS_STR58(str) \
	typename lis::PushChar< LIS_STR57(str), lis::CharAt(str, 57) >::string

#define LIS_STR59(str) \
	typename lis::PushChar< LIS_STR58(str), lis::CharAt(str, 58) >::string

#define LIS_STR60(str) \
	typename lis::PushChar< LIS_STR59(str), lis::CharAt(str, 59) >::string

#define LIS_STR61(str) \
	typename lis::PushChar< LIS_STR60(str), lis::CharAt(str, 60) >::string

#define LIS_STR62(str) \
	typename lis::PushChar< LIS_STR61(str), lis::CharAt(str, 61) >::string

#define LIS_STR63(str) \
	typename lis::PushChar< LIS_STR62(str), lis::CharAt(str, 62) >::string

#define LIS_STR64(str) \
	typename lis::PushChar< LIS_STR63(str), lis::CharAt(str, 63) >::string





}





#endif
