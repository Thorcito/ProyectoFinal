`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 07:15:10 PM
// Design Name: 
// Module Name: Mux_toALU_TB
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


module Mux_toALU_TB();
    reg [31:0] In_A, In_B;
    reg Selector;
    wire [31:0] OutMux;
    
    Mux_toALU uut(In_A, In_B, Selector, OutMux);
    initial begin
    In_A = 32'hF;   
    In_B = 32'hA;
    Selector = 0; 
    #100
    Selector = 1;     
    #100
    Selector = 0;
    #100
    Selector = 1;
  end
    
endmodule