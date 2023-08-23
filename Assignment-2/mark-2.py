import re

kws = ["int", "double", "float", "char", "for", "while", "do", "if", "else", "switch", "case"]
ops = "+-*/%=<>!|&"
pars = "(){}[]"
seps = ",;'\""
ids = {}
op = []
c = ''
s = ''
err = 0
rf = None

def read_file():
    global rf
    filename = input("\nEnter the filename: ")
    try:
        rf = open(filename, "r")
    except:
        print("Error opening file.")

def remove_comments(line):
    in_string = False
    new_line = []
    i = 0

    while i < len(line):
        if line[i] == '"' or line[i] == "'":
            in_string = not in_string
            new_line.append(line[i])
            i += 1
            continue

        if not in_string:
            if line[i:i+2] == '//':
                break
            elif line[i:i+2] == '/*':
                while i < len(line) - 1 and line[i:i+2] != '*/':
                    i += 1
                i += 2  # Skip '*/'
                continue

        new_line.append(line[i])
        i += 1

    return ''.join(new_line)

def lexemes():
    global s, op, c, err, rf
    code = remove_comments(rf.read())
    print("Assignment1: \n",code)
    i = 0
    line_number = 1
    print("Assignment2: \n")
    print()
    while i < len(code):
        c = code[i]

        if c == '\n':
            line_number += 1
            i += 1
        elif c in seps:
            print(f"[sep {c}] ", end='')
            i += 1
        elif c in pars:
            print(f"[par {c}] ", end='')
            i += 1
        elif c in ops:
            op = []
            while i < len(code) and code[i] in ops:
                op.append(code[i])
                i += 1
            print(f"[op {''.join(op)}] ", end='')
        elif c.isalpha() or c == '_':
            s = ''
            while i < len(code) and (code[i].isalnum() or code[i] == '_'):
                s += code[i]
                i += 1
            if s in kws:
                print(f"[kw {s}] ", end='')
            elif s == "return":
                print(f"[ret {s}] ", end='')
            else:
                if s not in ids:
                    ids[s] = len(ids) + 1
                print(f"[id {ids[s]}] ", end='')
        elif c.isdigit() or (c == '.' and i + 1 < len(code) and code[i + 1].isdigit()):
            s = ''
            while i < len(code) and (code[i].isdigit() or code[i] == '.'):
                s += code[i]
                i += 1
            print(f"[num {s}] ", end='')
        else:
            i += 1
            err += 1

    print("\nErrors:", err)
    print("Line number:", line_number)

def main():
    read_file()
    lexemes()
if __name__ == "__main__":
    main()
