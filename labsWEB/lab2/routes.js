const express = require("express")
const router = express.Router()

let database = require("./storage/data.json")

router.get("/", async (req, res) => {
    console.log(`Open main page`)
    res.render('start', {
        value: database.books
    })
})

router.get("*", (req, res) => {
    res.status(404)
    res.end("Not found")
})

module.exports = router