#pragma once

#include "list.h"
#include <iostream>

using std::size_t;

class Term 
{
protected:
	size_t degree;

	double k;

public:
	const size_t MAX_DEGREE = 9;

	Term(size_t deg = 0, double kf = 0) : degree(deg), k(kf)
	{
		if (!is_deg_correct())
		{
			throw std::invalid_argument("Degree is out of range");
		}
	}

	size_t get_x_degree() const noexcept
	{
		return degree / 100;
	}
	size_t get_y_degree() const noexcept
	{ 
		return(degree / 10) % 10;
	}
	size_t get_z_degree() const noexcept
	{
		return degree % 10;
	}
	size_t get_degree() const noexcept
	{
		return degree;
	}

	double get_k() const noexcept
	{
		return k;
	}
	void set_k(const double _k) noexcept 
	{
		k = _k;
	}
	bool is_deg_correct() const noexcept
	{
		return (get_x_degree() <= MAX_DEGREE && get_y_degree() <= MAX_DEGREE && get_z_degree() <= MAX_DEGREE);
	}

	Term operator+(const Term& m)
	{
		if (this->degree == m.degree)
		{
			return Term(degree, k + m.k);
		}

		throw std::logic_error("Cannot add terms with different degrees");
	}
	Term operator-(const Term& m)
	{
		if (this->degree == m.degree)
		{
			return Term(degree, k - m.k);
		}

		throw std::logic_error("Cannot subtract terms with different degrees");
	}
	Term operator*(const double scalar)
	{
		Term res(this->degree, this->k * scalar);

		if (res.get_k() == 0)
		{
			return Term(0, 0);
		}

		return res;
	}
	Term operator*(const Term& other)
	{
		size_t new_x = get_x_degree() + other.get_x_degree();
		size_t new_y = get_y_degree() + other.get_y_degree();
		size_t new_z = get_z_degree() + other.get_z_degree();

		if (new_x > MAX_DEGREE || new_y > MAX_DEGREE || new_z > MAX_DEGREE)
		{
			throw std::runtime_error("Multiplication results in an out-of-range degree");
		}

		size_t newDegree = new_x * 100 + new_y * 10 + new_z;
		double newK = k * other.k;

		return Term(newDegree, newK);
	}
};




class Polynomial : public List<Term>
{
public:
	Polynomial() {}
	~Polynomial() {}
	Polynomial(const Polynomial& other) : List<Term>(other) {}

	Polynomial& operator=(const Polynomial& other)
	{
		if (this != &other)
		{
			List<Term>::operator=(other);
		}

		return *this;
	}

	void add_term(const Term& t)
	{
		if (t.get_k() == 0)
		{
			return;
		}

		Iterator curr = begin();
		Node<Term>* prev = nullptr;

		while (curr != end() && (*curr).get_degree() > t.get_degree())
		{
			prev = curr.get_current();

			++curr;
		}

		if (curr != end() && (*curr).get_degree() == t.get_degree())
		{
			(*curr).set_k((*curr).get_k() + t.get_k());

			if ((*curr).get_k() == 0)
			{
				erase(curr.get_current());
			}
		}
		else
		{
			insert(t, prev);
		}
	}

	Polynomial operator+(const Polynomial& p) const
	{
		Polynomial res(*this);

		for (Iterator it = p.begin(); it != p.end(); ++it)
		{
			res.add_term(*it);
		}

		return res;
	}
	Polynomial operator*(double scalar) const
	{
		Polynomial res;

		for (Iterator it = begin(); it != end(); ++it)
		{
			res.add_term(*it * scalar);
		}

		return res;
	}
	Polynomial operator*(const Term& t) const
	{
		Polynomial res;

		for (Iterator it = begin(); it != end(); ++it)
		{
			res.add_term(*it * t);
		}

		return res;
	}
	Polynomial operator*(const Polynomial& p) const
	{
		Polynomial res;

		for (Iterator it1 = begin(); it1 != end(); ++it1)
		{
			for (Iterator it2 = p.begin(); it2 != p.end(); ++it2)
			{
				Term product = *it1 * *it2;

				res.add_term(product);
			}
		}

		return res;
	}
};