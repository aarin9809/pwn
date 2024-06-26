// 고객 니즈

// 1. 자판기의 기능을 갖고 있는 프로그램을 만드시오.
// 2. 사용자로부터 금액을 입력 받고, 사용자가 구매할 수 있는 상품 목록을 보여줍니다.
// 3. 사용자는 원하는 상품을 선택하고, 프로그램은 선택된 상품의 가격을 사용자의 금액에서 차감한 후 잔액을 보여줍니다.
// 4. 프로그램은 여러 상품을 연속적으로 구매할 수 있으며, 잔액이 부족할 경우 구매를 할 수 없다는 메시지를 출력합니다.

// 상품 목록 : 콜라  사이다    물   비타600
// 가.      격 : 1800  1300   1000   600

// 주의 사항 : 해당 프로그램을 만들 때 입력, 출력, if문, for문을 꼭 사용해야 합니다.




// pseudo code
// 1. 최초 1회에만 소비자가 사용 가능한 돈을 먼저 입력 받는다.(이하 사용자돈)
// 1-1. 그 뒤부터는 계속 품목명을 입력 받는다.

// 2. 가지고 있는 잔액과 내가 다음에 사려는 물건 값을 비교하여
// 2-1. 구매 가능 하다면(if true false) 
//     2-2. 반복문을 반복
// 2-3. 구매할 수 없다면 잔액부족으로 프로그램 종료

// 변수 : 사용자돈, 품목을 담은 배열, 품목에 대한 가격 배열, 어떤 물건을 살지 입력 받을 배열, 
// for문에서 사용할 i 변수(아니 c에서는 대체 왜 for문 안에서 변수 선언을 못하게 만든거임)


// 후기
// 1.	왜 c에는 기본적으로 안되는것도 많고, 지원되는것도 별로 없는가... 왜 bool 쓰려면 헤더를 추가해야하는건데!!! 그냥 <stdio.h>에 있으면 서로 좋지 않은가...

// 2.	간만에 파이썬 자바 하다가 c하려니까 정말 애를 깨나 썼다. 솔직히 길어야 2시간 3시간이면 끝낼줄 알았는데 복기한답시고 공부 이거저것 다시 하느라 6시간은 쓴거같다...


// 3.	scanf로 일일이 주소 지정해주는게 진또배기 귀차니즘 우리 파이썬이는 scanf 없는디...

// 4.	strcmp 몰라서 애 엄청 먹었다. 파이썬에서는 == 나 !=면 끝나는 걸 헤더를 추가해서... 인수를 두개를 넣고 돌려서 리턴 값이 게다가 0 || 1...



#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char stuff[4][10] = {"콜라", "사이다", "물", "비타600"};    // 비타600 길이 생각하고 널널하게 잡아서 배열 10 할당해줌 그러고 품목은 4개니 2차원배열로 배열 초기화.
    int price[4] = {1800, 1300, 1000, 600};               // 배열 길이 4로 배열 초기화.
    int usrmoney;       // 사용자가 최초에 가지고 있는 돈을 입력받을 정수 변수
    char buy[10];       // 사용자가 구매할 품목을 입력받을 배열 변수
    int i;      //for for^^

    printf("금액을 입력하세요: ");      
    scanf("%d", &usrmoney);

    while(1) {                      // 무한 츠쿠요미 "ON" 
        bool canBuy = false;        // 일단 살 능력이 '없다'로 먹고 들어가기. 왜 와이? 매번 사용자가 구매할 형편이 되는지 판단하기 위해!

        // 상품 목록 출력용 for문
        printf("상품 목록: ");      

        for(i = 0; i < 4; i++) {
            printf("%s / ", stuff[i]);
        }
        
        // 가격 출력용 for문
        printf("\n가     격: ");

        for(i = 0; i < 4; i++) {
            printf("%d / ", price[i]);
        }

        printf("\n");

        printf("구매할 물건을 입력하세요: ");
        scanf("%s", buy);

        // 사실 이 부분부터가 자판기 프로그램의 가장 핵심 로직 부분이라 생각 됨.
        for(i = 0; i < 4; i++) {                    // 물건 종류든 가격이든 4종류니까 4번 반복!
            if(strcmp(buy, stuff[i]) == 0) {        // strcmp는 파이썬에서 if('???' == '***') 같은 느낌? 맞으면 0 리턴 다르면 1 리턴
                if(usrmoney >= price[i]) {         // 사용자가 가진 돈이 품목들 중 살 수 있는 품목이 있으면
                    usrmoney -= price[i];          // 사용자 돈에서 그 금액만큼 깐다.
                    printf("잔액: %d원\n", usrmoney); // 그러고 잔액 출력. 
                    canBuy = true;                  // 구매가 가능한지 여부 확인
                    break;                          // for문 종료
                } else {
                    printf("잔액이 부족합니다.\n");
                }
            }
        }

        if(!canBuy) {                   // 살 능력없으면
            break;                      // while문 탈출
        }
    }

    return 0;
}