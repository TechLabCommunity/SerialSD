# SerialSD

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
Actually, there are these commands:

* ```GET:key``` return value from **key**.
* ```LOG:hello``` write into log file hello string. If file doesn't exist, it will be created.
* ```ACK:test``` return the same request's string. This is useful when you want to know if system are available.

