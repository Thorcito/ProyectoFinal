# 
# Synthesis run script generated by Vivado
# 

namespace eval rt {
    variable rc
}
set rt::rc [catch {
  uplevel #0 {
    set ::env(BUILTIN_SYNTH) true
    source $::env(HRT_TCL_PATH)/rtSynthPrep.tcl
    rt::HARTNDb_resetJobStats
    rt::HARTNDb_resetSystemStats
    rt::HARTNDb_startSystemStats
    rt::HARTNDb_startJobStats
    set rt::cmdEcho 0
    rt::set_parameter writeXmsg true
    rt::set_parameter enableParallelHelperSpawn true
    set ::env(RT_TMP) "C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.runs/synth_1/.Xil/Vivado-29692-MSI/realtime/tmp"
    if { [ info exists ::env(RT_TMP) ] } {
      file delete -force $::env(RT_TMP)
      file mkdir $::env(RT_TMP)
    }

    rt::delete_design

    rt::set_parameter datapathDensePacking false
    set rt::partid xc7a35tcpg236-2L
    source $::env(HRT_TCL_PATH)/rtSynthParallelPrep.tcl
     file delete -force synth_hints.os

    set rt::multiChipSynthesisFlow false
    source $::env(SYNTH_COMMON)/common.tcl
    set rt::defaultWorkLibName xil_defaultlib

    set rt::useElabCache false
    if {$rt::useElabCache == false} {
      rt::read_verilog {
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/ALU_2to1.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/ALU_suma.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/Banco_Registros.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/ExtendUnit_12to32.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/ExtendUnit_8to32.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/Mem_Datos.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/Mem_Instrucciones.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/Mux_2to1.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/Register.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/Unidad_Control.v}
      {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.srcs/sources_1/new/main.v}
    }
      rt::filesetChecksum
    }
    rt::set_parameter usePostFindUniquification false
    set rt::top main
    rt::set_parameter enableIncremental true
    rt::set_parameter markDebugPreservationLevel "enable"
    set rt::reportTiming false
    rt::set_parameter elaborateOnly false
    rt::set_parameter elaborateRtl false
    rt::set_parameter eliminateRedundantBitOperator true
    rt::set_parameter dataflowBusHighlighting false
    rt::set_parameter generateDataflowBusNetlist false
    rt::set_parameter dataFlowViewInElab false
    rt::set_parameter busViewFixBrokenConnections false
    set_param edifin.funnel true
    rt::set_parameter elaborateRtlOnlyFlow false
    rt::set_parameter writeBlackboxInterface true
    rt::set_parameter ramStyle auto
    rt::set_parameter merge_flipflops true
# MODE: 
    rt::set_parameter webTalkPath {C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.cache/wt}
    rt::set_parameter synthDebugLog false
    rt::set_parameter printModuleName false
    rt::set_parameter enableSplitFlowPath "C:/Users/Nadir's PC/Documents/TEC/Microprocesadores y microcontroladores/Proyecto2022/Proyecto RISCV32/RISKV - Proyecto/RISKV - Proyecto.runs/synth_1/.Xil/Vivado-29692-MSI/"
    set ok_to_delete_rt_tmp true 
    if { [rt::get_parameter parallelDebug] } { 
       set ok_to_delete_rt_tmp false 
    } 
    if {$rt::useElabCache == false} {
        set oldMIITMVal [rt::get_parameter maxInputIncreaseToMerge]; rt::set_parameter maxInputIncreaseToMerge 1000
        set oldCDPCRL [rt::get_parameter createDfgPartConstrRecurLimit]; rt::set_parameter createDfgPartConstrRecurLimit 1
        $rt::db readXRFFile
      rt::run_synthesis -module $rt::top
        rt::set_parameter maxInputIncreaseToMerge $oldMIITMVal
        rt::set_parameter createDfgPartConstrRecurLimit $oldCDPCRL
    }

    set rt::flowresult [ source $::env(SYNTH_COMMON)/flow.tcl ]
    rt::HARTNDb_stopJobStats
    rt::HARTNDb_reportJobStats "Synthesis Optimization Runtime"
    rt::HARTNDb_stopSystemStats
    if { $rt::flowresult == 1 } { return -code error }


  set hsKey [rt::get_parameter helper_shm_key] 
  if { $hsKey != "" && [info exists ::env(BUILTIN_SYNTH)] && [rt::get_parameter enableParallelHelperSpawn] } { 
     $rt::db killSynthHelper $hsKey
  } 
  rt::set_parameter helper_shm_key "" 
    if { [ info exists ::env(RT_TMP) ] } {
      if { [info exists ok_to_delete_rt_tmp] && $ok_to_delete_rt_tmp } { 
        file delete -force $::env(RT_TMP)
      }
    }

    source $::env(HRT_TCL_PATH)/rtSynthCleanup.tcl
  } ; #end uplevel
} rt::result]

if { $rt::rc } {
  $rt::db resetHdlParse
  set hsKey [rt::get_parameter helper_shm_key] 
  if { $hsKey != "" && [info exists ::env(BUILTIN_SYNTH)] && [rt::get_parameter enableParallelHelperSpawn] } { 
     $rt::db killSynthHelper $hsKey
  } 
  source $::env(HRT_TCL_PATH)/rtSynthCleanup.tcl
  return -code "error" $rt::result
}
