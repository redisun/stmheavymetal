#include <algorithm>
#include <iterator>

extern "C"
{
  struct ctor_t
  {
    typedef void(*constructor_type)();
    typedef std::reverse_iterator<const constructor_type*> const_reverse_iterator;
  };

  extern ctor_t::constructor_type _ctors_end[];
  extern ctor_t::constructor_type _ctors_begin[];
}

namespace rhandler
{
  void init_ctors();
}

void rhandler::init_ctors()
{
  std::for_each(ctor_t::const_reverse_iterator(_ctors_end),
                ctor_t::const_reverse_iterator(_ctors_begin),
                [](const ctor_t::constructor_type cf)
                {
                  cf();
                });
}
