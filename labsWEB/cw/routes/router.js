const express = require('express');
const fs = require("fs")
const router = express.Router();

router.get("/", async (req, res) => {
    res.sendFile("/home/evgeny/git/labs_etu/labsWEB/cw/views/start.html")
})

router.get("/game", async (req, res) => {
    res.sendFile("/home/evgeny/git/labs_etu/labsWEB/cw/views/game.html")
})

router.get("/level_data/:level", async (req, res) => {
    let level = req.params["level"]
    switch (level) {
        case "1": res.send(fs.readFileSync("tilesets/city_level1_ready2.json")); break;
        case "2": res.send(fs.readFileSync("tilesets/city_level2_ready2.json")); break;
        default: res.send("{}")
    }
})
module.exports = router