---
title: 'put_code/[1,2]'
predicates:
 - 'put_code/1' : output a character code to the current output stream
 - 'put_code/2' : output a character code to a specific output stream
---
`put_code/1` `--` output a character code to the current output stream

`put_code/2` `--` output a character code to a specific output stream


## FORMS

put_code(Char)

put_code(Stream_or_Alias, Code)


## DESCRIPTION

put_code/1 will write out the character code bound to Char to the current output stream.

put_code/2 will write out the character code bound to Char to the output stream associated with Stream_or_Alias.


## EXAMPLES

```
?- put_code(0'\t),put_code(0'h),put_code(0'o),put_code(0'w),
?-_put_code(0'd),put_code(0'y),put_code(0'\n).
howdy
yes.
```


## ERRORS

Stream_or_Alias is a variable

-- -- -- -- &gt; instantiation_error.

Stream_or_Alias is neither a variable nor a stream descriptor nor an alias

-- -- -- -- &gt; domain_error(stream_or_alias, Stream_or_Alias) .

Stream_or_Alias is not associated with an open stream

-- -- -- -- &gt; existence_error(stream, Stream_or_Alias) .

Stream_or_Alias is not an output stream

-- -- -- -- &gt; permission_error(output, stream, Stream_or_Alias) .

Code is a variable

-- -- -- -- &gt; instantiation_error.

Code is neither a variable nor a character

-- -- -- -- &gt; type_error(character, Code) .


## SEE ALSO

- `get_code/1`  
`put_char/1`  
`open/4`  
`close/1`  
`char_code/2`  
`nl/1`

- **_User Guide(Prolog I/O)_**