.name "wrong op"
.comment "sd command"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live 1				#wrong arg for live
		zjmp %:live