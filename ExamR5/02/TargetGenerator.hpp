#ifndef TargetGenerator_HPP
# define TargetGenerator_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;
# include <vector>
# include "ATarget.hpp"
# include "ATarget.hpp"

class TargetGenerator
{
private:
	std::vector<ATarget*>	_target;
public:
	TargetGenerator() {}
	TargetGenerator(TargetGenerator const & src) { *this = src; }
	TargetGenerator & operator=(TargetGenerator const & src) { (void)src; return *this; }
	virtual ~TargetGenerator() { }

	void		learnTargetType(ATarget * spell)
	{
		if (!spell)
			return ;
		for(std::vector<ATarget*>::iterator it = _target.begin(); it != _target.end(); it++)
			if ((*it)->getType() == spell->getType())
				return ;
		_target.push_back(spell->clone());
	}
	void		forgetTargetType(std::string const & spellName)
	{
		for(std::vector<ATarget*>::iterator it = _target.begin(); it != _target.end(); it++)
			if ((*it)->getType() == spellName)
			{
				delete *it;
				_target.erase(it);
				return ;
			}
	}
	ATarget*		createTarget(std::string const & spellName)
	{
		for(std::vector<ATarget*>::iterator it = _target.begin(); it != _target.end(); it++)
			if ((*it)->getType() == spellName)
				return (*it)->clone();
		return NULL;
	}
};

#endif