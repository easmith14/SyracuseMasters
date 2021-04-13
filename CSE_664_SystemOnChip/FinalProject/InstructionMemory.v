module InstructionMemory(output[7:0] Instruction, input[7:0] Address);
//Address here is likely from PC
reg[7:0] StoredInstructions [0:255];

//read in instructions from file, then return the appropriate one
initial $readmemb("InstructionMemory.dat",StoredInstructions);
assign Instruction = StoredInstructions[Address];

endmodule