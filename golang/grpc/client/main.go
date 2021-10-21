package main

import (
	"log"
	"net"
	"os"
	"time"

	pb "prac/hello"

	"golang.org/x/net/context"
	"google.golang.org/grpc"
)

const (
	address     = "/tmp/hello.sock" //"localhost:50051"
	defaultName = "world"
)

func main() {
	// Set up a connection to the server.
	dialer := func(addr string, t time.Duration) (net.Conn, error) {
		return net.Dial("unix", address)
	}
	conn, err := grpc.Dial(address, grpc.WithInsecure(), grpc.WithDialer(dialer))
	if err != nil {
		log.Fatalf("did not connect: %v", err)
	}
	defer conn.Close()
	c := pb.NewHelloServiceClient(conn)

	// Contact the server and print out its response.
	name := defaultName
	if len(os.Args) > 1 {
		name = os.Args[1]
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()
	r, err := c.SayHello(ctx, &pb.HelloRequest{Greeting: name})
	if err != nil {
		log.Fatalf("could not greet: %v", err)
	}
	log.Printf("Greeting: %s", r.Reply)
}
