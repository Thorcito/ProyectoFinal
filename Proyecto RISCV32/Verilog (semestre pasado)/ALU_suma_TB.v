`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/06/2022 02:25:33 PM
// Design Name: 
// Module Name: ALU_suma_TB
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

module ALU_suma_TB();
reg [31:0] PC_reg_out;
wire [31:0] Next_PC;
 
ALU_suma uut(PC_reg_out, Next_PC);
initial begin
PC_reg_out= 32'd0;
#100
PC_reg_out= 32'd1;
#100
PC_reg_out= 32'd2;
#100
PC_reg_out= 32'd3;
#100
PC_reg_out= 32'd4;

end
endmodule
