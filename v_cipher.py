#!/usr/bin/env python

import string
import itertools

Letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
CipherText = "ASUY KTM'PQ FUWQULYP DGOD KDUIX, FI ASW WMS MMQ YZYY FYUUSKN KTM"


def CaculateIC(text):
    sum = 0
    length = len(text)
    counts = [0] * 26
    for ch in text:
        if ch in Letters:
            index = Letters.find(ch)
            counts[index] += 1
    for num in counts:
        sum += (num * (num - 1))
    IC = sum / (length * (length - 1))
    return IC

def BreakIntoGroups(text, n):
    groups = []
    sum = 0

    for i in range(n):
        groups.append([])
    for i in range(len(text)):
        groups[i % n].append(text[i])
    for i in range(n):
        sum += CaculateIC(groups[i])
    return sum/n


def FlatText(text):
    FlatCipher = ""
    for ch in text:
        if ch in Letters:
            FlatCipher += ch
        else:
            continue
    return FlatCipher


def FindKeyLength(text):
    FlatCipher = FlatText(CipherText)
    maxIC = CaculateIC(CipherText)
    keyLen = 1

    for i in range(2, 5):
        IC = BreakIntoGroups(FlatCipher, i)
        if IC > maxIC:
            maxIC = IC
            keyLen = i
    return keyLen


def Decrypt(text):
    res = []
    keyLen = FindKeyLength(text)
    kIndex = 0
    allKeys = list(itertools.product(string.ascii_uppercase, repeat=keyLen))
    for key in allKeys:
        decypted = ""
        for ch in CipherText:
            if ch in Letters:
                offset = ord(key[kIndex]) - ord('A')
                newVal = Letters.find(ch) - Letters.find(key[kIndex])
                if newVal < 0:
                    newVal = 26 + newVal
                decypted += Letters[newVal]
                kIndex += 1
                if not kIndex < keyLen:
                    kIndex = 0
            else:
                decypted += ch

        res.append(f"Key: {key} = {decypted}")

    return res


with open("wordlist.txt", "r") as wordlist:
    s = "start"
    wordSet = set()

    while s != "":
        s = wordlist.readline()
        s = s.strip().upper()
        wordSet.add(s)

    possibleTexts = Decrypt(CipherText)
    filteredTexts = []

    for text in possibleTexts:
        count = 0
        text_split = text.split()

        for token in text_split:
            if token in wordSet:
                count += 1

        if count >= 7:
            filteredTexts.append(text)

    print(filteredTexts)

