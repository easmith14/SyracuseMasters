module HalfAdder(output c_out, sum, input a, b);
xor 		M1(sum, a, b);
and 		M2(c_out, a, b);
endmodule