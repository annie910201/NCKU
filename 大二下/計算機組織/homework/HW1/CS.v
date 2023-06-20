`timescale 1ns/10ps

module CS(Y, X, reset, clk);

input clk, reset;
input [7:0] X;
output reg [9:0] Y;//remember to set reg

reg [11:0] Xapp;
reg [7:0] X_array [8:0];//save 9 numbers
reg [3:0] i;//to count 9
reg [10:0] sum;//the sum of 9 number

always@(posedge clk or posedge reset)
begin
    if(reset)//reset all variables
    begin
        for(i=0;i<4'b1001;i=i+1)
            X_array[i] <= 0;
        i <= 0;
        sum <= 0;
        Y <= 0;
        Xapp <= 0;
    end
    else
    begin
        for(i=0;i<4'b1000;i=i+1)
            X_array[i] <= X_array[i+1] ;//put every number to front, delete the first, and add last
        X_array[8] <= X;//use new number to replace
        sum <= sum+X-X_array[0];//delete X_series[0] and add new X
    end
end

always@(*)
begin
    Xapp=0;//remember to initialize
    for(i=0;i<4'b1001;i=i+1)
    begin
        if((X_array[i] <= sum/9) && (X_array[i] > Xapp))//find the number which is biggest number of 9 numbers and smaller than average
            Xapp=X_array[i];
        else
            Xapp = Xapp;
    end
    Y=(sum+(Xapp<<3)+Xapp)>>3;//the devidor is 9-1=8//use shift is fast
end




endmodule



