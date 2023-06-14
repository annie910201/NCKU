.source hw3.j
.class public Main
.super java/lang/Object
.method public static another_function()V
.limit stack 20
.limit locals 20
ldc "another_function"
getstatic java/lang/System/out Ljava/io/PrintStream;
swap
invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L_exit:
return
.end method
.method public static is_divisible_by(II)B
.limit stack 20
.limit locals 20
iload 2
iload 1
; ------here is if start------
iload 2
ldc 0
isub
; --- here is equal to ---
ifeq L_if_0
goto L_if_1
L_if_0: 
; ---------equal end---------
goto L_exit
L_if_1: 

; ------if_end------
iload 1
iload 2
irem
ldc 0
isub
; --- here is equal to ---
ifeq L_if_2
goto L_if_3
L_if_2: 

L_if_3: 
; ---------equal end---------
L_exit:
return
.end method
.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
invokestatic Main/another_function()V
ldc 3
istore 0
ldc 2
istore 1
; ------here is if start------
iload 0
iload 1
invokestatic Main/is_divisible_by(II)B
ifeq L_if_4
goto L_if_5
L_if_4: 
ldc "divisible"
getstatic java/lang/System/out Ljava/io/PrintStream;
swap
invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L_if_5: 
; ------if_end------
ldc "not divisible"
getstatic java/lang/System/out Ljava/io/PrintStream;
swap
invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
L_exit:
return
.end method
