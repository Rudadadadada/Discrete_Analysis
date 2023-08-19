# Лабораторные работы по курсу "Дискретный анализ"

#### [`ЛР 1: сортировка за линейное время`](https://github.com/Rudadadadada/Discrete_Analysis/tree/master/lab1)
Сортировка за линейной время - сортировка, которая не использует операцию сравнения.
Вариант N. 5-2. Требуется разработать программу, осуществляющую ввод пар «ключ-значение», их упорядочивание по возрастанию ключа указанным алгоритмом сортировки за линейное время и вывод отсортированной последовательности.
- Тип сортировки: сортировка подсчётом.
- Тип ключа: числа от 0 до 65535.
- Тип значения: строки фиксированной длины 64 символа, во входных данных могут встретиться строки меньшей длины, при этом строка дополняется до 64-х нулевыми символами, которые не выводятся на экран.

#### [`ЛР 2: сбалансированные деревья`](https://github.com/Rudadadadada/Discrete_Analysis/tree/master/lab2)

Вариант 2. Необходимо создать программную библиотеку, реализующую указанную структуру данных, на основе которой разработать программу-словарь. В словаре каждому ключу, представляющему из себя регистронезависимую последовательность букв английского алфавита длиной не более 256 символов, поставлен в соответствие некоторый номер, от 0 до 264 - 1. Разным словам может быть поставлен в соответствие один и тот же номер.

Программа должна обрабатывать строки входного файла до его окончания. Каждая строка может иметь следующий формат:
- `+ word 34` — добавить слово «word» с номером 34 в словарь. Программа должна вывести строку «OK», если операция прошла успешно, «Exist», если слово уже находится в словаре.
- `- word` — удалить слово «word» из словаря. Программа должна вывести «OK», если слово существовало и было удалено, «NoSuchWord», если слово в словаре не было найдено.
- `word` — найти в словаре слово «word». Программа должна вывести «OK: 34», если слово было найдено; число, которое следует за «OK:» — номер, присвоенный слову при добавлении. В случае, если слово в словаре не было обнаружено, нужно вывести строку «NoSuchWord».
- `! Save /path/to/file` — сохранить словарь в бинарном компактном представлении на диск в файл, указанный парамером команды. В случае успеха, программа должна вывести «OK», в случае неудачи выполнения операции, программа должна вывести описание ошибки (см. ниже).
- `! Load /path/to/file` — загрузить словарь из файла. Предполагается, что файл был ранее подготовлен при помощи команды Save. В случае успеха, программа должна вывести строку «OK», а загруженный словарь должен заменить текущий (с которым происходит работа); в случае неуспеха, должна быть выведена диагностика, а рабочий словарь должен остаться без изменений. Кроме системных ошибок, программа должна корректно обрабатывать случаи несовпадения формата указанного файла и представления данных словаря во внешнем файле.

Для всех операций, в случае возникновения системной ошибки (нехватка памяти, отсутсвие прав записи и т.п.), программа должна вывести строку, начинающуюся с «ERROR:» и описывающую на английском языке возникшую ошибку.

Различия вариантов заключаются только в используемых структурах данных: Красно-чёрное дерево.


#### [`ЛР 3: исследование качества программ`](https://github.com/Rudadadadada/Discrete_Analysis/tree/master/lab3)

Для реализации словаря из предыдущей лабораторной работы, необходимо провести исследование скорости выполнения и потребления оперативной памяти. В случае выявления ошибок или явных недочётов, требуется их исправить.
Результатом лабораторной работы является отчёт, состоящий из:
- Дневника выполнения работы, в котором отражено что и когда делалось, какие средства использовались и какие результаты были достигнуты на каждом шаге выполнения лабораторной работы.
- Выводов о найденных недочётах.
- Сравнение работы исправленной программы с предыдущей версией.
- Общих выводов о выполнении лабораторной работы, полученном опыте.

Для профилирования были использованы утилиты gprof и Valgrind.

#### [`ЛР 4: строковые алгоритмы`](https://github.com/Rudadadadada/Discrete_Analysis/tree/master/lab4)

Вариант K. 4-1. Необходимо реализовать один из стандартных алгоритмов поиска образцов для указанного алфавита.
- Вариант алгоритма: Поиск одного образца основанный на построении Z-блоков.
- Слова не более 16 знаков латинского алфавита (регистронезависимые).
