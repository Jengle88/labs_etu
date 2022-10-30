import {
    toAddNewBookPage, toBookInfoPage,
    toIndexPage,
} from "./client.js";

// set id
const buttonAddNewBook = document.getElementById("start_add_new_book")
const mainTitle = document.getElementById("main_title")
const listOfBooksElem = document.getElementsByClassName("book-in-list-of-books")
const listOfBooks = Array.prototype.slice.call(listOfBooksElem)


// set listeners
buttonAddNewBook.addEventListener("click", toAddNewBookPage)
mainTitle.addEventListener("click", toIndexPage)
listOfBooks.forEach(htmlBookCard => {
    htmlBookCard.addEventListener("click", () => {
        const id = htmlBookCard.id.split("book_in_list_of_books#")[1]
        toBookInfoPage(id)
    })
})

