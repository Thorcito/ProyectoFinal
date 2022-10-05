`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:17:46
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
    input [31:0] In_a,        
    input [31:0] In_b,
    input AluOP,   
    output reg [31:0] OUT_ALU2
    );
        
    always @(*) begin
        case(AluOP)
            1'b0:  OUT_ALU2 = In_a + In_b;
            1'b1:  OUT_ALU2 = In_a & In_b;
        default: OUT_ALU2 = 32'd0;    
        endcase
        
    end
endmodule
