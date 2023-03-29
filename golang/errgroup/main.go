package main

import (
	"context"
	"fmt"

	"golang.org/x/sync/errgroup"
)

func internal(i int) error {
	if i%2 == 0 {
		return fmt.Errorf("internal error %d", i)
	}
	return nil
}

func main() {
	fmt.Println("vim-go")
	group, _ := errgroup.WithContext(context.Background())
	for i := 0; i < 10; i++ {
		iInFor := i
		group.Go(func() error {
			err := internal(iInFor)
			if err != nil {
				fmt.Println("handle error", err)
				return err
			}
			fmt.Println("handle success", iInFor)
			fmt.Println("weird i", i, iInFor)
			return nil
		})
	}
	if err := group.Wait(); err != nil {
		fmt.Println("catch group error here")
		return
	}
	fmt.Println("finish process")
	return
}
