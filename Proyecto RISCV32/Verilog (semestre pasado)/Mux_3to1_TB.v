`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 05:41:04 PM
// Design Name: 
// Module Name: Mux_3to1_TB
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

module Mux_3to1_TB();
    reg [31:0] In_A, In_B, In_C;
    reg [1:0] Selector;
    wire [31:0] OutMux;
    
    Mux_3to1 uut(In_A, In_B, In_C, Selector, OutMux);
    initial begin
    In_A = 32'h10;   
    In_B = 32'hA;
    In_C = 32'h1F;
    Selector = 2'd0; 
    #100
    Selector = 2'd0;     
    #100
    Selector = 2'd1;
    #100
    Selector = 2'd2;
    #100
    Selector = 2'd3;     
    #100
    Selector = 2'd0;
    #100
    Selector = 2'd3;
  end
endmodule
