`timescale 1ns / 1ps

module edge_detector_p(
    input clk, reset_p,
    input cp,
    output p_edge, n_edge);

    reg ff_cur, ff_old;
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)begin
            ff_cur <= 0;
            ff_old <= 0;
        end
        else begin
            ff_cur <= cp;
            ff_old <= ff_cur;
        end
    end
    
    assign p_edge = ({ff_cur, ff_old} == 2'b10) ? 1 : 0;
    assign n_edge = ({ff_cur, ff_old} == 2'b01) ? 1 : 0;
endmodule

module edge_detector_n(
    input clk, reset_p,
    input cp,
    output p_edge, n_edge);

    reg ff_cur, ff_old;
    always @(negedge clk or posedge reset_p)begin
        if(reset_p)begin
            ff_cur <= 0;
            ff_old <= 0;
        end
        else begin
            ff_cur <= cp;
            ff_old <= ff_cur;
        end
    end
    
    assign p_edge = ({ff_cur, ff_old} == 2'b10) ? 1 : 0;
    assign n_edge = ({ff_cur, ff_old} == 2'b01) ? 1 : 0;
endmodule

module ring_counter_fnd(
    input clk, reset_p,
    output reg [3:0] com);

    reg [20:0] clk_div = 0;
    always @(posedge clk)clk_div = clk_div + 1;
    
    wire clk_div_nedge;
    edge_detector_p ed(.clk(clk), .reset_p(reset_p), .cp(clk_div[16]), .n_edge(clk_div_nedge));

    always @(posedge clk or posedge reset_p)begin
        if(reset_p)com = 4'b1110;
        else if(clk_div_nedge)begin
            if(com == 4'b0111)com = 4'b1110;
            else com = {com[2:0], 1'b1};
        end
    end

endmodule