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


function createBookTitleAndAuthorDiv(title, author) {
    let bookTitleAndAuthor = document.createElement("div")
    bookTitleAndAuthor.className = "book-title-and-author"
    let bookTitle = document.createElement("p")
    bookTitle.className = "book-title"
    bookTitle.innerText = title
    let bookAuthor = document.createElement("p")
    bookAuthor.className = "book-author"
    bookAuthor.innerText = author
    bookTitleAndAuthor.append(bookTitle, bookAuthor)
    return bookTitleAndAuthor;
}

function createBookStatusAndActionsDiv(status) {
    let bookStatusAndActions = document.createElement("div")
    bookStatusAndActions.className = "book-status-and-actions"
    let bookStatus = document.createElement("p")
    bookStatus.className = "book-status"
    bookStatus.innerText = status
    let bookActionsDiv = document.createElement("div")
    bookActionsDiv.className = "book-actions"
    let addBookActionImg = document.createElement("img")
    addBookActionImg.src = "ic_add_book.png"
    addBookActionImg.className = "book-action-icon"
    addBookActionImg.onclick = function () {

    }
    let removeBookActionImg = document.createElement("img")
    removeBookActionImg.src = "ic_remove_book.png"
    removeBookActionImg.className = "book-action-icon"
    removeBookActionImg.onclick = function () {

    }
    bookActionsDiv.append(addBookActionImg, removeBookActionImg)
    bookStatusAndActions.append(bookStatus, bookActionsDiv)
    return bookStatusAndActions
}

function createBook(title, author, status) {
    let newBook = document.createElement("div")
    newBook.className = "book-in-list-of-books"
    let bookTitleAndAuthor = createBookTitleAndAuthorDiv(title, author);
    let bookStatusAndActions = createBookStatusAndActionsDiv(status)
    newBook.append(bookTitleAndAuthor, bookStatusAndActions)
    return newBook
}

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
        let newBook = createBook(books[i].title, books[i].author, books[i].bookStatus)
        listOfBooks.appendChild(newBook)
    }
}
