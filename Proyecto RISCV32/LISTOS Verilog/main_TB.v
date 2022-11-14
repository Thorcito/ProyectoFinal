`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.10.2022 15:21:45
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


module main_TB;
    reg CLK; //clock
    reg RST; //reset
    wire [31:0] SALIDA; //instruccion 
    wire [31:0] Nextepc; //direccion siguiente de instruccion 
    wire [31:0] Pc; //direccion de instruccion
    wire [4:0] Adda; //registro 1 de la instruccion
    wire [4:0] Addb; //registro 2 de la instruccion 
    wire [4:0] Adddest; //registro destino de la instruccion 
    wire [31:0] Infoa;  //informacion del registro 1 
    wire [31:0] Infob;   //informacion del registro 2
    wire [31:0] Immext; //immediato de la instruccion extendido a 32 bits 
    wire [31:0] ALUOut; //salida de la operacion realizada en la alu
    wire [31:0] Data; //informacion que se quiere escribir en un registro
    wire [31:0] Rdata; //informacion leida en un registro en la memoria de datos
    
    //declaracion de variables a utilizar en el test bench  
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
