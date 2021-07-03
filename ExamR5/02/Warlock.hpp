#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;
# include <vector>
# include "ATarget.hpp"
# include "ASpell.hpp"
# include "SpellBook.hpp"

class Warlock
{
private:
	std::string				_name;
	std::string				_title;
	SpellBook				_spellBook;
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
		_spellBook.learnSpell(spell);
	}

	void		forgetSpell(std::string const & spellName)
	{
		_spellBook.forgetSpell(spellName);
	}

	void		launchSpell(std::string const & spellName, ATarget const & target)
	{
		if (_spellBook.createSpell(spellName))
			_spellBook.createSpell(spellName)->launch(target);
	}
};

#endif