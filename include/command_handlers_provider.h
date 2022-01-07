#include "commands/transfer.h"
#include "commands/float_math.h"
#include "commands/stack_control.h"
#include "commands/jump.h"
#include "commands/int_math.h"
#include "commands/io.h"
#include "commands/shortint_math.h"
#include "commands/base_math.h"
#include <map>
#include "types.h"
#include "memory.h"
#include "base_command_handler.h"
class command_handlers_provider {
public: 
	static std::map<code_t,command_handler*> get_command_handlers(memory& mem,state& s)
	{
		std::map<code_t,command_handler*> m = std::map<code_t,command_handler*>();
		m.insert ( std::pair<code_t,command_handler*>(1,new mov_command_handler(mem,s,0)) );
		m.insert ( std::pair<code_t,command_handler*>(2,new fadd_command_handler(mem,s,1)) );
		m.insert ( std::pair<code_t,command_handler*>(3,new fsub_command_handler(mem,s,1)) );
		m.insert ( std::pair<code_t,command_handler*>(4,new fdiv_command_handler(mem,s,1)) );
		m.insert ( std::pair<code_t,command_handler*>(5,new fmul_command_handler(mem,s,1)) );
		m.insert ( std::pair<code_t,command_handler*>(6,new addw_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(7,new subw_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(8,new divw_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(9,new mulw_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(10,new jmpr_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(11,new jmpl_command_handler(mem,s,3)) );
		m.insert ( std::pair<code_t,command_handler*>(12,new jmplr_command_handler(mem,s,4)) );
		m.insert ( std::pair<code_t,command_handler*>(13,new enter_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(14,new leave_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(15,new call_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(16,new ret_command_handler(mem,s,1)) );
		m.insert ( std::pair<code_t,command_handler*>(17,new adds_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(18,new subs_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(19,new divs_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(20,new muls_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(21,new addws_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(22,new subws_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(23,new divws_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(24,new mulws_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(25,new neg_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(26,new print_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(27,new in_command_handler(mem,s,2)) );
		m.insert ( std::pair<code_t,command_handler*>(28,new out_command_handler(mem,s,2)) );
		return m;
	}
};