`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 06:01:14 PM
// Design Name: 
// Module Name: ExtendUnit_12to32
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


module ExtendUnit_12to32(
    input [11:0] Extender,          // el valor debe ser 21 bits de y no de 5 bits
    output [31:0] Extendido        // el valor debe ser de 32 bits y no de 10 bits
    );
    
    assign Extendido = {{20{Extender[11]}},Extender};
    
endmodule
