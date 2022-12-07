const express = require('express');
const router = express.Router();

router.get("/", async (req, res) => {
    res.sendFile("/home/evgeny/git/labs_etu/labsWEB/cw/views/start.html")
})

router.get("/game", async (req, res) => {
    res.sendFile("/home/evgeny/git/labs_etu/labsWEB/cw/views/game.html")
})
module.exports = router