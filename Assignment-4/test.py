def main():
    try:
        p2 = open("input.txt", "r")
        p4 = open("output.txt", "w")
    except:
        print("Error")
        return

    line = 1
    cnt = 0
    kw = ["int", "float", "double", "if", "else", "for", "return", "void"]
    sc = ['(', ')', '{', '}', ';', ',', '=', '<', '>']
    M = {}

    while True:
        print(f"{line}: ", end='')
        line_str = p2.readline().strip()
        
        if not line_str:
            break
        
        if len(line_str) > 1 and line_str[0] == '/' and (line_str[1] == '*' or line_str[1] == '/'):
            print()
        else:
            print(line_str)
            temp = ""
            checkstr = ""
            forchk = False
            ifchk = 0
            cnt1 = 0
            cnt2 = 0
            
            for i in range(len(line_str)):
                temp += line_str[i]
                
                if temp == "for":
                    forchk = True
                    
                if temp == "if":
                    cnt2 = 0
                    ifchk = 1
                elif temp == "else" and ifchk != 2:
                    if line - 1 not in M:
                        M[line - 1] = []
                    M[line - 1].append("Unmatched 'else' at ")
                
                if line_str[i] == ')':
                    cnt1 = 0
                    forchk = False
                
                if temp in kw and checkstr in kw and checkstr not in ["if", "else"]:
                    if line - 1 not in M:
                        M[line - 1] = []
                    M[line - 1].append("Back to back keyword at ")
                    checkstr = temp
                    temp = ""
                
                if line_str[i] in sc:
                    checkstr = temp = ""
                
                if line_str[i] == ' ':
                    check = '.'
                    temp = temp[:-1]
                    checkstr = temp
                    temp = ""
                    continue
                elif line_str[i] == ';' and forchk:
                    cnt1 += 1
                    if cnt1 > 2:
                        if line - 1 not in M:
                            M[line - 1] = []
                        M[line - 1].append("Duplicate token at ")
                elif line_str[i] == ';':
                    if ifchk != 1:
                        ifchk = 0
                    if ifchk == 1 and cnt2 == 0:
                        ifchk = 2
                    if check == ';':
                        if line - 1 not in M:
                            M[line - 1] = []
                        M[line - 1].append("Duplicate token at ")
                    check = ';'
                elif line_str[i] == '{':
                    if ifchk == 1:
                        cnt2 += 1
                    cnt += 1
                    check = '.'
                elif line_str[i] == '}':
                    if ifchk != 1:
                        ifchk = 0
                    if ifchk == 1:
                        cnt2 -= 1
                    if ifchk == 1 and cnt2 == 0:
                        ifchk = 2
                    check = '.'
                    cnt -= 1
                    if cnt < 0:
                        if line - 1 not in M:
                            M[line - 1] = []
                        M[line - 1].append("Misplaced '}' at ")
                        cnt = 0
                else:
                    check = '.'

        line += 1

    print()
    for key, value in M.items():
        for item in value:
            print(item + str(key))
            p4.write(item + str(key) + "\n")

    p2.close()
    p4.close()

if __name__ == "__main__":
    main()
