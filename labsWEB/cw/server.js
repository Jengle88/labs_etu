const express = require('express');
const server = express()
const fs = require("fs");
const https = require("https");

const PORT = process.env.PORT || 3000

server.use("/audio", express.static(__dirname + "/audio"))
server.use("/images", express.static(__dirname + "/images"))
server.use("/scripts", express.static(__dirname + "/scripts"))
server.use("/stylesheets", express.static(__dirname + "/stylesheets"))
server.use("/certificate", express.static(__dirname + '/certificate'))
server.use("/", require("./routes/router.js"))

server.set("views", express.static(__dirname + "/views"))

// HTTPS setup
let key  = fs.readFileSync('./certificate/lab.key', 'utf8');
let cert = fs.readFileSync('./certificate/lab.csr', 'utf8');

// HTTPS connection initialization
const httpsServer = https.createServer({key, cert}, server);

httpsServer.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})
