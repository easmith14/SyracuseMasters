module ProgramCounter(output reg[7:0] InstructionAddress, input[7:0] Register, input[3:0] Immediate, input SelPC, LoadPC, IncPC, CLK, CLB);

always @(posedge CLK or posedge CLB)
begin 
	if(CLB)
		InstructionAddress = 8'b0;
	else begin
		if(CLK)
		begin
			if(IncPC) InstructionAddress = InstructionAddress + 1;
			if(LoadPC)
			begin
				//may need to do bit shifting here
				if(SelPC) InstructionAddress = 8'b0 + Immediate;
				else InstructionAddress = Register;
			end
		end
	end
end

endmodule
