# Построение CFG
## Сборка и запуск
 
```
1. git clone https://gitlab.se.ifmo.ru/pavel5926/popov-pavel-spo-2024 
2. cd popov-pavel-spo-2024
3. git checkout develop
4. cd Lab-2
```
- 2 Средство сборки - `CMake`. ОС - `Linux`.
```
    5. mkdir build && cd build
    6. cmake ..
    7. make
    8. ./cfgbuilder - исполняемый файл
```
- 3 Поддержка аргумнентов командной строки есть, но я для отладки сэмулировал `argc` и `argv`. Пример есть в `main.c`. Редактируется по аналогии при желаниии. 

## Комментарий
1. Корневая директория второй лабораторной работы `Lab-2`. Будем считать, что мы находимся в ней.

2. Тестовые примеры. Необходимо класть в директорию `input`. Подготовлены два тестовых примера. 
    - `prog-1.txt` - упор сделан на построение CFG.
    - `prog-2.txt` - упор сделан на построение Call Graph.
3. Выхоные файлы с графами генерируются в директорию `output/<prog-name>`.
## P.S.
В системе должна быть установлена библиотека antlr3c ерсии 3.4.

На случай, если со сборкой возникнут неустранимые проблемы,
прикладываю графы, которые хотел показать, в папку `graphs`.