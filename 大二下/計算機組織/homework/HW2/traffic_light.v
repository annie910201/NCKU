module traffic_light (clk,rst,pass,R,G,Y);
input  clk;
input  rst;
input  pass;
output reg R;
output reg G;
output reg Y;

reg [8:0] count_green;
reg [5:0] count_non;
reg [7:0] count_yellow;
reg [8:0] count_red;
reg [2:0] mode;

always@(posedge clk or posedge rst)
begin
    if(rst)
    begin
        R <= 0;
        G <= 1;
        Y <= 0;
        count_green <= 0;
        count_non <= 0;
        count_yellow <= 0;
        count_red <= 0;
        mode <= 3'b001;
    end
    else
    begin
        if(pass && mode != 3'b001)
        begin
            count_yellow <= 0;
            count_red <= 0;
            count_green <= 0;
            mode <= 3'b001;
            G <= 1;
            R <= 0;
            Y <=0 ;
        end
        else
        begin
            case(mode)
                3'b001://green*512
                begin
                    if(count_green == 9'b111111111)
                    begin
                        count_green <= 0;
                        mode <= 3'b010;
                        G <= 0;
                        R <= 0;
                        Y <=0 ;
                    end
                    else
                    begin
                        count_green <= count_green +1;
                        G <= 1;
                        R <= 0;
                        Y <=0 ;
                    end

                end
                3'b010://non*64
                begin
                    if(count_non == 6'b111111)
                    begin
                        count_non <= 0;
                        mode <= 3'b011;
                        G <= 1;
                        R <= 0;
                        Y <=0 ;
                    end
                    else
                    begin
                        count_non <= count_non +1;
                        G <= 0;
                        R <= 0;
                        Y <= 0 ;
                    end

                end
                3'b011://green*64
                begin
                    if(count_green == 9'b000111111)
                    begin
                        count_green <= 0;
                        mode <= 3'b100;
                        G <= 0;
                        R <= 0;
                        Y <=0 ;
                    end
                    else
                    begin
                        G <= 1;
                        R <= 0;
                        Y <=0 ;
                        count_green <= count_green +1;
                    end

                end
                3'b100://non*64
                begin
                    if(count_non == 6'b111111)
                    begin
                        count_non <= 0;
                        mode <= 3'b101;
                        G <= 1;
                        R <= 0;
                        Y <=0 ;
                    end
                    else
                    begin
                        G <= 0;
                        R <= 0;
                        Y <=0 ;
                        count_non <= count_non +1;
                    end

                end
                3'b101://green*64
                begin
                    if(count_green == 9'b000111111)
                    begin
                        count_green <= 0;
                        mode <= 3'b110;
                        G <= 0;
                        R <= 0;
                        Y <=1 ;
                    end
                    else
                    begin
                        G <= 1;
                        R <= 0;
                        Y <=0 ;
                        count_green <= count_green +1;
                    end

                end
                3'b110://yellow*256
                begin
                    if(count_yellow == 8'b11111111)
                    begin
                        count_yellow <= 0;
                        mode <= 3'b111;
                        G <= 0;
                        R <= 1;
                        Y <=0;
                    end
                    else
                    begin
                        G <= 0;
                        R <= 0;
                        Y <=1 ;
                        count_yellow <= count_yellow +1;
                    end

                end
                3'b111://red*512
                begin
                    if(count_red == 9'b111111111)
                    begin
                        count_red <= 0;
                        mode <= 3'b001;
                        G <= 1;
                        R <= 0;
                        Y <=0;
                    end
                    else
                    begin
                        G <= 0;
                        R <= 1;
                        Y <=0;
                        count_red <= count_red +1;
                    end
                end
            endcase
        end
    end
end
endmodule
