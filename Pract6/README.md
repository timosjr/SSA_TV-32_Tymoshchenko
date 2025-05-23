# Завдання 1 (варіант 20)

## Умова

Зберіть ASan summary table: тип помилки, приклад, реакція інструмента, час виконання.

## Виконання

У таблиці зібрані помилки, приклад коду з цією помилкою, реакція інструмента та час виконання.

| №  | Тип помилки                        | Приклад коду                                                             | Реакція ASan                                                                                              | Час виявлення   |
|----|-----------------------------------|--------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------|-----------------|
| 1  | **Вихід за межі масиву (stack buffer overflow)** | ```c\nchar buf[5]; buf[5] = 'x';```                                          | `stack-buffer-overflow` з вказаним рядком, адресою та зміщенням                                          | Під час виконання |
| 2  | **Вихід за межі купи (heap buffer overflow)**    | ```c\nchar *p = malloc(4); p[4] = 'x';```                                   | `heap-buffer-overflow`, адреса виділення і точка помилки                                                  | Під час виконання |
| 3  | **Use-after-free**                 | ```c\nchar *p = malloc(10); free(p); p[0] = 'a';```                            | `heap-use-after-free`, показує, де виділили, де звільнили, де помилилися                                  | Під час виконання |
| 4  | **Double free**                    | ```c\nchar *p = malloc(10); free(p); free(p);```                               | `attempting double-free`, ASan вкаже на подвійне звільнення                                               | Під час виконання |
| 5  | **Stack use after return**         | ```c\nchar* foo() { char local[10]; return local; }```                         | Може проявитися як `stack-use-after-return` або `SEGV`, залежно від компілятора та опцій                       | Під час виконання |
| 6  | **Глобальний вихід за межі(global buffer overflow)**       | ```c\nextern char global[5]; char x = global[6];```                             | `global-buffer-overflow`, якщо глобальна змінна перевищена                                                | Під час виконання |
| 7  | **Невірне звільнення (invalid free)** | ```c\nint a; free(&a);```                                                   | `attempting free on address which was not malloc()`                                                       | Під час виконання |

### №1 Вихід за межі масиву (stack buffer overflow)

![](task20/ex1.png)

### №2 Вихід за межі купи (heap buffer overflow)

![](task20/ex2.png)

### №3 Use-after-free

![](task20/ex3.png)

### №4 Double free

![](task20/ex4.png)

### №5 Stack use after return

![](task20/ex5.png)

### №6 Глобальний вихід за межі(global buffer overflow)

![](task20/ex6.png)

### №7 Невірне звільнення (invalid free)

![](task20/ex7.png)
