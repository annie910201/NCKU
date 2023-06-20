module image_processor#(
    parameter DATA_WIDTH = 12,
    parameter ADDR_WIDTH = 19,
    parameter DATA_LENGTH = 120000 //400 * 300
    )(
    input           clk_p,
    input           rst,
    output 	 reg	[ADDR_WIDTH-1:0]	w_addr,
    output   reg    [ADDR_WIDTH-1:0]    o_addr,
    input 			[DATA_WIDTH-1:0]	data_in,
    output 	 reg	[DATA_WIDTH-1:0]	data_out,
    output   reg    output_valid,
    input           [1:0]               cmd,
    output   reg all_ready
    );
    /************parameter description:******************************************************************************
       *    1. Read data from "bram IP" ,which contains the image data from SDK
       *        w_addr : assign address to bram_IP
       *        data_in : after assigning the parameter w_addr, you'll get the corrresponding data from bram_IP
       *        
       *    2. Write data to "memory_for_prcossing IP"
       *        output_valid : Let 'output_valid' be "High" when you want to output data
       *        o_addr :  assign address to "memory_for_prcossing IP"
       *        data_out : output the corresponding pixel value
       *       
       *    3. Control 
       *        cmd : you can use this parameter to decide what image_processing method you want to use
       ********************************************************************************************************/

    reg [9:0] ready_count;
    reg ready;

    reg [2:0] current_state;
    reg [2:0] next_state;
    parameter INIT = 0;
    parameter READ_GRAY = 1;
    parameter CHECK_LOC = 2;
    parameter GET_TWO = 3;
    parameter GET_SIX = 4;
    parameter WRITE_RES = 5;
    parameter SHOW_INTERLACE = 6;
    parameter FINISH = 7;
    reg even_row;

    reg [9:0] counter;
    reg [ADDR_WIDTH-1:0] location;
    reg [2:0] count_neighbor;
    reg [3:0] d1, d2, d3;
    reg [3:0] gray;
    reg [4:0] sum1, sum2, sum3;
    reg change;
    reg [1:0] cmd_use;

    /* Init System */
    always@(posedge clk_p)begin
        if (rst) begin
           ready_count <= 0;
           ready <= 0;
        end
        else begin
          if (ready_count==10'b1111111111)begin
            ready <= 1;
          end
          else begin
            ready_count <= ready_count + 1;
          end
        end
    end
    

    /* FSM */
    always @(posedge clk_p) begin
        if (rst) 
            current_state <= INIT;
        else 
            current_state <= next_state;
    end

    /* Next-state logic */
    always @(*) begin
        case (current_state)
            INIT: 
                next_state = (ready)?READ_GRAY:INIT;
            READ_GRAY:
                next_state =  (o_addr == DATA_LENGTH -1)?CHECK_LOC:READ_GRAY;
            CHECK_LOC:
                if(cmd_use == 2'd0) // cmd == 0, 原圖
                    next_state = FINISH;
                else if(cmd_use == 2'd1) // cmd == 1, interlaced 
                    next_state = SHOW_INTERLACE;
                else// else => ELA圖
                    next_state = (counter == 0 || counter == 399) ? GET_TWO : GET_SIX;
            GET_SIX:
                next_state = (count_neighbor == 3'd7)?WRITE_RES:GET_SIX;
            GET_TWO:
                next_state = (count_neighbor == 3'd3)?WRITE_RES:GET_TWO;
            WRITE_RES:
                next_state = (o_addr == DATA_LENGTH - 401 /*倒數第二排最右邊座標*/)?FINISH:CHECK_LOC;
            SHOW_INTERLACE:
                next_state = (o_addr == DATA_LENGTH -1)?FINISH:SHOW_INTERLACE;
            FINISH:
                next_state = (change)? INIT:FINISH;
            default:
                next_state = INIT;
        endcase
    end
    
    /* Processing */

    // change
    always @(posedge clk_p) begin
        if(rst) begin
            change <= 0;
            cmd_use <= 0;
        end
        else begin
            cmd_use <= cmd;
            if(cmd_use != cmd)
                change <= 1;
            else 
                change <= 0;
        end
    end
    // w_addr
    always @(posedge clk_p) begin
        if(rst)
            w_addr <= 0;
        else if(current_state == READ_GRAY)
            w_addr <= w_addr +1;
        else if(next_state == GET_TWO) begin
            case (count_neighbor)
                3'd0:
                    w_addr <= location - 400;//b
                3'd1:
                    w_addr <= location + 400;//e
            endcase
        end
        else if(next_state == GET_SIX) begin
            case (count_neighbor)
                3'd0:
                    w_addr <= location - 401;//a
                3'd1:
                    w_addr <= location + 401;//f
                3'd2:
                    w_addr <= location - 400;//b
                3'd3:
                    w_addr <= location + 400;//e
                3'd4:
                    w_addr <= location - 399;//c
                3'd5:
                    w_addr <= location + 399;//d
            endcase
        end
        else if(current_state == CHECK_LOC && next_state == SHOW_INTERLACE)
            w_addr <= 0;
        else if(current_state == SHOW_INTERLACE)
            w_addr <= w_addr +1;
    end

    // o_addr
    always @(posedge clk_p) begin
    if(rst)
        o_addr <= 0;
    else if(current_state == READ_GRAY)
        o_addr <= w_addr;
    else if(next_state == WRITE_RES)
        o_addr <= location;
    else if(current_state == CHECK_LOC && next_state == SHOW_INTERLACE)
        o_addr <= 0;
    else if(current_state == SHOW_INTERLACE)
        o_addr <= w_addr;
    end

    // output_valid
    always @(posedge clk_p) begin
    if(rst)
        output_valid <= 0;
    else if(current_state == READ_GRAY)
        output_valid <= 1;
    else if(next_state == WRITE_RES)
        output_valid <= 1;
    else if(current_state ==SHOW_INTERLACE)
        output_valid <= 1;
    else 
        output_valid <= 0;
    end

    // data_out
    always @(posedge clk_p) begin
    if(rst)
        data_out <= 0;
    else if(current_state == READ_GRAY)
        data_out <= data_in;
    else if(next_state == WRITE_RES)begin
        if(current_state == GET_TWO)
            data_out <= {sum1[3:0], sum1[3:0],sum1[3:0]} ;
        else begin //GET_SIX
            if(d2 <= d1 && d2 <= d3)
			    data_out <= {sum2[3:0], sum2[3:0],sum2[3:0]} ;
            else if(d1 <= d3)
                data_out <= {sum1[3:0], sum1[3:0],sum1[3:0]} ;
            else
                data_out <= {sum3[3:0], sum3[3:0],sum3[3:0]} ;
        end
    end
    else if(current_state == SHOW_INTERLACE)
        if(even_row)
            data_out <= {gray, gray, gray};
        else
            data_out <= 0;
    end

    // even_row
    always @(posedge clk_p) begin
    if(rst)
        even_row <= 1;
    else if(current_state == SHOW_INTERLACE && counter == 10'd399)
        even_row = ~even_row;
    end

    // counter
    always @(posedge clk_p) begin
    if(rst)
        counter <= 0;
    else if(current_state == WRITE_RES && counter != 399)
        counter <= counter+1;
    else if(current_state == WRITE_RES && counter == 399)
        counter <= 0;
    else if(current_state == CHECK_LOC && next_state == SHOW_INTERLACE)
        counter <= 0;
    else if(current_state == SHOW_INTERLACE && counter != 399)
        counter <= counter+1;
    else if(current_state == SHOW_INTERLACE && counter == 399)
        counter <= 0;
    end

    // count_neighbor
    always @(posedge clk_p) begin
    if(rst)
        count_neighbor <= 0;
    else if(next_state == GET_SIX || next_state == GET_TWO)
        count_neighbor <= count_neighbor + 1;
    else if(current_state == WRITE_RES)
        count_neighbor <= 0;
    end

    // location
    always @(posedge clk_p) begin
    if(rst)
        location <= 400;
    else if(current_state == WRITE_RES && counter != 399)
        location <= location +1;
    else if(current_state == WRITE_RES && counter == 399)
        location <= location + 401;
    end
    wire [3:0] R = data_in[3:0] >>2;// 0.299
    wire [3:0] G = data_in[7:4] >>1;//0.587
    wire [3:0] B = data_in[11:8] >>3;// 0.114
    // gray
    always @(posedge clk_p) begin
    if(rst)
        gray <= 0;
    else if(current_state == SHOW_INTERLACE)
        gray <= R + G + B ;
    end

    // d1, d2, d3, sum1, sum2, sum3
    always @(posedge clk_p) begin
    if(rst)begin
        d1 <= 0;
        d2 <= 0;
        d3 <= 0;
        sum1 <= 0;
        sum2 <=0;
        sum3 <= 0;
    end
    else if(current_state == GET_TWO) begin
        if(count_neighbor == 1)
		    sum1 <= data_in[3:0];
	    else if(count_neighbor == 2)
		    sum1 <= (data_in[3:0] + sum1)>>1;
    end
    else if(current_state == GET_SIX)
    begin
        case (count_neighbor)
            3'd1:
                d1 <= data_in[3:0];
            3'd2:
            begin
                sum1 <= (d1 + data_in[3:0])>>1;
                d1 <= (d1 >= data_in[3:0])? d1 - data_in[3:0] : data_in[3:0] - d1;
            end
            3'd3:
                d2 <= data_in[3:0];
            3'd4:
            begin
                sum2 <= (d2 + data_in[3:0])>>1;
                d2 <= (d2 >= data_in[3:0])? d2 - data_in[3:0] : data_in[3:0] - d2;
            end
            3'd5:
                d3 <= data_in[3:0];
            3'd6:
            begin
                sum3 <= (d3 + data_in[3:0])>>1;
                d3 <= (d3 >= data_in[3:0])? d3 - data_in[3:0] : data_in[3:0] - d3;
            end
        endcase
    end
    end

    // all_ready
    always @(posedge clk_p) begin
        if(rst)
            all_ready <= 0;
        else if(next_state == FINISH)
            all_ready <= 1;
    end
    
endmodule
