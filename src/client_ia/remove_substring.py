#!/usr/bin/python

def remove_substring(s):
    badsubstring = ["{", "}", " "]
    for badsubstrings in badsubstring:
        s = s.replace(badsubstrings, "")
        s.split()
    return s
