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

extern "C" void __unused_irq          () __attribute__((noreturn)){ for(;;) { ;; }}

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
    __initial_sp,           // 0x0000, initial stack pointer
    __reset_handler,        // 0x0004, startup routine
    __nmi_handler,          // 0x0008, nmi exception
    __hard_fault_handler,   // 0x000C, hard fault exception
    __mem_manage_handler,   // 0x0010, memory management exception
    __bus_fault_handler,    // 0x0014, bus fault exception
    __usage_fault_handler,  // 0x0018, usage fault exception
    __unused_irq,           // 0x001C, reserved
    __unused_irq,           // 0x0020, reserved
    __unused_irq,           // 0x0024, reserved
    __unused_irq,           // 0x0028, reserved
    __svc_handler,          // 0x002C, svc handler
    __debug_mon_handler,    // 0x0030, debug monitor
    __unused_irq,           // 0x0034, reserved
    __pend_sv_handler,      // 0x0038, pending sv
    __sys_tick_handler,     // 0x003C, system tick handler
    __unused_irq,           // 0x0040, wwdg irq handler
    __unused_irq,           // 0x0044, pvd through exti line detection interrupt
    __unused_irq,           // 0x0048, tamper interrupt
    __unused_irq,           // 0x004C, rtc global interrupt
    __unused_irq,           // 0x0050, flash global interrupt
    __unused_irq,           // 0x0054, rcc global interrupt
    __unused_irq,           // 0x0058, exti line0 interrupt
    __unused_irq,           // 0x005C, exti line1 interrupt
    __unused_irq,           // 0x0060, exti line2 interrupt
    __unused_irq,           // 0x0064, exti line3 interrupt
    __unused_irq,           // 0x0068, exti line4 interrupt
    __unused_irq,           // 0x006C, dma1 channel1 global interrupt
    __unused_irq,           // 0x0070, dma1 channel2 global interrupt
    __unused_irq,           // 0x0074, dma1 channel3 global interrupt
    __unused_irq,           // 0x0078, dma1 channel4 global interrupt
    __unused_irq,           // 0x007C, dma1 channel5 global interrupt
    __unused_irq,           // 0x0080, dma1 channel6 global interrupt
    __unused_irq,           // 0x0084, dma1 channel7 global interrupt
    __unused_irq,           // 0x0088, adc1 and adc2 global interrupt
    __unused_irq,           // 0x008C, can1 tx interrupt
    __unused_irq,           // 0x0090, can1 rx0 interrupts
    __unused_irq,           // 0x0094, can1 rx1 interrupt
    __unused_irq,           // 0x0098, can1 sce interrupt
    __unused_irq,           // 0x009C, exti line[9:5] interrupts
    __unused_irq,           // 0x00A0, tim1 break interrupt
    __unused_irq,           // 0x00A4, tim1 update interrupt
    __unused_irq,           // 0x00A8, tim1 trigger and commutation interrupt
    __unused_irq,           // 0x00AC, tim1 capture compare interrupt
    __unused_irq,           // 0x00B0, tim2 global interrupt
    __unused_irq,           // 0x00B4, tim3 global interrupt
    __unused_irq,           // 0x00B8, tim4 global interrupt
    __unused_irq,           // 0x00BC, i2c1 event interrupt
    __unused_irq,           // 0x00C0, i2c1 error interrupt
    __unused_irq,           // 0x00C4, i2c2 event interrupt
    __unused_irq,           // 0x00C8, i2c2 error interrupt
    __unused_irq,           // 0x00CC, spi1 global interrupt
    __unused_irq,           // 0x00D0, spi2 global interrupt
    __unused_irq,           // 0x00D4, usart1 global interrupt
    __unused_irq,           // 0x00D8, usart2 global interrupt
    __unused_irq,           // 0x00DC, usart3 global interrupt
    __unused_irq,           // 0x00E0, exti line[15:10] interrupts
    __unused_irq,           // 0x00E4, rtc alarm through exti line interrupt
    __unused_irq,           // 0x00E8, usb otg fs wakeup through exti line interrupt
    __unused_irq,           // 0x00EC, reserved
    __unused_irq,           // 0x00F0, reserved
    __unused_irq,           // 0x00F4, reserved
    __unused_irq,           // 0x00F8, reserved
    __unused_irq,           // 0x00FC, reserved
    __unused_irq,           // 0x0100, reserved
    __unused_irq,           // 0x0104, reserved
    __unused_irq,           // 0x0108, tim5 global interrupt
    __unused_irq,           // 0x010C, spi3 global interrupt
    __unused_irq,           // 0x0110, uart4 global interrupt
    __unused_irq,           // 0x0114, uart5 global interrupt
    __unused_irq,           // 0x0118, tim6 global interrupt
    __unused_irq,           // 0x011C, tim7 global interrupt
    __unused_irq,           // 0x0120, dma2 channel1 global interrupt
    __unused_irq,           // 0x0124, dma2 channel2 global interrupt
    __unused_irq,           // 0x0128, dma2 channel3 global interrupt
    __unused_irq,           // 0x012C, dma2 channel4 global interrupt
    __unused_irq,           // 0x0130, dma2 channel5 global interrupt
    __unused_irq,           // 0x0134, ethernet global interrupt
    __unused_irq,           // 0x0138, ethernet wakeup through exti line interrupt
    __unused_irq,           // 0x013C, can2 tx interrupts
    __unused_irq,           // 0x0140, can2 rx0 interrupts
    __unused_irq,           // 0x0144, can2 rx1 interrupt
    __unused_irq,           // 0x0148, can2 sce interrupt
    __unused_irq,           // 0x014C, usb otg fs global interrupt
  }
}