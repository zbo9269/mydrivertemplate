#! /usr/bin/env python
""" """

def opendriver():
    fd = open("/dev/driver0","w",0)
    try: 
        fd.write("12")
    except IOError as err:  
        print(err) 
    return fd  

def closedriver(fd):
    fd.close()

if __name__ == "__main__":
    fd = opendriver()  
    closedriver(fd) 
