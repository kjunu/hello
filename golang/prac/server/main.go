package main

import (
	"fmt"
	"log"
	"net"
	"sync/atomic"
	"time"

	pb "prac/hello"

	"golang.org/x/net/context"
	"google.golang.org/grpc"
	"google.golang.org/grpc/reflection"
)

const (
	port = "192.168.0.177:50051"
)

// server is used to implement helloworld.GreeterServer.
type server struct{}

var secRPC uint64
var totalRPC uint64

// SayHello implements helloworld.GreeterServer
func (s *server) SayHello(ctx context.Context, in *pb.HelloRequest) (*pb.HelloResponse, error) {
	atomic.AddUint64(&totalRPC, 1)
	atomic.AddUint64(&secRPC, 1)
	time.Sleep(time.Millisecond * 100)
	return &pb.HelloResponse{Reply: "Hello " + in.Greeting}, nil
}

func main() {
	secRPC = 0
	totalRPC = 0
	go printRPC()
	lis, err := net.Listen("tcp", port)
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	s := grpc.NewServer()
	pb.RegisterHelloServiceServer(s, &server{})
	// Register reflection service on gRPC server.
	reflection.Register(s)
	if err := s.Serve(lis); err != nil {
		log.Fatalf("failed to serve: %v", err)
	}
}

func printRPC() {
	for {
		time.Sleep(time.Second)
		sec := atomic.LoadUint64(&secRPC)
		tot := atomic.LoadUint64(&totalRPC)
		fmt.Println("RPC cnt", sec, tot)
		secRPC = 0
	}
}
