////송신
//module uart_tx #(
//    parameter CLKS_PER_BIT = 1250  // 12MHz 클럭에서 9600 baud rate를 위한 설정
//)(
//    input wire clk,        // 시스템 클럭
//    input wire reset_p,    // 리셋 신호 (active high)
//    input wire tx_start,   // 전송 시작 신호
//    input wire [7:0] tx_data,  // 전송할 8비트 데이터
//    output reg tx_busy,    // 전송 중 상태 표시
//    output reg tx          // 실제 UART 출력 핀
//);

//    // 상태 정의
//    localparam IDLE = 2'b00;      // 대기 상태
//    localparam START_BIT = 2'b01; // 시작 비트 전송 상태
//    localparam DATA_BITS = 2'b10; // 데이터 비트 전송 상태
//    localparam STOP_BIT = 2'b11;  // 정지 비트 전송 상태

//    reg [1:0] state;       // 현재 상태
//    reg [12:0] clk_count;  // 클럭 카운터
//    reg [2:0] bit_index;   // 현재 전송 중인 비트 인덱스
//    reg [7:0] tx_data_reg; // 전송할 데이터 레지스터

//    always @(posedge clk or posedge reset_p) begin
//        if (reset_p) begin
//            state <= IDLE;
//            tx_busy <= 1'b0;
//            tx <= 1'b1;  // UART 유휴 상태는 high
//            clk_count <= 0;
//            bit_index <= 0;
//        end else begin
//            case (state)
//                IDLE: begin
//                    tx <= 1'b1;
//                    tx_busy <= 1'b0;
//                    clk_count <= 0;
//                    bit_index <= 0;

//                    if (tx_start == 1'b1) begin  // 전송 시작 신호 감지
//                        tx_data_reg <= tx_data;
//                        state <= START_BIT;
//                        tx_busy <= 1'b1;
//                    end
//                end

//                START_BIT: begin
//                    tx <= 1'b0;  // 시작 비트는 항상 0

//                    if (clk_count < CLKS_PER_BIT - 1) begin
//                        clk_count <= clk_count + 1;
//                    end else begin
//                        clk_count <= 0;
//                        state <= DATA_BITS;
//                    end
//                end

//                DATA_BITS: begin
//                    tx <= tx_data_reg[bit_index];  // LSB부터 전송

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
//                    tx <= 1'b1;  // 정지 비트는 항상 1

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

////수신
//module uart_rx #(
//    parameter CLKS_PER_BIT = 1250  // 12MHz 클럭에서 9600 baud rate를 위한 설정
//)(
//    input wire clk,        // 시스템 클럭
//    input wire reset_p,    // 리셋 신호 (active high)
//    input wire rx,         // UART 수신 핀
//    output reg [7:0] rx_data,  // 수신된 8비트 데이터
//    output reg rx_done     // 수신 완료 신호
//);

//    // 상태 정의
//    localparam IDLE = 2'b00;      // 대기 상태
//    localparam START_BIT = 2'b01; // 시작 비트 감지 상태
//    localparam DATA_BITS = 2'b10; // 데이터 비트 수신 상태
//    localparam STOP_BIT = 2'b11;  // 정지 비트 감지 상태

//    reg [1:0] state;       // 현재 상태
//    reg [12:0] clk_count;  // 클럭 카운터
//    reg [2:0] bit_index;   // 현재 수신 중인 비트 인덱스
//    reg [7:0] rx_data_temp;  // 임시 데이터 저장 레지스터

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

//                    if (rx == 1'b0) begin  // 시작 비트 감지
//                        state <= START_BIT;
//                    end
//                end

//                START_BIT: begin
//                    if (clk_count == (CLKS_PER_BIT - 1) / 2) begin  // 비트 중앙에서 샘플링
//                        if (rx == 1'b0) begin
//                            clk_count <= 0;
//                            state <= DATA_BITS;
//                        end else begin
//                            state <= IDLE;  // 잘못된 시작 비트, 다시 대기
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
//                        rx_data_temp[bit_index] <= rx;  // 데이터 비트 샘플링

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
//                        rx_done <= 1'b1;  // 수신 완료 신호
//                        rx_data <= rx_data_temp;  // 수신된 데이터 출력
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