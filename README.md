# Vigenere Cypher

## Introduction

The original Vigenere Cypher is a message encrypting method. Thanks to a key, it can encrypt a message using a simple addition method. Each letter of the alphabet represent a number (eg 'a' = 1, 'b' = 2 etc.). The value of the letters of the message are added to the value of the letters of the key. For example, with the message 'HELLOWORLD' and the key 'ABC', the cypher would do:
```
  HELLOWORLD
+ ABCABCABCA
= IGOMQZPTOE
```

## This cypher

This version of the Vigenere Cypher is quite different. It has 2 encrypting and decrypting method:
- An alphabetical version, with letter from 'a' to 'z' and from 'A' to 'Z' (and the space ' ')
- A full ASCII version, encrypting anything that is ASCII

The alphabetical version is easier to use for copy and paste. However it is not a real Vigenere Cypher as the values of the letters are not 'a' = 1, 'b' = 2 etc.


## How to use

Launch the Vigenere-Cypher.exe or build the main.cpp and launch the executable. When launched, everything is explained.

## Author 

Thomas RABIAN - thomas.rabian@protonmail.com
