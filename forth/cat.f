: ioerror ( n -- ) ." ioerror: " . cr ;

: show ( read_count -- )
	dup 0 < if ioerror then
	pad swap ( 'pad read_count ) type ;

: untileof ( fd -- fd )
		begin
			dup pad 1024 sysread ( fd read_count )
			?dup while show ( fd )
		repeat ;

: cat ( 'filename-counted-string -- )
	count ( 'filename nfilename )
	cstring0 r/o sysopen ( fd )
	dup -1 > ( fd fd>=0? )
	if ( fd ) untileof sysclose drop
	else ." open error: " .
	then ;

: scat ( 'filename nfilename -- ) \ nfilename = length of filename
   cstring0 r/o sysopen ( fd )
	dup -1 > ( fd fd>=0? )
	if ( fd ) untileof sysclose drop
	else ." open error: " .
	then ;
