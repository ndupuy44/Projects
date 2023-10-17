#!/usr/bin/env python

CipherText = "v jbaqre vs jr'yy rire or chg vagb fbatf be gnyrf"
Letters = "abcdefghijklmnopqrstuvwxyz"

#First for loop to go through all possible shifts
for shift in range(len(Letters)):
    Decrypted = ""
    #Second for loop applies shifts to cipher text
    for ch in CipherText:
        if ch in Letters:
            CharVal = Letters.find(ch)
            ShiftVal = CharVal - shift
            if ShiftVal < 0:
                ShiftVal = ShiftVal + 26
            Decrypted = Decrypted + Letters[ShiftVal]
        else:
            Decrypted = Decrypted + ch
    print(f"Key = {shift} left, {26-shift} right: {Decrypted}")
