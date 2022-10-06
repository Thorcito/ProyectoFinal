`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 05:54:00 PM
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
    input [1:0] Selector,   
    output reg [31:0] OUT_ALU2
    );
        
    always @(*) begin
        case(Selector)
            2'b00:  OUT_ALU2 = In_a + In_b;
            2'b01:  OUT_ALU2 = In_a >> In_b;
            2'b10:  OUT_ALU2 = In_a | In_b;
            2'b11:  OUT_ALU2 = In_a & In_b;
        default: OUT_ALU2 = 32'd0;    
        endcase
        
    end
endmodule

