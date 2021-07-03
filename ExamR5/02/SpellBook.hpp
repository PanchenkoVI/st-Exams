#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;
# include <vector>
# include "ATarget.hpp"
# include "ASpell.hpp"

class SpellBook
{
private:
	std::vector<ASpell*>	_spells;
public:
	SpellBook() {}
	SpellBook(SpellBook const & src) { *this = src; }
	SpellBook & operator=(SpellBook const & src) { (void)src; return *this; }
	virtual ~SpellBook() { }

	void		learnSpell(ASpell * spell)
	{
		if (!spell)
			return ;
		for(std::vector<ASpell*>::iterator it = _spells.begin(); it != _spells.end(); it++)
			if ((*it)->getName() == spell->getName())
				return ;
		_spells.push_back(spell->clone());
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
	ASpell*		createSpell(std::string const & spellName)
	{
		for(std::vector<ASpell*>::iterator it = _spells.begin(); it != _spells.end(); it++)
			if ((*it)->getName() == spellName)
				return (*it)->clone();
		return NULL;
	}
};

#endif