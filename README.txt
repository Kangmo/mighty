0. 동의사항

   가. "마이티"의 저작권은 본인 김강모에게 있습니다.

   나. 공개 프로그램을 제작할 경우

       * 새로 작성된 소스와 같이 배포
       * 원 프로그램이름(마이티)을 ABOUT 대화상자에 기록
       * 원 제작자 이름(김강모)을 ABOUT 대화상자에 기록
      

   나. 상용 프로그램(쉐어웨어 포함)을 제작할 경우

       * 원 제작자(김강모)와 별도의 라이센스 계약 체결.
       * 연락처 : kmkim95@cs.korea.ac.kr
                  Capcom@hitel.net
                  서울시 강서구 화곡 6동 963-19 두성주택 B103호

   위의 사항에 완전히 동의하는 경우에 한해, 마이티 소스를 이용한
   새로운 프로그램의 개발을 허용합니다. 

   위의 사항을 준수하지 않을 경우, 저작권 법으로 대응하겠습니다.

1. 개요

   1995년 7월 부터 제작된 마이티 호스트 1.0 beta 1.5
   버젼의 소스를 공개 합니다.

   이소스의 일부분을 떼어 사용한다면 모를까,
   호스트를 만들기에는 힘든점이 많을 것으로 생각됩니다.
   한라프로를 사용하였기 때문에 640KB라는 메모리 장벽을 
   넘기가 쉽지 않을 것이기 때문입니다.

   스크립트 모듈을 제외한 모든 부분은 맨땅에 헤딩 방식으로 만든
   것입니다.  호스트를 만들려고 하는데, 도저히 감이 안잡하시는
   분들은 한번쯤 분석해 보시는 것도 도움이 될 듯 합니다.
   주석이 거의 안달려 있지만, 변수이름을 보고 잘 생각해 보시면
   분석하는것이 그리 어렵지만은 않을 것입니다.

   스크립트 모듈은 Little C라는 프로그램의 소스를 고친 것입니다.
   Little C에 C의 배열, 함수호출방법등의 많은 개념을 더 추가하였습니다.

2. 설치
   
   0. 볼랜드 C++ 3.1 설치

   1. 마이티 소스 설치
      pkunzip -d m-source.zip [볼랜드C 디렉토리]

      만약 볼랜드C가 C:\BORLANDC에 설치되었다면,

      pkunzip -d m-source.zip C:\BORLANDC

      라고 입력하시면 됩니다.

      아래의 라이브러리들은 여러분의 편의를 위해 같이 넣었습니다.
      옜날 버젼이라 구하기가 쉽지 않을것 같아서 입니다.

      Spawn library
      Xmsif library
      Pcl   library

   2. 설정
  
      Borlandc를 mighty디렉토리 속에서 실행하여
      [Project][Open Project]를 선택, mighty.prj를 불러온다.

      [Options][Directories]를 선택, 볼랜드C디렉토리를
      제대로 설정해 준다.

   3. 한라프로 2.4 최신판 설치
      하이텔 go hanpro 5에서 다운로드 받아서 설치.

