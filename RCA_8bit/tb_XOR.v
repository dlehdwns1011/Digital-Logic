`timescale 1ns/100ps
module tb_XOR;
	reg tb_a, tb_b; //input 
	wire tb_y0;     //output

	//ordered mapping 
	_XOR U1_XOR(tb_a, tb_b, tb_y0);
	
	initial begin //test start
			tb_a = 0; tb_b = 0;
	#10;	tb_a = 0; tb_b = 1; 
	#10;	tb_a = 1; tb_b = 0; 
	#10;	tb_a = 1; tb_b = 1; 
	#10; 
	end //test end
endmodule
