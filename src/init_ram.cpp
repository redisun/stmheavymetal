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

namespace rhandler
{
  void init_ram();
}

void rhandler::init_ram()
{
  typedef std::uint32_t mem_aligned_t;

  const std::size_t size_data_section =
    std::size_t(
      static_cast<const mem_aligned_t*>(static_cast<const void*>(&_data_end))
      - static_cast<const mem_aligned_t*>(static_cast<const void*>(&_data_begin)));

  std::copy(static_cast<const mem_aligned_t*>(static_cast<const void*>(&_rom_data_begin)),static_cast<const mem_aligned_t*>(static_cast<const void*>(&_rom_data_begin)) + size_data_section, static_cast<mem_aligned_t*>(static_cast<void*>(&_data_begin)));

  std::fill(static_cast<mem_aligned_t*>(static_cast<void*>(&_bss_begin)),static_cast<mem_aligned_t*>(static_cast<void*>(&_bss_end)),
  static_cast<mem_aligned_t>(0U));
  
}