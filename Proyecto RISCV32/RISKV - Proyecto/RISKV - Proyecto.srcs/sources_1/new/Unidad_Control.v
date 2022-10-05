`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:42:49
// Design Name: 
// Module Name: Unidad_Control
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


module Unidad_Control(
    input [2:0] funct,
    input [6:0] opcode,
    output reg [1:0] WEmem, 
    output reg  ALUreg, ALUop, WEreg, Lreg
    );
    
    always @(*) begin
        case(opcode)
            
            7'b0000011: 
            begin 
                ALUreg <= 1'b1;
                ALUop <= 1'b0;
                WEmem <= 2'b00;
                WEreg <= 1'b1;
                if (funct == 3'b100) begin
                    Lreg <= 1'b1; 
                end else begin
                    Lreg <= 1'b0;
                end
            end
                
            7'b0010011: 
            begin 
                ALUreg <= 1'b0;
                WEmem <= 2'b00;
                WEreg <= 1'b1;
                if (funct == 3'b111) begin
                    ALUop <= 1'b1;
                end else begin
                    ALUop <= 1'b0;
            end
            end

            7'b0100011:
            begin
                ALUop <= 1'b0;
                WEreg <= 1'b0;
                if (funct == 3'b000) begin
                    WEmem <= 2'b10;
                end else begin
                    WEmem <= 2'b01;
            end
            end
        default: 
        begin
            ALUreg <= 1'b0;
            ALUop <= 1'b0;
            WEmem <= 2'b00;
            WEreg <= 1'b0;
            Lreg <= 1'b0;
        end
        endcase
    end
endmodule
