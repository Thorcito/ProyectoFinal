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
    input [7:0] Extender,          // el valor debe ser 21 bits de y no de 5 bits
    output [31:0] Extendido        // el valor debe ser de 32 bits y no de 10 bits
    );
    
    assign Extendido = {24'b0,Extender};
endmodule
