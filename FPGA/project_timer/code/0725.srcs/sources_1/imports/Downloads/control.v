module button_cntr(
    input clk, reset_p,
    input btn,
    output btn_pedge, btn_nedge);

    reg [20:0] clk_div = 0;
    always @(posedge clk)clk_div = clk_div + 1;
    
    wire clk_div_nedge;
    edge_detector_p ed_clk(.clk(clk), .reset_p(reset_p), 
        .cp(clk_div[16]), .n_edge(clk_div_nedge));

    reg debounced_btn;
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)debounced_btn = 0;
        else if(clk_div_nedge)debounced_btn = btn;
    end
    
    edge_detector_p ed_btn(.clk(clk), .reset_p(reset_p), 
        .cp(debounced_btn), .n_edge(btn_nedge), .p_edge(btn_pedge));

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

module fnd_cntr(
    input clk, reset_p,
    input [15:0] value,
    output [3:0] com,
    output [7:0] seg_7);
    
    ring_counter_fnd rc(clk, reset_p, com);
    
    reg [3:0] hex_value;
    always @(posedge clk)begin
        case(com)
            4'b1110: hex_value = value[3:0];
            4'b1101: hex_value = value[7:4];
            4'b1011: hex_value = value[11:8];
            4'b0111: hex_value = value[15:12];
        endcase
    end
    
    decoder_7seg dec_7seg(.hex_value(hex_value), .seg_7(seg_7));
endmodule

module decoder_7seg(
    input [3:0] hex_value,
    output reg [7:0] seg_7);

    always @(hex_value)begin
        case(hex_value)
            //              abcd_efgp
            0  : seg_7 = 8'b0000_0011;  // 0
            1  : seg_7 = 8'b1001_1111;  // 1
            2  : seg_7 = 8'b0010_0101;  // 2
            3  : seg_7 = 8'b0000_1101;  // 3
            4  : seg_7 = 8'b1001_1001;  // 4
            5  : seg_7 = 8'b0100_1001;  // 5
            6  : seg_7 = 8'b0100_0001;  // 6
            7  : seg_7 = 8'b0001_1111;  // 7
            8  : seg_7 = 8'b0000_0001;  // 8
            9  : seg_7 = 8'b0000_1001;  // 9
            10 : seg_7 = 8'b0000_0101;  // a
            11 : seg_7 = 8'b1100_0001;  // b
            12 : seg_7 = 8'b0110_0011;  // C
            13 : seg_7 = 8'b1000_0101;  // d
            14 : seg_7 = 8'b0110_0001;  // E
            15 : seg_7 = 8'b0111_0001;  // F
        endcase
    end

endmodule