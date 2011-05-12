<code><strong>logredirect<strong></code> is a simple tool to grab stdout from one program and redirect it in a pro logging system. It comes in help when your program spits lots of output and you want to roll, max size logs, etc. It uses log4c as backend. 

Requirements
------------

* log4c

Compile
-------

	./make

Usage
-----

Suppose you have a program that spits on stdout if you want to store that on a file. Then you can do this:

	$ myprogram | ./logredirect myprogram.test

This will redirect the stdout from <code>myprogram</code> to a log configured on the file <code>log4crc</code>. Second parameter <code>root.test</code> is a logging category that conforms on log4c mechanism. See log4c docs and <code>log4crc</code> for more details. 

Next work
---------

* add regex to match err, info. Probably with pcre. 
* port to Windoze

