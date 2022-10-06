`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 06:23:08 PM
// Design Name: 
// Module Name: main_TB
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


module main_TB();
    reg CLK;
    reg RST;
    wire [31:0] SALIDA;
    wire [31:0] Nextepc;
    wire [31:0] Pc; 
    wire [4:0] Adda;
    wire [4:0] Addb;
    wire [4:0] Adddest;
    wire [31:0] Infoa;
    wire [31:0] Infob; 
    wire [31:0] Immext;
    wire [31:0] ALUOut;
    wire [31:0] Data;
    wire [31:0] Rdata;
     
    main UUT (.CLK(CLK),.RST(RST),.Nach(SALIDA), .nextepc(Nextepc), .pc(Pc), .adda(Adda), .addb(Addb), 
    .adddest(Adddest), .infoa(Infoa), .infob(Infob), .immext(Immext), .AluOut(ALUOut), .data(Data), .rdata(Rdata)); 
    
    always #5 CLK = ~CLK;
    initial begin
    
    RST=1;
    CLK=0;
    #10
    RST=0;
    
    end
  
endmodule
