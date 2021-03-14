 `timescale 1ns/100ps //testbench of full adder
  
 module tb_fa;
	reg tb_a, tb_b, tb_ci; 
	wire tb_s, tb_co; //3input, 2output
	
	FA U0_fa(tb_a,tb_b,tb_ci,tb_s,tb_co);
	//use full adder
	initial
	begin //test start
				tb_a = 0; tb_b = 0; tb_ci = 0;
		#10	tb_a = 0; tb_b = 1;
		#10	tb_a = 1; tb_b = 0;
		#10	tb_a = 1; tb_b = 1;
		#10	tb_a = 0; tb_b = 1; tb_ci = 1;
		#10	tb_a = 1; tb_b = 0;
		#10	tb_a = 1; tb_b = 1;
		#10	$stop;
	end //test end
endmodule
