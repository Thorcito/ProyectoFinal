`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:41:16
// Design Name: 
// Module Name: Mux_2to1
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


module Mux_2to1(
    input [31:0] In_A, 
    input [31:0] In_B,
    input Selector,
    output reg [31:0] OutMux
    );
    
    always @ (*) begin  
     case (Selector)  
        1'd0 : OutMux <= In_A;  
        1'd1 : OutMux <= In_B; 
        default : OutMux <=32'b0; 
     endcase  
   end
endmodule
