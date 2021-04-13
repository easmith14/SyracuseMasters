module Lab1_testbench();

reg[1:0] a, b;
reg c_in;

wire[1:0] sum;
wire c_out;

initial begin
	//c_in = 0
	a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	//c_in = 1
	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;

	#10 a = 'b00;
	#10 a = 'b01;
	#10 a = 'b10;
	#10 a = 'b11;
end

initial begin
	//c_in = 0
	b = 'b00;
	#40 b = 'b01;
	#40 b = 'b10;
	#40 b = 'b11;

	//c_in = 1
	#40 b = 'b00;
	#40 b = 'b01;
	#40 b = 'b10;
	#40 b = 'b11;
end

initial begin
	c_in = 0;
	#160 c_in = 1;
end

Adder_2 test_adder(.c_out(c_out), .sum(sum), .a(a), .b(b), .c_in(c_in));

endmodule