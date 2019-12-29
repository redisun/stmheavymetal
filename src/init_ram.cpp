#include <algorithm>
#include <cstddef>
#include <cstdint>

extern "C"
{
  extern std::uintptr_t _rom_data_begin;
  extern std::uintptr_t _data_begin;
  extern std::uintptr_t _data_end;
  extern std::uintptr_t _bss_begin;
  extern std::uintptr_t _bss_end;
}

namespace rram
{
  void init_ram();
}

void rram::init_ram()
{
  typedef std::uint32_t mem_aligned_t;

  const std::size_t size_data_section =
    std::size_t(
      static_cast<const mem_aligned_t*>(static_cast<const void*>(&_data_end))
      - static_cast<const mem_aligned_t*>(static_cast<const void*>(&_data_begin)));
  
}