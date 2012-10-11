i think its all done, the validExecute basically check for permissions.
mode 0= check R, mode 1= RX, mode 2 = RW. it is checked 2 times in a few cases. also, change ALL the words of Permission to Permissions <<<<<(with a S) in funix, directory, and permissions.cpp. be sure all the output matches sean, especially error messages. if they are not right, just change it yourself.
