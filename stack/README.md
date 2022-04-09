# Класс `Stack`
Стек на динамическом массиве.

## Создание
Создаётся пустой стек:
```c++
Stack<int> s;
std::cout << s.isEmpty();   // True
```

## Добавление и удаление элементов
Без излишеств:
```c++
Stack<int> s;
s.push(12);
std::cout << s.isEmpty() << ' ' << s.pop() << ' ' << s.isEmpty();   // False 12 True
```

## Верхушка стека
```c++
Stack<int> s;
s.push(12);
std::cout << s.top() << ' ';    // 12
s.push(100);
std::cout << s.top() << ' ';    // 100
```

## Сложность операций
| Функция  | Время  |
| -------- | ------ |
| `push()` | $O(n)$ |
| `pop()`  | $O(1)$ |
| `top()`  | $O(1)$ |

В худшем случае метод `push()` работает за $O(n)$. В среднем за $(???)$.