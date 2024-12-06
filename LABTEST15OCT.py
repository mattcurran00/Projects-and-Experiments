#function to check valid, function to fix, main function
#get string - if exit entered exit program - check string valid - if not valid fix - if valid print

import random # import random for adding characetrs
import string # import string for string functions

def is_valid(usr):  # function to check if password is valid
    if len(usr) < 10: # chekc lenght
        print("Password not valid - Too short")
        return False
    
    has_uppercase = False
    for char in usr:
       
        if char.isupper():
            has_uppercase = True
            break
    if has_uppercase == False:
        return False
    

    if not any(char.isdigit() for char in usr):  # check for numbers
        print("Password not valid - No digit")
        return False

    if not any(char in string.punctuation for char in usr):  # check for special characters
        print("Password not valid - No special character")
        return False

    return True  # if no if statements trigger its a valid password

def strengthen_password(usr):
    if len(usr) < 10:  # add random characters to meet length. trigger first as adding random characters may satisdfy following if statements 
        while len(usr) < 10:
            usr += random.choice(string.ascii_letters + string.digits + string.punctuation)
        print("Password lengthened to meet 10 characters") # passworf now valid
    
    if not any(char.isupper() for char in usr):  # add uppercase letter if missing
        usr += random.choice(string.ascii_uppercase) # cat random uppercase letter to existing string
        print("Added an uppercase letter")

    if not any(char.isdigit() for char in usr):  # add number if missing
        usr += random.choice(string.digits) # cat random number to existing string 
        print("Added a digit")

    if not any(char in string.punctuation for char in usr):  # add special character if missing
        usr += random.choice(string.punctuation) # cat special character to existing string 
        print("Added a special character")
    
    return usr

def main():
    while True:
        usr = input("Enter password for evaluation (or type 'exit'): ") # prompt user for password

        if usr.lower() == "exit":  # exit condition, use lower for simplicity
            print("Exiting program.")
            break # break out of loop
        
        if not is_valid(usr): # cherck if password valifd
            usr = strengthen_password(usr) # call strenghten function to strengthen password

        print("Valid Password:", usr)

main() # call main
