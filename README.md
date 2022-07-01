# Alphabetic-CipherCrack
This program will take in a file with lines of text (all of Shakespeare's work in a .txt or ciphertext to crack, for example) and will count each instance of single letters, bigrams (two letter sequences), and trigrams (three letters).

It will then put all of the counts and information alongside it into an outfile (specified in the Command Line Argument).

FYI: This is meant to be used as more of a "tool" to produce further assumptions/studying about a replacement cipher, rather than a program to directly "crack" a cipher.
The counting of letters in this manner does *not* directly give you the cracked code.
________________________
Once compiled, the program should be run in this format:<pre>
./[executableName] inFile outFile
</pre>

*** An outfile will be created on your machine if the outfile specified by the command line does not exist ***
