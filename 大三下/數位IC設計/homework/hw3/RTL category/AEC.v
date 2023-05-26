module AEC(clk, rst, ascii_in, ready, valid, result);

// Input signal
input clk;
input rst;
input ready;
input [7:0] ascii_in;
// Output signal
output reg valid;
output reg [6:0] result;
// Register
reg [2:0] current_state;
reg [2:0] next_state;
parameter INIT = 0;
parameter READ = 1;
parameter TRANSFER = 2;
parameter CALCULATION = 3;
parameter OUTPUT = 4;
reg [7:0] stack [0:7];
reg [7:0] output_buffer [0:15];
reg [7:0] input_buffer [0:15];
reg [2:0] top;
reg [3:0] tail_in;
reg [3:0] tail_out; 
reg transfer_over;
//-----Your design-----//
/* next state */
always @(posedge clk) begin
    if(rst)
        current_state <= INIT;
    else
        current_state <= next_state;
end

/* state logic */
always @(*) begin
    case (current_state)
        INIT:
            next_state = (ready)?READ:INIT;
        READ:
            next_state = (ascii_in == 8'd61)?TRANSFER:READ;
        TRANSFER:
            next_state = (transfer_over)?CALCULATION:TRANSFER;
        CALCULATION:
            next_state = (output_buffer[tail_out] == 8'd61)?OUTPUT:CALCULATION;
        OUTPUT:
            next_state = INIT;
        default: 
            next_state = INIT;
    endcase
end

/* output */
always @(posedge clk) begin
if(rst) 
begin
    valid <= 0;
    result <= 0;
end
else if(next_state == OUTPUT)
begin
    valid <= 1;
    result <= stack[0];
end
else
begin
    valid <= 0;
end
end

/* datapath */
// stack and output_buffer and input_buffer
integer  i;
always @(posedge clk) begin
if(rst) 
begin
    for(i = 0;i<8;i=i+1)
        stack[i] <= 0;
    for(i = 0;i<16;i=i+1)
        output_buffer[i] <= 0;
    for(i = 0;i<16;i=i+1)
        input_buffer[i] <= 0;
    top <= 0;
    tail_in <= 0;
    tail_out <= 0;
    transfer_over <= 0;
end
else if(next_state == READ)
begin
    input_buffer[tail_in] <= ascii_in;
    tail_in <= tail_in + 1;
end
else if(current_state == READ) // read =
begin
    input_buffer[tail_in] <= ascii_in;
    tail_in <= 0;
end
else if(next_state == TRANSFER)
begin
    if((input_buffer[tail_in] >= 8'd48 && input_buffer[tail_in] <= 8'd57) || (input_buffer[tail_in] >= 8'd97 && input_buffer[tail_in] <= 8'd102)) // number
    begin
        output_buffer[tail_out] <= input_buffer[tail_in];
        tail_out <= tail_out + 1;
        tail_in <= tail_in + 1;
    end
    else if(input_buffer[tail_in] == 8'd42) // *
    begin
        if(top > 0 && stack[top-1] == 8'd42) // precedence is equal
        begin
            top <= top - 1;
            output_buffer[tail_out] <= 8'd42;
            tail_out <= tail_out + 1;
        end
        else
        begin
            stack[top] <= 8'd42;
            top <= top + 1;
            tail_in <= tail_in + 1;
        end
    end
    else if(input_buffer[tail_in] == 8'd43 || input_buffer[tail_in] == 8'd45) // + or -
    begin
        if(top > 0 && stack[top-1] != 8'd40) // precedence is higher or equal and not left parenthesis 
        begin
            top <= top - 1;
            output_buffer[tail_out] <= stack[top-1];
            tail_out <= tail_out + 1;
        end
        else
        begin
            stack[top] <= input_buffer[tail_in];
            top <= top + 1;
            tail_in <= tail_in + 1;
        end
    end
    else if(input_buffer[tail_in] == 8'd40) // left parenthesis 
    begin
        stack[top] <= 8'd40;
        top <= top + 1;
        tail_in <= tail_in + 1;
    end
    else if(input_buffer[tail_in] == 8'd41) // right parenthesis 
    begin
        if(stack[top-1]==8'd40) // encounter left parenthesis 
        begin
            top <= top - 1;
            tail_in <= tail_in + 1;
        end
        else
        begin
            output_buffer[tail_out] <= stack[top-1];
            tail_out <= tail_out + 1;
            top <= top - 1;
        end
    end
    else if(input_buffer[tail_in] == 8'd61) // =
    begin
        if(top>0)
        begin
            output_buffer[tail_out] <= stack[top-1];
            tail_out <= tail_out + 1;
            top <= top - 1;
        end
        else
        begin
            output_buffer[tail_out] <= 8'd61;
            tail_out <= 0;
            top <= 0;
            transfer_over <= 1;
        end
    end
end
else if(next_state == CALCULATION)
begin
    if(output_buffer[tail_out] >= 8'd48 && output_buffer[tail_out] <= 8'd57) // 0~9
    begin
        stack[top] <= output_buffer[tail_out] - 48;
        top <= top + 1;
        tail_out <= tail_out + 1;
    end
    else if(output_buffer[tail_out] >= 8'd97 && output_buffer[tail_out] <= 8'd102) // a~f
    begin
        stack[top] <= output_buffer[tail_out] - 87;
        top <= top + 1;
        tail_out <= tail_out + 1;
    end
    else if(output_buffer[tail_out] == 8'd42) // *
    begin
        stack[top-2] <= stack[top-1] * stack[top-2];
        top <= top -1;
        tail_out <= tail_out + 1;
    end
    else if(output_buffer[tail_out] == 8'd43) // +
    begin
        stack[top-2] <= stack[top-1] + stack[top-2];
        top <= top -1;
        tail_out <= tail_out + 1;
    end
    else if(output_buffer[tail_out] == 8'd45) // -
    begin
        stack[top-2] <= stack[top-2] - stack[top-1];
        top <= top -1;
        tail_out <= tail_out + 1;
    end
end
else if(next_state == OUTPUT)
begin
    top <= 0;
    tail_in <= 0;
    tail_out <= 0;
    transfer_over <= 0;
end
end

endmodule