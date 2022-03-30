# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\School\Vivado\ZynqHelloStandalone\workspace\hellostandaloneplatform\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\School\Vivado\ZynqHelloStandalone\workspace\hellostandaloneplatform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {hellostandaloneplatform}\
-hw {C:\School\Vivado\ZynqHelloStandalone\main_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/School/Vivado/ZynqHelloStandalone/workspace}

platform write
platform generate -domains 
platform active {hellostandaloneplatform}
domain active {zynq_fsbl}
bsp reload
domain active {standalone_domain}
bsp reload
bsp config stdin "ps7_uart_1"
bsp config stdout "ps7_uart_1"
bsp write
bsp reload
catch {bsp regenerate}
platform generate
platform clean
