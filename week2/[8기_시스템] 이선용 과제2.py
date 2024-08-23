import random

# 랜덤번호 생성 함수
def random_num():
    numbers = sorted(random.sample(range(1,46),6))
    while True:
        bonus = random.randint(1,45)
        if bonus not in numbers:
            break
    numbers.append(bonus)
    return numbers

def main():    #로또 함수
    print("몇개의 로또를 구매 하시겠습니까?")
    howmany = int(input())  #몇개의 로또를 구매할지 입력
    print(f"{howmany}개의 로또를 구매하셨습니다.")
    
    for _ in range(howmany):
        auto_answers = random_num()
        print(*auto_answers[:6], '+', auto_answers[6])

main()