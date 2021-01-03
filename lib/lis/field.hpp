#ifndef LIS_FIELD_HPP
#define LIS_FIELD_HPP

#include <cstring>
#include <iterator>
#include <type_traits>
#include <utility>

#include <lis/iostream.hpp>
#include <lis/meta.hpp>
#include <lis/math.hpp>
#include <lis/point.hpp>





namespace lis
{
	
	
	
	
	
template<typename ValueType>
struct Field
{
	// types
	typedef ValueType value_type;



		// iterator-class
private:
	struct Simple {};
	struct Const {};
	struct TapeAt {};

	template<class IsConst, class TapeMode>
	class Iterator: public std::iterator<
		std::bidirectional_iterator_tag,
		typename IF<
			std::is_same<IsConst, Const>::value,
			Field::value_type const,
			Field::value_type
		>::type
	>
	{
	public:
		// types
		typedef typename Iterator::value_type value_type;

		typedef typename IF<
			std::is_same<IsConst, Const>::value,
			Field const, Field
		>::type field_type;





		// copy
		template<class C, class TM>
		Iterator( Iterator<C, TM> const &tocp );

		template<class C, class TM>
		Iterator &operator=(Iterator<C, TM> const &rhs);



		// move
		Iterator &operator++();
		inline Iterator operator++(int);

		Iterator &operator--();
		inline Iterator operator--(int);

		Iterator &incy();
		Iterator &incy(int n);

		Iterator &reducey();
		Iterator &reducey(int n);




		// at
		inline value_type &operator*() const;
		inline value_type *operator->() const;
		
		inline value_type *base() const;
		inline PointI point() const;



		// get info
		template<class C, class TM>
		bool operator==(Iterator<C, TM> const &rhs) const;

		template<class C, class TM>
		inline bool operator!=(Iterator<C, TM> const &rhs) const;

		inline bool isedge() const;
		inline bool isend() const;

		// создаёт новый итератор, который можно потом изменять:
		// отправить, например, в функцию make_reverse_iterator;
		// из этого итератора может выйти. Но создаётся новый! В
		// цикле вызывать эту функцию для проверки дошёл ли до 
		// конца итератор - нельзя, используй для этого либо isend,
		// либо iterendc
		Iterator iterend() const;
		static inline Iterator const &citerend();
		


	private:
		friend class Field;

		static Iterator create_iterend();



		// methods
		Iterator();
		Iterator(
			field_type &field,
			int left = 0, int top = 0,
			int width = -1, int height = -1
		);

		inline void plusplus(Simple);
		inline void plusplus(TapeAt);

		inline void minusminus(Simple);
		inline void minusminus(TapeAt);



		// data-members
		int top, left, width, height, fw, fh;
		int x, y;
		value_type *d, *fd;




	};



public:
		// other
	typedef Iterator<Simple, Simple> iterator_type;
	typedef Iterator<Const, Simple> const_iterator_type;
	typedef Iterator<Simple, TapeAt> iterator_tape_type;
	typedef Iterator<Const, TapeAt> const_iterator_tape_type; 
	
	
	
	
	
	// static const members
	static constexpr int const OFFSET_COUNT = 8;
	static constexpr int const OFFSET[OFFSET_COUNT][2] = {
		{ -1, -1 }, { 0, -1 }, { 1, -1 }, //  Directions:
		                       { 1, 0  }, //  0  1  2
		                       { 1, 1  }, //  7  *  3
		            { 0, 1  },            //  6  5  4
		{ -1, 1  },                       // 
		{ -1, 0  },                       // 
	};
	




	// data-members
	int w = 0, h = 0;
	value_type *d = nullptr;
	
	
	
	
	
	// init, free
	inline Field &init();
	inline Field &init(int width, int height);
	inline Field &free();



	// clear & zeroize
	inline Field &clear();
	inline Field &clear(value_type const &value);

	inline Field &clearline(int line);
	inline Field &clearline(
		value_type const &value, int line
	);

