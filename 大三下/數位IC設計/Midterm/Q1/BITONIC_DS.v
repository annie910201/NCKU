module BITONIC_DS(number_in1, number_in2, number_out1, number_out2);
input  [7:0] number_in1;
input  [7:0] number_in2;
output reg [7:0] number_out1;
output reg [7:0] number_out2;

wire smaller = (number_in1 > number_in2);
always @(*) begin
    if(smaller)
    begin
        number_out1 = number_in1;
        number_out2 = number_in2;
    end
    else
    begin
        number_out1 = number_in2;
        number_out2 = number_in1;
    end
end
endmodule