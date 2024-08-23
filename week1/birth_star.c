/*
생년월일 입력 받아서 몇 월인지 영어/별자리로 출력하기[배열]
1) 사용자로부터 생년월일을 입력받고, 해당 월을 영어로 출력하며 해당 월일에 맞게 별자리를 알려주는 프로그램을 작성하시오.
2) 사용자로부터 정확한 생년월일을 입력 받아야하며, 올바르지 않은 입력
[예: 잘못된 날짜 형식, 존재하지않는 날짜 등]이 입력되면 프로그램은 종료되어야 함.

주의 사항
1) 해당 프로그램을 만들땐 배열을 필수적으로 사용할 것.
2) 입력받은 생년월일을 배열을 이용해서 처리하면 됨.
3) 입력받은 월과 일을 기반으로 별자리를 결정함.
    별자리는 특정 날짜 범위에 따라 결정되므로, 이 범위를 정의하고 입력받은 날짜가 어느 범위에 속하는지 확인하는 로직을 구현해야 함.

별자리표
양자리 : 3월 21일 ~ 4월 19일
황소자리 : 4월 20일 ~ 5월 20일
쌍둥이자리 : 5월 21일 ~ 6월 21일
게자리 : 6월 22일 ~ 7월 22일
사자자리 : 7월 23일 ~ 8월 22일
처녀자리 : 8월 23일 ~ 9월 23일
천칭자리 : 9월 24일 ~ 10월 22일
전갈자리 : 10월 23일 ~ 11월 22일
사수자리 : 11월 23일 ~ 12월 24일
염소자리 : 12월 25일 ~ 1월 19일
물병자리 : 1월 20일 ~ 2월 18일
물고기자리 : 2월 19일 ~ 3월 20일

=================================================

pseudo code
변수
1) 쪼개진 년 배열, 월 배열, 일 배열
2) for문에 사용할 i
3) 영어로 된 달 배열
4) 입력받은 월에 따라 영어로 된 달을 리턴하는 함수

'-' 기준으로 생년월일을 입력받는다. - 완료
'-'를 기준으로 년 월 일을 나눠서 각 배열에 저장한다. - 완료 
1월이면 영어 월 배열에서 1번째 배열에 있는 수를 적용.
1월일때 "january"가 나와야하는 조건 0<mm && mm<2

for 

*/

#include <stdio.h>

// 각 별자리의 시작 날짜 (월과 일)
const int start[12][2] = {              //각 별자리별로 시작하는 달과 일을 2차원 배열로 초기화
                            {3, 21},  
                            {4, 20},  
                            {5, 21},  
                            {6, 21},  
                            {7, 23},  
                            {8, 23},  
                            {9, 23},  
                            {10, 23}, 
                            {11, 22}, 
                            {12, 22}, 
                            {1, 20},  
                            {2, 19} 
};

// 각 별자리의 이름
const char *const star_signs[12] = {
                                    "양자리",
                                    "황소자리",
                                    "쌍둥이자리",
                                    "게자리",
                                    "사자자리",
                                    "처녀자리",
                                    "천칭자리",
                                    "전갈자리",
                                    "사수자리",
                                    "염소자리",
                                    "물병자리",
                                    "물고기자리"    //별자리 배열
};

char month[12][10] = { 
                        "January",
                        "Fabuary", 
                        "March", 
                        "April", 
                        "May", 
                        "June", 
                        "July", 
                        "August", 
                        "September", 
                        "October", 
                        "November", 
                        "December"}; //달 배열

char* what_is_month(int mm) {   // 입력한 달을 판별하여 그에 맞는 영어 달을 판별하는 함수
    if (mm >= 1 && mm <= 12)
        return month[mm - 1];
    else
        return "";
}

int main() {
    int year;
    int month;
    int day;
    int i;

    printf("생년월일을 입력하세요 (YYYY-MM-DD): ");
    scanf("%04d-%d-%d", &year, &month, &day);

    // 입력한 날짜를 판별해 영어 달과 별자리를 출력하는 로직
    for (i = 0; i < 12; i++) {
        if ((month == start[i][0] && day >= start[i][1]) ||
            (month == start[(i + 1) % 12][0] && day < start[(i + 1) % 12][1])) {
            printf("%s %s\n", what_is_month(month), star_signs[i]);
            break;
        }
    }

    if (i == 12) {
        printf("유효하지 않은 날짜입니다.\n");
    }
    return 0;
}



/*
별자리표
양자리 : 3월 21일 ~ 4월 19일
황소자리 : 4월 20일 ~ 5월 20일
쌍둥이자리 : 5월 21일 ~ 6월 21일
게자리 : 6월 22일 ~ 7월 22일
사자자리 : 7월 23일 ~ 8월 22일
처녀자리 : 8월 23일 ~ 9월 23일
천칭자리 : 9월 24일 ~ 10월 22일
전갈자리 : 10월 23일 ~ 11월 22일
사수자리 : 11월 23일 ~ 12월 24일
염소자리 : 12월 25일 ~ 1월 19일
물병자리 : 1월 20일 ~ 2월 18일
물고기자리 : 2월 19일 ~ 3월 20일
    // printf("Year: %d\n", yy[0]);
    // printf("Month: %02d\n", mm[0]);
    // printf("Day: %02d\n", dd[0]);
*/