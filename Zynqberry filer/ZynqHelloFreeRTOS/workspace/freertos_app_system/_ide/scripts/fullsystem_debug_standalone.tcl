# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\School\Vivado\ZynqHelloFreeRTOS\workspace\freertos_app_system\_ide\scripts\fullsystem_debug_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\School\Vivado\ZynqHelloFreeRTOS\workspace\freertos_app_system\_ide\scripts\fullsystem_debug_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "JTAG-ONB4 2516330075ADA" && level==0 && jtag_device_ctx=="jsn-JTAG-ONB4-2516330075ADA-13722093-0"}
fpga -file C:/School/Vivado/ZynqHelloFreeRTOS/workspace/freertos_app/_ide/bitstream/main_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/School/Vivado/ZynqHelloFreeRTOS/workspace/freerots/export/freerots/hw/main_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/School/Vivado/ZynqHelloFreeRTOS/workspace/freertos_app/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/School/Vivado/ZynqHelloFreeRTOS/workspace/freertos_app/Debug/freertos_app.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
