const express = require("express")
const router = express.Router()
const fs = require("fs")

/**
 * @type {{books: [{id: "", title: "", author: "", status: "", return_date: ""}]}}
 * @desc Array with books
 */
let database = require("./storage/data.json")


/**
 * @route GET /api/get_book/:book_id
 * @param book_id - id of the required book
 * @desc Return available ID for new book
 */
router.get("/api/get_book/:book_id", (req, res) => {
    if (isNaN(Number(req.params.book_id)))
        res.send("Invalid book id")

    const id = Number(req.params.book_id)
    const book = database.books.find(item => item.id === id)
    res.send(book)
})

/**
 * @route GET /api/get_books
 * @desc Return array of books
 */
router.get("/api/get_books", (req, res) => {
    res.send(database.books)
})

/**
 * @route POST /api/add_book
 * @desc Add new book to storage
 */
router.post("/api/add_book", (req, res) => {
    let book = req.body.book

    if (!book)
        res.send("Error book data")

    book.id = getFreeId()
    database.books.push(book)
    fs.writeFileSync("./storage/data.json", JSON.stringify(database))
    res.send(database)
})

/**
 * @route GET /
 * @desc Loads start page with books
 */
router.get("/", async (req, res) => {
    database = require("./storage/data.json")
    console.log(`Open start page`)
    res.render('start', {
        value: database.books
    })
})

/**
 * @route GET /add_new_book
 * @desc Loads page for new book
 */
router.get("/add_new_book", async (req, res) => {
    console.log(`Open add_book page`)
    res.render('add_book')
})

/**
 * @route GET *
 * @desc If request not found
 */
router.get("*", (req, res) => {
    res.status(404)
    res.end("Not found")
})

function getFreeId() {
    let id = 1
    for (let book of database.books) {
        if (book.id >= id) {
            id = book.id + 1
        }
    }
    return id
}

module.exports = router