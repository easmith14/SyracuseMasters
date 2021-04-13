module RegisterFile(output reg[7:0] RegisterValue, input[7:0] AccValue, input[3:0] RegisterAddress, input LoadReg, CLK, CLB);

reg[7:0] Registers [7:0];
//update output to be value stored at current address
assign RegisterValue = Registers[RegisterAddress];

always @(CLK or posedge CLB)
begin 
	if(CLB)
		RegisterValue = 8'b0;
	else begin
		if(CLK)
		begin
			//copy information from ACC if told to
			if(LoadReg) Registers[RegisterAddress] = AccValue;
		end
	end
end

endmodule