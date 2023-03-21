module MMS_4num(result, select, number0, number1, number2, number3);

input        select;
input  [7:0] number0;
input  [7:0] number1;
input  [7:0] number2;
input  [7:0] number3;
output reg [7:0] result; 
reg [7:0] tmp1;
reg [7:0] tmp2;
wire cmp_0and1;
wire cmp_2and3;
wire cmp_res;
assign cmp_0and1 = (number0 < number1) ? 1 : 0;
assign cmp_2and3 = (number2 < number3) ? 1 : 0;
assign cmp_res = (tmp1 < tmp2)? 1:0;
always @(*) begin
	case({select, cmp_0and1})
	2'b00:
		tmp1 = number0;
	2'b01:
		tmp1 = number1;
	2'b10:
		tmp1 = number1;
	2'b11:
		tmp1 = number0;
	endcase

	case({select, cmp_2and3})
	2'b00:
		tmp2 = number2;
	2'b01:
		tmp2 = number3;
	2'b10:
		tmp2 = number3;
	2'b11:
		tmp2 = number2;
	endcase

	case({select, cmp_res})
	2'b00:
		result = tmp1;
	2'b01:
		result = tmp2;
	2'b10:
		result = tmp2;
	2'b11:
		result = tmp1;
	endcase

end
endmodule