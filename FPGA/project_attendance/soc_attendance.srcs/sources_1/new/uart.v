////�۽�
//module uart_tx #(
//    parameter CLKS_PER_BIT = 1250  // 12MHz Ŭ������ 9600 baud rate�� ���� ����
//)(
//    input wire clk,        // �ý��� Ŭ��
//    input wire reset_p,    // ���� ��ȣ (active high)
//    input wire tx_start,   // ���� ���� ��ȣ
//    input wire [7:0] tx_data,  // ������ 8��Ʈ ������
//    output reg tx_busy,    // ���� �� ���� ǥ��
//    output reg tx          // ���� UART ��� ��
//);

//    // ���� ����
//    localparam IDLE = 2'b00;      // ��� ����
//    localparam START_BIT = 2'b01; // ���� ��Ʈ ���� ����
//    localparam DATA_BITS = 2'b10; // ������ ��Ʈ ���� ����
//    localparam STOP_BIT = 2'b11;  // ���� ��Ʈ ���� ����

//    reg [1:0] state;       // ���� ����
//    reg [12:0] clk_count;  // Ŭ�� ī����
//    reg [2:0] bit_index;   // ���� ���� ���� ��Ʈ �ε���
//    reg [7:0] tx_data_reg; // ������ ������ ��������

//    always @(posedge clk or posedge reset_p) begin
//        if (reset_p) begin
//            state <= IDLE;
//            tx_busy <= 1'b0;
//            tx <= 1'b1;  // UART ���� ���´� high
//            clk_count <= 0;
//            bit_index <= 0;
//        end else begin
//            case (state)
//                IDLE: begin
//                    tx <= 1'b1;
//                    tx_busy <= 1'b0;
//                    clk_count <= 0;
//                    bit_index <= 0;

//                    if (tx_start == 1'b1) begin  // ���� ���� ��ȣ ����
//                        tx_data_reg <= tx_data;
//                        state <= START_BIT;
//                        tx_busy <= 1'b1;
//                    end
//                end

//                START_BIT: begin
//                    tx <= 1'b0;  // ���� ��Ʈ�� �׻� 0

//                    if (clk_count < CLKS_PER_BIT - 1) begin
//                        clk_count <= clk_count + 1;
//                    end else begin
//                        clk_count <= 0;
//                        state <= DATA_BITS;
//                    end
//                end

//                DATA_BITS: begin
//                    tx <= tx_data_reg[bit_index];  // LSB���� ����

//                    if (clk_count < CLKS_PER_BIT - 1) begin
//                        clk_count <= clk_count + 1;
//                    end else begin
//                        clk_count <= 0;

//                        if (bit_index < 7) begin
//                            bit_index <= bit_index + 1;
//                        end else begin
//                            bit_index <= 0;
//                            state <= STOP_BIT;
//                        end
//                    end
//                end

//                STOP_BIT: begin
//                    tx <= 1'b1;  // ���� ��Ʈ�� �׻� 1

//                    if (clk_count < CLKS_PER_BIT - 1) begin
//                        clk_count <= clk_count + 1;
//                    end else begin
//                        tx_busy <= 1'b0;
//                        state <= IDLE;
//                    end
//                end

//                default: begin
//                    state <= IDLE;
//                end
//            endcase
//        end
//    end

//endmodule

////����
//module uart_rx #(
//    parameter CLKS_PER_BIT = 1250  // 12MHz Ŭ������ 9600 baud rate�� ���� ����
//)(
//    input wire clk,        // �ý��� Ŭ��
//    input wire reset_p,    // ���� ��ȣ (active high)
//    input wire rx,         // UART ���� ��
//    output reg [7:0] rx_data,  // ���ŵ� 8��Ʈ ������
//    output reg rx_done     // ���� �Ϸ� ��ȣ
//);

//    // ���� ����
//    localparam IDLE = 2'b00;      // ��� ����
//    localparam START_BIT = 2'b01; // ���� ��Ʈ ���� ����
//    localparam DATA_BITS = 2'b10; // ������ ��Ʈ ���� ����
//    localparam STOP_BIT = 2'b11;  // ���� ��Ʈ ���� ����

//    reg [1:0] state;       // ���� ����
//    reg [12:0] clk_count;  // Ŭ�� ī����
//    reg [2:0] bit_index;   // ���� ���� ���� ��Ʈ �ε���
//    reg [7:0] rx_data_temp;  // �ӽ� ������ ���� ��������

//    always @(posedge clk or posedge reset_p) begin
//        if (reset_p) begin
//            state <= IDLE;
//            rx_done <= 1'b0;
//            clk_count <= 0;
//            bit_index <= 0;
//            rx_data <= 8'h00;
//            rx_data_temp <= 8'h00;
//        end else begin
//            case (state)
//                IDLE: begin
//                    rx_done <= 1'b0;
//                    clk_count <= 0;
//                    bit_index <= 0;

//                    if (rx == 1'b0) begin  // ���� ��Ʈ ����
//                        state <= START_BIT;
//                    end
//                end

//                START_BIT: begin
//                    if (clk_count == (CLKS_PER_BIT - 1) / 2) begin  // ��Ʈ �߾ӿ��� ���ø�
//                        if (rx == 1'b0) begin
//                            clk_count <= 0;
//                            state <= DATA_BITS;
//                        end else begin
//                            state <= IDLE;  // �߸��� ���� ��Ʈ, �ٽ� ���
//                        end
//                    end else begin
//                        clk_count <= clk_count + 1;
//                    end
//                end

//                DATA_BITS: begin
//                    if (clk_count < CLKS_PER_BIT - 1) begin
//                        clk_count <= clk_count + 1;
//                    end else begin
//                        clk_count <= 0;
//                        rx_data_temp[bit_index] <= rx;  // ������ ��Ʈ ���ø�

//                        if (bit_index < 7) begin
//                            bit_index <= bit_index + 1;
//                        end else begin
//                            bit_index <= 0;
//                            state <= STOP_BIT;
//                        end
//                    end
//                end

//                STOP_BIT: begin
//                    if (clk_count < CLKS_PER_BIT - 1) begin
//                        clk_count <= clk_count + 1;
//                    end else begin
//                        rx_done <= 1'b1;  // ���� �Ϸ� ��ȣ
//                        rx_data <= rx_data_temp;  // ���ŵ� ������ ���
//                        state <= IDLE;
//                    end
//                end
//                default: begin
//                    state <= IDLE;
//                end
//            endcase
//        end
//    end
//endmodule