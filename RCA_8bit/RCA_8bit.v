module RCA_8bit(A,B,Cin,S,Cout);

input [7:0]A,B; //Declare Input 8Bits A and B
input Cin; //Declare Input Carry In
output [7:0]S;  //Declare Output 8Bits S
output Cout;   //Declare Output Carry Out

wire [6:0]t;
//Instance Using 8's Full Adder
//In order to design 8bits Adder, 8 full Adder
//The Carry generated in the addition operation of each bit is transferred to the next bit operation.
FA U0_FA(A[0],B[0],Cin,S[0],t[0]);
FA U1_FA(A[1],B[1],t[0],S[1],t[1]);
FA U2_FA(A[2],B[2],t[1],S[2],t[2]);
FA U3_FA(A[3],B[3],t[2],S[3],t[3]);
FA U4_FA(A[4],B[4],t[3],S[4],t[4]);
FA U5_FA(A[5],B[5],t[4],S[5],t[5]);
FA U6_FA(A[6],B[6],t[5],S[6],t[6]);  
FA U7_FA(A[7],B[7],t[6],S[7],Cout); //Last Carry out is Output Carry of Module

endmodule
