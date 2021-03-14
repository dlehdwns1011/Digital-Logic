module FA(A,B,Cin,S,Cout);
	input A,B,Cin; //Declare Input A, B and Carry In
	output S,Cout; //Declare Output Sum and Carry Out
	
	wire T;
	
	//instance
	_XOR U0_XOR(A,B,T);   //T = A ⊕ B Using XOR gate
	_XOR U1_XOR(T,Cin,S); //S = T ⊕ Cin Using XOR gate
	assign Cout = (A & B) | (T & Cin); //assign for Carry Out
	
endmodule
