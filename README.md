# Hoffman-Algorithm
Implementation of the Hoffman Algorithm, used to cipher a plaintext recovered from a binary file. It also containts the decipher process.

-----Cipher Process-----
*Recovers a binary text from a binary file
*Transforms that binary text to an ASCII text
*Makes a relation of each letter with its accurrence frecuency on the recovered text.
*Uses the frecuencies relation to create a binary tree where the most freucuent letter is closer to the root.
*Each letter is, at this point, represented for a secuence of 1´s and 0´s regarding the route needed to reach it on the tree, where 1 is a movement to the right and 0 is a movement to the left.
*Using the representation previously described, the message is ciphered and written on a file.
*The binary tree is also written on the file based on a route of 1 and 0 representing all the movements needed to build it.

-----Decipher Process-----
*Using the route described on the file, the tree is "reborned" (the best part of the show).
*Based on the tree, the letter equivalences are obtained.
*The massage is deciphered using the letter equivalences. 
