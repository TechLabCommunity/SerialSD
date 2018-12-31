# SerialSD

![alt text](https://img.shields.io/appveyor/ci/gruntjs/grunt.svg "Build passed")

SerialSD is a project to manage **configuration** and **log** file.  
This project needs one Arduino's compatible board and SdFat library.

## How it works

This software must be upload into an Arduino's board with SD Adapter and this memory must be formatted in FAT32.  
Afterwards, creation of non-empty single file named _CONFIG.TXT_ is required with a syntax like this:  

```
key1:value1
key2:value2
```

":" is the default delimiter.

Then, connect RX and TX pin to your main board project and start to send serial requests.

## Serial request

For the sake of simplicity, a serial request has the same config file's syntax.  
Serial has ```\n``` terminator and it was set 150 like maximum buffer size .  
Actually, there are these commands:

* ```GET:key``` return value from **key**.
* ```LOG:hello``` write into log file hello string. If file doesn't exist, it will be created.
* ```ACK:test``` return the same request's string. This is useful when you want to know if system are available.

For the first part, **case is insensitive**.
For each request, the result can be **OK** or **ERR**.
When you got **ERR**, there are only some cases:

* ```KEY_NOT_FOUND``` When you GET a key which doesn't exist.
* ```IMPOSSIBLE_WRITE``` When you LOG but there're problems with SD.
* ```BAD_REQUEST``` When format request is invalid.
* ```MAX_TIMEOUT_REACH``` When Serial has recorded some bytes, but there's no terminator in 3 seconds.

## System errors

SerialSD must be always on. So, all errors return a **SYSERR** and cause a sotware reset after 10 seconds.  
Some possible troubles:

* ```FILE_NOT_FOUND``` some required files weren't found.
* ```BEGIN_SD_FAILED``` SdFat library begin failed.
* ```UNKNOWN``` Unknown errors.

## Test it!

**test** folder has many bash script files and you can launch them to test requests:  
```console
test/test_ack.sh /dev/ttyUSB0
```
