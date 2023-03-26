# Сервер-приложение для управления шагающим роботом
## Подгрузка всех модулей
```bash
git submodule update --init --recursive
```
Подгружаемые модули:
- palitra_ros2 [^1]
- palette-server-api [^2]
- palette-server-ui [^3]
## Запуск сервера
```bash
ros2 launch server-core-pkg core.launch.py
```
## Конфигурация запуска
При необходимости указывать аргументы запуска модулей в launch файле:
> server-core-pkg/launch/core.launch.py

[^1]: [Модуль moveit и симуляции](https://github.com/ArtemVinokurov/palitra_ros2/tree/dev)
[^2]: [Модуль API сервера](https://github.com/MrLeonardPak/palette-server-api/tree/dev)
[^3]: [Модуль UI](https://github.com/MrLeonardPak/palette-server-ui/tree/cli)