	inline Field &clearlines(
		int bline, int nline
	);
	inline Field &clearlines(
		value_type const &value,
		int bline, int nline
	);

	inline Field &zeroize();
	inline Field &zeroize(int line);
	inline Field &zeroize(int bline, int nline);





	// check vlaid
		// simple
	inline bool isValid(int x, int y) const;

	template<class Point>
	inline bool isValid(Point const &p) const;



		// for near
	inline bool isValid(int x, int y, int dir) const;

	template<class Point>
	inline bool isValid(Point const &p, int dir) const;





	// correct
	inline void correct(int &x, int &y) const;

	template<class Point>
	inline void correct(Point &p) const;





	// get 
	inline void getxy(int i, int &x, int &y) const;
	inline PointI getxy(int i) const;

	inline void getxy(value_type const *p, int &x, int &y) const;
	inline PointI getxy(value_type const *p) const;

	inline int geti(int x, int y) const;

	template<class Point>
	inline int geti(Point const &p) const;



	// geometry
	inline PointF origin(int x, int y, float a) const;
	inline PointF origin(PointI const &p, float a) const;
	inline PointF origin(value_type const *p, float a) const;





	// at
		// simple
	inline value_type &at(int x, int y);
	inline value_type const &at(int x, int y) const;


		// for point
	template<class Point>
	inline value_type const &at(
		Point const &p
	) const;

	template<class Point>
	inline value_type &at(
		Point const &p
	);



		// tape at simple
	inline value_type &att(int x, int y);
	inline value_type const &att(int x, int y) const;


		// tape at for point
	template<class Point>
	inline value_type const &att(
		Point const &p
	) const;

	template<class Point>
	inline value_type &att(
		Point const &p
	);



		// near at simple
	inline value_type &near(int x, int y, int dir);
	inline value_type const &near(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &near(Point const &p, int dir);

	template<class Point>
	inline value_type const &near(
		Point const &p, int dir
	) const;

		

		// near tape at simple
	inline value_type &neart(int x, int y, int dir);
	inline value_type const &neart(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &neart(Point const &p, int dir);

	template<class Point>
	inline value_type const &neart(
		Point const &p, int dir
	) const;



		// operator at
	inline value_type const *operator[](char y) const;
	inline value_type *operator[](char y);

	inline value_type const *operator[](int y) const;
	inline value_type *operator[](int y);

	inline value_type const *operator[](long y) const;
	inline value_type *operator[](long y);

	inline value_type const *operator[](long long y) const;
	inline value_type *operator[](long long y);

	template<class Point>
	inline value_type const &operator[](Point const &p) const;

	template<class Point>
	inline value_type &operator[](Point const &p);





	// iterators
		// simple
	inline value_type *begin();
	inline value_type *end();

	inline value_type const *begin() const;
	inline value_type const *end() const;



		// for line
	inline value_type *begin(int line);
	inline value_type *end(int line);
	
	inline value_type const *begin(int line) const;
	inline value_type const *end(int line) const;



		// class-iterator 
			// simple
	inline iterator_type iterator(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	);
	inline iterator_type const &iterend() const;

			// simple const
	inline const_iterator_type citerator(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	) const;
	inline const_iterator_type const &citerend() const;


			// tape
	inline iterator_tape_type iteratort(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	);
	inline iterator_tape_type const &iterendt() const;

			// tape const
	inline const_iterator_tape_type citeratort(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	) const;
	inline const_iterator_tape_type const &citerendt() const;





	template<class Ostream>
	Ostream &print(
		Ostream &os,
		std::string const &elterm = "\t",
		std::string const &lnterm = "\n"
	) const;





};	





#include "_field_implement.hpp"





}





template<class Ostream, typename ValueType>
Ostream &operator<<(Ostream &os, lis::Field<ValueType> const &toprint)
{
	toprint.print(os);
	return os;
}





#endif
