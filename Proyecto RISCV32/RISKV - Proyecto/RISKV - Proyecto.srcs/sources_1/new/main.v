`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04.10.2022 23:02:08
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


module main(
input CLK, 
input RST, 
output reg [31:0] Nach, 
output reg [31:0] nextepc, 
output reg [31:0] pc, 
output reg [4:0]adda, 
output reg [4:0]addb, 
output reg [4:0]adddest, 
output reg [31:0]infoa, 
output reg [31:0]infob, 
output reg [31:0]immext, 
output reg [31:0]AluOut,
output reg [31:0]data, 
output reg [31:0]rdata);


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

wire Immreg; 
wire [4:0] Outmux0; 
Mux_2to1 Inmediatos (Add_B, Add_Dest, Immreg, Outmux0);  



//Extension de 11bits a 32bits }
wire [6:0] ImmA;
wire [11:0] Imm;
wire [31:0] ImmExt;
assign ImmA = Inst[31:25];
assign Imm = {ImmA, Outmux0};
ExtendUnit_12to32 Ext1 (Imm, ImmExt);

//MUX a la ALU 

//ALU 
wire ALUop;
wire [31:0] ALU_out;
ALU_2to1 ALU (Info_A, ImmExt, ALUop, ALU_out);


//Memoria de Datos 
wire [31:0] RData;
wire [1:0] WEmem;
wire [7:0] WrBy;
assign WrBy = Info_B[7:0];
Mem_Datos MemData (ALU_out, Info_B, WrBy, WEmem, CLK, RST, RData);

wire [7:0] extender; 
wire [31:0] extendido; 
assign extender = RData[7:0]; 
ExtendUnit_8to32 Extend2 (extender, extendido); 

wire [31:0] outmux1; 
wire Lreg; 

Mux_2to1 LREG (RData, extendido, Lreg, outmux1); 

wire Alureg; 

Mux_2to1 ALUREG (ALU_out, outmux1, Alureg, Write_Data); 




//Unidad de Control 
wire [2:0] funct;
wire [6:0] opcode;
assign funct = Inst[14:12];
assign opcode = Inst[6:0];
Unidad_Control UC (funct, opcode, WEmem, Alureg, ALUop, WEreg, Lreg, Immreg);

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
