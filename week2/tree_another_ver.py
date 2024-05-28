import os

def print_directory_tree():
    # 사용자로부터 디렉토리명을 입력받습니다.
    start_path = input("루트 디렉토리를 입력하세요: ")
    
    # 입력받은 디렉토리가 존재하는지 확인합니다.
    if not os.path.isdir(start_path):
        print("입력하신 디렉토리가 존재하지 않습니다.")
        return

    prefix = ''
    if start_path != "/":
        prefix = '|   '

    for root, dirs, files in os.walk(start_path):
        level = root.replace(start_path, '').count(os.sep)
        indent = prefix + '|   ' * (level - 1) + '|-- '
        print('{}{}/'.format(indent, os.path.basename(root)))
        sub_indent = prefix + '|   ' * level + '|-- '
        for f in files:
            print('{}{}'.format(sub_indent, f))

print_directory_tree()