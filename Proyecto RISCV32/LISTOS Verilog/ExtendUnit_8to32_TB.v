`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/05/2022 08:49:51 PM
// Design Name: 
// Module Name: ExtendUnit_8to32_TB
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


module ExtendUnit_8to32_TB
    reg [7:0] Extender;  //entrada de 8 bits
    wire [31:0] Extendido; //salida de 32 bits
    
    
ExtendUnit_8to32 uut (
//llamado de variables en el modulo del testbench correspondiente
.Extender(Extender),
.Extendido(Extendido)
);

initial begin
//se inicializan las entradas en cero por buena praxis
Extender = 8'd0;
#100
Extender = 8'd100; //probamos extendiendo el numero 100
#100
Extender = 8'd250; //probamos extendiendo el numero 255
#100
Extender = 8'd69; //probamos extendiendo el numero 69
end 
endmodule
