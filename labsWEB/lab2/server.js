const express = require("express");
const server = express()
const path = require('path');

server.use(express.json({ extended: false }));

server.use(express.static(path.join(__dirname, 'public')));

server.use("/styles", express.static(__dirname + '/public/styles'))
server.use("/scripts", express.static(__dirname + '/public/scripts'))

server.set("view engine", "pug")
server.set("views", __dirname + "/public/templates")

server.use("/", require("./routes"))

const PORT = process.env.PORT || 3000

server.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})