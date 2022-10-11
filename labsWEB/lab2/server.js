const express = require("express");
const server = express()

server.use(express.json({ extended: false }));

server.use("/styles", express.static(__dirname))
server.use("/scripts", express.static(__dirname + "/scripts"))

server.set("view engine", "pug")
server.set("views", __dirname)

server.use("/", require("./routes"))

const PORT = process.env.PORT || 3000

server.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})