Requirements
------------

* log4c

Compile
-------

	./make

Usage
-----

Suppose you have a program that spits on stdout if you want to store that on a file. Then you can do this:

	$ myprogram | ./logredirect root.test

This will redirect the stdout from <code>myprogram</code> to a log configured on the file <code>log4crc</code>. Details in configuring that 


Next work
---------

* add regex to match err, info. Probably with pcre. 
* port to Windoze

