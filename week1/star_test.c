#include <stdio.h>

// 각 별자리의 시작 날짜 (월과 일)
const int start_dates[12][2] = {
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
                                        "물고기자리"
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

char* what_is_month(int mm) {
    if (mm >= 1 && mm <= 12)
        return month[mm - 1];
    else
        return "Invalid month";
}

int main() {
    int year, month, day;

    printf("생년월일을 입력하세요 (YYYY-MM-DD): ");
    scanf("%d-%d-%d", &year, &month, &day);

    int i;
    for (i = 0; i < 12; i++) {
        if ((month == start_dates[i][0] && day >= start_dates[i][1]) ||
            (month == start_dates[(i + 1) % 12][0] && day < start_dates[(i + 1) % 12][1])) {
            printf("%s %s\n", what_is_month(month), star_signs[i]);
            break;
        }
    }

    if (i == 12) {
        printf("유효하지 않은 날짜입니다.\n");
    }

    return 0;
}
