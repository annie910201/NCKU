.source hw3.j
.class public Main
.super java/lang/Object
.method public static main([Ljava/lang/String;)V
.limit stack 100
.limit locals 100
ldc 1
istore 0
iload 0
L_while_0: 
ldc 100
isub
; ------while_start------
iflt L_while_1
goto L_while_2
L_while_1: 
iload 0
getstatic java/lang/System/out Ljava/io/PrintStream;
swap
invokevirtual java/io/PrintStream/println(I)V
iload 0
iload 0
ldc 1
iadd
istore 0
goto L_while_0
L_while_2: 

; ------while_end------
return
.end method
