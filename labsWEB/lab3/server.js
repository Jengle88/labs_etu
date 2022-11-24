const express = require("express")
const server = express()
const path = require('path');

const PORT = process.env.PORT || 3000

server.use(express.json({ extended: false }));

server.use(express.static(path.join(__dirname, 'public')));

server.use("/stylesheets", express.static(__dirname + '/public/stylesheets'))
server.use("/scripts", express.static(__dirname + '/public/scripts'))

server.set("views", __dirname + "/public/views")
server.set("view engine", "pug")

server.use("/", require("./routes/posts.js"))


server.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})