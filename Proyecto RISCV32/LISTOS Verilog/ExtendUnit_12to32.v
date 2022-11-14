`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:09:47
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
    input [11:0] Extender,          // entrada 12 bits
    output [31:0] Extendido        // salida 32 bits
    );
    
    assign Extendido = {{20{Extender[11]}},Extender}; //concatena 20 ceros a la entrada dejando la entrada a la derecha
endmodule
