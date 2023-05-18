module demosaic(clk, reset, in_en, data_in, wr_r, addr_r, wdata_r, rdata_r, wr_g, addr_g, wdata_g, rdata_g, wr_b, addr_b, wdata_b, rdata_b, done);
input clk;
input reset;
input in_en;
input [7:0] data_in;
output reg wr_r;
output reg [13:0] addr_r;
output reg [7:0] wdata_r;
input [7:0] rdata_r;
output reg wr_g;
output reg [13:0] addr_g;
output reg [7:0] wdata_g;
input [7:0] rdata_g;
output reg wr_b;
output reg [13:0] addr_b;
output reg [7:0] wdata_b;
input [7:0] rdata_b;
output reg done;

reg [2:0] current_state;
reg [2:0] next_state;
parameter INIT = 0;
parameter READ = 1;
parameter GET_DATA = 2;
parameter OUTPUT = 4;
parameter FINISH = 5;

reg [9:0] tmp_r, tmp_g, tmp_b;

reg [13:0] counter;
reg [2:0] mode;

wire [13:0] up, down, left, right;
assign up = counter - 128;
assign down = counter + 128;
assign left = counter - 1;
assign right = counter + 1;

always @(posedge clk) begin
    if(reset)
        current_state <= INIT;
    else
        current_state <= next_state;
end

always @(*) begin
    case (current_state)
        INIT:
            next_state = (in_en) ? READ : INIT; 
        READ:
            next_state = (addr_g == 16383) ? GET_DATA : READ;
        GET_DATA:
            if({counter[7], counter[0]} == 2'b00 || {counter[7], counter[0]} == 2'b11)
                next_state = (mode == 3) ? OUTPUT: GET_DATA;
            else
                next_state = (mode == 5) ? OUTPUT : GET_DATA;
        OUTPUT:
            next_state = (counter == 16254) ? FINISH : GET_DATA; 
        default: 
            next_state = INIT;
    endcase
end

// wr
always @(posedge clk) begin
    if(reset)
    begin
        wr_r <= 0;
        wr_g <= 0;
        wr_b <= 0;
    end
    else if(next_state == READ)
    begin
        case({counter[7], counter[0]})
        2'b00:
        begin
            wr_g <= 1;
            wr_r <= 0;
            wr_b <= 0;
        end
        2'b01:
        begin
            wr_r <= 1;
            wr_b <= 0;
            wr_g <= 0;
        end
        2'b10:
        begin
            wr_b <= 1;
            wr_g <= 0;
            wr_r <= 0;
        end
        2'b11:
        begin
            wr_g <= 1;
            wr_r <= 0;
            wr_b <= 0;
        end
        endcase
    end
    else if(next_state == GET_DATA)
    begin
        wr_r <= 0;
        wr_g <= 0;
        wr_b <= 0;
    end
    else if(next_state == OUTPUT)
    begin
        case({counter[7], counter[0]})
        2'b00:
        begin
            wr_g <= 0;
            wr_r <= 1;
            wr_b <= 1;
        end
        2'b01:
        begin
            wr_r <= 0;
            wr_b <= 1;
            wr_g <= 1;
        end
        2'b10:
        begin
            wr_b <= 0;
            wr_g <= 1;
            wr_r <= 1;
        end
        2'b11:
        begin
            wr_g <= 0;
            wr_r <= 1;
            wr_b <= 1;
        end
        endcase
    end
end

// wdata
always @(posedge clk) begin
    if(reset)
    begin
        wdata_r <= 0;
        wdata_g <= 0;
        wdata_b <= 0;
    end
    else if(next_state == READ)
    begin
        case({counter[7], counter[0]})
        2'b00:
            wdata_g <= data_in;
        2'b01:
            wdata_r <= data_in;
        2'b10:
            wdata_b <= data_in;
        2'b11:
            wdata_g <= data_in;
        endcase
    end
    else if(next_state == OUTPUT)
    begin
        case({counter[7], counter[0]})
        2'b00:// g
        begin
            wdata_b <= tmp_b[7:0];
            wdata_r <= tmp_r[7:0];
        end
        2'b01:// r
        begin
            wdata_b <= tmp_b[7:0];
            wdata_g <= tmp_g[7:0];
        end
        2'b10:// b
        begin
            wdata_g <= tmp_g[7:0];
            wdata_r <= tmp_r[7:0];
        end
        2'b11:// g
        begin
            wdata_b <= tmp_b[7:0];
            wdata_r <= tmp_r[7:0];
        end
        endcase
    end
end

