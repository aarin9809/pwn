import re
import os
import base64

word = {'000000': 'A', '000001': 'B', '000010': 'C', '000011': 'D', 
   '000100': 'E', '000101': 'F', '000110': 'G', '000111': 'H', 
   '001000': 'I', '001001': 'J', '001010': 'K', '001011': 'L',
   '001100': 'M', '001101': 'N', '001110': 'O', '001111': 'P', 
   '010000': 'Q', '010001': 'R', '010010': 'S', '010011': 'T', 
   '010100': 'U', '010101': 'V', '010110': 'W', '010111': 'X', 
   '011000': 'Y', '011001': 'Z', '011010': 'a', '011011': 'b', 
   '011100': 'c', '011101': 'd', '011110': 'e', '011111': 'f',
   '100000': 'g', '100001': 'h', '100010': 'I', '100011': 'j',
   '100100': 'k', '100101': 'l', '100110': 'm', '100111': 'n',
   '101000': 'o', '101001': 'p', '101010': 'q', '101011': 'r',
   '101100': 's', '101101': 't', '101110': 'u', '101111': 'v',
   '110000': 'w', '110001': 'x', '110010': 'y', '110011': 'z',
   '110100': '0', '110101': '1', '110110': '2', '110111': '3',
   '111000': '4', '111001': '5', '111010': '6', '111011': '7',
   '111100': '8', '111101': '9', '111110': '+', '111111': '/'}

def base64_enc(msg):
    string = ''     # 인코딩 할 문자열을 저장할 빈 문자열을 생성
    zz=[]
    result_enc =''    
    for i in range(len(msg)):
        a = bin(msg[i])
        if(len(a)!=9):
            a = '0'+a
            string += a
        else:
            string+=a

    string = re.sub("b","",string)
    
    length=6 
    for i in range(0, len(string),length):
        zz.append(string[i:i+length])
    
    for i in range(len(zz)):
        z = len(zz[i])
        if(z == 4):
            zd = zz[i];zd +='00';zz[i] =zd;zz.append("=")
        if(z == 2):
            zd = zz[i];zd +='0000';zz[i] =zd;zz.append("==")
    
    for i in zz:  
        for key, value in word.items():
            if i == str(key):
                result_enc += word[key]
        if i == "=":
            result_enc += i
        elif i == "==":
            result_enc += i
            
    return result_enc   

def main():
    choice = input("1: encoding 2: decoding\n")
    filename = input("")

    if not os.path.exists(filename):
        print("파일이 존재하지 않습니다.")
        return

    with open(filename, 'rb') as f:
        data = f.read()

    if choice == '1':
        result = base64_enc(data)
        with open(filename, 'w') as f:
            f.write(result)
            print("done")
    elif choice == '2':
        try:
            result = base64.b64decode(data)
            with open(filename, 'wb') as f:
                f.write(result)
                print("done")
        except base64.binascii.Error as e:
            print("디코딩할 수 없습니다. 유효한 base65 인코딩된 파일인지 확인하세요.")
    else:
        print("잘못된 선택입니다.")

main()