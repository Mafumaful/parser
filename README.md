# parser🚛

整理了一下研究生做过的一个项目，写一个 parser。

整体流程是输入一个 bool 运算，进入 parser 生成对应的二叉树，并输出一个 bool 运算的结果。🧭

# 如何使用？🧼

```bash
make
parser
```

输入格式如下

```
1 * VAr ; VAr: 1, VAr: 0
1 * VAr ; VAr: 1
1 * VAr;VAr : 0
1 * VAr + 0
1 * VAr + 0 ; VAr 1
1 *(VAr + 0 );
A + B * -0 * (1 + -CD); A : 1, B : 0, CD : 1
A + B * -0 * (1 + -CD); A : 0, B : 0, CD : 1
   Ur * c; Ur:1, c:1
 Ur * c * (1+0)) ; Ur:1, c:1
 Ur * c * (1+0) ; Ur:1, c:1
 (1 * (a1 +VAr)) ; VAr: 1, a1: 0, VAr: 0
 (1 * (a1 +VAr)) !; VAr: 1, a1: 0, VAr: 1
1*0+-1;
 (1 * (0 +1)) ;
```

它将会产生相应的输出 🎫

```
Error: contradicting assignment
1
0
Error: invalid input
Error: invalid input
Error: incomplete assignment
1
0
1
Error: invalid input
1
Error: contradicting assignment
Error: invalid input
0
1

```

或者是修改 test_input.sh 文件 🎓 直接打印对应的输出结果。

```bash
chmod +x test_input.sh
./test_input.sh
```
