`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 09:58:07 PM
// Design Name: 
// Module Name: Unidad_Control_TB
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


module Unidad_Control_TB();
reg [2:0] funct;
reg [6:0] opcode;
wire [1:0] ALUreg, ALUop;
wire ALUsrc, WEmem, WEreg, immsrc;
 
Unidad_Control uut(
.funct(funct),
.opcode(opcode),
.ALUreg(ALUreg),
.ALUop(ALUop),
.ALUsrc(ALUsrc),
.WEmem(WEmem),
.WEreg(WEreg),
.immsrc(immsrc)
);

initial begin

funct = 3'd0;
opcode = 7'd0;
#100
opcode = 7'b0110011;
#100
opcode = 7'b0000011;
#100
opcode = 7'b0100011;
#100 
opcode = 7'b0110111;
#100
opcode = 7'b0010011;
funct = 3'b000;
#100
funct = 3'b101;
#100
funct = 3'b110;
#100
funct = 3'b111;

end
endmodule