3. 기타

   1. 마이티의 메시지 출력에 관하여
      
      "전자우편을 검색합니다" 와 같이 사용자에게 보여줄 메시지들은
      MIGHTY.ORI 화일에 저장되어 있다. 세모 모양의 특수문자(127)이
      메시지를 구분하는 글자 역할을 한다.

      이 화일은 MIGHTY.DAT로 암호화되어 배포되는데, 이때 암호는
      2개의 문자열이 되며, MIGHTY_D.CPP의 PASS1과 PASS2가 암호이다.

      그러면 MIGHTY.ORI화일을 암호화 하는 방법을 알아보자.

      먼저 MIGHTY.ORI화일을 MIGHTY.DAT화일로 복사한다.

      COPY MIGHTY.ORI MIGHTY.DAT

      그리고 CNVTDAT.EXE를 MIGHTY.DAT가 있는 디렉토리에서 실행한다.

      그러면 암호화된 MIGHTY.DAT가 생성된다.

      CNVTDAT.EXE의 소스는 CNVTDAT.CPP로, 암호를 변경하려면
      암호화 프로그램인 CNVTDAT.CPP와 암호해독 프로그램인 MIGHTY_D.CPP
      의 암호를 모두 바꾸어 주고, MIGHTY.DAT를 암호화 해주어야 한다.

      640KB라는 메모리 장벽을 넘기 위해 MIGHTY.DAT는 XMS에 올린다.


   2. 마이티의 모듈들
      mighty.cpp    : 주 프로그램
      mighty_c.cpp  : 통신 모듈
      mighty_d.cpp  : 데이터 화일 모듈 (MIGHTY.DAT)
      mighty_m1.cpp : 메뉴 모듈 I
      mighty_m.cpp  : 메뉴 모듈 II
      mighty_f.cpp  : 기본 함수 모듈
      mighty_o.cpp  : 기본 객체 모듈
      filebox.cpp   : 화일 상자 유저 인터페이스 모듈
      mighty_v.cpp  : 안시(vt100 & 이야기 그림안시) 처리 모듈
      mighty_p.cpp  : 풀다운 메뉴 모듈
      mighty_i.cpp  : 유저 인터페이스 모듈
      vg.cpp        : VG (VisualGo) 온라인 NCD이동 모듈
      lclib.cpp     : 스크립트 언어 라이브러리 모듈      
      littlec.cpp   : 스크립트 언어 주 모듈
      parser.cpp    : 스크립트 언어 파서 모듈
      cvar.cpp      : 스크립트 언어 변수 모듈
     
   3. 마이티의 대강의 동작 방식
      마이티는 C++로 작성되어 객체 지향 방식으로 설계 되었다.

      그러나 마이티가 개발되기 시작한 것이 1995년 7월이었던 반면,
      본인은 C++이 아닌 C를 처음 접한것이 1995년 4월이었고,
      C++은 커녕 객체지향이라는 개념조차 정립되지 않은 상태에서
      마이티를 제작하게 되어, 완벽한 객체 지향 방식은 아님을
      미리 밝힌다.

      먼저, 사용된 객체의 class이름을 적어본다.
      
      1. SuperClass         - MIGHTY_O.CPP
         객체들을 큐에 집어넣고 돌릴 생각으로 만든 최 상위 객체이다.
         Java의 Object class와 같은 개념이라면.. Java에 대한 모독이
         되겠지.. ^^;

         멀티 호스트 제작을 생각하다 고안한것이 객체를 큐에 넣고 
         일정한 time slice동안만 실행 될 수 있도록 하려 했으나,
         타이머 인터럽트를 잡는 도중 그만 포기하고 말았다.
     
         마이티에서 사용한 통신 라이브러리인 PCL은 최대 16포트까지
         통신 포트를 열 수 있도록 해준다.

      2. WaitConnect         - MIGHTY_O.CPP
         접속 대기 객체이다. 
      3. CutConnect          - MIGHTY_O.CPP
         접속을 해제해주는 객체이다.
      4. InputId              - MIGHTY_O.CPP
         아이디를 입력하는 상태의 객체이다.

      5. BaseMenu            - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         이 객체는 가상 객체로, 무언가 하나 골라야 하는 (메뉴)
         형식의 객체는 모두 이 객체를 파생한다.

         ex> 게시판, 서브메뉴, 등등.

      6. BaseExec            - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         이 객체는 무언가 하나 고르는 형식이 아니라 단순히
         잠시 실행되었다가 종료되는 객체는 이 객체를 파생한다.

         ex> 대화방

      7. Chat               - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         대화방을 구현한 객체이다.
         
      8. SubMenu             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         서브메뉴를 구현한 객체이다.

      9. BbsData             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         게시판의 글 1개를 관리하는 객체이다.
         편지, 자료실, 게시판 등등.. 글이 포함되는 객체는 모두
         이 객체를 사용하게 된다.

      10. TextMenu             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         게시판의 글 여러개를 관리하는 객체이다.
         여러개의 글 중 하나의 글을 고르거나 삭제하거나 하는 등
         여러개의 글을 관리하는 객체, 즉 편지, 자료실, 게시판..
         뭐 이런 객체들은 이 객체를 파생한다.

      11. BbsMenu              - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
         게시판 객체이다.
         
      12. NoticeMenu           - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          공지사항 객체이다.

      13. CMail                - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          메일의 상위 객체이다.
          메일 관련 메뉴들은 이 객체를 파생한다.

      14. CMailSee             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          메일 보기 메뉴 객체이다.

      15. MailMenu             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          메일 메뉴 객체이다.

      16. CheckMail             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          몇통의 메일이 도착되어 있는지 확인하는 객체이다.

      17. WMailMenu             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          메일을 작성하는 것을 구현한 객체.

      18. RMailMenu            - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          메일 읽기 메뉴 객체이다.

      19. MBox                 - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
	  편지 보관함 객체이다..

      20. MSee                 - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          보낸 편지 확인 객체이다.

      21. DnPdsMenu             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          다운로드 전용 자료실 객체이다. (CD-Rom자료실)

      22. PdsMenu             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
	  자료실 객체이다.

      23. JoinIn               - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          가입메뉴 객체이다.

      24. ViewUserMenu          - MIGHTY_M.CPP 또는 MIGHT_M1.CPP 
	  사용자 정보 보기 객체이다.

      25. TimeBankMenu          - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
	  시간은행 객체이다. 

      26. CircleID             - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          동호회 ID 1개를 관리하는 객체이다.

      27. CircleMenu           - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          동호회 가입 메뉴 객체이다.

      28. SendMail            - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          편지 보내기 메뉴객체 이다.
          글을 읽다가 S를 누르면 이 객체의 수행이 시작된다.

      29. ScriptMenu          - MIGHTY_M.CPP 또는 MIGHT_M1.CPP
          스크립트 실행 메뉴 객체이다.

      30. SMorder             - MIGHTY_O.CPP
          시삽 명령인 SM 명령 상태의 객체이다. 

      31. RDS	             - MIGHTY_O.CPP	
          리모트 도스쉘 객체이다.


      객체를 다루는 함수
         appObject  : 다음에 수행할 객체를 등록한다. ( Append )
         runObject  : 큐 속에 들어있는 객체를 수행한다.



     ** 마이티의 동작 메카니즘.

      객체 지향 방식으로 BBS운영 프로그램을 만들기 위해 본인이
      직접 개발한 메카니즘이다.

      마이티에서는 모든 메뉴를 객체화 하여 제작하였다.
      그러면 어떻게 이런 객체들을 묶어서 "마이티"라는 사설 BBS
      프로그램을 만들 수가 있었을까??

      마이티는 평상시에는 접속 대기 상태로 있다가, 
      접속이 되면 사용자 ID를 입력받고, 
      공지사항을 실행한다.
 
      그리고 사용자가 가는 메뉴의 인덱스에 따라 해당 객체를
      수행 해주다가, 사용자의 남은시간이 0이 되거나, 
      사용자가 bye나 x 명령을 실행하여 접속을 종료하게 될 경우
      접속 종료 객체를 수행한다.

      접속 종료 객체는 모뎀상의 접속을 사실상 해제하고는
      접속 대기 객체를 수행한다.       
      
      이렇게 되어 사용자 1인이 접속하는 사설 BBS의 한 사이클이
      수행되는 것이다.



      대기 -> ID입력 -> 공지사항 실행 -> ... -> 접속종료  --> 대기


      MIGHTY.CPP의 MAIN함수를 보도록 하자.
         
    int main()
    {
    	first_core = farcoreleft();
    	PrintLogo();
    	MemoryManagerInit();
    	readCfg();
    	varInit();
    	readHostInfo();
    	readMenuData();
    	readProtocol();
    	DIRprocess();
    	commInit();
    	SaveDosScr();
    	hanInit();
    	ConfigInit();
   	InitLogData();

    	PD = new _PD(1, 2, 3, 15, 4, 3, 11, 15, 7, 14, 7, 9, 13, 15, 8);
    	bPdRan=1;
    	
        appObject(WAIT, NULL);
    	for(;;) runObject();
    }

    여기서 맨마지막 두 줄만이 가장 중요한 내용이다.
    WAIT는 WaitConnect(접속 대기)를 나타내는 메시지로, appObject에게
    처음(다음에) 수행할 객체가 WaitConnect객체임을 나타낸다.
    
    메뉴에 해당하는 모든 객체에는 run() 함수가 있는데,
    runObject함수는 appObject에 의해 등록된 객체의
    run()함수를 수행하게 된다. run()함수가 종료되기 전에
    수행중인 객체는 다음에 수행될 객체를 appObject를 통해
    등록하게 된다. run()함수가 종료되면, runObject또한 종료된다.

    그래서 runObject 함수는 무한히 계속 수행되는 것이다.
    객체 하나가 다른 객체를 수행시키고는 종료되기 때문에,
    이른바 객체 체인을 형성, 각종 객체가 무난히 수행되는 것이다.


4. 후기.
   
     시간이 많지 않은 관계로 많은 내용을 적지는 못하였다.

     쉐어 웨어 발표를 목표로 한건 챙겨보려고 만든 프로그램이
     마이티이지만, 부족한 점이 많아서 매번 공개로만 발표했던
     프로그램이다.

     2년간의 노고가 깃든 소스이기 때문에 공개하기까지 많은
     갈등을 때려야 했다. 

     부족하지만, 혹시라도 이 소스에서 힌트를 얻어 다른 좋은
     프로그램에 쓰인다면, "장기 이식" 과도 같은 효과를 내는
     것이 아닌가 생각한다. 

     본인이 약간 바쁜 관계로 소스에 대한 주석을 달지 못하는 것이
     매우 안타깝다.  

     본인이 시간이 많지 않은 관계로, 소스의 작동방식 및 분석에
     관한 메일은 사절한다.