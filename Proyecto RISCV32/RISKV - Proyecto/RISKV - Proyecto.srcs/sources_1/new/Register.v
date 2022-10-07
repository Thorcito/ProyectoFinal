`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 12:11:09 AM
// Design Name: 
// Module Name: Register
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


module Register(
      input  clk, //clock
      input  rst, //reset
      input  [31:0] PC_in, //instruccion entrante
      output [31:0] PC_out //instruccion saliente
    );
    
      reg [31:0] PC_reg; //variale interna para almacenar la instruccion
      always @ (posedge clk) //siempre que haya un cambio en el clock
      if (rst) begin //si se acciona el reset la variable interna se vuelve cero
        PC_reg <= 0;   
      end else begin
        PC_reg <= PC_in; //en caso de no haber reset la variable interna se convierte en la instruccion entrante 
      end
      assign PC_out = PC_reg; //se le asigna a la salida la variable interna
endmodule
