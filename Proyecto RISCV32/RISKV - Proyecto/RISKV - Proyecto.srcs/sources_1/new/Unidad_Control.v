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
    input [2:0] funct, //se declara entrada bits 12 al 14
    input [6:0] opcode, //se declara entrada bits 0 al 6
    output reg [1:0] WEmem, //se declara salida que activa la escritura en la memoria
    output reg  ALUreg, //se declara salida ALUreg para decidir si se quiere la salida de alu o calculo de memoria
    output reg ALUop, //se declara salida para funcion a ejecutrar en la alu 
    output reg WEreg, //se declara salida para activar la escritura en registro destino
    output reg Lreg, //se declara salida para diferenciar entre loadear palabra o byte
    output reg Immreg  //se declara salida para diferenciar cuales bits tomar para completar el imm
    );
    
    always @(*) begin //siempre que exista un cambio en las entradas 
        case(opcode) 
            
            7'b0000011: //cuando sea una instruccion tipo loader
            begin 
            //setea las salidas de la siguiente manera
                ALUreg <= 1'b1;
                ALUop <= 1'b0;
                WEmem <= 2'b00;
                WEreg <= 1'b1;
                Immreg <= 1'b0;
                if (funct == 3'b100) begin //en caso de ser un byte 
                    Lreg <= 1'b1; 
                end else begin //en caso de ser una palabra 
                    Lreg <= 1'b0;
                end
            end
                
            7'b0010011: //cunado sea una instruccion addi o anddi 
            begin 
            //setea las salidas de la siguiente manera
                ALUreg <= 1'b0;
                WEmem <= 2'b00;
                WEreg <= 1'b1;
                Immreg <= 1'b0;
                if (funct == 3'b111) begin //en caso de ser and 
                    ALUop <= 1'b1;
                end else begin //en caso de ser suma 
                    ALUop <= 1'b0;
            end
            end

            7'b0100011: //cuando la instruccion es tipo store 
            begin
            //setea las salidas de la siguiente manera
                ALUop <= 1'b0;
                WEreg <= 1'b0;
                Immreg <= 1'b1;
                if (funct == 3'b000) begin //en casi de ser un byte
                    WEmem <= 2'b10;
                end else begin //en caso de ser una palabra 
                    WEmem <= 2'b01;
            end
            end
        default: //caso estandard estan todas las salidas en cero 
        begin
            ALUreg <= 1'b0;
            ALUop <= 1'b0;
            WEmem <= 2'b00;
            WEreg <= 1'b0;
            Lreg <= 1'b0;
            Immreg <= 1'b0;
        end
        endcase
    end
endmodule