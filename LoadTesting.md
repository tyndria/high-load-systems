1. Найдем оптимальное значение rps

Проведем сначала тест при увеличении rps от 10 до 1000 в течение 10 минут.
Для мониторинга использования памяти и процессора используем утилиту `psrecord`.

Тест в Яндекс.Танк: https://overload.yandex.net/online/239675

Мониторинг CPU / Memory:

![Alt text](/images/plot1.png?raw=true)

Разладка сервиса наступае при ...

2. Проведем тестирование при оптимальном значении

line(10, 300, 3m) const(300, 12m)

Тест в Яндекс.Танк: https://overload.yandex.net/online/239684

Мониторинг CPU / Memory:

![Alt text](/images/plot2.png?raw=true)