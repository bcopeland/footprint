#!/usr/bin/python
import re

def copy_tokens(count, tokens):
    out = ''
    while count > 0 and tokens:
        ttype, tval = tokens[0]
        if ttype == 'QSTR':
            # split string into as many chars as will fit
            to_copy = min(count, len(tval))
            out += '"%s"' % (tval[0:to_copy])
            if to_copy >= len(tval):
                tokens = tokens[1:]
            else:
                tokens[0] = (ttype, tval[to_copy:])
            count -= to_copy
        else:
            # copy the whole thing, might overrun
            out += tval
            count -= len(tval)
            tokens = tokens[1:]

    return out, count, tokens

def tokenize(s):
    token_specification = [
        ('QSTR',    r'"[^"]*"'),
        ('NUMBER',  r'\d+(\.\d*)?'),
        ('ID',      r'[A-Za-z0-9_$]+'),
        ('DOP',     r'(\+\+)|(\+=)'),
        ('OP',      r'[+*\/\-=|&<>?%^!]'),
        ('SPACE',   r'[ \t\n]+'),
        ('OTHER',   r'[\[\]{}();,:]'),
    ]
    tok_regex = '|'.join('(?P<%s>%s)' % pair for pair in
        token_specification)

    get_token = re.compile(tok_regex).match
    match = get_token(s)
    pos = 0
    while match:
        ttype = match.lastgroup
        val = match.group(ttype)
        # dequote
        if ttype == 'QSTR':
            val = val[1:-1]
        yield (ttype, val)
        pos = match.end()
        match = get_token(s, pos)

    print '%s' % s[pos:]

csrc = "decrypt.c"
template = "foot.txt"

code_str = ""
for l in open(csrc):
    # skip preproc
    if l.startswith('#') or l.startswith('//'):
        continue

    #markup reserved words that need spaces..
    l = re.sub(r'(q|typedef|int|char|unsigned|return|case) ', r'\1~', l)
    # drop all other spaces
    l = re.sub(r' *', '', l)
    # add back needed spaces
    l = re.sub(r'~', ' ', l)

    code_str += l.strip()

code_len = len(code_str)
template_str = ""
for l in open(template):
    template_str += l

out_str = ""
codetoks = list(tokenize(code_str))
for ttype,tstr in tokenize(template_str):

    if not codetoks:
        break
    code_type, code_str = codetoks[0]

    if ttype == 'SPACE':
        out_str += tstr
        if code_type == 'SPACE':
            codetoks = codetoks[1:]

    else:
        add_str, rem, codetoks = copy_tokens(len(tstr), codetoks)
        out_str += add_str

print '%s' % out_str
print "/* code len: %s */" % code_len

