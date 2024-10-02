`timescale 1ns / 1ps

module loadable_watch_top(
    input clk, reset_p,
    input [2:0] btn,
    output [3:0] com,
    output [7:0] seg_7);
    
    wire btn_mode;
    wire btn_sec;
    wire btn_min;
    wire set_watch;    
    wire inc_sec, inc_min;
    wire clk_usec, clk_msec, clk_sec, clk_min;
    
    
    
    button_cntr btn0(.clk(clk), .reset_p(reset_p), .btn(btn[0]), .btn_pedge(btn_mode));
    button_cntr btn1(.clk(clk), .reset_p(reset_p), .btn(btn[1]), .btn_pedge(btn_sec));
    button_cntr btn2(.clk(clk), .reset_p(reset_p), .btn(btn[2]), .btn_pedge(btn_min));
    
    T_flip_flop_p t_mode(.clk(clk), .reset_p(reset_p), .t(btn_mode), .q(set_watch));
    
    wire watch_load_en, set_load_en;
    edge_detector_n ed_source(
        .clk(clk), .reset_p(reset_p), .cp(set_watch),
        .n_edge(watch_load_en), .p_edge(set_load_en));
    
    assign inc_sec = set_watch ? btn_sec : clk_sec;
    assign inc_min = set_watch ? btn_min : clk_min;

    clock_div_100 usec_clk(.clk(clk), .reset_p(reset_p), .clk_div_100(clk_usec));
    clock_div_1000 msec_clk(.clk(clk), .reset_p(reset_p), 
        .clk_source(clk_usec), .clk_div_1000(clk_msec));
    clock_div_1000 sec_clk(.clk(clk), .reset_p(reset_p), 
        .clk_source(clk_msec), .clk_div_1000_nedge(clk_sec));
    clock_div_60 min_clk(.clk(clk), .reset_p(reset_p), 
        .clk_source(inc_sec), .clk_div_60_nedge(clk_min));
        
    loadable_counter_bcd_60 sec_watch(
        .clk(clk), .reset_p(reset_p),
        .clk_time(clk_sec),
        .load_enable(watch_load_en),
        .load_bcd1(set_sec1), .load_bcd10(set_sec10),
        .bcd1(watch_sec1), .bcd10(watch_sec10));
    loadable_counter_bcd_60 min_watch(
        .clk(clk), .reset_p(reset_p),
        .clk_time(clk_min),
        .load_enable(watch_load_en),
        .load_bcd1(set_min1), .load_bcd10(set_min10),
        .bcd1(watch_min1), .bcd10(watch_min10));
        
    loadable_counter_bcd_60 sec_set(
        .clk(clk), .reset_p(reset_p),
        .clk_time(btn_sec),
        .load_enable(set_load_en),
        .load_bcd1(watch_sec1), .load_bcd10(watch_sec10),
        .bcd1(set_sec1), .bcd10(set_sec10));
    loadable_counter_bcd_60 min_set(
        .clk(clk), .reset_p(reset_p),
        .clk_time(btn_min),
        .load_enable(set_load_en),
        .load_bcd1(watch_min1), .load_bcd10(watch_min10),
        .bcd1(set_min1), .bcd10(set_min10));
    wire [15:0] value, watch_value, set_value;    
    wire [3:0] watch_sec1, watch_sec10, watch_min1, watch_min10; 
    wire [3:0] set_sec1, set_sec10, set_min1, set_min10;    
    assign watch_value = {watch_min10, watch_min1, watch_sec10, watch_sec1};
    assign set_value = {set_min10, set_min1, set_sec10, set_sec1}; 
    assign value = set_watch ? set_value : watch_value;   
    fnd_cntr fnd(.clk(clk), .reset_p(reset_p), .value(value), .com(com), .seg_7(seg_7));

endmodule


module stop_watch_csec_top(
    input clk, reset_p,
    input [2:0] btn,
    output [3:0] com,
    output [7:0] seg_7,
    output led_start, led_lap);
    
    wire clk_start;
    wire start_stop;
    reg lap;
    wire clk_usec, clk_msec, clk_csec, clk_sec, clk_min;
    wire btn_start, btn_lap, btn_clear;    
    wire reset_start;
    assign clk_start = start_stop ? clk : 0;

    clock_div_100 usec_clk(.clk(clk_start), .reset_p(reset_start), .clk_div_100(clk_usec));
    clock_div_1000 msec_clk(.clk(clk_start), .reset_p(reset_start), 
        .clk_source(clk_usec), .clk_div_1000(clk_msec));
    clock_div_10_LKM(.clk(clk), .reset_p(reset_p), .clk_source(clk_msec),
        .clk_div_10_nedge(clk_csec));
    clock_div_1000 sec_clk(.clk(clk_start), .reset_p(reset_start), 
        .clk_source(clk_msec), .clk_div_1000_nedge(clk_sec));
    clock_div_60 min_clk(.clk(clk_start), .reset_p(reset_start), 
        .clk_source(clk_sec), .clk_div_60_nedge(clk_min));
    
    button_cntr btn0(.clk(clk), .reset_p(reset_p), .btn(btn[0]), .btn_pedge(btn_start));
    button_cntr btn1(.clk(clk), .reset_p(reset_p), .btn(btn[1]), .btn_pedge(btn_lap));
    button_cntr btn2(.clk(clk), .reset_p(reset_p), .btn(btn[2]), .btn_pedge(btn_clear));
    
    
    assign reset_start = reset_p | btn_clear;
    
    T_flip_flop_p t_start(.clk(clk), .reset_p(reset_start), .t(btn_start), .q(start_stop));
    assign led_start = start_stop;
    
    always @(posedge clk or posedge reset_p)begin
        if(reset_p)lap = 0;
        else begin
            if(btn_lap) lap = ~lap;
            else if(btn_clear) lap = 0;
        end
    end
    
    assign led_lap = lap;
    
    wire [3:0] min10, min1, sec10, sec1, csec10, csec1; 
    counter_bcd_100_clear_LHS(.clk(clk), .reset_p(reset_p),
       .clk_time(clk_csec), .clear(btn_clear), .bcd1(csec1), .bcd10(csec10));  
    counter_bcd_60_clear counter_sec(.clk(clk), .reset_p(reset_p), 
        .clk_time(clk_sec), .clear(btn_clear), .bcd1(sec1), .bcd10(sec10));
    counter_bcd_60_clear counter_min(.clk(clk), .reset_p(reset_p), 
        .clk_time(clk_min), .clear(btn_clear), .bcd1(min1), .bcd10(min10));
        
    reg [15:0] lap_time;
    wire [15:0] cur_time;
    assign cur_time = {sec10, sec1, csec10, csec1};
    always @(posedge clk or posedge reset_p)begin
        if(reset_p) lap_time = 0;
        else if(btn_lap) lap_time = cur_time;
        else if(btn_clear) lap_time = 0;
    end    
        
    wire [15:0] value;    
    assign value = lap ? lap_time : cur_time;   
    fnd_cntr fnd(.clk(clk), .reset_p(reset_p), .value(value), .com(com), .seg_7(seg_7));    

endmodule

module cook_timer_top(
    input clk, reset_p,
    input [3:0] btn,
    output [3:0] com,
    output [7:0] seg_7,
    output [15:0] led_debug,
    output fan_off);

    wire clk_usec, clk_msec, clk_sec, clk_min;
    clock_div_100 usec_clk(.clk(clk), .reset_p(reset_p), .clk_div_100(clk_usec));
    clock_div_1000 msec_clk(.clk(clk), .reset_p(reset_p), 
        .clk_source(clk_usec), .clk_div_1000(clk_msec));
    clock_div_1000 sec_clk(.clk(clk), .reset_p(reset_p), 
        .clk_source(clk_msec), .clk_div_1000_nedge(clk_sec));
    
    wire btn_start, btn_sec, btn_min, btn_alarm_off;
    button_cntr btn0(.clk(clk), .reset_p(reset_p), .btn(btn[0]), .btn_pedge(btn_start));
    button_cntr btn1(.clk(clk), .reset_p(reset_p), .btn(btn[1]), .btn_pedge(btn_sec));
    button_cntr btn2(.clk(clk), .reset_p(reset_p), .btn(btn[2]), .btn_pedge(btn_min));
    button_cntr btn3(.clk(clk), .reset_p(reset_p), .btn(btn[3]), .btn_pedge(btn_alarm_off));
    
    
    wire [3:0] set_min10, set_min1, set_sec10, set_sec1;
    wire [3:0] cur_min10, cur_min1, cur_sec10, cur_sec1;
    counter_bcd_60 counter_sec(.clk(clk), .reset_p(reset_p), 
        .clk_time(btn_sec), .bcd1(set_sec1), .bcd10(set_sec10));
    counter_bcd_60 counter_min(.clk(clk), .reset_p(reset_p), 
        .clk_time(btn_min), .bcd1(set_min1), .bcd10(set_min10));
        
    wire dec_clk;
    loadable_down_counter_bcd_60 cur_sec(
        .clk(clk), .reset_p(reset_p), .clk_time(clk_sec),
        .load_enable(btn_alarm_off),
        .load_bcd1(set_sec1), .load_bcd10(set_sec10),
        .bcd1(cur_sec1), .bcd10(cur_sec10), .dec_clk(dec_clk));
    loadable_down_counter_bcd_60 cur_min(
        .clk(clk), .reset_p(reset_p), .clk_time(dec_clk), 
        .load_enable(btn_alarm_off),
        .load_bcd1(set_min1), .load_bcd10(set_min10),
        .bcd1(cur_min1), .bcd10(cur_min10));
    
    wire [15:0] value, set_time, cur_time;
    
    wire [15:0] set_time_calc, cur_time_calc;
    assign set_time_calc = set_min10*600 + set_min1*60 + set_sec10*10 + set_sec1;
    assign cur_time_calc = cur_min10*600 + cur_min1*60 + cur_sec10*10 + cur_sec1;
    
    assign set_time = {set_min10, set_min1, set_sec10, set_sec1};
    assign cur_time = {cur_min10, cur_min1, cur_sec10, cur_sec1};
    
    reg start_set, alarm; 
    always @(posedge clk or posedge reset_p)begin
        if (reset_p) begin
            start_set <= 0;
            alarm <= 0;
        end
        else begin
            if (btn_alarm_off && !start_set) begin
                // Start countdown when btn_alarm_off is pressed and timer is not already started
                if (set_time != 0) begin
                    start_set <= 1;
                end
            end
            else if (cur_time == 0 && start_set) begin
                start_set <= 0;
                alarm <= 1;
            end
            else if (btn_alarm_off && start_set) begin
                // Turn off alarm when btn_alarm_off is pressed while alarm is active
                alarm <= 0;
                start_set <= 0;
            end
        end
    end
    
    assign fan_off = alarm;

    reg [15:0] led_reg;
    integer num_leds_off;
    
    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            led_reg <= 16'b1111111111111111;  // All LEDs on by default
        end
        else if (start_set) begin
            // Calculate the number of LEDs to turn off
            if (set_time != 0) begin
                num_leds_off = ((set_time_calc - cur_time_calc) * 16) / set_time_calc;
            end
            else begin
                num_leds_off = 0;
            end
            
            // Update LED state based on the number of LEDs to turn off
            led_reg = 16'b1111111111111111;  // Default: All LEDs on
            
            // Turn off LEDs based on the number of LEDs to turn off
            case (num_leds_off)
                0: led_reg = 16'b1111111111111111; // All LEDs on
                1: led_reg = 16'b1111111111111110; // 1st LED off
                2: led_reg = 16'b1111111111111100; // 2 LEDs off
                3: led_reg = 16'b1111111111111000; // 3 LEDs off
                4: led_reg = 16'b1111111111110000; // 4 LEDs off
                5: led_reg = 16'b1111111111100000; // 5 LEDs off
                6: led_reg = 16'b1111111111000000; // 6 LEDs off
                7: led_reg = 16'b1111111110000000; // 7 LEDs off
                8: led_reg = 16'b1111111100000000; // 8 LEDs off
                9: led_reg = 16'b1111111000000000; // 9 LEDs off
                10: led_reg = 16'b1111110000000000; // 10 LEDs off
                11: led_reg = 16'b1111100000000000; // 11 LEDs off
                12: led_reg = 16'b1111000000000000; // 12 LEDs off
                13: led_reg = 16'b1110000000000000; // 13 LEDs off
                14: led_reg = 16'b1100000000000000; // 14 LEDs off
                15: led_reg = 16'b1000000000000000; // 15 LEDs off
                16: led_reg = 16'b0000000000000000; // All LEDs off
                default: led_reg = 16'b1111111111111111; // All LEDs on if num_leds_off is invalid
            endcase
        end
        else begin
            led_reg <= 16'b1111111111111111;  // All LEDs on when timer is not running
        end
    end
    
    assign led_debug = led_reg;
    
    assign value = start_set ? cur_time : set_time;   
    fnd_cntr fnd(.clk(clk), .reset_p(reset_p), .value(value), .com(com), .seg_7(seg_7));  
    
endmodule