#include "ATarget.hpp"

	void			ATarget::getHitBySpell(ASpell const & spell) const
	{
		PRINT( _name << " has been " << spell.getEffects() << "!" )
	}