`timescale 1ns / 1ps

// UART �۽ű�
module uart_tx(
    input clk,             // FPGA Ŭ��
    input reset,           // ���� ��ȣ
    input [7:0] data_in,   // ������ ������
    input send,            // ���� Ʈ����
    output reg tx,         // UART ���� ��
    output reg busy        // ���� �� ����
);
    parameter CLK_FREQ = 100_000_000; // Ŭ�� ���ļ� (100MHz)
    parameter BAUD_RATE = 9600;       // UART ���� �ӵ�
    parameter BIT_PERIOD = CLK_FREQ / BAUD_RATE; // �� ��Ʈ�� ���� �ֱ�

    reg [3:0] bit_index;    // ���� ���� ���� ��Ʈ�� �ε���
    reg [15:0] baud_count;  // ��Ʈ ������ ���� ī����
    reg [9:0] tx_shift_reg; // �����Ϳ� ��ŸƮ, ���� ��Ʈ�� ������ 10��Ʈ ��������

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            tx <= 1;         // �⺻ ����
            busy <= 0;       // ���� ���� ���� �ƴ�
            baud_count <= 0;
            bit_index <= 0;
            tx_shift_reg <= 10'b1111111111; // �⺻ ����
        end else if (send && !busy) begin
            tx_shift_reg <= {1'b1, data_in, 1'b0}; // �����Ϳ� ��ŸƮ ��Ʈ, ���� ��Ʈ
            busy <= 1;
            bit_index <= 0; // ��Ʈ �ε��� �ʱ�ȭ
        end else if (busy) begin
            if (baud_count < BIT_PERIOD - 1) begin
                baud_count <= baud_count + 1;
            end else begin
                baud_count <= 0;
                tx <= tx_shift_reg[0];
                tx_shift_reg <= {1'b1, tx_shift_reg[9:1]}; // ��Ʈ ����Ʈ
                if (bit_index < 9) begin
                    bit_index <= bit_index + 1;
                end else begin
                    busy <= 0; // ���� �Ϸ�
                    bit_index <= 0;
                end
            end
        end
    end
endmodule

//----------------------------------------------------------------------------------------------------------------------------------------

module uart_rx (
    input clk, reset_p,
    input rx,                 // UART ���� �� (HC-06�� TX �ɿ� ����)
    output reg [7:0] data_out, // ���ŵ� ������
    output reg received       // ������ ���� �Ϸ� ��ȣ
);

    parameter CLKS_PER_BIT = 10417; // 100MHz / 9600 baud rate
    parameter CLKS_PER_HALF_BIT = CLKS_PER_BIT / 2;

    reg [3:0] state;
    reg [15:0] clock_count;
    reg [2:0] bit_index;
    reg [7:0] rx_data;

    parameter IDLE = 4'b0000;
    parameter START_BIT = 4'b0001;
    parameter DATA_BITS = 4'b0010;
    parameter STOP_BIT = 4'b0011;
    parameter CLEANUP = 4'b0100;

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            state <= IDLE;
            received <= 1'b0;
            data_out <= 8'h00;
            clock_count <= 0;
            bit_index <= 0;
        end
            else begin
                case (state)
                    IDLE: begin
                        received <= 1'b0;
                        clock_count <= 0;
                        bit_index <= 0;
                        
                        if (rx == 1'b0) begin
                            state <= START_BIT;
                        end
                    end
                    START_BIT: begin
                        if (clock_count == CLKS_PER_HALF_BIT) begin
                            if (rx == 1'b0) begin
                                clock_count <= 0;
                                state <= DATA_BITS;
                            end
                                else begin
                                    state <= IDLE;
                                end
                        end
                            else begin
                                clock_count <= clock_count + 1;
                            end
                    end
                    DATA_BITS: begin
                        if (clock_count < CLKS_PER_BIT - 1) begin
                            clock_count <= clock_count + 1;
                        end
                            else begin
                                clock_count <= 0;
                                rx_data[bit_index] <= rx;
                                if (bit_index < 7) begin
                                    bit_index <= bit_index + 1;
                                end
                                    else begin
                                        bit_index <= 0;
                                        state <= STOP_BIT;
                                    end
                            end
                    end
                    STOP_BIT: begin
                        if (clock_count < CLKS_PER_BIT - 1) begin
                            clock_count <= clock_count + 1;
                        end
                            else begin
                                received <= 1'b1;
                                data_out <= rx_data;
                                state <= CLEANUP;
                            end
                    end
                    CLEANUP: begin
                        state <= IDLE;
                        received <= 1'b0;
                    end
                    default: state <= IDLE;
                endcase
            end
    end
endmodule

// �ֻ��� TOP Module-----------------------------------------------------------------------------------------------------------------------
module SOC_check_top(
    input clk,              // 100 MHz Ŭ��
    input reset_p,        // switch ���� ��ȣ
    input [4:0] btn,        // 4���� ��ư �Է�
    output tx,              // UART �۽� ��
    input rx,               // UART ���� ��
    output [3:0] com,       // 7-���׸�Ʈ ���� ĳ�ҵ� ����
    output [7:0] seg_7,     // 7-���׸�Ʈ ���׸�Ʈ ����
    output reg [15:0] led   // LED ���
);

    // ��ư ���� ���� ��ȣ
    wire btn_up, btn_left, btn_right, btn_down;     // ��ư ���� ���� ��ȣ
    wire [15:0] value;                              // ǥ���� 16��Ʈ ��
    reg [3:0] digit [0:3];                          // 4���� 4��Ʈ �ڸ��� �迭
    reg [1:0] sel_digit;                            // ���� ���õ� �ڸ���
    // FND ���� ������ ��������
    reg [15:0] save_fnd_value;

    // ��ư ���� ���� ��� �ν��Ͻ�ȭ
    button_cntr btn0_counter(.clk(clk), .reset_p(reset_p), .btn(btn[0]), .btn_pedge(btn_set));
    button_cntr btn1_counter(.clk(clk), .reset_p(reset_p), .btn(btn[1]), .btn_pedge(btn_up));
    button_cntr btn2_counter(.clk(clk), .reset_p(reset_p), .btn(btn[2]), .btn_pedge(btn_left));
    button_cntr btn3_counter(.clk(clk), .reset_p(reset_p), .btn(btn[3]), .btn_pedge(btn_right));
    button_cntr btn4_counter(.clk(clk), .reset_p(reset_p), .btn(btn[4]), .btn_pedge(btn_down));

    // ��ư�� ������ ���ڸ� �����ϴ� ����
    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            digit[0] <= 4'd0;
            digit[1] <= 4'd0;
            digit[2] <= 4'd0;
            digit[3] <= 4'd0;
            sel_digit <= 2'b00;
        end
            else begin
                // �ڸ��� ���� �� �� ���� ����
                if (btn_right) sel_digit <= (sel_digit == 2'b00) ? 2'b11 : sel_digit - 1;
                if (btn_left) sel_digit <= (sel_digit == 2'b11) ? 2'b00 : sel_digit + 1;
    
                if (btn_up && digit[sel_digit] < 4'd9) digit[sel_digit] <= digit[sel_digit] + 1;
                if (btn_down && digit[sel_digit] > 4'd0) digit[sel_digit] <= digit[sel_digit] - 1;
            end
    end

    // 7-���׸�Ʈ ǥ�ø� ���� �� ����
    assign value = {digit[3], digit[2], digit[1], digit[0]};

    // 7-���׸�Ʈ ��Ʈ�ѷ� �ν��Ͻ�ȭ
    fnd_cntr fnd_controller(
        .clk(clk),
        .reset_p(reset_p),
        .value(value),
        .com(com),
        .seg_7(seg_7)
    );

    // ��� ���� �Ķ���� �� ��ȣ ����
    parameter CLK_FREQ = 100_000_000;      // Ŭ�� ���ļ� (100MHz)
    parameter BAUD_RATE = 9600;            // UART�� ���� �ӵ� (9600bps)
    parameter CLKS_PER_BIT = CLK_FREQ / BAUD_RATE;

    // �۽� ��ȣ
    reg [7:0] data_to_send;   // ������ ������
    reg send;                 // ������ ���� Ʈ����
    wire busy;                // ���� �� ����

    // ���� ��ȣ
    wire [7:0] received_data;  // ���� ������
    wire received_flag;        // ������ ���� �Ϸ� ��ȣ
    reg send_flag;
    wire busy_flag;

    // ���� ����
    localparam IDLE = 3'b000;          // ��� ����
    localparam SEND_DIGIT = 3'b001;    // ���� �۽� ����
    localparam WAIT_BUSY = 3'b010;     // �۽� �Ϸ� ��� ����

    // ���� �ӽ� �� UART �۽� ����
    reg [2:0] state;                    // ���� �ӽ� ����
    reg [1:0] digit_index;              // ���� �ڸ��� �ε���
    reg btn_set_prev;                   // ���� btn_set ����

    // �۽� ��� �ν��Ͻ�ȭ
    uart_tx #(
        .CLK_FREQ(CLK_FREQ),
        .BAUD_RATE(BAUD_RATE)
    ) uart_tx_inst (
        .clk(clk),
        .reset(reset_p),
        .data_in(data_to_send),
        .send(send),
        .tx(tx),
        .busy(busy)
    );

    // ���� ��� �ν��Ͻ�ȭ
    uart_rx uart_receiver (
        .clk(clk),
        .reset_p(reset_p),
        .rx(rx),
        .data_out(received_data),
        .received(received_flag)
    );
    
    // �۽� ����
    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            save_fnd_value <= 16'h0000;   // FND �� �ʱ�ȭ
            data_to_send <= 8'h00;
            send <= 1'b0;
            state <= IDLE;
            digit_index <= 2'd3; // �������� �����ϱ� ���� 3���� �ʱ�ȭ
            btn_set_prev <= 1'b0;
        end
            else begin
                btn_set_prev <= btn_set;
                case (state)
                    IDLE: begin
                        if (btn_set && !btn_set_prev) begin  // btn_set�� ��� ���� ����
                            save_fnd_value <= value;        // ���� FND ���� ����
                        end
                        if (received_flag && received_data == "Q") begin
                            digit_index <= 2'd3;            // ������ �ڸ����� �ʱ�ȭ
                            state <= SEND_DIGIT;            // �۽� ����
                        end
                    end
                    SEND_DIGIT: begin
                        if (!busy) begin
                            case (digit_index)
                                2'd3: data_to_send <= save_fnd_value[15:12] + 8'h30; // ���� ���� �ڸ���
                                2'd2: data_to_send <= save_fnd_value[11:8] + 8'h30;
                                2'd1: data_to_send <= save_fnd_value[7:4] + 8'h30;
                                2'd0: data_to_send <= save_fnd_value[3:0] + 8'h30; // ���� ���� �ڸ���
                            endcase
                            send <= 1'b1;
                            state <= WAIT_BUSY;
                        end
                    end
                    WAIT_BUSY: begin
                        if (!busy) begin
                            send <= 1'b0;
                            if (digit_index == 2'd0) begin  // ��� �ڸ��� ���� �Ϸ�
                                state <= IDLE;
                            end
                                else begin
                                    digit_index <= digit_index - 1'b1; // ���� �ڸ����� �̵�
                                    state <= SEND_DIGIT;
                                end
                        end
                    end
                    default: state <= IDLE;
                endcase
            end
    end

    // ���� �� LED ���� ���� (�������� ����)
    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            led <= 16'h0000;
            send_flag <= 1'b0;
        end
            else begin
                if (received_flag) begin
                    case (received_data)
                //�ʿ��� �κи� �ּ��� Ǯ� ����ϼ���.
                //�л�--------------------------------------------------------------
//                      8'h30: led <= 16'h0000;  // ASCII '0'�̸� ��� LED�� ��
//                      8'h31: led <= 16'hFFFF;  // ASCII '1'�̸� ��� LED�� ��
                //------------------------------------------------------------------

                //������-------------------------------------------------------------
                    8'h30: led <= 16'h0000;  // ASCII '0'�̸� ��� LED�� ��
                    8'h31: led[0] <= 1'b1;   // ASCII '1'�̸� LED 1���� ��
                    8'h32: led[1] <= 1'b1;   // ASCII '2'�̸� LED 2���� ��
                    8'h33: led[2] <= 1'b1;   // ASCII '3'�̸� LED 2���� ��
                    8'h34: led[3] <= 1'b1;   // ASCII '4'�̸� LED 2���� ��
                    8'h35: led[4] <= 1'b1;   // ASCII '5'�̸� LED 2���� ��
                    8'h36: led[5] <= 1'b1;   // ASCII '6'�̸� LED 2���� ��
                    8'h37: led[6] <= 1'b1;   // ASCII '7'�̸� LED 2���� ��
                    8'h38: led[7] <= 1'b1;   // ASCII '8'�̸� LED 2���� ��
                    8'h39: led[8] <= 1'b1;   // ASCII '9'�̸� LED 2���� ��

                    8'h41: led[0] <= 1'b0;   // ASCII 'A'�̸� LED 1���� �� 
                    8'h42: led[1] <= 1'b0;   // ASCII 'B'�̸� LED 2���� ��
                    8'h43: led[2] <= 1'b0;   // ASCII 'C'�̸� LED 3���� ��
                    8'h44: led[3] <= 1'b0;   // ASCII 'D'�̸� LED 4���� ��
                    8'h45: led[4] <= 1'b0;   // ASCII 'E'�̸� LED 5���� ��
                    8'h46: led[5] <= 1'b0;   // ASCII 'F'�̸� LED 6���� ��
                    8'h47: led[6] <= 1'b0;   // ASCII 'G'�̸� LED 7���� ��
                    8'h48: led[7] <= 1'b0;   // ASCII 'H'�̸� LED 8���� ��
                    8'h49: led[8] <= 1'b0;   // ASCII 'I'�̸� LED 9���� ��
                //-------------------------------------------------------------------
                            default: led <= led;     // �ٸ� ���̸� LED ���� ����
                    endcase
                    if (!busy) begin
                        send_flag <= 1'b1;
                    end
                end
                    else begin
                        send_flag <= 1'b0;
                    end
            end
    end

endmodule