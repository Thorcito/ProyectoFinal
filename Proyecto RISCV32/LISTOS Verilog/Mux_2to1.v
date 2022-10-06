`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/05/2022 11:55:04 PM
// Design Name: 
// Module Name: Mux_2to1
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


module Mux_2to1(
    input [31:0] In_A, //opcion 1 del mux
    input [31:0] In_B, //opcion 2 del mux
    input Selector, //senal encargada de elegir la opcion 1 o 2
    output reg [31:0] OutMux //salida del mux 
    );
    
    always @ (*) begin //siempre que haya un cmabio en las entradas 
     case (Selector)  
        1'd0 : OutMux <= In_A; //si el selecotr esta en 0 selecciona la opcion 1 
        1'd1 : OutMux <= In_B; //si el selecotr esta en 1 selecciona la opcion 2 
        default : OutMux <=32'b0; //caso default la salida es cero 
     endcase  
   end
endmodule
