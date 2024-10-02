`timescale 1ns / 1ps

module complete(
    input clk, reset_p,
    input [3:0] btn,
    output [3:0] com,
    output [7:0] seg_7,
    output [15:0] led_debug);

    wire fan_off;

    cook_timer_top cook(
        .clk(clk), .reset_p(reset_p), .btn(btn[3:0]),
        .com(com), .seg_7(seg_7), .led_debug(led_debug), .fan_off(fan_off));
endmodule