include /forth/helpers.f

1 2 + 3 + 4 + 5 + .
: first 1 2 + 3 + . ;

first

include /forth/ns.f
" ns before" type cr
ns

"	#l0" " /net" MAFTER sbind
"	#I0" " /net" MAFTER sbind

" ns after" type cr
ns


" end of init.f" type cr
