`timescale 1ns/10ps

module ELA(clk, rst, in_data, data_rd, req, wen, addr, data_wr, done);

input				clk;
input				rst;
input		[7:0]	in_data;
input		[7:0]	data_rd;
output	reg			req;
output	reg			wen;
output	reg	[9:0]	addr;
output	reg	[7:0]	data_wr;
output	reg			done;

reg [3:0] current_state;
reg [3:0] next_state;
parameter INIT = 0;
parameter PULL_REQ = 1;
parameter READ_GRAY = 2;
parameter ADD_ROW = 3;
parameter CHECK_LOC = 4;
parameter GET_TWO = 5;
parameter GET_SIX = 6;
parameter WRITE_RES = 7;
parameter FINISH = 8;

reg [4:0] counter;
reg [4:0] count_row;
reg [2:0] count_neighbor;
reg [7:0] d1, d2, d3;
reg [8:0] sum1, sum2, sum3;

wire [4:0]up, down, right, left, center;
assign up = (count_row<<1);
assign down = (count_row<<1) + 5'd2;
assign left = counter-1;
assign right = counter+1;
assign center = (count_row<<1) + 5'd1;

always @(posedge clk) begin
if(rst)
	current_state <= INIT;
else
	current_state <= next_state;
end

always @(*) begin
case (current_state)
	INIT: 
		next_state = PULL_REQ;
	PULL_REQ:
		next_state = READ_GRAY;
	READ_GRAY:
		next_state = (addr[4:0] == 5'd31)?ADD_ROW:READ_GRAY;
	ADD_ROW:
		next_state = (count_row == 5'd15)?CHECK_LOC:PULL_REQ;
	CHECK_LOC:
		next_state = (counter == 5'd0 || counter == 5'd31)?GET_TWO:GET_SIX;
	GET_SIX:
		next_state = (count_neighbor == 3'd7)?WRITE_RES:GET_SIX;
	GET_TWO:
		next_state = (count_neighbor == 3'd3)?WRITE_RES:GET_TWO;
	WRITE_RES:
		next_state = (count_row == 5'd15 && counter == 5'd31)?FINISH:CHECK_LOC;
	FINISH:
		next_state = FINISH;
	default: 
		next_state = INIT;
endcase
end


//count_row
always @(posedge clk) begin
if(rst)
	count_row <= 0;
else if(current_state == ADD_ROW && next_state == CHECK_LOC)
	count_row <= 0;
else if(current_state == ADD_ROW)
	count_row <= count_row + 1;
else if(current_state == WRITE_RES)
begin
	if(counter == 5'd31)
		count_row <= count_row +1;
end
end

// counter
always @(posedge clk) begin
if(rst)
	counter <= 0;
else if(current_state == READ_GRAY || next_state == READ_GRAY)
	counter <= counter +1;
else if(current_state == ADD_ROW)
	counter <= 0;
else if(current_state == WRITE_RES)
	counter <= counter +1;
end

//req
always @(posedge clk) begin
if(rst)
	req <= 0;
else if(next_state == PULL_REQ)
	req <= 1;
else
	req <= 0;
end

//wen, 0=>read, 1=>write
always @(posedge clk) begin
if(rst)
	wen <= 0;
else if(next_state == READ_GRAY)
	wen <= 1;
else if(next_state == GET_SIX || next_state == GET_TWO)
	wen <= 0;
else if(next_state == WRITE_RES)
	wen <= 1;
else
	wen <= 0;
end

// addr
always @(posedge clk) begin
if(rst)
	addr <= 0;
else if(next_state == READ_GRAY)
	addr <={count_row<<1, counter};
else if(next_state == GET_SIX)
begin
	case (count_neighbor)
		3'd0: 
			addr <= {up, left};//a
		3'd1:
			addr <= {down, right};//f
		3'd2:
			addr <= {up, counter};//b
		3'd3:
			addr <= {down, counter};//e
		3'd4:
			addr <= {up, right};//c
		3'd5:
			addr <= {down, left};//d
	endcase
end
else if(next_state == GET_TWO)
begin
	if(count_neighbor == 0)
		addr <= {up, counter};
	else if(count_neighbor == 1)
		addr <= {down, counter};
end
else if(next_state == WRITE_RES)
	addr <= {center, counter};
else 
	addr <= 0;
end

// data_wr
always @(posedge clk) begin
if(rst)
	data_wr <= 0;
else if(next_state == READ_GRAY)
	data_wr <= in_data;
else if(next_state == WRITE_RES)
	if(current_state == GET_TWO)
		data_wr <= sum1>>1;
	else
	begin
		if(d2<=d1 && d2 <= d3)
			data_wr <= sum2>>1;
		else if(d1 <= d3)
			data_wr <= sum1>>1;
		else
			data_wr <= sum3>>1;
	end
end

// d1, d2, d3
always @(posedge clk) begin
if(rst)
begin
	d1 <= 0;
	d2 <= 0;
	d3 <= 0;
	sum1 <= 0;
	sum2 <=0;
	sum3 <= 0;
end
else if(current_state == GET_SIX)
begin
	case (count_neighbor)
		3'd1:
			d1 <= data_rd;
		3'd2:
		begin
			sum1 <= d1 + data_rd;
			d1 <= (d1>=data_rd)? d1-data_rd:data_rd-d1;
		end
		3'd3:
			d2 <= data_rd;
		3'd4:
		begin
			sum2 <= d2 + data_rd;
			d2 <= (d2>=data_rd)? d2-data_rd:data_rd-d2;
		end
		3'd5:
			d3 <= data_rd;
		3'd6:
		begin
			sum3 <= d3 + data_rd;
			d3 <= (d3>=data_rd)? d3-data_rd:data_rd-d3;
		end
	endcase
end
else if(current_state == GET_TWO)
begin
	if(count_neighbor == 1)
		sum1 <= data_rd;
	else if(count_neighbor == 2)
		sum1 <= data_rd + sum1;
end
end

// counter_neighbor
always @(posedge clk) begin
if(rst)
	count_neighbor <= 0;
else if(next_state == GET_SIX || next_state == GET_TWO)
	count_neighbor <= count_neighbor+1;
else if(current_state == WRITE_RES)
	count_neighbor <= 0;
end
// done
always @(posedge clk) begin
if(rst)
	done <= 0;
else if(next_state == FINISH)
	done <= 1;
end

endmodule