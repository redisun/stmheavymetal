#include <array>
#include <cstddef>

extern "C" void __initial_sp();

extern "C" void __reset_handler       () __attribute__((used, noinline));
extern "C" void __nmi_handler         () __attribute__((used, noinline));
extern "C" void __hard_fault_handler  () __attribute__((used, noinline));
extern "C" void __mem_manage_handler  () __attribute__((used, noinline));
extern "C" void __bus_fault_handler   () __attribute__((used, noinline));
extern "C" void __usage_fault_handler () __attribute__((used, noinline));
extern "C" void __svc_handler         () __attribute__((used, noinline));
extern "C" void __debug_mon_handler   () __attribute__((used, noinline));
extern "C" void __pend_sv_handler     () __attribute__((used, noinline));
extern "C" void __sys_tick_handler    () __attribute__((used, noinline));
extern "C" void __unused_irq          () __attribute__((used, noinline));

extern "C" void __unused_irq          () { for(;;) { ;; }}

namespace rvector
{
  typedef void(*isr_handler)();

  constexpr std::size_t num_interrupts = 128U;
}

extern "C"
{
  const volatile std::array<rvector::isr_handler, rvector::num_interrupts> __reset_vector __attribute__((section(".reset_vector")));
}

extern "C"
{
  const volatile std::array<rvector::isr_handler, rvector::num_interrupts> __reset_vector =
  {
    __initial_sp,     // 0x0000, initial stack pointer
    __reset_handler,  // 0x0004, startup routine
    __nmi_handler,
    __hard_fault_handler,
    __mem_manage_handler,
    __bus_fault_handler,
    __usage_fault_handler,
    __unused_irq,
    __unused_irq,
    __unused_irq,
    __unused_irq,
    __svc_handler,
    __debug_mon_handler,
    __unused_irq,
    __pend_sv_handler,
    __sys_tick_handler,
    __unused_irq,
  }
}