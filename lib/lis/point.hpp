#ifndef LIS_POINT_HPP
#define LIS_POINT_HPP

#include <cmath>
#include <type_traits>
#include <utility>

#include <lis/iostream.hpp>
#include <lis/meta.hpp>







namespace lis
{







template<typename T>
struct Point
{
	// types
	typedef T value_type;
	




	// data-members
	value_type x, y;
	
	
	
	
	
	// methods
	template<class P>
	Point &operator=(P const &p)
	{
		x = p.x;
		y = p.y;
		return *this;
	}
	
	
	// conversion
	template<class P>
	inline operator P() const
	{
		P p;
		p.x = x;
		p.y = y;
		return p;
	}

	template<typename U>
	inline operator std::pair<U, U>() const
	{
		return std::pair<U, U>(x, y);
	}

	template<class P>
	inline P to() const
	{
		P p;
		p.x = x;
		p.y = y;
		return p;
	}

	template<typename U = value_type>
	inline std::pair<U, U> topair() const
	{
		return std::pair<U, U>{ x, y };
	}



	// geometry
	inline double len() const
	{
		return std::hypot(x, y);
	}

	inline double hypot() const
	{
		return std::hypot(x, y);
	}

	template<typename P>
	inline double dis(P const &p) const
	{
		return std::hypot(p.x-x, p.y-y);
	}

	inline Point norm() const
	{
		double const l = len();
		return { x/l, y/l };
	}



	// print
	template<class Ostream>
	Ostream &print( Ostream &os ) const
	{
		os << "(";
		lis::print(os, x) << ", ";
		lis::print(os, y) << ")";
		return os;
	}



};






// requaire operations
template<typename T, typename U>
inline bool operator==(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}


template<typename T, typename U>
inline bool operator!=(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return lhs.x != rhs.x || lhs.y != rhs.y;
}


template<typename T, typename U>
inline bool operator<(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return lhs.y != rhs.y ? lhs.y < rhs.y : lhs.x < rhs.x;
}


template<typename T, typename U>
inline bool operator>(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return lhs.y != rhs.y ? lhs.y > rhs.y : lhs.x > rhs.x;
}


template<typename T, typename U>
inline bool operator<=(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return !(lhs > rhs);
}

template<typename T, typename U>
inline bool operator>=(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return !(lhs < rhs);
}





// calculate operators
	// Point and Number
template<typename T, typename U>
inline Point<decltype(T()+U())> operator+(
	Point<T> const &lhs,
	U rhs
)
{
	return {lhs.x+rhs, lhs.y+rhs};
}


template<typename T, typename U>
inline Point<decltype(T()-U())> operator-(
	Point<T> const &lhs,
	U rhs
)
{
	return {lhs.x-rhs, lhs.y-rhs};
}


template<typename T, typename U>
inline Point<decltype(T()*U())> operator*(
	Point<T> const &lhs,
	U rhs
)
{
	return {lhs.x*rhs, lhs.y*rhs};
}


template<typename T, typename U>
inline Point<decltype(T()/U())> operator/(
	Point<T> const &lhs,
	U rhs
)
{
	return { lhs.x/rhs, lhs.y/rhs };
}





	// Point and Point
template<typename T, typename U>
inline Point<decltype(T()+U())> operator+(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x+rhs.x, lhs.y+rhs.y};
}


template<typename T, typename U>
inline Point<decltype(T()-U())> operator-(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x-rhs.x, lhs.y-rhs.y};
}


template<typename T, typename U>
inline Point<decltype(T()*U())> operator*(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x*rhs.x, lhs.y*rhs.y};
}


template<typename T, typename U>
inline Point<decltype(T()/U())> operator/(
	Point<T> const &lhs,
	Point<U> const &rhs
)
{
	return {lhs.x/rhs.x, lhs.y/rhs.y};
}





	// mod Point and Number
template<typename T, typename U>
inline Point<T> &operator+=(
	Point<T> &lhs,
	U rhs
)
{
	lhs.x += rhs;
	lhs.y += rhs;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator-=(
	Point<T> &lhs,
	U rhs
)
{
	lhs.x -= rhs;
	lhs.y -= rhs;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator*=(
	Point<T> &lhs,
	U rhs
)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator/=(
	Point<T> &lhs,
	U rhs
)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}





	// mod Point and Point
template<typename T, typename U>
inline Point<T> &operator+=(
	Point<T> &lhs,
	Point<U> const &rhs
)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator-=(
	Point<T> &lhs,
	Point<U> const &rhs
)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator*=(
	Point<T> &lhs,
	Point<U> const &rhs
)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	return lhs;
}


template<typename T, typename U>
inline Point<T> &operator/=(
	Point<T> &lhs,
	Point<U> const &rhs
)
{
	lhs.x /= rhs.x;
	lhs.y /= rhs.y;
	return lhs;
}







// print
template<class Ostream, typename T>
inline Ostream &operator<<(
	Ostream &os,
	Point<T> const &toprint 
)
{
	 return toprint.print(os);
}







// make 
template<typename T = void, class C>
inline auto makep(C const &from)
{
	Point< typename IF<
		std::is_same<T, void>::value,
		decltype(C::x), T
	>::type > p;

	p.x = from.x;
	p.y = from.y;

	return p;
}

template<typename T = void, typename U>
inline auto makep(U x, U y)
{
	Point< typename IF<
		std::is_same<T, void>::value,
		U, T
	>::type > p;

	p.x = x;
	p.y = y;

	return p;
}

template<typename T = void, typename U>
inline auto makep(std::pair<U, U> const &pair)
{
	Point< typename IF<
		std::is_same<T, void>::value,
		U, T
	>::type > p;

	p.x = pair.first;
	p.y = pair.second;

	return p;
}







// typedefs
typedef Point<char> PointC;
typedef Point<int> PointI;
typedef Point<unsigned> PointU;
typedef Point<float> PointF;
typedef Point<double> PointD;







}







#endif
