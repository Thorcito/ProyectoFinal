`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:08:16
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

input [31:0] Dir; 
output reg [31:0] Inst; 
reg[31:0] mem[127:0]; 

initial begin
    $readmemh("code1.txt",mem); 
end

 always @(*) begin
Inst <= mem[(Dir/4)];
end
endmodule

