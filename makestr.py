#!/usr/bin/python
from base64 import b32encode
from string import translate, maketrans
from rc4 import rc4crypt
import sys

key = "abcd"
msg = "FORTRAN rots the brain.  -- John McQuillin"

if len(sys.argv) > 1:
    msg = sys.argv[1]

# pad msg with spaces to 5 byte boundary to avoid '==='
if len(msg) % 5:
    msg += ' ' * (5 - len(msg) % 5)

crypt = rc4crypt(msg, key)
b32crypt = b32encode(crypt)
remapped = translate(b32crypt,
    maketrans("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567",
              "3:5[9&2^]{7}*<-8@=4(6#!>|)0+;1$%"))

print "msg: %s (size=%d)" % (msg, len(msg))
print "crypt: %s" % [ord(i) for i in crypt]
print "b32crypt: %s" % b32crypt
print "remapped: %s (size %d)" % (remapped, len(remapped))
