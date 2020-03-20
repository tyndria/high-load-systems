
Open questions:

- Why there is http_0 status and what does it mean in the context of my service
- Sometimes I'm getting protocol error


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

Yandex.Tank: https://overload.yandex.net/240494

schedule: line(10, 100, 3m) const(100, 10m) 

![Alt text](/images/plot3.png?raw=true)

This Tank test looks better, however, the service became unstable after 8 minutes.


4. Let's try to test NOT ONLY GET BUT PATCH REQUEST AS WELL

Yandex.Tank: https://overload.yandex.net/online/240572

schedule: line(10, 300, 10m)

ammo.txt:
```
242 
PATCH /hello_world/trashcan/trash_030.000000080.000000 HTTP/1.1
Host: xxxxxxxxx.dev.example.com
User-Agent: tank
Accept: */*
Content-Type: application/json
Connection: keep-alive
Content-Length: 33

{{"properties": {"plastic":true}}
171 
GET /hello_world/trashcans/lat/5/lng/5 HTTP/1.1
Host: xxxxxxxxx.dev.example.com
User-Agent: tank
Accept: */*
Content-Type: application/json
Connection: keep-alive

171 
GET /hello_world/trashcans/lat/5/lng/5 HTTP/1.1
Host: xxxxxxxxx.dev.example.com
User-Agent: tank
Accept: */*
Content-Type: application/json
Connection: keep-alive

171 
GET /hello_world/trashcans/lat/5/lng/5 HTTP/1.1
Host: xxxxxxxxx.dev.example.com
User-Agent: tank
Accept: */*
Content-Type: application/json
Connection: keep-alive

171 
GET /hello_world/trashcans/lat/5/lng/5 HTTP/1.1
Host: xxxxxxxxx.dev.example.com
User-Agent: tank
Accept: */*
Content-Type: application/json
Connection: keep-alive

```


![Alt text](/images/plot4.png?raw=true)

The service became unstable approximately on 130 rps.
I also see spike in memoty utilization (I'm not sure that I understand the reasons).

Let's try to test on 100 rps.

5. 100 RPS FOR GET AND PATCH

Yandex.Tank: https://overload.yandex.net/online/240579

![Alt text](/images/plot5.png?raw=true)

There is one spike on test but the overall picture looks not bad.
Excluding the spike the average response time is 200 ms.
