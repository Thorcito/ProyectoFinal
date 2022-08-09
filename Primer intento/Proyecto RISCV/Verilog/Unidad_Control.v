`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 06:15:17 PM
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
    output reg [1:0] ALUreg, ALUop,
    output reg ALUsrc, WEmem, WEreg, immsrc
    );
    
    always @(*) begin
        case(opcode)
            7'b0110011: 
            begin 
                ALUreg <= 2'b00;
                ALUop <= 2'b00;
                ALUsrc <= 0;
                WEmem <= 0;
                WEreg <= 1;
            end
            
            7'b0000011: 
            begin 
                ALUreg <= 2'b01;
                ALUop <= 2'b00;
                ALUsrc <= 1;
                WEmem <= 0;
                WEreg <= 1;
                immsrc <= 1;
            end
                
            7'b0100011: 
            begin 
                ALUop <= 2'b00;
                ALUsrc <= 1;
                WEmem <= 1;
                WEreg <= 0;
                immsrc <= 0;
            end
            
            7'b0110111: 
            begin 
                ALUreg <= 2'b10;
                WEmem <= 0;
                WEreg <= 1;
            end
            
            7'b0010011:
            begin
                ALUreg <= 2'b00;
                ALUsrc <= 1;
                WEmem <= 0;
                WEreg <= 1;
                immsrc <= 1;
            case(funct)
                3'b000: ALUop <= 2'b00;
                3'b101: ALUop <= 2'b01;
                3'b110: ALUop <= 2'b10;
                3'b111: ALUop <= 2'b11;
            endcase
            end
        default: 
        begin
            ALUreg <= 2'b00;
            ALUop <= 2'b00;
            ALUsrc <= 0;
            WEmem <= 0;
            WEreg <= 0;
            immsrc <= 0;
        end
        endcase
    end
endmodule
