`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/05/2022 11:29:00 PM
// Design Name: 
// Module Name: Banco_Registros
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


module Banco_Registros(
    input  [4:0] Add_A, //Registro 1 
    input  [4:0] Add_B, //Registro 2
    input [4:0] Add_Dest, //Registro Destino
    input [31:0] Write_Data, //Informacion 
    input CLK, //clock
    input RST, //reset
    input Write_En,//Write Enable 
    output reg [31:0] Info_A, //Contenido del Registro A
    output reg [31:0] Info_B //Contenido del Registro B
    );
    
    reg [31:0] REGISTROS [31:0];
    integer i;

initial begin //Inicializando las Memorias 

for (i=0; i<32; i=i+1)
    begin
    REGISTROS[i]=0;
    end

end

always @(*) begin //siempre que haya un cambio saca la informacion que este en los registros (lee datos)
    Info_A <= REGISTROS[Add_A];
    Info_B <= REGISTROS[Add_B];  
end

always @(posedge CLK)begin //siempre que haya un clock se va a generar una escritura si el write en esta activo 
    if (RST) begin //caso en que se accione el reset
        Info_A <= 0;
        Info_B <= 0;
        end
    if (Write_En == 1'b1)begin //senal para indicar que se va a hacer una escritura en un registro 
        REGISTROS[Add_Dest] = Write_Data;
    end
end

endmodule
