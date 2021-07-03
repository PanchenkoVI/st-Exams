#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;
# include <vector>
# include "ATarget.hpp"
# include "ASpell.hpp"

class Warlock
{
private:
	std::string				_name;
	std::string				_title;
	std::vector<ASpell*>	_spells;
	Warlock();
	Warlock(Warlock const & src);
	Warlock & operator=(Warlock const & src);
public:
	Warlock(std::string name, std::string title) : _name(name), _title(title)
		{ PRINT(_name << ": This looks like another boring day.") }
	virtual ~Warlock() { PRINT(_name << ": My job here is done!") }

	std::string const &		getName() const { return _name; }
	std::string const &		getTitle() const { return _title; }
	void					setTitle(std::string title) { _title = title; }
	void					introduce() const { PRINT(_name << ": I am " << _name << ", " << _title << "!") }

	void		learnSpell(ASpell * spell)
	{
		if (!spell)
			return ;
		for(std::vector<ASpell*>::iterator it = _spells.begin(); it != _spells.end(); it++)
			if ((*it)->getName() == spell->getName())
				return ;
		_spells.push_back(spell);
	}
	void		forgetSpell(std::string const & spellName)
	{
		for(std::vector<ASpell*>::iterator it = _spells.begin(); it != _spells.end(); it++)
			if ((*it)->getName() == spellName)
			{
				delete *it;
				_spells.erase(it);
				return ;
			}
	}
	void		launchSpell(std::string const & spellName, ATarget const & target)
	{
		for(std::vector<ASpell*>::iterator it = _spells.begin(); it != _spells.end(); it++)
			if ((*it)->getName() == spellName)
				(*it)->launch(target);
	}
};

#endif