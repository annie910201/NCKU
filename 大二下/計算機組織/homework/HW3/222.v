module SME(clk,reset,chardata,isstring,ispattern,valid,match,match_index);
input clk;
input reset;
input [7:0] chardata;
input isstring;
input ispattern;
output reg          match;
output reg  [4:0]   match_index;
output reg          valid;

reg [7:0] string [31:0];//紀錄string陣列
reg [7:0] pattern [7:0];//紀錄pattern陣列
reg [7:0] i;//數數
reg [5:0] count_string;//用來數讀入陣列時的位置
reg [3:0] count_pattern;
reg [5:0] string_size;//陣列最終大小
reg [3:0] pattern_size;
reg [5:0] count_cp_str;//比較兩字串時當作pointer
reg [3:0] count_cp_pat;
reg front_match;//前面的字串是否一致
reg [4:0] tmp_index;//暫放match_index
reg start_op;//是否輸入^
reg end_op;//是否輸入$
reg mode;//為提取或是計算模式
reg zero_string;//是否歸零
reg zero_pat;

always @(posedge clk or posedge reset)
begin
    if(reset)
    begin
        for(i=0;i<8'd32;i=i+1)
            string[i] <= 0;
        for(i=0;i<8'd8;i=i+1)
            pattern[i] <= 0;
        match <= 0;
        match_index <= 5'b00000;
        valid <= 0;
        count_pattern <= 0 ;
        count_string <= 0 ;
        count_cp_str <= 0;
        count_cp_pat <= 0;
        front_match <= 0;
        tmp_index <= 0;
        start_op <= 0;
        end_op <= 0;
        string_size <= 0;
        pattern_size <= 0;
        mode <= 0;
        zero_string <= 0;
        zero_pat <= 0;
    end
    else
    begin
        if(isstring)
        begin
            if(!zero_string)//歸零其他位置時順遍讀入第一個數字
            begin
                count_string <= 1;
                zero_string <= 1;
                for(i=1;i<=string_size;i=i+1)
                    string[i] <= 0;
                string[0] <= chardata;
            end
            else
            begin//讀東西
                string[count_string] <= chardata ;
                count_string <= count_string + 1;
            end
        end
        else
        begin
            if(ispattern)
            begin
                if(chardata==8'h5E)//^不須讀入陣列只須判斷有沒有(反正一定在字首)
                    start_op <= 1;
                else if(chardata==8'h24)//$不須讀入陣列只須判斷有沒有(反正一定在字尾)
                    end_op <= 1;
                else
                begin
                    if(!zero_pat)//歸零其他位置時順遍讀入第一個數字
                    begin
                        count_pattern <= 1;
                        zero_pat <= 1;
                        for(i=1;i<=7;i=i+1)
                            pattern[i] <= 0;
                        pattern[0] <=chardata;
                    end
                    else
                    begin
                        pattern[count_pattern] <= chardata ;
                        count_pattern <= count_pattern + 1;
                    end
                end
                valid <= 0;//將valid及其他相關數據拉回0
                match <= 0;
                match_index <= 0;
                count_cp_pat <= 0;
                count_cp_str <= 0;
                pattern_size <=0;
                front_match <= 0;
                tmp_index <= 0;
            end
            else
            begin
                if(mode==0)//提取模式(先接收字串大小並將歸零變數拉回)
                begin
                    zero_pat <= 0;
                    zero_string <= 0;
                    string_size<= count_string;
                    pattern_size <= count_pattern;
                    mode <= mode+1;
                end
                else if(mode==1)//計算模式
                begin
                    if(count_cp_str!=string_size&& count_cp_pat!=pattern_size)//當兩指標只到patten或string字尾時跳出
                    begin
                        if((string[count_cp_str]==pattern[count_cp_pat] || pattern[count_cp_pat]==8'h2E) && (front_match || count_cp_pat ==0))//(字元一樣||是點點)&&(前面是一致的||是string的第一個字元)
                        begin
                            if(count_cp_pat==1)//此時已經有tmp_index，去判斷由其位置推估的start.end是否合理
                            begin
                                if(start_op)
                                begin
                                    if(tmp_index!=0 && string[tmp_index-1]!=8'h20)//tmp_index要不在string字首或其前面有空白
                                    begin
                                        front_match <= 0;
                                        count_cp_pat <= 0;
                                        count_cp_str <= count_cp_str;
                                    end
                                    else
                                    begin
                                        front_match <= 1;
                                        count_cp_pat <= count_cp_pat + 1;
                                        count_cp_str <= count_cp_str+1;
                                    end
                                end

                                if(end_op)
                                begin
                                    if(tmp_index+pattern_size!=count_string &&  string[tmp_index+pattern_size]!=8'h20)//tmp_index+pattern長度要不在string字尾或其最後面有空白
                                    begin
                                        front_match <= 0;
                                        count_cp_pat <= count_cp_pat + 1;
                                        count_cp_str <= count_cp_str+1;
                                    end
                                    else
                                    begin
                                        front_match <= 1;
                                        count_cp_pat <= count_cp_pat + 1;
                                        count_cp_str <= count_cp_str+1;
                                    end
                                end

                                if(!end_op && !start_op)//如果都沒有特殊符號就可以繼續找
                                begin
                                    front_match <= 1;
                                    count_cp_pat <= count_cp_pat + 1;
                                    count_cp_str <= count_cp_str+1;
                                end
                            end

                            else if(count_cp_pat==0)//須訂下tmp_index
                            begin
                                tmp_index <=count_cp_str ;
                                front_match <= 1;
                                count_cp_pat <= count_cp_pat + 1;
                                count_cp_str <= count_cp_str+1;
                            end

                            else
                            begin
                                front_match <= 1;
                                count_cp_pat <= count_cp_pat + 1;
                                count_cp_str <= count_cp_str +1;
                            end

                        end
                        else
                        begin
                            if (front_match)//若前面一致而後有字元不符合，須退回前幾格去判斷
                                count_cp_str <= count_cp_str-count_cp_pat+1;
                            else
                                count_cp_str <= count_cp_str + 1 ;
                            front_match <= 0;
                            tmp_index <= tmp_index;
                            count_cp_pat <= 0;
                        end
                    end

                    else
                    begin
                        mode <= 0 ;
                        valid <= 1;
                        start_op <= 0;
                        end_op <= 0;
                        match_index <= tmp_index ;
                        if(front_match && count_cp_pat==pattern_size)
                        begin
                            if(start_op && end_op)//有匹配到且有^跟$
                            begin
                                if((tmp_index==0 || (tmp_index>=1&& string[tmp_index-1]==8'h20))&&(tmp_index+count_pattern==count_string || string[tmp_index+count_pattern]==8'h20))
                                    match <= 1;
                                else
                                    match <= 0;
                            end

                            else//有匹配到且沒有特殊字元
                                match <= 1;
                        end
                        else//沒有匹配到
                            match <= 0;
                    end
                end
            end
        end
    end
end

endmodule
