`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 01:45:46 AM
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
reg [31:0] In_a, In_b; //operando de 1 y 2 de la alu
reg AluOP; //selector de operaciones
wire [31:0] OUT_ALU2; //salida de la alu
 
ALU_2to1 uut(In_a, In_b, AluOP, OUT_ALU2);
initial begin
//se definen operandos para realizar una suma 
In_a= 32'd15;
In_b= 32'd4;
AluOP = 0;
#100
//se realiza un and 
AluOP= 1;
#100
//se definen operandos para realizar una suma
In_a= 32'h0000FFFF;
In_b= 32'hFFFF0000;
AluOP=0;
#100
//se realiza una and
AluOP = 1;
end
endmodule
