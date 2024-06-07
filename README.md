# KBST
Реализация библиотеки для работы с K-мерными бинарными деревьями поиска(KBST) на языке C.
Эти деревья преимущественно используются для нахождения ближайшех соседей точки или набора точек в заданной гиперсфере или гиперпрямоугольнике.

ОБЩАЯ ИДЕЯ:
Из набора точек выбирается опорная точка, которая делит плоскость на две чаcти относительно одной из координат, 
в двухмерном пространстве - это вертикали и горизонтали.
Допустим, разделение сделано по горизонтали, то есть по оси Y, 
тогда в каждой из получившихся подплоскостях снова выбираются опорные точки, которые делят эти плоскости по следующей оси - оси X.
Получаем бинарное дерево, в котором вершинами являются опорные точки, 
а координата разделения меняется в зависимоти от глубины вершины (координата разделения = глубина вершины % мерность пр-ва).
При сравнении другой точки с точкой в дереве используется именно эта координата разделения.

# Работа с библиотекой
Чтобы подключить библиотеку к вашуме .c файлу, вам необходимо разместить файлы в libKBST.a и libKBST.h, а также папку libKBST в той же директории где и .c файл.
В .c файле подключить хедер библиотеки #include "libKBST.h", так вы сможете вызывать основные функции библиотеки.
Для линковки используйте команду "gcc <Ваш файл.c> libKBST.a -lm -I libKBST/source" в командной строке. -lm нужен для подсоединения библиотеки math.h,
проставление include path (-I) нужно для указания пути к хедерам бибилиотеки.
Для самостоятельной сборки библиотеки в папке libKBST есть скриптовый файл makeLib.sh, при вызове которого произойдёт сборка.

# Тест
Помимо самих файлов библиотеки, в репозитории также есть тестовая программа(test.c), её входные(input.txt) и выходные данные(output.txt), а также два .png файла(imgs)
для визуализации тестов. Тестовый файл и данные следует разместить в одной директории с libKBST.a, libKBST.h и libKBST.
