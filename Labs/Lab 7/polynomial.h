#pragma once

#include <iostream>
#include <math.h>


template <typename T, int N>
class Polynomial;


template< typename T, int N >
std::ostream& operator<<(std::ostream& out, Polynomial<T, N> const& pol);



template <typename T, int N>
class Polynomial {
public:
	// friend template operator<<
  friend std::ostream& operator<< <>(std::ostream& out, Polynomial<T, N> const& pol);

  // default ctor
	Polynomial()
	{
		for (int i = 0; i < N + 1; i++)
			coeff[i] = 0;
	}


	// index operator
	T& operator[](int i)
	{
		return coeff[i];
	}

	// const index operator
  T operator[](int i) const
  {
    return coeff[i];
  }


  // conversion ctor
  template <typename U>
  Polynomial(Polynomial<U, N> const& other)
  {
	  for (int i = 0; i < N + 1; i++)
		coeff[i] = other[i];

  }


  // multiplication Polynomial<T, N> * Polynomial<T, M>
  template <int M>
  Polynomial<T, N + M> operator*(Polynomial<T, M> const& rhs) const
  {
    Polynomial<T, N + M> result;
    for (int i = 0; i < N + 1; i++)
      for (int j = 0; j < M + 1; j++)
        result[i + j] += coeff[i] * rhs[j];
    return result;
  }

  // () operator
  T operator()(T x)
  {
	  T result = 0;
	  for (int i = 0; i < N + 1; i++)
      result += coeff[i] * pow(x, i);
	  return result;
  }

  


  private:
  T coeff[N+1];
};

#include "polynomial.cpp"