`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 06:11:05 PM
// Design Name: 
// Module Name: Mux_3to1
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


module Mux_3to1(
    input [31:0] In_A,
    input [31:0] In_B,
    input [31:0] In_C,
    input [1:0] Selector,
    output reg [31:0] OutMux
    );
    always @ (*) begin  
    case (Selector)  
       2'd0 : OutMux <= In_A;  
       2'd1 : OutMux <= In_B;
       2'd2 : OutMux <= In_C;  
       default : OutMux <=32'b0; 
    endcase  
   end  
endmodule


