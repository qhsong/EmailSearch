A big string search test
===========
we use Bloomfilter and Trie to find it in ten million emails.As input files isn't a regular email string,we use some function to filter that email address.
This is first homework in bupt proggramming course.The program is used to search one hundred email addresses in ten million which is not case sensitive.If it appeared,print "yes",or print "no".

BloomFilter
--------
To achieve it ,I use Bloom Filter algrithm.In order to build a index ,I use a 28M bit array to store the it.
