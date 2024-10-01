`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2024/07/23 12:15:08
// Design Name: 
// Module Name: tb_dht11_cntr
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module tb_dht11_cntr();

    parameter [7:0] humi_data = 8'd80;
    parameter [7:0] tmpr_data = 8'd30;
    parameter [7:0] check_sum = humi_data + tmpr_data;
    parameter [39:0] data = {humi_data, 8'b0, tmpr_data, 8'b0, check_sum};

    reg clk, reset_p;
    wire [7:0] humidity, temperature;
    tri1 dht11_data;
    reg data_buffer, wr_en;
    assign dht11_data = wr_en ? data_buffer : 'bz;
    
    dht11_cntr DUT(clk, reset_p, dht11_data, humidity, temperature);
    
    initial begin
        clk = 0;
        reset_p = 1;
        wr_en = 0;
    end
    
    always #5 clk = ~clk;
    integer i;
    initial begin
        #10;
        reset_p = 0; #10;
        wait(!dht11_data);
        wait(dht11_data);
        #20_000;
        data_buffer = 0; wr_en = 1; #80_000;
        wr_en = 0; #80_000;
        
        for(i=0;i<40;i=i+1)begin
            wr_en = 1; data_buffer = 0; #50_000;
            data_buffer = 1;
            if(data[39-i]) #70_000;
            else #29_000;
        end
        wr_en = 1; data_buffer = 0; #10;
        wr_en = 0; #10_000;
        $finish;
    end



endmodule






























