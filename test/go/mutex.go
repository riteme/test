package main

import (
	"fmt"
	"math/rand"
	"sync"
	"sync/atomic"
	"time"
)

func main() {
	var rcnt, wcnt, ans uint64
	var mux sync.Mutex
	mem := make(map[int]int)

	for i := 0; i < 100; i++ {
		go func() {
			for {
				key := rand.Intn(8)
				mux.Lock()
				v := mem[key]
				mux.Unlock()
				atomic.AddUint64(&rcnt, 1)
				atomic.AddUint64(&ans, uint64(v))
				time.Sleep(time.Millisecond)
			}
		}()
	}

	for i := 0; i < 10; i++ {
		go func() {
			for {
				key := rand.Intn(8)
				val := rand.Int()
				mux.Lock()
				mem[key] = val
				mux.Unlock()
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
