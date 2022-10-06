`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 02:23:37 PM
// Design Name: 
// Module Name: ALU_2to1_TB
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

module ALU_2to1_TB();
reg [31:0] In_a, In_b;
reg [1:0] Selector;
wire [31:0] OUT_ALU2;
 
ALU_2to1 uut(In_a, In_b, Selector, OUT_ALU2);
initial begin
In_a= 32'd15;
In_b= 32'd4;
Selector=0;
#100
Selector= 2'b00;
#100
Selector= 2'b01;
#100
Selector= 2'b10;
#100
Selector= 2'b11;
end
endmodule

