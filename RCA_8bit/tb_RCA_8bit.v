 `timescale 1ns/100ps //testbench of RCA
 
module tb_RCA_8bit;
//Testbench of RCA_8bits
reg [7:0]tb_a,tb_b;
reg tb_cin; //input
wire [7:0]tb_y;
wire tb_co; //output

//instance of RCA_8bits module
RCA_8bit U0_RCA_8bit(tb_a,tb_b,tb_cin,tb_y,tb_co);

initial
	begin //test start
			tb_a=8'b0; tb_b=8'b0; tb_cin = 0; //initial set
	#10;	tb_a=8'd1; tb_b=8'd1; 
	#10;	tb_a=8'd2; tb_b=8'd2; 
	#10;	tb_a=8'd3; tb_b=8'd3; 
	#10;	tb_a=8'd10; tb_b=8'd2;
	#10;	tb_a=8'h9C; tb_b=8'hff; 
	#10;	tb_a=8'hC8; tb_b=8'h64; 
	#10;	tb_a=8'd1; tb_b=8'd1; tb_cin = 1; //Carry In rising
	#10;	tb_a=8'd2; tb_b=8'd2; 
	#10;	tb_a=8'd3; tb_b=8'd3; 
	#10;	$stop;
	end //test end
endmodule
