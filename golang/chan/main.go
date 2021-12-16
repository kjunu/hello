package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int)

	go func() {
		fmt.Println("start send")
		ch <- 1000
		for i := 0; i < 3; i++ {
			fmt.Println("send", i)
			time.Sleep(100 * time.Microsecond)
			ch <- i
			if i == 2 {
				close(ch)
			}
		}
	}()
	time.Sleep(300 * time.Microsecond)
	fmt.Println("start wait")
EXIT:
	for {
		select {
		case in, ok := <-ch:
			if ok {
				fmt.Println("recv", in)
				if in == 1 {
					time.Sleep(2 * time.Second)
					continue
				}
			} else {
				fmt.Println("not ok", in)
				break EXIT
			}
			fmt.Println("end")
		}
	}
	fmt.Println("vim-go")
}
