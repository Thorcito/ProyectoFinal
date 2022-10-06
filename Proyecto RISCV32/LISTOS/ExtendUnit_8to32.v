`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:11:28
// Design Name: 
// Module Name: ExtendUnit_8to32
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


module ExtendUnit_8to32(
    input [7:0] Extender, //entrada de 8 bits 
    output reg [31:0] Extendido //salida de 32 bits       
    );
    
    assign Extendido = {24'b0,Extender}; //concatena 24 ceros a la entrada dejando la entrada a la derecha
endmodule