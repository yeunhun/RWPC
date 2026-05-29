# LifecycleManager

## #0. 무슨 역할을 수행하나요?

 cypress traveo2 series 는 hw 구조적인 특성으로 HSM Framework 내부의 Configuration Lock API를 수행할 수 없습니다. 대신 이 LifecycleManager 스크립트를 사용하여 Configuration Lock을 진행합니다.  LifecycleManager는 lifecycle을 normal provisioned ->  secure mode 로 변경하며 HSM 의 code/work flash에 대한 보호 기능을 활성화 합니다.

**참고** - normal과 normal provisioned는 같은 lifecycle이 아닙니다. 해당 용어 관련 상세 내용은 cypress 문의 혹은 TRM을 참조하시기 바랍니다.



## #1. script 목록 및 요약

- Traveo2_lifecycle_SECURE.cmm : sre 파일을 sram에 로드하여 lifecyle 작업을 수행합니다.



## #2. script 로드 방법

- 방법1. cmm을 실행하여 srec 파일을 직접 load

- 방법2. do sramm.cmm PATH=c:\srec파일경로\LifecycleManager_SECUREWITHDEBUG_CYT@BX_rel.sre



## #3. script 진행 방법

F7을 누르거나 list 창에서 go 버튼을 눌러 진행하면 된다.



## #4. 결과 확인 방법

#### A. 최종 결과 확인 방법

**CYT2BX 시리즈** : Data.dump 0x0800d400 창(0x0800d400 sram 영역의 32bit 값)

**CYT4BX 시리즈** : Data.dump 0x2800d400 창(0x2800d400 sram 영역의 32bit 값)

성공: 0x0000900D

실패: 0x0000BAAD

#### B. 오류 발생했을 때 오류 코드

**CYT2BX 시리즈** : Data.dump 0x0800d404 창(0x0800D404 sram 영역 32bit 값)

**CYT4BX 시리즈** : Data.dump 0x2800d404 창(0x2800D404 sram 영역 32bit 값)

일반적으로 0xF00000XX 형태로 나옴

#### C. 기타: 참고용 진행 과정 로그 간단 설명 

**CYT2BX 시리즈** : Data.dump 0x0800d000 창(0x0800D000 sram 영역 32bit 값) 

**CYT4BX 시리즈** : Data.dump 0x2800d000 창(0x2800D000 sram 영역 32bit 값)

**가장 첫줄: 현재 sram에 로드된 fw type**

LSup:sec -  Lifecycle Manager가 secure mode로 lifecycle 작업을 시작한다는 메세지



## #5. 상세 구조 설명

- cmm 스크립트는 sre 파일을 sram에 로드한다.

- 부팅이 진행되면 HSM Core만 깨어나 lifecycle secure mode 전환 및 HSM code/work flash 영역 보안 설정을 진행한다. 모든 작업이 성공하면 0x0800D400(0x2800D400) 영역에 0x0000900D 값이 설정된다.

- 이 펌웨어는 code/work flash 영역을 변경하지 않는다.  오직 sram에 로드되어 진행된다. 리부팅을 하면 sram이 초기화 되므로 다시 원래 펌웨어의 동작을 수행할 수 있다.

- 이 작업을 하는 동안 반드시 다른 작업을 수행하지 않도록 한다.
- 작업이 종료된 후 power off/on을 해야 정상 적용 된다.
- LifecycleManager는 0x08001000(0x28001000) 부터 sram을 사용한다.



## #6. 수정 내역

- 20201120: 상세구조 설명 추가
- 20201123: 오타 수정
- 20201217: cyt4bx 시리즈 추가
- 20210928: efuse flag 수정