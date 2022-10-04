`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 04:29:38 PM
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
    reg [4:0] In_A, In_B;
    reg Selector;
    wire [4:0] OutMux;
    
    Mux_2to1 uut(In_A, In_B, Selector, OutMux);
    initial begin
    In_A = 5'hF;   
    In_B = 5'hA;
    Selector = 0; 
    #100
    Selector = 1;     
    #100
    Selector = 0;
    #100
    Selector = 1;
  end
    
endmodule
