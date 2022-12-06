const express = require('express');
const path = require('path');
const server = express()
const fs = require("fs");
const https = require("https");

const PORT = process.env.PORT || 3000

server.use(express.static(path.join(__dirname, 'public')));
server.use("/audio", express.static(__dirname + "/public/audio"))
server.use("/images", express.static(__dirname + "/public/images"))
server.use("/", express.static(__dirname + "/public/scripts"))
server.use("/stylesheets", express.static(__dirname + "/public/stylesheets"))

server.set("views", express.static(__dirname + "/public/views"))

// HTTPS setup
let key  = fs.readFileSync('./public/certificate/lab.key', 'utf8');
let cert = fs.readFileSync('./public/certificate/lab.csr', 'utf8');

// HTTPS connection initialization
const httpsServer = https.createServer({key, cert}, server);

httpsServer.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`)
})

module.exports = server;

