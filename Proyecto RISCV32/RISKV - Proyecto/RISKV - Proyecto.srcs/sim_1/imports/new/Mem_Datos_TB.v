`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 01:12:30 AM
// Design Name: 
// Module Name: Mem_Datos_TB
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


module Mem_Datos_TB();
reg [31:0] ALUResult; //Direccion de Memoria
reg [31:0] WriteWord; //Informacion en Memoria 
reg [7:0] WriteByte;  //informacion en memoria (byte)
reg [1:0] Write_EN;         //Enable de Escritura
reg CLK, RST;              //Clock y Reset 
wire [31:0] Read_Data; //Salida Informacion en memoria 

Mem_Datos uut(
//llamado de variables en el modulo del testbench correspondiente
.ALUResult(ALUResult), 
.WriteWord(WriteWord), 
.WriteByte(WriteByte),
.Write_EN(Write_EN), 
.CLK(CLK),
.RST(RST), 
.Read_Data(Read_Data)
);

always #5 CLK = ~CLK; //se crea el clock 
initial begin
//se inicializan todas las variables en cero por buena praxis 
CLK = 0;
RST = 0;
ALUResult = 32'hFFFF0000;
WriteWord = 32'd0;
WriteByte = 8'd0;
Write_EN = 2'd0;
#100 
//prueba de escritura de palabra en una direccion de memoria 
ALUResult = 32'hFFFF0000;
WriteWord = 32'd2;
Write_EN = 2'd1;
#100 
//prueba de lectura de informacion en memoria 
ALUResult = 32'hFFFF0000;
WriteWord = 32'd1;
Write_EN = 2'd0;
#100 
//prueba de escritura de palabra en una direccion de memoria
ALUResult = 32'hFFFF0004;
WriteWord = 32'd4;
Write_EN = 2'd1;
#100 
//prueba de lectura de informacion en memoria
ALUResult = 32'hFFFF0004;
Write_EN = 2'd0;
#100
//prueba de escritura de byte en una direccion de memoria
ALUResult = 32'hFFFF0004;
WriteByte = 8'hAA;
Write_EN = 2'd2;
#100
//prueba de lectura de informacion en memoria 
ALUResult = 32'hFFFF0004;
WriteByte = 8'h88;
Write_EN = 2'd0;
#100
//prueba de escritura de palabra en una direccion de memoria
ALUResult = 32'hFFFF0004;
WriteWord = 32'hAABBCCDD;
Write_EN = 2'd1;
#100
//prueba de escritura de byte en una direccion de memoria
ALUResult = 32'hFFFF0004;
WriteByte = 8'h88;
Write_EN = 2'd2;
#100
//prueba de lectura de informacion en memoria
ALUResult = 32'hFFFF0004;
Write_EN = 2'd0;
end
endmodule
