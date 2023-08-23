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

def main():
    input_filename = "input.c"
    output_filename = "output.c"

    filtered_code = []

    with open(input_filename, "r") as fp:
        in_multi_line_comment = False

        for line in fp:
            line = line.strip()  # Remove leading/trailing whitespace
            if in_multi_line_comment:
                if '*/' in line:
                    in_multi_line_comment = False
                    _, line = line.split('*/', 1)
                else:
                    continue

            line = remove_comments(line)
            
            if not line:
                continue  # Skip empty lines

            filtered_code.append(line)

            if '/*' in line:
                if '*/' not in line:
                    in_multi_line_comment = True

    single_line_code = ' '.join(filtered_code)

    with open(output_filename, "w") as fw:
        fw.write(single_line_code)

    print(single_line_code)

if __name__ == "__main__":
    main()
