#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# define PRINT(x) std::cout << x << std::endl;

class Warlock
{
private:
	std::string		_name;
	std::string		_title;
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
	void					introduce() const 
		{ PRINT(_name << ": I am " << _name << ", " << _title << "!") }
};

#endif