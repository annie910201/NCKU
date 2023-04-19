module rails(clk, reset, number, data1, data2, valid, result1, result2);

input        clk;
input        reset;
input  [3:0] number;
input  [3:0] data1;
input  [3:0] data2;
output  reg     valid;
output  reg     result1; 
output  reg     result2;

reg [2:0] current_state;
reg [2:0] next_state;
parameter INIT = 0;
parameter READ_NUM = 1;
parameter READ_OUT = 2;
parameter CHECK_RAIL_1 = 3;
parameter CHECK_RAIL_2 = 4;
parameter OUTPUT = 5;
parameter FINISH = 6;

reg [3:0] stack1[0:6];
reg [3:0] top1;
reg [3:0] stack2[0:4];
reg [2:0] top2;
reg [3:0] buffer_input_1[0:9];
reg [3:0] buffer_input_2[0:9];
reg [3:0] ptr1;
reg [3:0] ptr1_2stage;
reg [3:0] ptr2;
reg [3:0] in_station;
reg [3:0] rail_num;
integer  i;
reg [3:0] counter;
reg checkover_1;
reg checkover_2;
reg exist_1;
reg exist_2;

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
			next_state = (counter == rail_num) ? CHECK_RAIL_1 : READ_OUT;
		CHECK_RAIL_1:
			if(checkover_1)
                next_state = (exist_1)?CHECK_RAIL_2:OUTPUT;
            else
                next_state = CHECK_RAIL_1;
        CHECK_RAIL_2:
			next_state = (checkover_2) ? OUTPUT : CHECK_RAIL_2;
		OUTPUT:
			next_state = FINISH;
		FINISH:
			next_state = READ_NUM;
		default: 
			next_state = INIT;
	endcase
end
// stack1
always @(posedge clk) begin
    if(reset || current_state == OUTPUT)
    begin
        for(i=0;i<7;i=i+1)
            stack1[i]<= 0;
        top1 <= 0;
        checkover_1 <= 0;
        exist_1 <= 0;
        ptr1 <= 0;
        in_station <= 1;
    end
    else if(current_state == CHECK_RAIL_1)
    begin
        if(stack1[top1] > buffer_input_1[ptr1] || top1 == 4'd7)
        begin
            checkover_1 <= 1;
            exist_1 <= 0;
        end
        else if(ptr1 == rail_num)
        begin
            checkover_1 <= 1;
            exist_1 <= 1;
        end
        else if(top1 == 0 && stack1[top1] == 0)
        begin
            stack1[top1] <= in_station;
            in_station <= in_station + 1;
        end
        else if(stack1[top1]!=buffer_input_1[ptr1])
        begin
            stack1[top1+1] <= in_station;
            in_station <= in_station +1;
            top1 <= top1 +1;
        end
        else if(top1 >0)
        begin
            stack1[top1] <= 0;
            top1 <= top1 -1;
            ptr1 <= ptr1 +1;
        end
        else 
        begin
            stack1[top1] <= 0;
            ptr1 <= ptr1 +1;
        end
    end
end
// stack2
always @(posedge clk) begin
    if(reset || current_state == OUTPUT)
    begin
        for(i=0;i<5;i=i+1)
            stack2[i]<= 0;
        top2 <= 0;
        checkover_2 <= 0;
        exist_2 <= 0;
        ptr2 <= 0;
        ptr1_2stage <= 0;
    end
    else if(current_state == CHECK_RAIL_2)
    begin
        if(top2 == 4'd5)
        begin
            checkover_2 <= 1;
            exist_2 <= 0;
        end
        else if(ptr2 == rail_num)
        begin
            checkover_2 <= 1;
            exist_2 <= 1;
        end
        else if(top2 == 0 && stack2[top2] == 0)
        begin
            stack2[top2] <= buffer_input_1[ptr1_2stage];
            ptr1_2stage <= ptr1_2stage + 1;
        end
        else if(stack2[top2]!=buffer_input_2[ptr2])
        begin
            stack2[top2+1] <= buffer_input_1[ptr1_2stage];
            ptr1_2stage <= ptr1_2stage + 1;
            top2 <= top2 +1;
        end
        else if(top2 >0)
        begin
            stack2[top2] <= 0;
            top2 <= top2 -1;
            ptr2 <= ptr2 +1;
        end
        else 
        begin
            stack2[top2] <= 0;
            ptr2 <= ptr2 +1;
        end
    end
end
// rail_num
always @(posedge clk) begin
	if(reset)
		rail_num <= 0;
	else if(next_state == READ_NUM)
		rail_num <= number;
end
// buffer_input
always @(posedge clk) begin
	if(reset || current_state == OUTPUT)
	begin
		for(i=0;i<10;i=i+1)
			buffer_input_1[i] <= 0;
        for(i=0;i<11;i=i+1)
			buffer_input_2[i] <= 0;
        counter <= 0;
	end
	else if(next_state == READ_OUT)
    begin
		buffer_input_1[counter] <= data1;
        buffer_input_2[counter] <= data2;
        counter <= counter +1;
    end
	
end
/* output */
always @(posedge clk) begin
	if(reset)
	begin
		valid <= 0;
		result1 <= 0;
        result2 <= 0;
	end
	else if(next_state == OUTPUT)
	begin
		result1 <= (exist_1) ? 1 : 0;
        result2 <= (exist_2) ? 1 : 0;
		valid <= 1;
	end
	else
	begin
		result1 <= 0;
		valid <= 0;
	end
end
endmodule