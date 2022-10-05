`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:38:50
// Design Name: 
// Module Name: ALU_suma
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


module ALU_suma(
    input [31:0] PC_reg_out,
    output reg [31:0] Next_PC
    );
    always@(*)
    Next_PC = PC_reg_out + 32'd4; // add
endmodule
