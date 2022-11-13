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
    input wire [31:0] WriteWord, //Informacion en Memoria (palabra)
    input wire [7:0] WriteByte,  //informacion en memoria (byte)
    input wire [1:0] Write_EN,   //Enable de Escritura
    input wire CLK,   //Clock 
    input wire RST,  // reset
    output reg [31:0] Read_Data //Salida Informacion en Memoria 
);

    reg [31:0] MEMORIA [0:65535];  //variable interna 
    
    integer i,k,q;  //contadores y offset
    integer file_id;  //variable para abrir el archivo
    reg [31:0] word;  //Auxiliar para el WriteByte

    initial begin //Inicializando las Memorias 
        Read_Data <= 0;
        assign q=4294901760;
        //Se definen los espacions de memoria desde 0xffff0000
    for (i=0; i<65535; i=i+1)begin 
        MEMORIA[i]=0;
       end
    end 

    initial begin 
        file_id=$fopen("MEM_DUMP.txt","w");  //se abre el archivo de texto
    end


    always @(posedge CLK)  //siempre que haya un cambio en el clock
        if (RST) begin  //si se acciona el reset la salida es cero
            Read_Data <= 0;
    end else begin
        if (Write_EN == 2'b01)begin  //si la senal de escritura vale 1 
        MEMORIA[ALUResult-q] <= WriteWord;  //se escribe la palabra en la direccion de memeoria 
    end else if (Write_EN == 2'b10)begin   //si la senal de escritura vale 2
        //se escribe el byte mas significativo en la direccion de memoria 
        
        MEMORIA[ALUResult-q] <= {word[31:8],WriteByte};  //caso contrario solo se hace una lectura de lo que haya en memoria 
    end 
end
    always @(*) begin
        Read_Data <= MEMORIA[ALUResult-q];  //Se actualiza la salida de la memoria de manera asíncrona
        word <= MEMORIA[ALUResult-q];  //Se actualiza la variable auxiliar para el wb
    end 

initial begin  //Se escribe le dump de memoria
    #800
    for (k=0; k<65635; k=k+1) begin
        $fdisplay(file_id, "%h", k,"  ", MEMORIA[k]); 
    end
end
endmodule
