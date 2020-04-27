# C

Содержание:

memcached_client.c  файл с исходным кодом. Содержит три функции: setData, getData, deleteData. 

build_script.sh   - скрипт для сборки memcached_client.c

telnet_test.exp  - скрипт с проверкой через telnet. Он написан на expect

memclient.exp  - скрипт для запуска приложения memclient. Написан с помощью синтаксиса expect

файл .travis.yml в корневом каталоге репозитория содержит инструкции для сборки проекта

Проверка осуществляется через Travis-CI:    https://travis-ci.org/

Для проверки можно:
1. fork
2. зайти на Travis-CI
3. запустить сборку
