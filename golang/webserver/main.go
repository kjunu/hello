package main

import (
	"fmt"

	"github.com/gin-gonic/gin"
)

func main() {
	fmt.Println("vim-go")
	router := gin.Default()
	setupRouter(router)
}

func setupRouter(router *gin.Engine) {
	handler := Handler{}
	router.GET("/image", handler.GetImage)
}

type Handler struct {
}

func (h *Handler) GetImage(c *gin.Context) {
	fmt.Println("get Image")
}
