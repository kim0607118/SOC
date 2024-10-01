`timescale 1ns / 1ps

module T_flip_flop_p(
    input clk, reset_p,
    input t,
    output reg q);

    always @(posedge clk or posedge reset_p)begin
        if(reset_p)q = 0;
        else begin
            if(t) q = ~q;
            else q = q;
        end
    end
endmodule

module T_flip_flop_n(
    input clk, reset_p,
    input t,
    output reg q);

    always @(negedge clk or posedge reset_p)begin
        if(reset_p)q = 0;
        else begin
            if(t) q = ~q;
            else q = q;
        end
    end
endmodule

module up_counter_asyc(
    input clk, reset_p,
    output [3:0] count);

    T_flip_flop_n T0(.clk(clk), .reset_p(reset_p), .t(1), .q(count[0]));
    T_flip_flop_n T1(.clk(count[0]), .reset_p(reset_p), .t(1), .q(count[1]));
    T_flip_flop_n T2(.clk(count[1]), .reset_p(reset_p), .t(1), .q(count[2]));
    T_flip_flop_n T3(.clk(count[2]), .reset_p(reset_p), .t(1), .q(count[3]));

endmodule

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

module clock_div_100(
    input clk, reset_p,
    output clk_div_100,
    output clk_div_100_nedge);
    
    reg [6:0] cnt_sysclk;
    
    always @(negedge clk or posedge reset_p)begin
        if(reset_p)cnt_sysclk = 0;
        else begin
            if(cnt_sysclk >= 99) cnt_sysclk = 0;
            else cnt_sysclk = cnt_sysclk + 1;
        end
    end
    
    assign clk_div_100 = (cnt_sysclk < 50) ? 0 : 1;
    
    edge_detector_n ed(
        .clk(clk), .reset_p(reset_p), .cp(clk_div_100),
        .n_edge(clk_div_100_nedge));
endmodule

module clock_div_1000(
    input clk, reset_p,
    input clk_source,
    output clk_div_1000,
    output clk_div_1000_nedge);
    
    reg [9:0] cnt_clksource;
    
    wire clk_source_nedge;
    edge_detector_n ed_source(
        .clk(clk), .reset_p(reset_p), .cp(clk_source),
        .n_edge(clk_source_nedge));
    
    always @(negedge clk or posedge reset_p)begin
        if(reset_p)cnt_clksource = 0;
        else if(clk_source_nedge)begin
            if(cnt_clksource >= 999) cnt_clksource = 0;
            else cnt_clksource = cnt_clksource + 1;
        end
    end
    
    assign clk_div_1000 = (cnt_clksource < 500) ? 0 : 1;
    
    edge_detector_n ed(
        .clk(clk), .reset_p(reset_p), .cp(clk_div_1000),
        .n_edge(clk_div_1000_nedge));
endmodule

module clock_div_60(
    input clk, reset_p,
    input clk_source,
    output clk_div_60,
    output clk_div_60_nedge);
    
    reg [5:0] cnt_clksource;
    
    wire clk_source_nedge;
    edge_detector_n ed_source(
        .clk(clk), .reset_p(reset_p), .cp(clk_source),
        .n_edge(clk_source_nedge));
    
    always @(negedge clk or posedge reset_p)begin
        if(reset_p)cnt_clksource = 0;
        else if(clk_source_nedge)begin
            if(cnt_clksource >= 59) cnt_clksource = 0;
            else cnt_clksource = cnt_clksource + 1;
        end
    end
    
    assign clk_div_60 = (cnt_clksource < 30) ? 0 : 1;
    
    edge_detector_n ed(
        .clk(clk), .reset_p(reset_p), .cp(clk_div_60),
        .n_edge(clk_div_60_nedge));
endmodule

module clock_div_10_LKM(   // 10ë¶„ì£¼
    input clk, reset_p,
    input clk_source,
    output clk_div_10,
    output clk_div_10_nedge);

    reg [3:0] cnt_clksource;    // 10ê¹Œì? ?„¸ê¸? ?œ„?•´ 3ë¹„íŠ¸(16) ì¤?

    wire clk_source_nedge;
    edge_detector_n ed_source(
        .clk(clk), .reset_p(reset_p), .cp(clk_source),
        .n_edge(clk_source_nedge));

    always @(negedge clk or posedge reset_p)begin
        if(reset_p)cnt_clksource = 0;
        else if(clk_source_nedge)begin
            if(cnt_clksource >= 9) cnt_clksource = 0;
            else cnt_clksource = cnt_clksource + 1;
        end
    end

    assign clk_div_10 = (cnt_clksource < 5) ? 0 : 1;

    edge_detector_n ed(
        .clk(clk), .reset_p(reset_p), .cp(clk_div_10),
        .n_edge(clk_div_10_nedge));

endmodule

module counter_bcd_60(
    input clk, reset_p,
    input clk_time,
    output reg [3:0] bcd1, bcd10);

    wire clk_time_nedge;
    edge_detector_n ed_clk(
        .clk(clk), .reset_p(reset_p), .cp(clk_time),
        .n_edge(clk_time_nedge));
        
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)begin
            bcd1 = 0;
            bcd10 = 0;
        end
        else if(clk_time_nedge)begin
            if(bcd1 >= 9)begin
                bcd1 = 0;
                if(bcd10 >= 5)bcd10 = 0;
                else bcd10 = bcd10 + 1;
            end
            else bcd1 = bcd1 + 1;
        end  
    end

endmodule

module counter_bcd_60_clear(
    input clk, reset_p,
    input clk_time,
    input clear,
    output reg [3:0] bcd1, bcd10);

    wire clk_time_nedge;
    edge_detector_n ed_clk(
        .clk(clk), .reset_p(reset_p), .cp(clk_time),
        .n_edge(clk_time_nedge));
        
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)begin
            bcd1 = 0;
            bcd10 = 0;
        end
        else begin
            if(clear)begin
                bcd1 = 0;
                bcd10 = 0;
            end
            else if(clk_time_nedge)begin
                if(bcd1 >= 9)begin
                    bcd1 = 0;
                    if(bcd10 >= 5)bcd10 = 0;
                    else bcd10 = bcd10 + 1;
                end
                else bcd1 = bcd1 + 1;
            end
        end  
    end

endmodule

module counter_bcd_100_clear_LHS(
       input clk, reset_p,
       input clk_time,
       input clear, // ì¶”ê?
       output reg[3:0] bcd1, bcd10);

       wire clk_time_nedge;
       edge_detector_n ed_clk(
            .clk(clk), .reset_p(reset_p), .cp(clk_time),
            .n_edge(clk_time_nedge));

       always @(posedge clk or posedge reset_p)begin 
              if(reset_p)begin
                   bcd1 = 0;
                   bcd10 = 0;
              end
              else begin
                   if(clear)begin // ì¶”ê? clearê°? 1?¼?•Œ bcd1,bcd10 = 0 ?œ¼ë¡? ì´ˆê¸°?™”
                        bcd1 = 0;
                        bcd10 = 0;
                   end
                  else if(clk_time_nedge)begin 
                        if(bcd1 >= 9 ) begin
                            bcd1 = 0;
                            if(bcd10 >= 9) bcd10 = 0; // 60ì§„ìˆ˜?´?‹ˆê¹? 6ë³´ë‹¤ ?¬ë©? 0?œ¼ë¡? ì´ˆê¸°?™” 
                            else bcd10 = bcd10 + 1; // ê·? ?´?™¸?—?Š” 1?”© ì¦ê??•œ?‹¤.
                        end
                        else bcd1 = bcd1 +1;
                  end
             end
       end
endmodule

module loadable_counter_bcd_60(
    input clk, reset_p,
    input clk_time,
    input load_enable,
    input [3:0] load_bcd1, load_bcd10,
    output reg [3:0] bcd1, bcd10);

    wire clk_time_nedge;
    edge_detector_n ed_clk(
        .clk(clk), .reset_p(reset_p), .cp(clk_time),
        .n_edge(clk_time_nedge));
        
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)begin
            bcd1 = 0;
            bcd10 = 0;
        end
        else begin
            if(load_enable)begin
                bcd1 = load_bcd1;
                bcd10 = load_bcd10;
            end
            else if(clk_time_nedge)begin
                if(bcd1 >= 9)begin
                    bcd1 = 0;
                    if(bcd10 >= 5)bcd10 = 0;
                    else bcd10 = bcd10 + 1;
                end
                else bcd1 = bcd1 + 1;
            end
        end  
    end

endmodule

module loadable_down_counter_bcd_60(
    input clk, reset_p,
    input clk_time,
    input load_enable,
    input [3:0] load_bcd1, load_bcd10,
    output reg [3:0] bcd1, bcd10,
    output reg dec_clk);

    wire clk_time_nedge;
    edge_detector_n ed_clk(
        .clk(clk), .reset_p(reset_p), .cp(clk_time),
        .n_edge(clk_time_nedge));
        
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)begin
            bcd1 = 0;
            bcd10 = 0;
            dec_clk = 0;
        end
        else begin
            if(load_enable)begin
                bcd1 = load_bcd1;
                bcd10 = load_bcd10;
            end
            else if(clk_time_nedge)begin
                if(bcd1 == 0)begin
                    bcd1 = 9;
                    if(bcd10 == 0)begin
                        bcd10 = 5;
                        dec_clk = 1;
                    end
                    else bcd10 = bcd10 - 1;
                end
                else bcd1 = bcd1 - 1; 
            end
            else dec_clk = 0;
        end  
    end

endmodule