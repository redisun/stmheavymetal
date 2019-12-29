namespace rhandler
{
  void init_ram();
  void init_ctors();
}

extern "C" int main();
extern "C" void __reset_handler() __attribute__((used, noinline));

void __reset_handler()
{
  // #1 load the stack pointer
  // the initial value of the stack pointer is loaded from base position in interrupt vector

  // #2 init watchdog, port, oscillator

  // #3 init static objects from rom to ram
  // zero clear default initialized static ram
  rhandler::init_ram();

  // #4 call all ctor initializations
  rhandler::init_ctors();

  // #5 jump to main
  main();
  // #6 catch unexpected return from main
}