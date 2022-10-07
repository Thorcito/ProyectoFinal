`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 09:58:07 PM
// Design Name: 
// Module Name: Unidad_Control_TB
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


module Unidad_Control_TB();
reg [2:0] funct; //se declara entrada bits 12 al 14
reg [6:0] opcode; //se declara entrada bits 0 al 6
wire [1:0] WEmem; //se declara salida que activa la escritura en la memoria
wire ALUreg; //se declara salida ALUreg para decidir si se quiere la salida de alu o calculo de memoria
wire  ALUop; //se declara salida para funcion a ejecutrar en la alu 
wire  WEreg; //se declara salida para activar la escritura en registro destino
wire  Lreg; //se declara salida para diferenciar entre loadear palabra o byte
wire  Immreg; //se declara salida para diferenciar cuales bits tomar para completar el imm

Unidad_Control uut(
//llamado de variables en el modulo del testbench correspondiente
.funct(funct),
.opcode(opcode),
.WEmem(WEmem),
.ALUreg(ALUreg),
.ALUop(ALUop),
.WEreg(WEreg),
.Lreg(Lreg),
.Immreg(Immreg)
);

initial begin

//se inicializan las entradas en cero por buena praxis
funct = 3'd0;
opcode = 7'd0;
#100

//INSTRUCCIONES TIPO I
//como las primeras 7 instrucciones son addi el funct3 se mantiene en cero 
opcode = 7'b0010011; //opcode para instruccion mov, li y addi
#100 //instruccion mov 
#100 //instruccion li
#100 //instruccion li
#100 //instruccion li
#100 //instruccion addi 
#100 //instruccion addi 
#100 //instruccion addi 
funct = 3'b010; //cambiamos funct para instruccion lw
opcode = 7'b0000011; //cambiamos opcode para instruccion lw
#100 //instruccion lw
#100 //instruccion lw
funct = 3'b100; //cambiamos funct para instruccion lbu opcode se mantiene
#100 //instruccion lbu
funct = 3'b111; //cambiamos funct para instruccion andi
opcode = 7'b0010011; //cambiamos opcode para instruccion andi
#100 //instruccion andi


//INSTRUCCIONES TIPO S
funct = 3'b010; //cambiamos funct para inst sw
opcode = 7'b0100011; //cambiamos opcode para inst sw, sb
#100 //instruccion sw
#100 //instruccion sw
#100 //instruccion sw
funct = 3'b000; //cambiamos funct para instruccion sb
#100 //instruccion sb
funct = 3'b000; //instruccion sb 

end
endmodule
