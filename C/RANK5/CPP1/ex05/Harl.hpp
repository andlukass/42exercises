#ifndef HALR_H
# define HALR_H

# include <string>
# include <iostream>

class Harl{
private:
	void _debug(void);
	void _info(void);
	void _warning(void);
	void _error(void);

public:
	void complain(std::string level);
};

#endif 