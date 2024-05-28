# from os import listdir
# from os.path import isdir, join
# from anytree import Node, RenderTree
# from anytree.exporter import DotExporter
import os
import os.path
import anytree.exporter
import anytree

# 노드 추가 함수
def add_nodes(parent_node, directory):
    items = os.listdir(directory)
    for i in items:
        path = os.path.join(directory, i)
        child_node = anytree.Node(i, parent=parent_node)
        if os.path.isdir(path):
            add_nodes(child_node, path)

def main():
    # 사용자 디렉명 입력.
    root_dir = input("디렉토리를 입력하세요: ")

    if not os.path.isdir(root_dir):
        print("디렉토리가 존재하지 않습니다.")
        return
        
    root_node = anytree.Node(root_dir)
    add_nodes(root_node, root_dir)
    
    for pre, fill, node in anytree.RenderTree(root_node):
        print("%s%s" % (pre, node.name))

main()