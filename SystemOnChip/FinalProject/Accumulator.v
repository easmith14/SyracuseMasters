module Accumulator(output reg[7:0] AccValue, input[7:0] RegFileIn, ALUIn, input[3:0] Immediate, input[1:0] SelAcc, input CLK, CLB, LoadAcc);

reg[7:0] mux1_out, mux2_out;

always @(posedge CLK or posedge CLB)
begin 
	if(CLB)
		AccValue = 8'b0;
	else begin
		if(CLK)
		begin
			if(SelAcc[0]) mux1_out = RegFileIn;
			else mux1_out = 8'b0 + Immediate;

			if(SelAcc[1]) mux2_out = ALUIn;
			else mux2_out = mux1_out;

			if(LoadAcc)
			begin
				AccValue = mux2_out;
			end
		end
	end
end

endmodule