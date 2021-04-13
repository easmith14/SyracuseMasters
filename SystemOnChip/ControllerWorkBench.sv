module ControllerFSM(output[3:0] SelALU, output[1:0] SelAcc, output LoadAcc, LoadReg, LoadPC, SelPC, IncPC, LoadIR, 
			input[3:0] Opcode, input Z, C, CLK, CLB);

reg isActiveClock;

always @(posedge CLK or posedge CLB)
begin 
	if(CLB)
	begin
		SelALU = 0;
		SelAcc = 0;
		LoadAcc = 0;
		LoadReg = 0;
		LoadPC = 0;
		SelPC = 0;
		IncPC = 0;
		LoadIR = 0;
	end

	else
		//only load IR once every 2 clock cycles!!
		if(CLK) isActiveClock = ~isActiveClock;
		if(isActiveClock)
		begin
			//ensure constant input state
			LoadIR = 0;
			//default to incrementing PC unless opcode overrides
			IncPC = 1;

			case(Opcode)
			//Addition
			'b0001 : begin
				SelALU = Opcode;
				SelAcc = 'bx1;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end
			//Subtraction
			'b0010 : begin
				SelALU = Opcode;
				SelAcc = 'bx1;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end
			//Nor
			'b0011 : begin
				SelALU = Opcode;
				SelAcc = 'bx1;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end
			//Shift right
			'b1100 : begin
				SelALU = Opcode;
				SelAcc = 'bx1;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end
			//Shift left
			'b1011 : begin
				SelALU = Opcode;
				SelAcc = 'bx1;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end
			
			//Load Reg -> Acc
			'b0100 : begin
				SelAcc = 'b10;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end
			//Load Acc -> Reg
				LoadAcc = 0;
				LoadReg = 1;
				LoadPC = 0;
			end
			//Load Immediate -> Acc
			'b1101 : begin
				SelAcc = 'b00;
				LoadAcc = 1;
				LoadReg = 0;
				LoadPC = 0;
			end

			//Z Branch -> Reg
			'b0110 : begin
				LoadAcc = 0;
				LoadReg = 0;
				if(Z)
				begin
					LoadPC = 1;
					SelPC = 0;
					IncPC = 0;
				end
				else begin
					LoadPC = 0;
				end
			end
			//Z Branch -> Immediate
			'b0111 : begin
				LoadAcc = 0;
				LoadReg = 0;
				if(Z)
				begin
					LoadPC = 1;
					SelPC = 1;
					IncPC = 0;
				end
				else begin
					LoadPC = 0;
				end
			end
			//C Branch -> Reg
			'b1000 : begin
				LoadAcc = 0;
				LoadReg = 0;
				if(C)
				begin
					LoadPC = 1;
					SelPC = 0;
					IncPC = 0;
				end
				else begin
					LoadPC = 0;
				end
			end
			//C Branch -> Immediate
			'b1010 : begin
				LoadAcc = 0;
				LoadReg = 0;
				if(C)
				begin
					LoadPC = 1;
					SelPC = 1;
					IncPC = 0;
				end
				else begin
					LoadPC = 0;
				end
			end

			//No-Op
			'b0000 : begin
				LoadAcc = 0;
				LoadReg = 0;
				LoadPC = 0;
				LoadIR = 0;
			end
			//Halt
			'b1111 : begin
				LoadAcc = 0;
				LoadReg = 0;
				LoadPC = 0;
				LoadIR = 0;
				IncPC = 0;
			end
			//fall-through
			default : begin

			end
			endcase
		end
		//on off-cycles, load the Instruction indicated in the PC
		else
		begin
			LoadIR = 1;
		end
end

endmodule