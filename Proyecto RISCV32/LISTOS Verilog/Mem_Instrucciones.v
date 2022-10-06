`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 01:54:18 AM
// Design Name: 
// Module Name: Mem_Instrucciones
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


module Mem_Instrucciones(Dir, Inst);
input [31:0] Dir; //se declara la direccion de la instruccion 
output reg [31:0] Inst; //la instruccion en la direcciion 
reg[31:0] mem[127:0]; //variable interna 

initial begin
    $readmemh("code1.txt",mem); //lectura de archivo txt donde vienen todas las instrucciones 
end

always @(*) begin //siempre que haya un cambio 
Inst <= mem[(Dir/4)]; 
end
endmodule
