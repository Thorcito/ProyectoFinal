`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/05/2022 11:58:52 PM
// Design Name: 
// Module Name: Mux_2to1_TB
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Mux_2to1_TB();
    reg [31:0] In_A, In_B; //opcion 1 y 2 del mux
    reg Selector; //senal encargada de elegir la opcion 1 o 2
    wire [31:0] OutMux; //salida del mux
    
    Mux_2to1 uut(In_A, In_B, Selector, OutMux);
    
    initial begin
    //se definen valores para las opciones 1 y 2
    In_A = 32'hFFFFAAAA;   
    In_B = 32'hFFFFFFFF;
    Selector = 0; //se selecciona la opcion 1
    #100
    Selector = 1; //se selecciona la opcion 2    
    #100
    //se definen valores para las opciones 1 y 2
    In_A = 32'h6666AFAF;   
    In_B = 32'hAFAF1010;
    Selector = 0; //se selecciona la opcion 1
    #100
    Selector = 1; //se selecciona la opcion 2 
  end
endmodule
