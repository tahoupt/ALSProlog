---
title: 'see/1'
predicates:
 - 'see/1' : sets the current input stream
 - 'seeing/1' : returns the name of the current input stream
 - 'seen/0' : closes the current input stream
---
`see/1` `--` sets the current input stream

`seeing/1` `--` returns the name of the current input stream

`seen/0` `--` closes the current input stream


## FORMS

see(File)

seeing(File)

seen


## DESCRIPTION

see/1 sets the current input stream to the file named File. If File is already open for input, the existing file descriptor will be used. Otherwise, a new file descriptor will be allocated, and input operations will start at the beginning of the file.

seeing/1 unifies File with the name of the current input stream. If no stream has been explicitly opened by see/1, then file will be unified with the atom user.

seen/0 closes the current input stream and deallocates its file descriptor. The current input stream is then set to the special file
user

.
user

is the name of the default input stream which is normally connected to the keyboard. The special file user is always present, and seen/0 can never close it. Although seen/0 can never close the file user, seen/0 will reset the user I/O descriptor as follows. If a read/n has been executed from user, and if an end of file character sequence is encountered(Control-D on Unix or the Mac, or Control-Z on Win32/DOS and on the Mac), then the read/n returns end_of_file and a subsequent seen/0 on user will reset the I/O descriptor for user so that the EOF condition is no longer present.


## EXAMPLES

The following program will

- preserve the current input stream

- open a file

- read one term from it

- restore the previous input stream

firstTerm(File, Term) :-

seeing(CurrentInput),

see(File),

read(Term),

seen,

see(CurrentInput) .


## SEE ALSO

- `see/1`  
`seeing/1`  
`seen/1`  
`open/3`  
`open/4`  
`close/1`  
`close/2`  
`UserGuide(PrologI/O)`  
`[Bowen91`  
`7.8]`  
`[Clocksin81`  
`5.4]`  
`[Bratko86`  
`6.1].