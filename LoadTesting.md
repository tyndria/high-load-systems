1. Find "optimal" rps value

Conduct a test with the following schedule `line(10, 3000, 15m)`.

`psrecord` was used to record memory and cpu utilization.

Yandex.Tank test: https://overload.yandex.net/online/239951

CPU & memory:

![Alt text](/images/plot1.png?raw=true)

The response increased after __~500 rps__. According to the `psrecord` 
it seems that _cpu_ plot has several critical moments.

2. Test "optimal" rps value

Let's choose __300 rps__ as optimal value.

`line(10, 300, 3m) const(300, 15m)`

Yandex.Tank test: https://overload.yandex.net/online/239957

CPU & memory:
 
![Alt text](/images/plot2.png?raw=true)

It's quite difficult to assess this test because response time is bad since the beginning of the test. There were a tests when the service worked fine with 300 rps, for example, this one https://overload.yandex.net/239684.

Let's try to edit nginx config, set `worker_processes  4` and run 
the previous test again.

Yandex.Tank test: https://overload.yandex.net/online/239961

![Alt text](/images/plot3.png?raw=true)

The response time looks much more better, approximately average response time is 50 ms.

Unfortunately I don't see significant changes on psrecord charts.



