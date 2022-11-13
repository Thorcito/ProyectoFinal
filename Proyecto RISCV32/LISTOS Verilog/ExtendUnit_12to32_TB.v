`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/05/2022 08:49:51 PM
// Design Name: 
// Module Name: ExtendUnit_12to32_TB
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


module ExtendUnit_12to32_TB(
    reg [11:0] Extender,  //entrada de 12 bits
    wire [31:0] Extendido //salida de 32 bits
    );
    
ExtendUnit_12to32 uut (
//llamado de variables en el modulo del testbench correspondiente
.Extender(Extender),
.Extendido(Extendido)
);

initial begin
//se inicializan las entradas en cero por buena praxis
Extender = 12'd0;
#100
Extender = 12'd100; //probamos extendiendo el numero 100
#100
Extender = 12'd250; //probamos extendiendo el numero 255
#100
Extender = 12'd69; //probamos extendiendo el numero 69
end 
endmodule
