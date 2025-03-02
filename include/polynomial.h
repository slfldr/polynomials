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
		if (t.get_k() == 0) return;

		Node<Term>* prev = nullptr;
		Node<Term>* curr = first;

		while (curr && curr->value.get_degree() > t.get_degree())
		{
			prev = curr;
			curr = curr->next;
		}

		if (curr && curr->value.get_degree() == t.get_degree())
		{
			curr->value.set_k(curr->value.get_k() + t.get_k());

			if (curr->value.get_k() == 0)
			{
				erase(curr);
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

		for (Node<Term>* it = p.get_first(); it != nullptr; it = it->next)
		{
			res.add_term(it->value);
		}

		return res;
	}
	Polynomial operator*(double scalar) const
	{
		Polynomial res;

		for (Node<Term>* it = first; it != nullptr; it = it->next)
		{
			res.add_term(it->value * scalar);
		}

		return res;
	}
	Polynomial operator*(const Polynomial& p) const
	{
		Polynomial res;

		for (Node<Term>* it1 = first; it1 != nullptr; it1 = it1->next)
		{
			for (Node<Term>* it2 = p.get_first(); it2 != nullptr; it2 = it2->next)
			{
				Term product = it1->value * it2->value;
				res.add_term(product);
			}
		}

		return res;
	}
};