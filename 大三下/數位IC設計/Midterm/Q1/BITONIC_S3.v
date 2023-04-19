`include "BITONIC_AS.v"
`include "BITONIC_DS.v"
module BITONIC_S3(  number_in1, number_in2, number_in3, number_in4,
                    number_in5, number_in6, number_in7, number_in8,
                    number_out1, number_out2, number_out3, number_out4,
                    number_out5, number_out6, number_out7, number_out8);

input  [7:0] number_in1;
input  [7:0] number_in2;
input  [7:0] number_in3;
input  [7:0] number_in4;
input  [7:0] number_in5;
input  [7:0] number_in6;
input  [7:0] number_in7;
input  [7:0] number_in8;

output  [7:0] number_out1;
output  [7:0] number_out2;
output  [7:0] number_out3;
output  [7:0] number_out4;
output  [7:0] number_out5;
output  [7:0] number_out6;
output  [7:0] number_out7;
output  [7:0] number_out8;

wire [7:0] tmp1;
wire [7:0] tmp2;
wire [7:0] tmp3;
wire [7:0] tmp4;
wire [7:0] tmp5;
wire [7:0] tmp6;
wire [7:0] tmp7;
wire [7:0] tmp8;

wire [7:0] tmpp1;
wire [7:0] tmpp2;
wire [7:0] tmpp3;
wire [7:0] tmpp4;
wire [7:0] tmpp5;
wire [7:0] tmpp6;
wire [7:0] tmpp7;
wire [7:0] tmpp8;

BITONIC_AS b1(number_in1, number_in5, tmp1,tmp5);
BITONIC_AS b2(number_in2, number_in6, tmp2, tmp6);
BITONIC_AS b3(number_in3, number_in7, tmp3, tmp7);
BITONIC_AS b4(number_in4, number_in8, tmp4, tmp8);

BITONIC_AS b5(tmp1, tmp3, tmpp1,tmpp3);
BITONIC_AS b6(tmp2, tmp4, tmpp2,tmpp4);
BITONIC_AS b7(tmp5, tmp7, tmpp5,tmpp7);
BITONIC_AS b8(tmp6, tmp8, tmpp6,tmpp8);

BITONIC_AS b9(tmpp1, tmpp2, number_out1, number_out2);
BITONIC_AS b10(tmpp3, tmpp4, number_out3, number_out4);
BITONIC_AS b11(tmpp5, tmpp6, number_out5, number_out6);
BITONIC_AS b12(tmpp7, tmpp8, number_out7, number_out8);

endmodule
