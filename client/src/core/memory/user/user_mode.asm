.code

user_read_virtualmemory PROC
	mov r10 , rcx
	mov eax , 3Fh 
	syscall 
	ret
user_read_virtualmemory ENDP


user_write_virtualmemory PROC
	mov r10 , rcx
	mov eax , 3Ah
	syscall
	ret
user_write_virtualmemory ENDP



END
