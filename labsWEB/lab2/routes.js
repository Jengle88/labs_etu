const express = require("express")
const router = express.Router()

let database = require("./storage/data.json")

router.get("/", (req, res) => {
    res.render('start', {
        value: database.books
    })
})