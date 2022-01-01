#include <string>
class command_size_provider {
public: 
	static std::map<std::string,uint8_t> get_command_sizes()
	{
		std::map<std::string,uint8_t> m = std::map<std::string,uint8_t>();
		m.insert ( std::pair<std::string,uint8_t>("mov",0) );
		m.insert ( std::pair<std::string,uint8_t>("fadd",1) );
		m.insert ( std::pair<std::string,uint8_t>("fsub",1) );
		m.insert ( std::pair<std::string,uint8_t>("fdiv",1) );
		m.insert ( std::pair<std::string,uint8_t>("fmul",1) );
		m.insert ( std::pair<std::string,uint8_t>("addw",2) );
		m.insert ( std::pair<std::string,uint8_t>("subw",2) );
		m.insert ( std::pair<std::string,uint8_t>("divw",2) );
		m.insert ( std::pair<std::string,uint8_t>("mulw",2) );
		m.insert ( std::pair<std::string,uint8_t>("jmpr",2) );
		m.insert ( std::pair<std::string,uint8_t>("jmpl",3) );
		m.insert ( std::pair<std::string,uint8_t>("jmplr",4) );
		m.insert ( std::pair<std::string,uint8_t>("enter",2) );
		m.insert ( std::pair<std::string,uint8_t>("leave",2) );
		m.insert ( std::pair<std::string,uint8_t>("call",2) );
		m.insert ( std::pair<std::string,uint8_t>("ret",1) );
		m.insert ( std::pair<std::string,uint8_t>("adds",2) );
		m.insert ( std::pair<std::string,uint8_t>("subs",2) );
		m.insert ( std::pair<std::string,uint8_t>("divs",2) );
		m.insert ( std::pair<std::string,uint8_t>("muls",2) );
		m.insert ( std::pair<std::string,uint8_t>("addws",2) );
		m.insert ( std::pair<std::string,uint8_t>("subws",2) );
		m.insert ( std::pair<std::string,uint8_t>("divws",2) );
		m.insert ( std::pair<std::string,uint8_t>("mulws",2) );
		m.insert ( std::pair<std::string,uint8_t>("neg",2) );
		m.insert ( std::pair<std::string,uint8_t>("print",2) );
		m.insert ( std::pair<std::string,uint8_t>("in",2) );
		m.insert ( std::pair<std::string,uint8_t>("out",2) );
		return m;
	}
};