#if !defined(VM_BASE_MATH_HH)
#define VM_BASE_MATH_HH

#include "types.h"
#include "base_command_handler.h"
#include <type_traits>

class base_math : public command_handler
{
protected:
    template <typename T>
    static psw_t::flags_t get_new_flags(T a,T b,T result)
    {
        static_assert(std::is_arithmetic<T>::value,"Сравнивать можно только числа");
        psw_t::flags_t f;
        f.nf = result < 0;
        f.zf = result == 0;
        return f;
    }
public:
    base_math(memory& m, state& s,int sz):command_handler(m,s,sz){}
    ~base_math(){};
};


#endif // VM_BASE_MATH_HH
