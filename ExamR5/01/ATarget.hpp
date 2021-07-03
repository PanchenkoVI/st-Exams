#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;

class ATarget;
#include "ASpell.hpp"

class ATarget
{
protected:
	std::string		_name;
public:
	ATarget() {}
	ATarget(ATarget const & src) : _name(src._name) { *this = src; }
	ATarget & operator=(ATarget const & src) { _name = src._name; return *this; }
	ATarget(std::string name) : _name(name)
		{ }
	virtual ~ATarget() { }

	std::string const &		getType() const { return _name; }
	void					getHitBySpell(ASpell const & spell) const;
	virtual ATarget *		clone() const = 0;

};

#endif