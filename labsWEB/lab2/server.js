const express = require("express");
const server = express()


server.set("view engine", "pug")
server.set("views", __dirname)

const PORT = process.env.PORT || 3000

server.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})