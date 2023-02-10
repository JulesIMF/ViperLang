def spaces(maxlen, len):
    return " " * (maxlen - len)

with open('toks') as toks:
    for line in toks:
        t = line.strip().split(' ')
        print(f'type_["{t[1]}"] {spaces(len("continue"), len(t[1]))}= TokenType::{t[0]};')