module FullAdder(output c_out, sum, input a, b, c_in);
wire 		w1, w2, w3;
HalfAdder 	M1(w2, w1, a, b);
HalfAdder 	M2(w3,sum, c_in, w1);
or 		M3(c_out, w2, w3);
endmodule
