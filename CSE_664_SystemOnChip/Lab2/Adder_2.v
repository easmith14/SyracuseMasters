module Adder_2(output c_out, output[1:0]sum, input[1:0] a, b, input c_in);
wire 		c_in2;
FullAdder	M1(c_in2, sum[0], a[0], b[0], c_in);
FullAdder	M2(c_out, sum[1], a[1], b[1], c_in2);
endmodule
