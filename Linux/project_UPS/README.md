# UPS 무정전 전원 공급 장치

## 프로젝트 요약
- 수행 목표
   - 태양광, 일반 전원 두 가지의 전원과 라즈베리파이를 이용하여 안정적으로 클라이언트와 서버를 구동하고, 두 전원이 모두 사용할 수 없을 경우 안전하게 클라이언트와 서버를 종료할 수 있게 하는 시스템이다.
- 수행 이유
   - 전원 공급이 끊겼을 때 클라이언트와 서버에 계속 전원을 공급해줌과 동시에 안전한 종료
- 수행 결과
   - INA219를 이용한 전압 측정 성공
   - 조도 센서를 이용한 측정값에 따른 스텝모터 구동 성공
   - 소켓 통신을 통한 클라이언트와 서버간의 통신 성공
   - 배터리를 통한 라즈베리파이 구동 실패
- 기대효과 및 개선 사항
   - 연속성 있는 전원 공급으로 데이터 보호 및 안전성 강화
   - 친환경 에너지 사용으로 비용 절감
   - 전력 장애 대비
   - 자동화된 시스템 관리

## 프로젝트 목표
- 전원 안정성 확보 및 데이터 보호
   - 태양광 패널과 상용 전원을 통해 배터리를 충전하고, 충전된 배터리를 사용하여 클라이언트와 서버로 구성된 라즈베리파이 장비를 안정적으로 구동한다. 전원이 중단될 경우 배터리를 통해 시스템을 유지하며, ups에서 소켓 통신을 이용하여 클라이언트로 시스템 종료 명령을 전달하여 데이터 손실을 방지한다.
- 전원 관리 자동화 및 효율성 향상
   - 전원 공급 상태를 모니터링하고, 조도에 따라 태양광 패널의 덮개를 자동으로 열고 닫는 시스템을 구현한다. 이로써 패널의 수명을 연장하고 에너지 효율성을 높인다.
- 비용 절감 및 환경 친화적 에너지 활용
   - 태양광 패널을 통해 재생 가능한 에너지를 활용하여 전기 요금을 절감하고, 환경에 미치는 영향을 최소화한다. 에너지 자원의 효율적 사용을 통해 지속 가능한 운영을 지원한다.
- 시스템 신뢰성 및 관리 효율성 증대
   - 전원 장애 시 자동으로 시스템을 종료하는 프로세스를 통해 데이터의 손실을 방지하고 신뢰성을 높인다. Ups와 클라이언트 간의 소켓 통신을 통해 명령을 주고받으며, 시스템 관리의 효율성을 증대시킨다.
- 전원 보호 및 장비 보호
   - 태양광 패널을 보호하기 위해 자동 개폐 장치를 구현하여 패널의 물리적 손상을 방지하고, 필요시에만 태양광 발전을 가능케 한다.				

## 수행 결과
- INA219 모듈 두 개, ADC(Analog Digital Converter) 3모듈을 I2C 통신을 통하여 다중 채널을 구현하였다. INA219를 통하여 태양광 발전 전압과 상용 전원의 전압을 측정하였으며, ADC의 조도 센서를 접합하여 광량을 측정하고 이를 바탕으로 태양광 패널 자동 개폐 장치, 전원 모니터링 시스템을 완성하였다.
태양광 패널 자동 개폐 장치를 이용하여 광량이 기준치 이상일 경우, 태양광 커버를 이동하여 태양광 발전을 실시하고 광량의 기준치 이하일 경우, 커버를 닫아 태양광 발전을 중지하고 패널을 보호하였다.
- 전원 모니터링 시스템을 통해 태양광 발전 전압과 상용 전원의 전압을 측정하여 각 전원의 상태를 모니터링 하였다. 두 전원 모두 공급이 중단될 경우, 배터리가 고갈되기 전에 시스템을 종료할 수 있도록 소켓 통신을 통해 시스템 종료 명령을 전달하는 기능을 구현하였다.   
- 스텝업 컨버터 모듈을 이용하여 목표 전압(5v)을 만들었으나, 클라이언트가 요구하는 전류량에 도달하지 못하였다. 추후에 더 높은 전류를 제공할 수 있는 스텝업 컨버터 모듈을 사용하여 충분한 전류를 만들 수 있다면  현재의 문제점을 보완할 수 있다. 

## 기대효과 및 수행 후기
- 연속적인 전원 공급
   - 태양광 에너지와 상용 전원을 결합하여 UPS 시스템을 구축하면 전원 공급의 안정성을 크게 높일 수 있다. 태양광은 태양이 비추는 동안 꾸준히 전력을 제공할 수 있으며, 이를 상용 전원과 함께 사용하면 더 안정적인 전력 공급이 가능해진다. 전원이 차단될 경우에는 배터리가 임시로 전력을 공급하여 시스템의 연속성을 유지할 수 있다.
- 데이터 보호 및 안전성 강화
   - UPS 시스템이 없다면 태양광 에너지와 상용 전원이 둘 다 중단될 경우, 시스템은 바로 전원이 차단되면서 작업하던 모든 내용이 저장되지 않고 손실되거나 시스템의 손상을 초래할 수 있다. 하지만 UPS 시스템이 있다면 태양광 에너지와 상용 전원이 중단되었을 때 배터리를 통해 시스템의 전원을 공급하면서 안내 메세지를 보내 작업하던 내용을 저장하고 안전하게 종료하라고 지시를 내릴 수 있다. 
- 비용 절감
   - 태양광 에너지를 활용하면 전기 요금을 절감할 수 있으며, 장기적으로는 경제적인 이점을 제공한다. 또한, 태양광 시스템이 상용 전원에 대한 의존도를 줄이게 되어 전력 비용을 줄일 수 있다.
- 환경 친화적
   - 태양광 에너지를 사용하면 탄소 배출을 줄이고 환경에 미치는 영향을 최소화할 수 있다. 이는 지속 가능한 에너지 사용을 촉진하는 데 기여한다.
- 전력 장애 대비
   - 전원 장애가 발생하더라도 시스템이 임시로 전력을 공급받아 작동할 수 있어 작업 중단을 최소화할 수 있다.
- 자동화된 시스템 관리
   - 서버가 전원 상태를 실시간으로 모니터링하고 문제가 발생했을 때 자동으로 안전하게 종료할 수 있도록 함으로써 시스템 관리의 자동화와 효율성을 높일 수 있다.
 
## 최종 결과물 첨부 자료(부품, 코드)

 ![image](https://github.com/user-attachments/assets/2fe470d6-b501-42ea-8e91-b493e2023e1f)

태양광 판넬 부착하기 전 파이, 배터리, 스텝모터 등 각종 부품들을 배치
 
그림2) 소켓 통신을 연결하는 코드
 
그림3) 조도 센서를 통해 광량을 체크하는 코드
 
그림4) 태양광 판넬과 상용 전원의 전압이 일정 수준 이하면 클라이언트 종료하는 코드
