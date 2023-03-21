`include "MMS_4num.v"
module MMS_8num(result, select, number0, number1, number2, number3, number4, number5, number6, number7);
input        select;
input  [7:0] number0;
input  [7:0] number1;
input  [7:0] number2;
input  [7:0] number3;
input  [7:0] number4;
input  [7:0] number5;
input  [7:0] number6;
input  [7:0] number7;
output reg [7:0] result; 
wire [7:0] tmp1_res;
wire [7:0] tmp2_res;
MMS_4num m1(tmp1_res, select, number0, number1, number2, number3 );
MMS_4num m2(tmp2_res, select, number4, number5, number6, number7 );
wire cmp_res;
assign cmp_res = (tmp1_res < tmp2_res) ? 1 : 0;
always @(*) begin
	case({select, cmp_res})
	2'b00:
		result = tmp1_res;
	2'b01:
		result = tmp2_res;
	2'b10:
		result = tmp2_res;
	2'b11:
		result = tmp1_res;
	endcase
end
endmodule