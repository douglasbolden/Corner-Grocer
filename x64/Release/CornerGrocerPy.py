#This is for the Counters we will be using to collect frequencies.
from collections import Counter
#Use of Regular Expressions
import re
#Use of Strings
import string

"""
DISCLAIMER:
COUNTERS CREATE A DICTIONARY, AND IN USING A DICTIONARY
WE CAN USE BOTH THE KEY AND THE VALUE as needed.
"""

"""
ItemsList()
Opens a file, and then displays only the items IN ALPHABETICAL ORDER!
"""
def ItemsList():
    c = Counter()
    
    # You will need to change this location to the location that your file is saved to.
    with open('C:\\Users\\dougl\\Desktop\\daily-items.txt') as itemlist:
        for line in itemlist:
            c[line.rstrip()] += 1

    for d, e in sorted(c.items()):
        print('{}'.format(d))

"""
PrintFrequencies()
Opens a file, and then displays the whole list IN ALPHABETICAL ORDER!
"""
def PrintFrequencies():
    c = Counter()
    
    # You will need to change this location to the location that your file is saved to.
    with open('C:\\Users\\dougl\\Desktop\\daily-items.txt') as itemlist:
        for line in itemlist:
            c[line.rstrip()] += 1

    for d, e in sorted(c.items()):
        print('{}: {}'.format(d, e))
        
"""
PrintFrequencies()
Opens a file, and then returns selected items value.
"""
def PrintSpecificFrequencies(specificWord):
    c = Counter()
    
    # You will need to change this location to the location that your file is saved to.
    with open('C:\\Users\\dougl\\Desktop\\daily-items.txt') as itemlist:
        for line in itemlist:
            c[line.rstrip()] += 1
            
    value = c['{}'.format(specificWord)]
    return value

"""
PrintFrequencies()
Opens a file, and then saves the list IN ALPHABETICAL ORDER!
Then displays the whole list IN ALPHABETICAL ORDER.
"""
def SaveDat():
    c = Counter()
    
    # You will need to change this location to the location that your file is saved to.
    with open('C:\\Users\\dougl\\Desktop\\daily-items.txt') as itemlist:
        for line in itemlist:
            c[line.rstrip()] += 1
    
    # You will need to change this location to the location that your file is saved to.
    with open('C:\\Users\\dougl\\Desktop\\frequency.dat', 'w') as file:
        for d, e in sorted(c.items()):
            file.write('{}: {}\n'.format(d, e))
            print('{}: {}'.format(d, e))

    print('Above List written to file frequency.dat')
