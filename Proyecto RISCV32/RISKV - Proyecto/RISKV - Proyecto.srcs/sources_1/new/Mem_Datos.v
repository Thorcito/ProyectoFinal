`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 22:21:46
// Design Name: 
// Module Name: Mem_Datos
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


module Mem_Datos(
    input wire [31:0] ALUResult, //Direccion de Memoria
    input wire [31:0] WriteWord, //Informacion en Memoria 
    input wire [7:0] WriteByte,
    input wire [1:0] Write_EN,         //Enable de Escritura
    input wire CLK,              //Clock 
    input wire RST,
    output reg [31:0] Read_Data //Salida Informacion en Memoria 
);

    reg [31:0] MEMORIA [0:65535];
    
    integer i,k,q;
    integer file_id;
    reg [31:0] word;

    initial begin //Inicializando las Memorias 
        Read_Data <= 0;
        assign q=4294901760;
        //Se definen los espacions de memoria desde 0xffff0000
    for (i=0; i<65535; i=i+1)begin 
        MEMORIA[i]=0;
       end
    end 

    initial begin 
        file_id=$fopen("MEM_DUMP.txt","w"); 
    end


    always @(posedge CLK)
        if (RST) begin
            Read_Data <= 0;
    end else begin
        if (Write_EN == 2'b01)begin
        MEMORIA[ALUResult-q] <= WriteWord;
    end else if (Write_EN == 2'b10)begin
        word <= MEMORIA[ALUResult-q];
        MEMORIA[ALUResult-q] <= {word[31:8],WriteByte};
    end 
end
    always @(*) begin
        Read_Data <= MEMORIA[ALUResult-q];
    end 
    reg [31:0] memory; 
    reg [7:0] m1, m2, m3, m0; 
initial begin 
    #800
    for (k=0; k<65635; k=k+4) begin
        m0 = MEMORIA[k];
        m1 = MEMORIA[k-1];
        m2 = MEMORIA[k-2];
        m3 = MEMORIA[k-3];
        memory = {m3[7:0], m2[7:0], m1[7:0], m0[7:0]};
        $fdisplayh(file_id, k,"  ", memory); 
    end
end
endmodule
