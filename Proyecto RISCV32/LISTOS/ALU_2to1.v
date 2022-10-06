`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 01:43:05 AM
// Design Name: 
// Module Name: ALU_2to1
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


module ALU_2to1(
    input [31:0] In_a, //operando 1 de la alu        
    input [31:0] In_b, //operando 2 de la alu
    input AluOP, //selector de operacion en la alu   
    output reg [31:0] OUT_ALU2 //salida de la alu
    );
    always @(*) begin //siempre que haya um cambio 
        case(AluOP)
            1'b0:  OUT_ALU2 = In_a + In_b; //si el selesctor es cero se realiza una suma de los operandos 
            1'b1:  OUT_ALU2 = In_a & In_b; //si el selector es un 1 se realiza una and de los operandos 
        default: OUT_ALU2 = 32'd0;  //caso default la salida de la alu es cero   
        endcase
        
    end
endmodule
