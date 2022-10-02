/*
const express = require('express')
const port = 3000
const app = express()

app.get('/', (req, res) => {
    res.send("Hello world!")
}).listen(port);

*/

const server = require("express")();
const port = 3000

server.get("/page", (req, res, next) => {
    res.end("Here is a page")
    next()
})

server.get("/", (req, res, next) => {
    res.end("Root Page")
    next()
})

server.get("*", (req, res) => {
    res.status(404)
    res.end("page not found")
})

server.listen(port, () => {
    console.log(`Server started at http://localhost:${port}`)
})
