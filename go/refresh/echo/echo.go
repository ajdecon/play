package main

import (
    "net"
    "io"
    "io/ioutil"
    "fmt"
    "log"
)

func main() {
    l, err := net.Listen("tcp",":36000")
    if (err!=nil) {
        log.Fatal(err)
    }
    for {
        conn, err := l.Accept()
        if (err != nil) {
            log.Fatal(err)
        }
        go func(c net.Conn) {
            buf, err := ioutil.ReadAll(c)
            if (err != nil) {
                log.Fatal(err)
            }
            fmt.Println("Received message: ", string(buf))
            io.WriteString(c,fmt.Sprintf("You said: %s",string(buf)))
            c.Close()
        }(conn)
    }

}
