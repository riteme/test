#!/usr/bin/env python

print('Get the average of some numbers.')
numstr=input('Please enter some numbers: ')

# read into list
strlist=numstr.split()
value=0.0
for s in strlist:
	value+=float(s)
average=value/len(strlist)
offest=0.0
for s in strlist:
	offest+=pow(float(s)-average,2)

# get average
print('The average of them is',average)
print('The offest of them is',offest)

