`timescale 1ns/10ps
module  ATCONV(
	input		clk,
	input		reset,
	output	reg	busy,	
	input		ready,	
			
	output reg	[11:0]	iaddr,
	input signed [12:0]	idata,
	
	output	reg 	cwr,
	output  reg	[11:0]	caddr_wr,
	output reg 	[12:0] 	cdata_wr,
	
	output	reg 	crd,
	output reg	[11:0] 	caddr_rd,
	input 	[12:0] 	cdata_rd,
	
	output reg 	csel
	);

reg [2:0] current_state;
reg [2:0] next_state;
parameter INIT = 0;
parameter READ = 1;
parameter RELU = 2;
parameter WR_L0 = 3;
parameter BREAK_POINT = 4;
parameter RD_L0 = 5;
parameter WR_L1 = 6;
parameter FINISH = 7;

parameter signed K0 = 13'h1fff;
parameter signed K1 = 13'h1ffe;
parameter signed K2 = 13'h1fff;
parameter signed K3 = 13'h1ffc;
parameter signed K4 = 13'h0010;
parameter signed K5 = 13'h1ffc;
parameter signed K6 = 13'h1fff;
parameter signed K7 = 13'h1ffe;
parameter signed K8 = 13'h1fff;
parameter bias = 13'h1ff4;

reg [5:0] x;
reg [5:0] y;
wire [5:0] up_2, down_2, left_2, right_2, up_1, down_1, left_1, right_1;
assign up_2 = y-2;
assign down_2 = y+2;
assign left_2 = x-2;
assign right_2 = x+2;
assign up_1 = y-1;
assign down_1 = y+1;
assign left_1 = x-1;
assign right_1 = x+1;

reg [3:0] counter;

reg signed [13:0] tmp1, tmp2;
wire signed[25:0] mul;
assign mul = tmp1 * tmp2;
reg signed [29:0] sum;
wire signed [13:0] tmp_res = sum[16:3]+1;

reg [12:0] tmp_max;
always @(posedge clk) begin
if(reset)
	current_state <= INIT;
else
	current_state <= next_state;
end

always @(*) begin
case (current_state)
	INIT: 
		next_state = (ready)?READ:INIT;
	READ:
		next_state = (counter == 4'd10)?RELU:READ;
	RELU:
		next_state = WR_L0;
	WR_L0:
		next_state = (y == 8'd63 && x == 8'd63)? BREAK_POINT:READ;
	BREAK_POINT:
		next_state = RD_L0;
	RD_L0:
		next_state = (counter == 4'd5)?WR_L1:RD_L0;
	WR_L1:
		next_state = (y == 8'd62 && x == 8'd62)?FINISH:RD_L0;
	default: 
		next_state = INIT;
endcase
end

/* output */
// busy
always @(posedge clk)begin
	if(reset)
		busy <= 0;
	else if(ready)
		busy <= 1;
	else if(next_state == FINISH)
		busy <= 0;
end
// iaddr
always @(posedge clk) begin
	if(reset)
		iaddr <= 0;
	else if(current_state == READ)
	begin
		case (counter)
			4'd0:
				if(x<=2 && y<=2)
					iaddr <= 0;
				else if(y <= 2)
					iaddr <= {6'd0, left_2};
				else if(x <= 2)
					iaddr <= {up_2, 6'd0};
				else 
					iaddr <= {up_2, left_2};
			4'd1:
				if(y==0)
					iaddr <= {y, x};
				else if(y==1)
					iaddr <= {up_1, x};
				else
					iaddr <= {up_2, x};
			4'd2:
				if(x>=61 && y<=2)
					iaddr <= 12'd63;
				else if(y <= 2)
					iaddr <= {6'd0, right_2};
				else if(x >= 61)
					iaddr <= {up_2, 6'd63};
				else 
					iaddr <= {up_2, right_2};
			4'd3:
				if(x==0)
					iaddr <= {y, x};
				else if(x==1)
					iaddr <= {y, left_1};
				else
					iaddr <= {y, left_2};
			4'd4:
				iaddr <= {y, x};
			4'd5:
				if(x==63)
					iaddr <= {y, x};
				else if(x==62)
					iaddr <= {y, right_1};
				else
					iaddr <= {y, right_2};
			4'd6:
				if(x<=2 && y>=61)
					iaddr <= 12'd4032;
				else if(y >= 61)
					iaddr <= {6'd63, left_2};
				else if(x <= 2)
					iaddr <= {down_2, 6'd0};
				else 
					iaddr <= {down_2, left_2};
			4'd7:
				if(y==63)
					iaddr <= {y, x};
				else if(y==62)
					iaddr <= {down_1, x};
				else
					iaddr <= {down_2, x};
			4'd8:
				if(x>= 61 && y>= 61)
					iaddr <= 12'd4095;
				else if(y >= 61)
					iaddr <= {6'd63, right_2};
				else if(x >= 61)
					iaddr <= {down_2, 6'd63};
				else 
					iaddr <= {down_2, right_2};
		endcase
	end
end
// crd
always @(posedge clk)begin
	if(reset)
		crd <= 0;
	else if(next_state == RD_L0)
		crd <= 1;
	else 
		crd <= 0;
end
// caddr_rd
always @(posedge clk)begin
	if(reset)
		caddr_rd <= 0;
	else if(current_state == RD_L0)
	begin
		case (counter)
			4'd0:
				caddr_rd <= {y, x};
			4'd1:
				caddr_rd <= {y, right_1};
			4'd2:
				caddr_rd <= {down_1, x};
			4'd3:
				caddr_rd <= {down_1, right_1};
		endcase
	end
end
// cwr
always @(posedge clk)begin
	if(reset)
		cwr <= 0;
	else if(next_state == WR_L0 || next_state == WR_L1)
		cwr <= 1;
	else 
		cwr <= 0;
end
// caddr_wr
always @(posedge clk)begin
	if(reset)
		caddr_wr <= 0;
	else if(next_state == WR_L0 )
		caddr_wr <= {y, x};
	else if(current_state == BREAK_POINT)
		caddr_wr <= 0;
	else if(current_state == WR_L1)
		caddr_wr <= caddr_wr +1;
end
// cdata_wr
always @(posedge clk)begin
	if(reset)
		cdata_wr <= 0;
	else if(next_state == WR_L0 )
		cdata_wr <= (sum[29])?0:tmp_res[13:1];
	else if(next_state == WR_L1)
	begin
		if(tmp_max==0)
			cdata_wr <= 0;
		else if(tmp_max[3:0] == 0)
			cdata_wr <= {tmp_max[12:4], 4'b0};
		else
			cdata_wr <= ({tmp_max[12:4], 4'b0} )+ 5'b10000;
	end
end
// csel
always @(posedge clk)begin
	if(reset)
		csel <= 0;
	else if(next_state == WR_L0 || next_state == RD_L0)
		csel <= 0;
	else if(next_state == WR_L1)
		csel <=1;
	else 
		csel <= 0;
end

/* datapath */
// x and y
always @(posedge clk) begin
	if(reset)
	begin
		x <= 0;
		y <= 0;
	end
	else if(current_state == WR_L0 )
	begin
		if(x==8'd63)
			y <= y+1;
		x <= x+1;
	end
	else if(current_state == WR_L1)
	begin
		if(x==8'd62)
			y <= y+2;
		x <= x+2;
	end
	
end
// counter
always @(posedge clk) begin
	if(reset)
		counter <= 0;
	else if(current_state == READ)
		counter <= counter+1;
	else if(current_state == WR_L0)
		counter <= 0;
	else if(current_state == RD_L0)
		counter <= counter +1;
	else if(current_state == WR_L1)
		counter <= 0;
end
// sum, tmp1, tmp2
always @(posedge clk) begin
	if(reset)
	begin
		tmp1 <= 0;
		tmp2 <= 0;
	end
	else if(current_state == READ)
	begin
		case (counter)
			4'd1:
			begin
				sum <= {13'd8191,bias, 4'b0};
				tmp1 <= idata;
				tmp2 <= K0;
			end
			4'd2:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K1;
			end
			4'd3:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K2;
			end
			4'd4:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K3;
			end
			4'd5:
			begin
				sum <= mul + sum;
				tmp1 <= idata;
				tmp2 <= K4;
			end
			4'd6:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K5;
			end
			4'd7:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K6;
			end
			4'd8:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K7;
			end
			4'd9:
			begin
				sum <= mul+sum;
				tmp1 <= idata;
				tmp2 <= K8;
			end
			4'd10:
				sum <= mul + sum;
			// 4'd11:
			// 	sum <= sum + {13'd8191,bias, 4'b0};
		endcase
	end
end

// tmp_max
always @(posedge clk) begin
	if(reset)
		tmp_max <= 0;
	else if(current_state == RD_L0)
	begin
		if(counter >= 1 && counter <= 4 && cdata_rd > tmp_max)
			tmp_max <= cdata_rd;
	end
	else if(current_state == WR_L1)
		tmp_max <= 0;
end
endmodule