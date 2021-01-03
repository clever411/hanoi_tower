#include <cmath>
#include <vector>

#include <lis/type.hpp>





namespace lis
{





// functions
/*
 * Алгоритм Евклида по нахождению НОД;
 * расширенный алгоритм Евклида, который находит
 * также корни диофантова уравнения
 * 	a*x + b*x = gcd(a, b);
 * с помощью расширенного алгоритма Евклида
 * можно найти обратный по простому модулю элемент,
 * нужный, чтобы делить под модулем;
 * а также НОК
 */
template<typename T>
T gcd(T a, T b)
{
	while(a)
	{
		b %= a;
		std::swap(a, b);
	}
	return b;
}

template<typename T>
T exgcd(T a, T b, T &x, T &y)
{
	if(a == 0)
	{
		x = 0, y = 1;
		return b;
	}

	T xx, yy, g;
	g = exgcd(b%a, a, xx, yy);
	x = yy - xx*(b/a);
	y = xx;
	return g;
}

template<typename T>
inline T lcm(T a, T b)
{
	return a/gcd(a, b)*b;
}



/*
 * Математический модуль числа;
 * разделить число под простым модулем
 */
template<typename T>
inline T mod(T a, T b)
{
	return (b + a%b) % b;
}

template<typename T>
inline T div(T a, T b, T m)
{
	T null;
	exgcd(b, m, b, null);
	return mod(a*b, m);
}



/*
 * Решето Эратосфена, которое находит все 
 * простые числа (они помечаются нулями),
 * меньшие n; а также по количеству простых
 * чисел (вычисляется всегда чуть больше)
 */
template<typename T = llong>
void sieve(T n, std::vector<T> &sie)
{
	sie.assign(n, 0);
	sie[0] = sie[1] = 1; // вычёркиваем 0 и 1
	for(T i = 2; i*i < n; ++i)
	{
		if(sie[i])
			continue;
		for(T j = i*i; j < n; j += i)
			sie[j] = i; // записываем первый делить числа
	}
}

template<typename T = llong>
void sieve_by_count(T count, std::vector<T> &sie)
{
	sieve(
		count * ceil(log(count)) * 6 / 5 + 5,
		sie
	);
	return;
}





}





// end
