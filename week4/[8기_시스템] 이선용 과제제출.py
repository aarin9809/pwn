'''
command에 help를 입력하면 매뉴얼이 출력됩니다.
showall을 입력하면 전체 정보가 출력됩니다.

원하는 정보를 검색하고 싶은 경우 해당하는 커맨드를 입력하세요.

'''
import pefile
import os


def dos_header(command):
    if(command == "emagic"):
        print(pe.DOS_HEADER.e_magic)
        
    elif(command == "lfanew"):
        print(pe.DOS_HEADER.e_lfanew)

    else:
        file_header(command)

def file_header(command):
    if(command == "machine"):
        print(pe.FILE_HEADER.Machine)

    elif(command == "numsection"):
        print(pe.FILE_HEADER.NumberOfSections)

    elif(command == "timestamp"):
        print(pe.FILE_HEADER.TimeDateStamp)

    elif(command == "szoption"):
        print(pe.FILE_HEADER.SizeOfOptionalHeader)

    else:
        optional_header(command)

def optional_header(command):
    if(command == "szcode"):
        print(pe.OPTIONAL_HEADER.SizeOfCode)

    elif(command == "epaddr"):
        print(pe.OPTIONAL_HEADER.AddressOfEntryPoint)

    elif(command == "imgbase"):
        print(pe.OPTIONAL_HEADER.ImageBase)

    elif(command == "dllchar"):
        print(pe.OPTIONAL_HEADER.DllCharacteristics)

    else:
        section_header(command)

def section_header(command):
    if(command == "secname"):
        for section in pe.sections:
            print(section.Name.decode('utf-8'))

    elif(command == "secva"):
        for section in pe.sections:
            print(section.Name.decode('utf-8'), hex(section.VirtualAddress))

    elif(command == "secraw"):
        for section in pe.sections:
            print(section.Name.decode('utf-8'), section.SizeOfRawData)

    else:
        fix(command)

def fix(command):
    if(command == "fiximg"):
        imagebase = int(input("Input Value: "))
        pe.OPTIONAL_HEADER.ImageBase = imagebase

    elif(command == "fixepaddr"):
        epaddr = int(input("Input Value: "))
        pe.OPTIONAL_HEADER.AddressOfEntryPoint = epaddr

    else:
        etc(command)

def etc(command):
    if(command == "exit"):
        exit()

    elif(command == "clear"):
        os.system("clear")

    elif(command == "cls"):
        os.system("cls")

    elif(command == "dump"):
        print(pe.dump_info())

    elif(command == "textdump"):
        print(pe.get_memory_mapped_image())

    elif(command == "help"):
        print_help()

    elif(len(command) == 0):
        pass
    
    elif(command == "showall"):
        showall()

    else:
        print("Command is not found")


def showall() :
    print("\n[DOS Header]")
    print("e_magic: ", pe.DOS_HEADER.e_magic)
    print("e_lfanew: ", pe.DOS_HEADER.e_lfanew)

    print("\n[FILE Header]")
    print("Machine: ", pe.FILE_HEADER.Machine)
    print("NumberOfSections: ", pe.FILE_HEADER.NumberOfSections)
    print("TimeDateStamp: ", pe.FILE_HEADER.TimeDateStamp)
    print("SizeOfOptionalHeader: ", pe.FILE_HEADER.SizeOfOptionalHeader)
    print("Characteristics: ", pe.FILE_HEADER.Characteristics)

    print("\n[OPTIONAL Header]")
    print("Magic: ", pe.OPTIONAL_HEADER.Magic)
    print("AddressOfEntryPoint: ", pe.OPTIONAL_HEADER.AddressOfEntryPoint)
    print("ImageBase: ", pe.OPTIONAL_HEADER.ImageBase)
    print("SectionAlignment: ", pe.OPTIONAL_HEADER.SectionAlignment)
    print("FileAlignment: ", pe.OPTIONAL_HEADER.FileAlignment)
    print("SizeOfImage: ", pe.OPTIONAL_HEADER.SizeOfImage)
    print("DllCharacteristics: ", pe.OPTIONAL_HEADER.DllCharacteristics)

    print("\n[SECTION Headers]")
    for section in pe.sections:
        print("\nName: ", section.Name.decode('utf-8'))
        print("VirtualSize: ", section.Misc_VirtualSize)
        print("VirtualAddress: ", hex(section.VirtualAddress))
        print("SizeOfRawData: ", section.SizeOfRawData)
        print("PointerToRawData: ", section.PointerToRawData)
        print("Characteristics: ", section.Characteristics)

    print("\n[DATA Directories]")
    for idx, entry in enumerate(pe.OPTIONAL_HEADER.DATA_DIRECTORY):
        print("\nDirectory", idx)
        print("Size: ", entry.Size)
        print("VirtualAddress: ", hex(entry.VirtualAddress))

    if hasattr(pe, 'DIRECTORY_ENTRY_IMPORT'):
        print("\n[IMPORT Table]")
        for entry in pe.DIRECTORY_ENTRY_IMPORT:
            print("\nDLL Name: ", entry.dll.decode('utf-8'))
            for imp in entry.imports:
                print("Ordinal: ", imp.ordinal)
                print("Name: ", imp.name.decode('utf-8') if imp.name else "")

    if hasattr(pe, 'DIRECTORY_ENTRY_EXPORT'):
        print("\n[EXPORT Table]")
        for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
            print("\nOrdinal: ", exp.ordinal)
            print("Address: ", hex(exp.address))
            print("Name: ", exp.name.decode('utf-8') if exp.name else "")

def print_help():
    print(""" 
    ----------------------------------------------------------
    |      Command                        Comment            |
    ----------------------------------------------------------
    |                        DOS_HEADER                      |
    ----------------------------------------------------------
    |    emagic                     Show Machine             |
    |    lfanew                     Show lfanew              |
    |    cblp                       Show cblp                |
    |    cp                         Show cp                  |
    |    crlc                       Show crlc                |
    |    cparhdr                    Show cparhdr             |
    |    minalloc                   Show minalloc            |
    ----------------------------------------------------------
    |                        FILE_HEADER                     |
    ----------------------------------------------------------
    |    machine                    Show Machine             |
    |    numsection                 Show NumberOfSections    |
    |    timestamp                  Show TimeDateStamp       |
    |    szoption                   Show SizeOfOptionalHeader|
    ----------------------------------------------------------
    |                      OPTIONAL_HEADER                   |                             
    ----------------------------------------------------------
    |    szcode                     Show SizeOfCode          |                                   
    |    epaddr                     Show AddressOfEP         |
    |    imgbase                    Show ImageBase           |
    |    dllchar                    Show DllCharacteristics  |
    ----------------------------------------------------------
    |                       SECTION_HEADER                   |
    ----------------------------------------------------------
    |    secname                    Show Name of Sections    |
    |    secva                      Show VA of Sections      |
    |    secraw                     Show SizeOfRawData       |
    ----------------------------------------------------------
    |                          Fix                           |
    ----------------------------------------------------------
    |    fiximg                     fix Value of ImageBase   |
    |    fixepaddr                  fix Value of EP Address  |
    ----------------------------------------------------------  
    |                          Etc                           |
    ----------------------------------------------------------
    |    clear                      Linux User clear         |
    |    cls                        Windows User clear       |
    |    exit                       Exit the program         |
    |    help                       Show Command             |
    |    showall                    Show all Information     |
    ----------------------------------------------------------
    """)

filepath = input("file name: ")
pe = pefile.PE(filepath)

while(1):
    command = input("command:")
    dos_header(command)