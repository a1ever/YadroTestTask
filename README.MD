# Тестовое задание YADRO

## [Условия](test_task.pdf)

## Тестирование
С помощью GoogleTests.
Тестируется парсер входных данных и результаты работы самого приложения.

## О решении
Есть класс GameClub, который представляет собой singleton.
Он хранит в себе текущее состояние компьютерного клуба - какие столы заняты, очередь ожидания, сколько денег за столы получено.

Класс Parser - отвечает за обработку входных данных, возвращает строку если была ошибка, также создает event и запускает действие связанное с каждым событием.

Класс IEventCommand - общий интерфейс для событий, имеет функцию execute.
С помощью функции execute происходит взаимодействие с GameClub, также она может вернуть исходящее событие.

Класс ProcessGameClub - основная точка взаимодействия с системой, принимает в себя поток с которого будет происходить чтения, и поток в который будет происходить вывод.
После запуска его метода Run, начнется анализ входного файла.
```c++
    std::ifstream fin(test_filename);
    auto process = gameclub::ProcessGameClub (fin, std::cout);
    process.Run();
```