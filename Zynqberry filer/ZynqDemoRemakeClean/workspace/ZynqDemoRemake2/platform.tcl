# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\School\Vivado\ZynqDemoRemake\workspace\ZynqDemoRemake2\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\School\Vivado\ZynqDemoRemake\workspace\ZynqDemoRemake2\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {ZynqDemoRemake2}\
-hw {C:\School\Vivado\ZynqDemoRemake\ZynqDemoRemake.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {C:/School/Vivado/ZynqDemoRemake/workspace}

platform write
platform generate -domains 
platform active {ZynqDemoRemake2}
domain active {zynq_fsbl}
bsp reload
bsp reload
domain active {standalone_domain}
bsp reload
bsp reload
platform active {ZynqDemoRemake2}
platform clean
platform clean
platform clean
platform clean
platform generate
platform active {ZynqDemoRemake2}
bsp reload
domain active {zynq_fsbl}
bsp reload
domain create -name {linux} -os {linux} -proc {ps7_cortexa9} -arch {32-bit} -display-name {linux} -desc {} -runtime {cpp}
platform write
domain config -boot {C:\School\Vivado\ZynqDemoRemake\os\vitis-images2}
platform write
domain config -bif {C:\School\Vivado\ZynqDemoRemake\os\petalinux-images2\bootgen.bif}
platform write
domain config -image {}
domain -report -json
platform write
domain config -runtime {cpp}
platform write
domain config -bootmode {sd}
platform write
domain config -bootmode {qspi}
platform write
domain config -rootfs {C:\School\Vivado\ZynqDemoRemake\os\petalinux-images2\rootfs.ext4}
platform write
platform generate
platform active {ZynqDemoRemake2}
platform active {ZynqDemoRemake2}
platform generate
platform active {ZynqDemoRemake2}
domain create -name {freertos_domain} -os {freertos} -proc {ps7_cortexa9_0} -arch {32-bit} -display-name {freertos_domain} -desc {} -runtime {cpp}
platform generate -domains 
platform write
domain -report -json
bsp reload
bsp write
platform active {ZynqDemoRemake2}
platform clean
platform clean
