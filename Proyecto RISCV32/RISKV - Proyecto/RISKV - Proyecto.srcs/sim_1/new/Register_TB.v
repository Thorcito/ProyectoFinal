`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 12:58:35 AM
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
reg clk, rst; //closk y reset
reg [31:0] PC_in; //instruccion entrante
wire [31:0] PC_out; //instruccion saliente

Register uut(clk, rst, PC_in, PC_out);
initial begin
    PC_in = 32'hFF;   //se define una instruccion entrante
    clk = 0; 
    #100
    clk = 1;     
    #100
    PC_in = 32'hAF; //se define una instruccion entrante
    clk = 0; 
    #100
    clk = 1;
    #100
    PC_in = 32'hFA; //se define una instruccion entrante
    clk = 0; 
    #100
    clk = 1;
  end
endmodule
