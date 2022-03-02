# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\School\Vivado\ZynqHelloFreeRTOS\workspace\freerots\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\School\Vivado\ZynqHelloFreeRTOS\workspace\freerots\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {freerots}\
-hw {C:\School\Vivado\ZynqHelloFreeRTOS\main_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {freertos10_xilinx} -out {C:/School/Vivado/ZynqHelloFreeRTOS/workspace}

platform write
platform generate -domains 
platform active {freerots}
bsp reload
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
bsp reload
platform generate
platform active {freerots}
domain active {freertos10_xilinx_domain}
bsp reload
bsp reload
platform clean
