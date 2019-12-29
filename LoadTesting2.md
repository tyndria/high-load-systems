
Open questions:

1. Why there is http_0 status and what does it mean in the context of my service
2. Sometimes I'm getting protocol error

1. Let's test GET NEAREST request

Yandex.Tank: https://overload.yandex.net/240483

schedule: line(10, 600, 10m)

CPU & memory:

![Alt text](/images/init_plot.png?raw=true)

The chart above is not really presentable.

However, the system started to throw the following error `socketpair failed 24 (Too many open files)`,
starting from the ~100 rps. 
Let's try to change the osx configuration for the max open files.


2. Change max open files

Yandex.Tank: https://overload.yandex.net/online/240485

schedule: line(10, 600, 10m)

![Alt text](/images/init_plot2.png?raw=true)

Error `Too many open files` disappeared, but the service anyway crashed on ~130 rps approximately.

3. Decrease rps to 100

Yandex.Tank: https://overload.yandex.net/online/240493

schedule: line(10, 100, 3m) const(100, 10m) 

![Alt text](/images/plot3.png?raw=true)

This chart looks better, however, the service became unstable after 8 minutes.