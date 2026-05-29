# CYT2B9X Trace32 CMM  script

## #0. 이 문서는?

HSM과 같이 배포된 CMM 파일들을 사용하기 쉽도록 안내합니다.



## #1. script 목록 및 요약

- cyt2b9x_HOST_HAE_release.cmm : host 에 fw 다운로드
- cyt2b9x_HOST_HAE_release_dual.cmm : host 에 fw 다운로드(dual bank용)
- cyt2b9x_HSM_HAE_release.cmm : hsm에 fw 다운로드
- cyt2b9x_HSM_HAE_release_dual.cmm : hsm에 fw 다운로드(dual bank용)
- cyt2b9x_flash_erase_all: code/work flash 모두 삭제



## #2. 각 script 사용 방법

### 1. cyt2b9x_HOST_HAE_release(_dual).cmm

- 수행 내용
  code/work flash 영역을 삭제한 다음 펌웨어를 chip에 다운로드 한다.
  dual bank용 스크립트의 경우 bank를 swap 한 다음 기록하는 과정이 추가되어 있다.

- 사용 방법
  Do ./cyt2b9x_HOST_HAE_release.cmm HOSTPATH=c:\host_cyt2bx.elf
  
- 주의 사항
  host의 환경에 맞게 내용을 변경 후 사용하도록 한다
  flash에 기록하기 위해 cpu 가 CM0+ core로 지정되어 있다. (CM4의 오타가 아니다)
  
  

### 2. cyt2b9x_HSM_HAE_release(_dual).cmm
- 수행 내용
  code/work flash 영역을 삭제한 다음 펌웨어를 chip에 다운로드 한다.
  보안 관련 설정이 포함된 sflash 영역 또한 일부 내용이 기록된다.
  dual bank용 스크립트의 경우 bank를 swap 한 다음 기록하는 과정이 추가되어 있다.
- 사용 방법
  Do ./cyt2b9x_HSM_HAE.cmm HSMPATH=c:\HSM_Framework_CYT2B9X_rel.sre
- 주의 사항
  host의 환경에 맞게 내용을 변경 후 사용하도록 한다. 
  예를 들어 이 스크립트는 기본적으로 CYT2B98 로 cpu type을 설정한다(SYStem.cpu CYT2B98CA-CM0+ -> CYT2B9XCA-CM0+ 등으로 각기 수정)



## #3. 수정 내역

2020.07.30: host 스크립트에서 work flash를 지우지 않도록 변경

2020.09.16: hsm framework 의 code flash 점유 크기 256KB -> 160KB 축소 반영

2020.09.21: hsm framwork 보안 flash 영역 기록 가능하도록 스크립트 수정

2020.11.12: 사용 예시 hex -> sre 변경

2021.02.05: 일부 환경에서 flash 관련 오동작 수정 및 watchdog 스크립트 추가 

2021.02.19: 오타 수정, dual bank 용 추가