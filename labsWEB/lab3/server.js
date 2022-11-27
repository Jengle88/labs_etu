const express = require("express")
const server = express()
const path = require('path');
const fs = require("fs");
const https = require("https");

const PORT = process.env.PORT || 3000

server.use(express.json({ extended: false }));

server.use(express.static(path.join(__dirname, 'public')));

server.use("/stylesheets", express.static(__dirname + '/public/stylesheets'))
server.use("/scripts", express.static(__dirname + '/public/scripts'))
server.use("/certificate", express.static(__dirname + '/public/certificate'))

server.set("views", __dirname + "/public/views")
server.set("view engine", "pug")

server.use("/api/users", require("./routes/users.js"))
server.use("/api/posts", require("./routes/posts.js"))
server.use("/", require("./routes/views.js"))


// HTTPS setup
let key  = fs.readFileSync('./public/certificate/lab.key', 'utf8');
let cert = fs.readFileSync('./public/certificate/lab.csr', 'utf8');

// HTTPS connection initialization
const httpsServer = https.createServer({key, cert}, server);

httpsServer.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})
