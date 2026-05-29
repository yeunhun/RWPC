# SflashResetManager

## #0. 무슨 역할을 수행하나요?

HSM firmware image(이하 fw) 의 TOC2, SWPU 정보를 기본값으로 초기화 합니다.

HSM fw는 CySAF 형식으로 패키징 되어 있습니다. CySAF 형식은 sflash 영역(보안 옵션 정보를 저장하는 영역)에 fw의 hash 정보 같은 것을 넣도록 되어있습니다.  하지만 cypress 에서 제공하는 CM0+ 용 예제 코드 및 dummy HSM fw 등의 경우 CyBAF 형식으로 sflash 정보를 사용하지 않도록 되어 있습니다. 그렇기 때문에 HSM fw를 기록한 이후 테스트를 위해 일반 CM0+ fw 를 사용하고자 하는 경우 부팅을 실패할 수 있습니다. 아래는 부팅을 실패하는 예시 입니다.

HSM fw 기록 -> 테스트용 CM0+ fw 기록(SDL 예제, dummy HSM fw 등) -> 부팅 불가(reset handler 진입 실패)

문제 상황은 아래와 같은 방법으로 해결이 가능합니다.

HSM fw 기록 -> SflashResetManager 실행 -> sflash 보안 옵션 영역 초기화 -> 전원 off/on -> 테스트용 CM0+ fw 기록 -> 정상 동작



## #1. 주의 및 참고 사항

- configuration lock 이후 사용 불가

- HSM fw 가 기록된 상태에서 실행하면 이후 HSM fw 부팅 불가(HSM fw를 재기록 해야 함)

- 만약 초기화 유틸리티가 계속 실패하는 경우 전원 off/on 후 곧바로 시도해보기를 추천드립니다.



## #2. script 목록 및 요약

- sflashResetManager_cyt?bx.cmm : elf 파일을 sram에 로드하여 초기화 작업을 수행합니다.



## #3. script 로드 방법

- do sflashResetManager_cyt???x.cmm




## #4. script 진행 방법

F7을 누르거나 list 창에서 go 버튼을 눌러 진행하면 된다.



## #5. 결과 확인 방법

#### A. 최종 결과 확인 방법

**CYT2BX 시리즈** : Data.dump 0x0800d400 창(0x0800d400 sram 영역의 32bit 값)

**CYT4BX 시리즈** : Data.dump 0x2800d400 창(0x2800d400 sram 영역의 32bit 값)

성공: 0x0000900D

실패: 0x0000BAAD

#### B. 기타: 참고용 진행 과정 로그 간단 설명 

**CYT2BX 시리즈** : Data.dump 0x0800d000 창(0x0800D000 sram 영역 32bit 값) 

**CYT4BX 시리즈** : Data.dump 0x2800d000 창(0x2800D000 sram 영역 32bit 값)

**가장 첫줄: 현재 sram에 로드된 fw type**

SF-fixer: sflash reset manager 가 정상 로드 되었음을 의미



## #6. 상세 구조 설명

- cmm 스크립트는 sre 파일을 sram에 로드한다.

- 부팅이 진행되면 HSM Core만 깨어나 sflash의 toc2, swpu 영역을 기본값으로 변경한다. 모든 작업이 성공하면 0x0800D400(0x2800D400) 영역에 0x0000900D 값이 설정된다.

- 이 펌웨어는 code/work flash 영역을 변경하지 않는다.  오직 sram에 로드되어 진행된다. 리부트 하면 sram에 로드 되었던 코드들이 모두 사라진다.

- 이 작업을 하는 동안 반드시 다른 작업을 수행하지 않도록 한다.
- 작업이 종료된 후 power off/on을 해야 정상 적용 된다.
- 이 스크립트는 0x08001000(0x28001000) 부터 sram을 사용한다.



## #7. 수정 내역

- 20210122: 문서 최초 버전
- 20210226: cmm 내부 elf 파일 오타 수정