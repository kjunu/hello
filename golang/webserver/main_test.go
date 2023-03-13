package main

import (
	"net/http"
	"net/http/httptest"
	"testing"

	"github.com/gin-gonic/gin"
	"github.com/stretchr/testify/assert"
)

func TestMain(t *testing.T) {
	router := gin.Default()
	setupRouter(router)
	req, err := http.NewRequest("GET", "/image", nil)
	assert.NoError(t, err)
	rr := httptest.NewRecorder()
	router.ServeHTTP(rr, req)
}
