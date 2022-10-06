`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 07:20:30 PM
// Design Name: 
// Module Name: Banco_Registros_TB
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


module Banco_Registros_TB();
    reg [4:0] Add_A; //Registro 1 
    reg [4:0] Add_B; //Registro 2
    reg [4:0] Add_Dest; //Registro Destino
    reg  [31:0] Write_Data; //Informacion 
    reg  CLK, RST; //CLK
    reg  Write_En;//Write Enable 
    wire [31:0] Info_A; //Contenido del Registro A
    wire [31:0] Info_B; //Contenido del Registro B

    Banco_Registros uut (
    .Add_A(Add_A),
    .Add_B(Add_B),
    .Add_Dest(Add_Dest),
    .Write_Data(Write_Data),
    .CLK(CLK),
    .RST(RST),
    .Write_En(Write_En),
    .Info_A(Info_A),
    .Info_B(Info_B)
    );

always #5 CLK=~CLK;
initial begin
CLK = 0;
RST=1;
#10
RST=0;
#10
Add_A = 5'd0;
Add_B = 5'd0;
Write_En = 1;
Add_Dest = 5'd0;
Write_Data = 32'd30;
#100
Add_Dest = 5'd1;
Write_Data = 32'd20;
#100
Add_Dest = 5'd2;
Write_Data = 32'd25;
#100
Add_Dest = 5'd3;
Write_Data = 32'd5;
#100
Add_Dest = 5'd4;
Write_Data = 32'd8;
#100
Write_En = 0;
Add_A = 5'd3;
Add_B = 5'd1;
#100
Add_A = 5'd2;
Add_B = 5'd0;
#100
Write_En = 1;
Add_A = 5'd3;
Add_B = 5'd3;
Add_Dest = 5'd7;
Write_Data = 32'd4;
end
endmodule