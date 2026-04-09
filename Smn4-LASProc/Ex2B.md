# Ex 2B

## a)

```c
pid_t pid1 = fork();
printf("pid1 %d\n", pid1);
pid_t pid2 = fork();
printf("pid2 %d\n", pid2);
```

affichage:
pid1 123
pid2 124
4 proc

## b)

```c
for (int i=1; i<=3; i++)
{
 pid_t pid = fork();
 if (pid != 0)
 printf("%d - pid %d\n", i, pid);
}
```

affichage:
1 - pid 123
2 - pid 124
3 - pid 125
 process

## c)

```c
for (int i=1; i<=3; i++)
{
 pid_t pid = fork();
 if (pid == 0) break;
 else printf("%d - pid %d\n", i, pid);
}
```

affichage:
