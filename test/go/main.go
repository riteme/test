package main

import (
	"fmt"
	"time"
	"math/rand"
	"sync/atomic"
)

type ReadOp struct {
	key int
	resp chan int
}

type WriteOp struct {
	key int
	val int
	resp chan bool
}

func main() {
	var rcnt, wcnt, ans uint64
	reads := make(chan ReadOp)
	writes := make(chan WriteOp)

	go func() {
		mem := make(map[int]int)
		for {
			select {
			case rop := <-reads:
				rop.resp <- mem[rop.key]
			case wop := <-writes:
				mem[wop.key] = wop.val
				wop.resp <- true
			}
		}
	}()

	for i := 0; i < 100; i++ {
		go func() {
			for {
				ch := make(chan int)
				reads <- ReadOp{
					key: rand.Intn(8),
					resp: ch,
				}
				atomic.AddUint64(&ans, uint64(<-ch))
				atomic.AddUint64(&rcnt, 1)
				time.Sleep(time.Millisecond)
			}
		}()
	}

	for i := 0; i < 10; i++ {
		go func() {
			for {
				ch := make(chan bool)
				writes <- WriteOp{
					key: rand.Intn(8),
					val: rand.Int(),
					resp: ch,
				}
				<-ch
				atomic.AddUint64(&wcnt, 1)
				time.Sleep(time.Millisecond)
			}
		}()
	}

	time.Sleep(time.Second)
	r := atomic.LoadUint64(&rcnt)
	w := atomic.LoadUint64(&wcnt)
	fmt.Println("read:", r)
	fmt.Println("write:", w)
	fmt.Println(atomic.LoadUint64(&ans))
}