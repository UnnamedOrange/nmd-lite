#include <iostream>
#include <json/json.h>

class main_t
{
public:
	main_t()
	{
		std::cout << "Hello, world!" << std::endl;
		Json::Value v = 1;
		std::cout << "This is a Json value: " << v.asInt() << std::endl;
	}
};