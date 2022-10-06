`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 02:03:22 AM
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
    input [31:0] PC_reg_out, //instruccion entrante 
    output reg [31:0] Next_PC //instruccion saliente 
    );
    always@(*) //siempre que haya un cambio 
    Next_PC = PC_reg_out + 32'd4; // a pc se le suma 4 para avanzar a la siguiente instruccion 
endmodule
