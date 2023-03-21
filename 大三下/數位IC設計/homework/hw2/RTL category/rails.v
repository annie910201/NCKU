module rails(clk, reset, data, valid, result);

input        clk;
input        reset;
input  [3:0] data;
output   reg    valid;
output   reg    result; 


reg [2:0] current_state;
reg [2:0] next_state;
parameter INIT = 0;
parameter READ_NUM = 1;
parameter READ_OUT = 2;
parameter CHECK_RAIL = 3;
parameter OUTPUT = 4;
parameter FINISH = 5;
reg [3:0] counter;
reg check_over;
reg exist_situation;
reg [4:0] rail_num;
reg [3:0] buffer_rail [0:10];
reg [3:0] buffer_input [0:10];
reg [4:0] head;
reg [4:0] ptr_input;
reg [4:0] in_station;

always @(posedge clk) begin
	if(reset) 
		current_state <= INIT;
	else
		current_state <= next_state ;
end
always @(*) begin
	case (current_state)
		INIT:
			next_state = (reset) ? INIT : READ_NUM;
		READ_NUM:
			next_state = READ_OUT;
		READ_OUT:
			next_state = (counter == rail_num) ? CHECK_RAIL : READ_OUT;
		CHECK_RAIL:
			next_state = (check_over) ? OUTPUT : CHECK_RAIL ;
		OUTPUT:
			next_state = FINISH;
		FINISH:
			next_state = READ_NUM;
		default: 
			next_state = INIT;
	endcase
end
/* output */
always @(posedge clk) begin
	if(reset)
	begin
		valid <= 0;
		result <= 0;
	end
	else if(next_state == OUTPUT)
	begin
		result <= (exist_situation) ? 1 : 0;
		valid <= 1;
	end
	else
	begin
		result <= 0;
		valid <= 0;
	end
end

/* datapath */
// rail_num
always @(posedge clk) begin
	if(reset)
		rail_num <= 0;
	else if(next_state == READ_NUM)
		rail_num <= data;
end
//counter
always @(posedge clk) begin
	if(reset)
		counter <= 0;
	else if(next_state == READ_NUM)
		counter <= 0;
	else if(next_state == READ_OUT)
		counter <= counter +1;
end
// buffer_rail
always @(posedge clk) begin
	if(reset || next_state == OUTPUT)
	begin
		buffer_rail[0] <= 0;
		buffer_rail[1] <= 0;
		buffer_rail[2] <= 0;
		buffer_rail[3] <= 0;
		buffer_rail[4] <= 0;
		buffer_rail[5] <= 0;
		buffer_rail[6] <= 0;
		buffer_rail[7] <= 0;
		buffer_rail[8] <= 0;
		buffer_rail[9] <= 0;
		buffer_rail[10] <= 0;
		head <= 0;
		in_station <= 1;
		check_over <= 0;
		exist_situation <= 0;
		ptr_input <= 0;
	end
	else if(current_state == CHECK_RAIL)
	begin
		if(buffer_rail[head] > buffer_input[ptr_input]) // result = 0
		begin
			check_over <= 1;
			exist_situation <= 0;
		end
		else if(ptr_input == rail_num) //result = 1
		begin
			check_over <= 1;
			exist_situation <= 1;
		end
		else if(buffer_rail[head] == 0 && head == 0) //if stack is empty
		begin
			buffer_rail[head] <= in_station;
			in_station <= in_station + 1;
		end
		else if(buffer_rail[head] !=buffer_input[ptr_input]) //if the outside train is not the next move one
		begin
			buffer_rail[head+1] <= in_station;
			in_station <= in_station + 1;
			head <= head +1;
		end
		else if(head >0) // if the outside train is the next move one
		begin
			buffer_rail[head] <= 0;
			head <= head -1;
			ptr_input <= ptr_input +1;
		end
		else // head ==0, if the outside train is the next move one and the stack become empty
		begin
			buffer_rail[head] <= 0;
			ptr_input <= ptr_input +1;
		end
	end
	
end
// buffer_input
always @(posedge clk) begin
	if(reset || current_state == OUTPUT)
	begin
		buffer_input[0] <= 0;
		buffer_input[1] <= 0;
		buffer_input[2] <= 0;
		buffer_input[3] <= 0;
		buffer_input[4] <= 0;
		buffer_input[5] <= 0;
		buffer_input[6] <= 0;
		buffer_input[7] <= 0;
		buffer_input[8] <= 0;
		buffer_input[9] <= 0;
		buffer_input[10] <= 0;
	end
	else if(next_state == READ_OUT)
		buffer_input[counter] <= data;
	
end
endmodule