// waddr
always @(posedge clk) begin
    if(reset)
    begin
        addr_r <= 0;
        addr_g <= 0;
        addr_b <= 0;
    end 
    else if(next_state == READ)
    begin
        case({counter[7], counter[0]})
        2'b00:
            addr_g <= counter;
        2'b01:
            addr_r <= counter;
        2'b10:
            addr_b <= counter;
        2'b11:
            addr_g <= counter;
        endcase
    end
    else if(next_state == GET_DATA)
    begin
        if(mode == 0)
            case({counter[7], counter[0]})
            2'b00:// g
            begin
                addr_r <= left;
                addr_b <= up;
            end
            2'b01:// r
            begin
                addr_g <= up;
                addr_b <= counter - 129;
            end
            2'b10:// b
            begin
                addr_g<= up;
                addr_r <= counter - 129;
            end
            2'b11:// g
            begin
                addr_r <= up;
                addr_b <= left;
            end
            endcase 
        else if(mode == 1)
            case({counter[7], counter[0]})
            2'b00:// g
            begin
                addr_r <= right;
                addr_b <= down;
            end
            2'b01:// r
            begin
                addr_g <= down;
                addr_b <= counter - 127;
            end
            2'b10:// b
            begin
                addr_g<= down;
                addr_r <= counter - 127;
            end
            2'b11:// g
            begin
                addr_r <= down;
                addr_b <= right;
            end
            endcase 
        else if(mode == 2)
            case({counter[7], counter[0]})
            2'b01:// r
            begin
                addr_g <= left;
                addr_b <= counter + 127;
            end
            2'b10:// b
            begin
                addr_g<= left;
                addr_r <= counter + 127;
            end
            endcase
        else if(mode == 3)
            case({counter[7], counter[0]})
            2'b01:// r
            begin
                addr_g <= right;
                addr_b <= counter + 129;
            end
            2'b10:// b
            begin
                addr_g<= right;
                addr_r <= counter + 129;
            end
            endcase 
    end
    else if(next_state == OUTPUT)
    begin
        addr_b <= counter;
        addr_g <= counter;
        addr_r <= counter;
    end
end

// tmp_r, tmp_g, tmp_b
always @(posedge clk) begin
    if(reset)
    begin
        tmp_b <= 0;
        tmp_g <= 0;
        tmp_r <= 0;
    end
    else if(current_state == GET_DATA && mode == 1)
        case({counter[7], counter[0]})
        2'b00:// g
        begin
            tmp_b <= rdata_b;
            tmp_r <= rdata_r;
        end
        2'b01:// r
        begin
            tmp_g <= rdata_g;
            tmp_b <= rdata_b;
        end
        2'b10:// b
        begin
            tmp_g <= rdata_g;
            tmp_r <= rdata_r;
        end
        2'b11:// g
        begin
            tmp_r <= rdata_r;
            tmp_b <= rdata_b;
        end
        endcase 
    else if(current_state == GET_DATA && (mode == 2 || mode == 3))
        case({counter[7], counter[0]})
        2'b00:// g
        begin
            tmp_b <= (rdata_b + tmp_b)>>1;
            tmp_r <= (rdata_r + tmp_r)>>1;
        end
        2'b01:// r
        begin
            tmp_g <= rdata_g + tmp_g;
            tmp_b <= rdata_b + tmp_b;
        end
        2'b10:// b
        begin
            tmp_g <= rdata_g + tmp_g;
            tmp_r <= rdata_r + tmp_r;
        end
        2'b11:// g
        begin
            tmp_r <= (rdata_r + tmp_r)>>1;
            tmp_b <= (rdata_b + tmp_b)>>1;
        end
        endcase 
    else if(current_state == GET_DATA &&mode == 4)
        case({counter[7], counter[0]})
        2'b01:// r
        begin
            tmp_g <= (rdata_g + tmp_g)>>2;
            tmp_b <= (rdata_b + tmp_b)>>2;
        end
        2'b10:// b
        begin
            tmp_g <= (rdata_g + tmp_g)>>2;
            tmp_r <= (rdata_r + tmp_r)>>2;
        end
        endcase 
end

// counter
always @(posedge clk) begin
    if(reset)
        counter <= 0;
    else if(current_state == READ && next_state == GET_DATA)
        counter <= 129;
    else if(next_state == READ || current_state == READ)
        counter <= counter + 1;
    else if(current_state == OUTPUT && counter[6:0] == 7'd126)
        counter <= counter + 3;
    else if(current_state == OUTPUT)
        counter <= counter + 1;
    
end

// mode
always @(posedge clk) begin
    if(reset)
        mode <= 0;
    else if(current_state == GET_DATA)
        mode <= mode + 1;
    else if(current_state == OUTPUT)
        mode <= 0;
    
end

// done
always @(posedge clk) begin
    if(reset)
        done <= 0;
    else if(next_state ==FINISH)
        done <= 1;
end

endmodule
