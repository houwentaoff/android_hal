# gps & gprs

1. QA
`cat /dev/ttyUSB2 &;echo "at+csq" >/dev/ttyUSB2`
```
返回: +CSQ: 22,99
```
2. 断开连接gprs
`kill -INT \`cat /var/run/ppp0.pid\`` not `kill -9 \'cat /var/run/ppp0.pid\'`

3. Use Reset gpio not Power gpio.

