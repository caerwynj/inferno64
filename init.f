include /forth/helpers.f

include /forth/ns.f
" ns before" type cr
ns

" #b"	" /dev"	MAFTER	sbind	\ kbd
" #c"	" /dev"	MAFTER	sbind	\ console device
\ " #d"	" /fd"	MREPL	sbind 	\ dup(3)	crashes 9ferno
\ " #e"	" /env"	MREPL MCREATE or sbind	\ environment
\ " #i"	" /dev"	MREPL	sbind	\ draw device
" #l0"	" /net"	MAFTER	sbind	\ Ethernet device
\ " #m"	" /dev"	MAFTER	sbind	\ pointer/mouse
" #p"	" /proc"	MREPL	sbind	\ proc device
\ " #r"	" /dev"	MAFTER	sbind	\ rtc
\ " #s"	" /chan"	MREPL	sbind	\ server registry	crashes 9ferno
" #t"	" /dev"	MAFTER	sbind	\ serial line
\ " #v"	" /dev"	MAFTER	sbind	\ VGA
" #I0"	" /net"	MAFTER	sbind	\ IP
" #P"	" /dev"	MAFTER	sbind	\ arch
" #S"	" /dev"	MAFTER	sbind	\ Disks
" #f"	" /dev"	MREPL	sbind	\ forth device

" ns after" type cr
ns

1 2 + 3 + 4 + 5 + .
: first 1 2 + 3 + . ;

first

" end of init.f" type cr
