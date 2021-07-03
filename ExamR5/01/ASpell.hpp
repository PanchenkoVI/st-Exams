#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;

class ASpell;
#include "ATarget.hpp"

class ASpell
{
protected:
	std::string		_name;
	std::string		_effects;
public:
	ASpell() {}
	ASpell(ASpell const & src) : _name(src._name), _effects(src._effects) { *this = src; }
	ASpell & operator=(ASpell const & src) { _name = src._name; _effects = src._effects; return *this; }
	ASpell(std::string name, std::string title) : _name(name), _effects(title)
		{ }
	virtual ~ASpell() { }

	std::string const &		getName() const { return _name; }
	std::string const &		getEffects() const { return _effects; }
	void					launch(ATarget const & target);
	virtual ASpell *		clone() const = 0;

};

#endif