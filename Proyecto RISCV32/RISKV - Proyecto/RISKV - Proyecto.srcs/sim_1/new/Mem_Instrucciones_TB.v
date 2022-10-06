`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/06/2022 01:59:18 AM
// Design Name: 
// Module Name: Mem_Instrucciones_TB
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


module Mem_Instrucciones_TB();
reg[31:0]  Add;        //se declara la direccion de la instruccion
wire[31:0]  Insto;    //la instruccion en la direcciion 
Mem_Instrucciones uut(
//llamado de variables en el modulo del testbench correspondiente
.Dir(Add), 
.Inst(Insto)
); 

initial begin
Add=0; 
#10
Add=1; 
#10
Add=2; 
#10
Add=3; 
#10
Add=4; 
#10
Add=5; 
#10
Add=6; 
#10
Add=7; 
#10
Add=8; 
#10
Add=9; 
#10
Add=10; 
#10
Add=11; 
#10
Add=12; 
#10
Add=13; 
#10
Add=14; 

end
endmodule
