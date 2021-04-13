module InstructionReg(output reg[3:0] Opcode, Immediate, RegAddress, input[7:0] Instruction, input CLK, CLB, LoadIR);

always @(posedge CLK or posedge CLB)
begin 
	if(CLB)
	begin
		Opcode = 4'b0;
		Immediate = 4'b0;
		RegAddress = 4'b0;
	end
	else begin
		if(CLK)
		begin
			if(LoadIR)
			begin
				//split instruction into its constituent parts
				Opcode = Instruction[7:4];
				Immediate = Instruction[3:0];
				RegAddress = Instruction[3:0];
			end
		end
	end
end

endmodule
