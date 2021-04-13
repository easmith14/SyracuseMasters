module FinalProjectTestbench();

integer f;
reg CLK, CLB;
wire LoadIR, IncPC, SelPC, LoadPC, LoadReg, LoadAcc, Z, C;
wire[1:0] SelAcc;
wire[3:0] SelALU, CurrOpcode, Immediate, RegAddress;
wire[7:0] CurrInstructionAddress, CurrInstruction, CurrRegVal, CurrAccVal, CurrAluVal;

//create InstructionMemory
InstructionMemory instructionMemory(CurrInstruction, CurrInstructionAddress);
//createInstructionRegister
InstructionReg instructionReg(CurrOpcode, Immediate, RegAddress, CurrInstruction, CLK, CLB, LoadIR);
//create PC
ProgramCounter programCounter(CurrInstructionAddress, CurrRegVal, Immediate, SelPC, LoadPC, IncPC, CLK, CLB);
//create RegisterFile
RegisterFile registerFile(CurrRegVal, CurrAccVal, RegAddress, LoadReg, CLK, CLB);
//create Accumulator
Accumulator accumulator(CurrAccVal, CurrRegVal, CurrAluVal, Immediate, SelAcc, CLK, CLB, LoadAcc);
//create ALU
ALU alu(CurrAluVal, Z, C, CurrRegVal, CurrAccVal, SelALU);
//create Controller
ControllerFSM controller(SelALU, SelAcc, LoadAcc, LoadReg, LoadPC, SelPC, IncPC, LoadIR, CurrOpcode, Z, C, CLK, CLB);

initial begin
CLK = 0;
forever #5 CLK = ~CLK;
end

initial begin
CLB = 1;
#7 CLB = 0;
end

initial begin
f = $fopen("result.txt");
$fclose(f);

forever begin
#10 begin 
f = $fopen("result.txt", "a");

$fdisplay(f,"time = %d\n", $time, 
"OpCode = %b\n", CurrOpcode,
"Immediate = %b\n", Immediate,
"Acc = %b\n", CurrAccVal,
"CurrRegValue = %b\n", CurrRegVal);
$fclose(f);
end
end
end

endmodule