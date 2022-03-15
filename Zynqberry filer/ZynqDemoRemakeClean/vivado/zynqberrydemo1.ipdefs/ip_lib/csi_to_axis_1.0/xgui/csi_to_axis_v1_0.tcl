# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"

}

proc update_PARAM_VALUE.C_LANES { PARAM_VALUE.C_LANES } {
	# Procedure called to update C_LANES when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_LANES { PARAM_VALUE.C_LANES } {
	# Procedure called to validate C_LANES
	return true
}

proc update_PARAM_VALUE.C_TIMEOUT { PARAM_VALUE.C_TIMEOUT } {
	# Procedure called to update C_TIMEOUT when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_TIMEOUT { PARAM_VALUE.C_TIMEOUT } {
	# Procedure called to validate C_TIMEOUT
	return true
}

proc update_PARAM_VALUE.C_M_AXIS_TDATA_WIDTH { PARAM_VALUE.C_M_AXIS_TDATA_WIDTH } {
	# Procedure called to update C_M_AXIS_TDATA_WIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.C_M_AXIS_TDATA_WIDTH { PARAM_VALUE.C_M_AXIS_TDATA_WIDTH } {
	# Procedure called to validate C_M_AXIS_TDATA_WIDTH
	return true
}


proc update_MODELPARAM_VALUE.C_M_AXIS_TDATA_WIDTH { MODELPARAM_VALUE.C_M_AXIS_TDATA_WIDTH PARAM_VALUE.C_M_AXIS_TDATA_WIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_M_AXIS_TDATA_WIDTH}] ${MODELPARAM_VALUE.C_M_AXIS_TDATA_WIDTH}
}

proc update_MODELPARAM_VALUE.C_LANES { MODELPARAM_VALUE.C_LANES PARAM_VALUE.C_LANES } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_LANES}] ${MODELPARAM_VALUE.C_LANES}
}

proc update_MODELPARAM_VALUE.C_TIMEOUT { MODELPARAM_VALUE.C_TIMEOUT PARAM_VALUE.C_TIMEOUT } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.C_TIMEOUT}] ${MODELPARAM_VALUE.C_TIMEOUT}
}

