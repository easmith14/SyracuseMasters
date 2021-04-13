module ALU (output reg[7:0] result, output reg Z, C, input[7:0] RegisterVal, AccVal, input[3:0] SelALU);

always@(*)
begin
	case(SelALU)
		//Addition
		'b0001 : result = RegisterVal + AccVal;
		//Subtraction
		'b0010 : result = RegisterVal - AccVal;
		//Nor
		'b0011 : result = ~(RegisterVal | AccVal);
		//Shift right, preserving sign
		'b1100 : result = AccVal >>> 1;
		//Shift left, preserving
		'b1011 : result = AccVal <<< 1;
		//else do nothing
		default : result = result;
	endcase

	//check for zero
	if(result == 0) Z = 1;
	else Z = 0;
	//check for negative (signed int)
	if(result[7] == 1) C = 1;
	else C = 0;
end

endmodule