`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 06:06:20 PM
// Design Name: 
// Module Name: Mem_Datos
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

module Mem_Datos(
input wire [31:0] ALUResult, //Direccion de Memoria
input wire [31:0] WriteData, //Informacion en Memoria 
input wire Write_EN,         //Enable de Escritura
input wire CLK,              //Clock 
input wire RST,
output reg [31:0] memo, //256 Palabras de 32 bits c/u
output reg [31:0] Read_Data //Salida Informacion en Memoria 
);

reg [31:0] MEMORIA [0:65535];

integer i,k,q;
integer file_id;
initial begin //Inicializando las Memorias 
Read_Data <= 0;
assign q=4294901760;
//Se definen los espacions de memoria desde 0xffff0000
for (i=0; i<65535; i=i+1)begin 
MEMORIA[i]=0;
end
end 

initial begin 
file_id=$fopen("MEM_DUMP.txt","w"); 
end


always @(posedge CLK)
if (RST) begin
Read_Data <= 0;
end else begin
if (Write_EN == 1'b1)begin
MEMORIA[ALUResult-q] <= WriteData;
Read_Data <= WriteData;
end
else begin 
Read_Data <= MEMORIA[ALUResult-q];
end 
end

initial begin 
#800
for (k=0; k<65635; k=k+1) begin
$fdisplay(file_id,"%h", k, MEMORIA[k]); 
end
end
endmodule
