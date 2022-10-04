`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10.05.2022 21:25:40
// Design Name: 
// Module Name: Register_TB
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


module Register_TB();
reg clk, rst;
reg [31:0] PC_in;
wire [31:0] PC_out;

Register uut(clk, rst, PC_in, PC_out);
initial begin
    PC_in = 32'hFF;   
    clk = 0; 
    #100
    clk = 1;     
    #100
    PC_in = 32'hAF;
    clk = 0; 
    #100
    clk = 1;
    #100
    PC_in = 32'hFA;
    clk = 0; 
    #100
    clk = 1;
  end
endmodule     