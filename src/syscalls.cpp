#include <cstddef>
#include <cstdint>

extern "C"
void* memset(void* dst, int c, size_t n)
{
  std::uint8_t* the_dst = reinterpret_cast<std::uint8_t*>(dst);

  for( ; n > static_cast<size_t>(0U); --n)
  {
    *the_dst = static_cast<uint8_t>(c);
    ++the_dst;
  }

  return dst;
}

extern "C"
void* memcpy(void* dst, const void* src, size_t n)
{
  std::uint8_t* the_dst = reinterpret_cast<std::uint8_t*>(dst);
  const std::uint8_t* the_src = reinterpret_cast<const std::uint8_t*>(src);

  for( ; n > static_cast<std::size_t>(0U); --n)
  {
    *the_dst = *the_src;
    ++the_dst;
    ++the_src;
  }

  return dst;
}

extern "C"
void* memmove(void* dst, const void* src, size_t n)
{
  std::uint8_t* the_dst = reinterpret_cast<std::uint8_t*>(dst);
  const std::uint8_t* the_src = reinterpret_cast<const std::uint8_t*>(src);

  if((the_src < the_dst) && (the_dst < (the_src + n)))
  {
    the_dst += n;
    the_src += n;

    for( ; n > static_cast<std::size_t>(0U); --n)
    {
      --the_dst;
      --the_src;
      *the_dst = *the_src;
    }
  }
  else
  {
    for( ; n > static_cast<size_t>(0U); --n)
    {
      *the_dst = *the_src;
      ++the_dst;
      ++the_src;
    }
  }

  return dst;
}