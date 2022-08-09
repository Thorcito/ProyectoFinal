`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06/08/2022 06:04:14 PM
// Design Name: 
// Module Name: main
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


module main(input CLK, input RST, output reg [31:0] Nach, output reg [31:0] nextepc, output reg [31:0] pc, output reg [4:0]adda, 
output reg [4:0]addb, output reg [4:0]adddest, output reg [31:0]infoa, output reg [31:0]infob, output reg [31:0]immext, output reg [31:0]AluOut,output reg [31:0]data, output reg [31:0]rdata);


//Contador del PC
wire [31:0] Next_PC, PC;
ALU_suma Cont_PC (PC, Next_PC);

//Registro del PC 
Register RegPC (CLK, RST, Next_PC, PC);

//Memoria de instrucciones 
wire [31:0] Inst;
Mem_Instrucciones Mem1 (PC, Inst);

//Banco de registros 
wire [4:0] Add_A, Add_B, Add_Dest;
wire [31:0] Write_Data, Info_A, Info_B;
wire WEreg;
assign Add_A = Inst[19:15];
assign Add_B = Inst[24:20]; 
assign Add_Dest = Inst[11:7]; 
Banco_Registros RegFile (Add_A, Add_B, Add_Dest, Write_Data, CLK, RST, WEreg, Info_A, Info_B);

//MUX a la ALU 
wire [31:0] ImmExt, ALU2;
wire ALUsrc;
Mux_toALU MuxALU (Info_B, ImmExt, ALUsrc, ALU2);


//ALU 
wire [1:0] ALUop;
wire [31:0] ALU_out;
ALU_2to1 ALU (Info_A, ALU2, ALUop, ALU_out);


//Memoria de Datos 
wire [31:0] RData;
wire WEmem;
Mem_Datos MemData (ALU_out, Info_B, WEmem, CLK, RST, RData);


//Mux de 3 a 1 
wire [31:0] Imm20;
wire [1:0] ALUreg;
Mux_3to1 Mux3a1 (ALU_out, RData, Imm20, ALUreg, Write_Data); 


//Extension de 20bits a 32bits 
wire [19:0] Imm20_in;
assign Imm20_in = Inst[31:12];
ExtendUnit_21to32 Ext2 (Imm20_in, Imm20);


//Mux para seleccionar inmediato 
wire immsrc;
wire [4:0] Immout;
Mux_2to1 MuxImm (Add_Dest, Add_B, immsrc, Immout);


//Extension de 11bits a 32bits }
wire [6:0] ImmA;
wire [11:0] Imm;
assign ImmA = Inst[31:25];
assign Imm = {ImmA, Immout};
ExtendUnit_12to32 Ext1 (Imm, ImmExt);



//Unidad de Control 
wire [2:0] funct;
wire [6:0] opcode;
assign funct = Inst[14:12];
assign opcode = Inst[6:0];
Unidad_Control UC (funct, opcode, ALUreg, ALUop, ALUsrc, WEmem, WEreg, immsrc);

always @(*) begin
    Nach <= Inst;
    nextepc <= Next_PC;
    pc      <= PC;
    adda    <= Add_A;
    addb    <= Add_B;
    adddest <= Add_Dest;
    infoa   <= Info_A;
    infob   <= Info_B;
    immext  <= ImmExt;
    AluOut  <= ALU_out;
    data    <= Write_Data;
    rdata   <= RData;
end
endmodule