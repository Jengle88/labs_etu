/*
const express = require('express')
const port = 3000
const app = express()

app.get('/', (req, res) => {
    res.send("Hello world!")
}).listen(port);

*/

const server = require("express")();
const port = 3000

server.get("/page", (req, res, next) => {
    res.end("Here is a page")
    next()
})

server.get("/", (req, res, next) => {
    res.end("Root Page")
    next()
})

server.get("*", (req, res) => {
    res.status(404)
    res.end("page not found")
})

server.listen(port, () => {
    console.log(`Server started at http://localhost:${port}`)
})

function scriptStart() {
    const BookStatus = Object.freeze({
        IN_STOCK: "В наличии",
        UNAVAILABLE: "Занята",
        OVERDUE: "Просрочена",
        UNKNOWN: "Неизвестно"
    })
    const books = [
        {title: "Книга 1", author: "Автор 1", bookStatus: BookStatus.IN_STOCK},
        {title: "Книга 2", author: "Автор 2", bookStatus: BookStatus.UNAVAILABLE},
        {title: "Книга 3", author: "Автор 3", bookStatus: BookStatus.OVERDUE},
        {title: "Книга 4", author: "Автор 4", bookStatus: BookStatus.IN_STOCK},
    ]
    let listOfBooks = document.getElementById("list_of_books")

    for (let i = 0; i < books.length; i++) {
        let newBook = TableRowBook.createBookRow(books[i].title, books[i].author, books[i].bookStatus, function () { })
        listOfBooks.appendChild(newBook)
    }
}
